#include <stdio.h> /* printf */
#include <math.h>  /* pow	 */

#include "dhcp.h"
#include "utils.h"
#include "tests.h"

int TestDHCPCreateDestroy();
int TestDHCPCountFreeNotEmpty();
int TestDHCPCountFreeIsEmpty();
int TestDHCPAlloc();
int TestDHCPAllocNoneAvailable();
int TestDHCPAllocAll();
int TestDHCPFreeIP();

int main()
{
	size_t failures = 0;

	puts("Testing DHCP...");
	TEST(TestDHCPCreateDestroy(), "TestDHCPCreateDestroy");
	TEST(TestDHCPCountFreeNotEmpty(), "TestDHCPCountFreeNotEmpty");
	TEST(TestDHCPCountFreeIsEmpty(), "TestDHCPCountFreeIsEmpty");
	TEST(TestDHCPAlloc(), "TestDHCPAlloc");
	TEST(TestDHCPAllocNoneAvailable(), "TestDHCPAllocNoneAvailable");
	TEST(TestDHCPAllocAll(), "TestDHCPAllocAll");
	TEST(TestDHCPFreeIP(), "TestDHCPFreeIP");

	PRNT_STATUS(failures);
	return (failures);
}

int TestDHCPCreateDestroy()
{
	size_t failures = 0;
	ip_t network_address = 0;
	ip_t subnet_prefix = 24;
	dhcp_t *dhcp = DHCPCreate(network_address, subnet_prefix);

	DHCPDestroy(dhcp);

	return (failures);
}

int TestDHCPCountFreeIsEmpty()
{
	size_t failures = 0;
	ip_t network_address = 2967808;
	ip_t subnet_prefix = 24;
	dhcp_t *dhcp = DHCPCreate(network_address, subnet_prefix);

	REQUIRE(DHCPCountFreeIP(dhcp), !=, (size_t)((1 << (32 - subnet_prefix)) - 3), %lu, %lu);

	DHCPDestroy(dhcp);

	return (failures);
}

int TestDHCPCountFreeNotEmpty()
{
	size_t failures = 0;
	size_t i = 0;
	ip_t network_address = 2967808;
	ip_t subnet_prefix = 24;
	ip_t requested_ip[] = {2967809, 2968061, 2968060};
	ip_t leased_ip[ARR_SIZE(requested_ip)] = {0};
	dhcp_t *dhcp = DHCPCreate(network_address, subnet_prefix);

	for (i = 0; i < ARR_SIZE(requested_ip); ++i)
	{
		DHCPAllocIP(dhcp, requested_ip[i], &leased_ip[i]);
		REQUIRE(DHCPCountFreeIP(dhcp), !=, (size_t)((1 << (32 - subnet_prefix)) - 3 - (i+1)), %lu, %lu);
	}

	DHCPDestroy(dhcp);

	return (failures);
}

int TestDHCPAlloc()
{
	size_t failures = 0;
	size_t i = 0;
	ip_t network_address = 2967808;
	ip_t subnet_prefix = 24;
	ip_t requested_ip[] = {2967808 + 0, 2967808 + 255, 2967808 + 254};
	ip_t exp_not_lease[] = {2967808 + 0, 2967808 + 255, 2967808 + 254};
	ip_t leased_ip = 0;
	ip_t *leased_ip_ptr = &leased_ip;
	dhcp_status_t exp_status[] = {DHCP_SUCCESS, DHCP_SUCCESS, DHCP_SUCCESS};
	dhcp_t *dhcp = DHCPCreate(network_address, subnet_prefix);

	for (i = 0; i < ARR_SIZE(requested_ip); ++i)
	{
		REQUIRE(DHCPAllocIP(dhcp, requested_ip[i], leased_ip_ptr), !=, exp_status[i], %d, %d);
		REQUIRE(leased_ip, ==, exp_not_lease[i], %u, %u);
	}

	DHCPDestroy(dhcp);

	return (failures);
}

