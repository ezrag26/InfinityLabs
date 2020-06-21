#ifndef __OL73_DHCP_H__
#define __OL73_DHCP_H__

#include <stddef.h> /* size_t */

typedef struct dhcp_s dhcp_t;

typedef unsigned int ip_t;

typedef enum
{
    DHCP_SUCCESS,   /* An IP was successfully allocated 		   			  */
    NO_FREE_LEASES,	/* There are no available IP's to be allocated 			  */
    DHCP_MEM_ERR	/* Memory allocation error when attempting to allocate IP */
} dhcp_status_t;

/**
 * @brief Creates a dhcp
 *
 * @param network_address, the network upon which to allocate host ip's
 * @param subnet_prefix, total number of most significant bits that all hosts on
 * the subnetwork will share.
 * @return dhcp_t* ptr to dhcp, NULL if failed
 */
dhcp_t *DHCPCreate(ip_t network_address, size_t subnet_prefix);

/**
 * @brief destroys and frees memory of a dhcp
 *
 * @param dhcp
 */
void DHCPDestroy(dhcp_t *dhcp);

/**
 * @brief Allocates a host IP
 *
 * @param dhcp
 * @param requested_ip, IP requested by user, 0 if no ip preferred
 * @param leased_ip, pointer to where the allocated IP will be stored
 * @return dhcp_status_t, see above for description of the statuses
 */
dhcp_status_t DHCPAllocIP(dhcp_t *dhcp, ip_t requested_ip, ip_t *leased_ip);

/**
 * @brief Frees a previously allocated IP which can be allocated again later
 *
 * @param dhcp
 * @param ip, ip to be freed.
 * @return, no return value
 */
void DHCPFreeIP(dhcp_t *dhcp, ip_t ip);

/**
 * @brief Counts the total available IP's that can be allocated
 *
 * @param dhcp
 * @return size_t, number of available IP's
 */
size_t DHCPCountFreeIP(const dhcp_t *dhcp);

#endif /* __OL73_DHCP_H__ */