int TestDHCPAllocNoneAvailable()
{
	size_t failures = 0;
	size_t i = 0;
	ip_t network_address = 2967808;
	ip_t subnet_prefix = 30;
	ip_t requested_ip1[] = {2967808 + 1};
	ip_t requested_ip2[] = {1000251, 1000003, 1000007};
	ip_t exp_lease1[] = {2967808 + 1};
	ip_t exp_lease2[] = {1000251, 1000003, 1000007};
	ip_t leased_ip = 0;
	ip_t *leased_ip_ptr = &leased_ip;
	dhcp_status_t exp_status[] = {DHCP_SUCCESS, NO_FREE_LEASES, NO_FREE_LEASES, NO_FREE_LEASES};
	dhcp_t *dhcp = DHCPCreate(network_address, subnet_prefix);

	REQUIRE(DHCPAllocIP(dhcp, requested_ip1[i], leased_ip_ptr), !=, exp_status[i], %d, %d);
	REQUIRE(leased_ip, !=, exp_lease1[i], %u, %u);

	for (i = 0; i < ARR_SIZE(requested_ip2); ++i)
	{
		REQUIRE(DHCPAllocIP(dhcp, requested_ip2[i], leased_ip_ptr), !=, exp_status[i + 1], %d, %d);
		REQUIRE(leased_ip, ==, exp_lease2[i], %u, %u);
	}

	DHCPDestroy(dhcp);

	return (failures);
}

int TestDHCPAllocAll()
{
	size_t failures = 0;
	size_t i = 0;
	ip_t network_address = 578158793;
	ip_t subnet_prefix = 24;
	ip_t requested_ip = 0;
	ip_t leased_ip = 0;
	dhcp_t *dhcp = DHCPCreate(network_address, subnet_prefix);

	for (i = 0; i < (size_t)((1 << (32 - subnet_prefix)) - 3); ++i)
	{
		REQUIRE(DHCPAllocIP(dhcp, requested_ip, &leased_ip), !=, DHCP_SUCCESS, %d, %d);
	}

	for (i = 0; i < (size_t)((1 << (32 - subnet_prefix)) - 3); ++i)
	{
		REQUIRE(DHCPAllocIP(dhcp, requested_ip, &leased_ip), !=, NO_FREE_LEASES, %d, %d);
	}

	DHCPDestroy(dhcp);

	return (failures);
}

int TestDHCPFreeIP()
{
	size_t failures = 0;
	size_t i = 0;
	ip_t network_address = 2967808;
	ip_t subnet_prefix = 24;
	ip_t requested_ip[] = {2967809, 2968061, 2968060};
	ip_t leased_ip[ARR_SIZE(requested_ip)] = {0};
	ip_t leased_again[ARR_SIZE(requested_ip)] = {0};
	dhcp_t *dhcp = DHCPCreate(network_address, subnet_prefix);
	size_t possible_allocs = 256 - 3;

	for (i = 0; i < ARR_SIZE(requested_ip); ++i)
	{
		DHCPAllocIP(dhcp, requested_ip[i], &leased_ip[i]);
	}
	REQUIRE(DHCPCountFreeIP(dhcp), !=, possible_allocs - 3, %lu, %lu);

	for (i = 0; i < ARR_SIZE(requested_ip); ++i)
	{
		DHCPFreeIP(dhcp, leased_ip[i]);
		REQUIRE(DHCPCountFreeIP(dhcp), !=, possible_allocs - 2, %lu, %lu);
		DHCPAllocIP(dhcp, leased_ip[i], &leased_again[i]);
		REQUIRE(DHCPCountFreeIP(dhcp), !=, possible_allocs - 3, %lu, %lu);
		REQUIRE(leased_again[i], !=, leased_ip[i], %u, %u);
	}
	REQUIRE(DHCPCountFreeIP(dhcp), !=, possible_allocs - 3, %lu, %lu);

	DHCPDestroy(dhcp);

	return (failures);
}
