#include <stdlib.h> /* alloc family */
#include <assert.h> /* assert		*/

#include "dhcp.h"
#include "utils.h"  /* PRNT_ERR 	*/

static const size_t MAX_PREFIX = 32;

typedef struct trie_node_s trie_node_t;

struct trie_node_s
{
	trie_node_t *children[2];
	int is_allocd;
} ;

struct dhcp_s
{
	trie_node_t *root;
	ip_t network_address;
	size_t levels;
} ;

/******************************* Trie Functions *******************************/

static void TrieDestroy(trie_node_t *trie_node)
{
	if (NULL == trie_node)
	{
		return;
	}

	TrieDestroy(trie_node->children[0]); trie_node->children[0] = NULL;
	TrieDestroy(trie_node->children[1]); trie_node->children[1] = NULL;

	free(trie_node); trie_node = NULL;
}

static trie_node_t *TrieCreateNode()
{
	trie_node_t *trie_node = (trie_node_t *)malloc(sizeof(trie_node_t));

	if (NULL == trie_node)
	{
		PRNT_ERR("Memory allocation error");
		return (NULL);
	}

	trie_node->children[0] = NULL;
	trie_node->children[1] = NULL;
	trie_node->is_allocd = 0;

	return (trie_node);
}

/****************************** Helper Functions ******************************/

static void UpdateIsAllocd(trie_node_t *cur_node, int req_path)
{
	/* both children's paths are fully allocd */
	if ((NULL != cur_node->children[!req_path]) &&
		cur_node->children[req_path]->is_allocd &&
		cur_node->children[!req_path]->is_allocd)
	{
		cur_node->is_allocd = 1;
	}
}

static void UpdateIP(ip_t *target_ip, size_t index)
{
	*target_ip = *target_ip ^ (1 << index);
}

static dhcp_status_t AllocIP(trie_node_t *root, ip_t *target_ip, size_t level)
{
	trie_node_t *cur_node = root;
	int mask = 1;
	size_t index = level - 1;
	int req_path = 0;

	assert(NULL != root);
	assert(NULL != target_ip);

	req_path = mask & (*target_ip >> index);

	if (0 == level)
	{
		/* last node can't have any more children, by default is alloc'd */
		cur_node->is_allocd = 1;
		return (DHCP_SUCCESS);
	}

	--level;

	/* req_path is open */
	if (NULL == cur_node->children[req_path])
	{
		/* create node and continue */
		if (NULL == (cur_node->children[req_path] = TrieCreateNode()) ||
			DHCP_MEM_ERR == AllocIP(cur_node->children[req_path], target_ip, level))
		{
			TrieDestroy(cur_node->children[req_path]);
			return (DHCP_MEM_ERR);
		}

	} /* available ip(s) in that path */
	else if (0 == cur_node->children[req_path]->is_allocd)
	{
		/* continue the path */
		if (DHCP_MEM_ERR == AllocIP(cur_node->children[req_path], target_ip, level))
		{
			return (DHCP_MEM_ERR);
		}

	} /* no child in opposite path */
	else
	{
		/* went to the other path, need to update ip */
		UpdateIP(target_ip, index);

		/* create node and continue */
		if (DHCP_MEM_ERR == AllocIP(cur_node, target_ip, ++level))
		{
			return (DHCP_MEM_ERR);
		}
	}

	UpdateIsAllocd(cur_node, req_path);

	return (DHCP_SUCCESS);
}

/******************************* DHCP Functions *******************************/

dhcp_t *DHCPCreate(ip_t network_address, size_t subnet_prefix)
{
	dhcp_t *dhcp = (dhcp_t *)malloc(sizeof(dhcp_t));
	size_t levels = MAX_PREFIX - subnet_prefix;
	ip_t host_mask = (1 << levels) - 1;				 /* all host bits are set */
	ip_t subnet_mask = network_address & ~host_mask;
	ip_t network_ip = subnet_mask | 0;
	ip_t broadcast_ip = subnet_mask | host_mask;
	ip_t dhcp_ip = broadcast_ip ^ 1;

	if (NULL == dhcp)
	{
		PRNT_ERR("Memory allocation error");
		return (NULL);
	}

	dhcp->network_address = network_address;
	dhcp->levels = levels;

	/* create root and initialize network_ip, broadcast ip, dhcp ip */
	if (NULL == (dhcp->root = TrieCreateNode()) ||
		DHCP_SUCCESS != DHCPAllocIP(dhcp, network_ip, &network_ip) ||
		DHCP_SUCCESS != DHCPAllocIP(dhcp, dhcp_ip, &dhcp_ip) ||
		DHCP_SUCCESS != DHCPAllocIP(dhcp, broadcast_ip, &broadcast_ip))
	{
		PRNT_ERR("Initialization error");
		DHCPDestroy(dhcp); dhcp = NULL;
		return (NULL);
	}

	return (dhcp);
}

/********************************* DHCPDestroy ********************************/

void DHCPDestroy(dhcp_t *dhcp)
{
	assert(NULL != dhcp);

	TrieDestroy(dhcp->root); dhcp->root = NULL;

	free(dhcp); dhcp = NULL;
}

/********************************** DHCPAlloc *********************************/

dhcp_status_t DHCPAllocIP(dhcp_t *dhcp, ip_t requested_ip, ip_t *leased_ip)
{
	trie_node_t *root = NULL;
	size_t levels = 0;

	assert(NULL != dhcp);

	root = dhcp->root;
	levels = dhcp->levels;

	/* all ip's are allocated */
	if (root->is_allocd)
	{
		return (NO_FREE_LEASES);
	}

	/* make sure IP given will always be in the network, not in another */
	*leased_ip = dhcp->network_address | (((1 << levels) - 1) & requested_ip);

	return (AllocIP(root, leased_ip, levels));
}

/********************************* DHCPFreeIP *********************************/

static int FindAndFreeIP(trie_node_t **cur_node, ip_t ip, size_t level)
{
	int mask = 1;
	size_t index = level - 1;
	int req_path = mask & (ip >> index);

	assert(NULL != *cur_node);

	if (0 == level)								   /* IP was found, free node */
	{
		(*cur_node)->is_allocd = 0;
		free(*cur_node); *cur_node = NULL;
		cur_node = NULL;
		return (0);
	}

	/* IP was not found */
	if (NULL == (*cur_node)->children[req_path] ||
		0 != FindAndFreeIP(&(*cur_node)->children[req_path], ip, --level))
	{
		PRNT_ERR("Invalid IP");
		return (1);
	}

	/* both children don't exist */
	if (NULL == (*cur_node)->children[req_path] &&
		NULL == (*cur_node)->children[!req_path])
	{
		free(*cur_node); *cur_node = NULL;
		cur_node = NULL;
	}
	else										 /* at least one child exists */
	{
		(*cur_node)->is_allocd = 0;
	}

	return (0);
}

void DHCPFreeIP(dhcp_t *dhcp, ip_t ip)
{
	assert(NULL != dhcp);

	FindAndFreeIP(&dhcp->root, ip, dhcp->levels);
}

/******************************* DHCPCountFreeIP ******************************/

static size_t CountFree(trie_node_t *cur_node, size_t level)
{
	if (NULL == cur_node)
	{
		return (1 << level);
	}

	/* total allocated ip's in current path */
	if (cur_node->is_allocd)
	{
		return (0);
	}

	/* next level */
	--level;

	return (CountFree(cur_node->children[0], level) +
			CountFree(cur_node->children[1], level));
}

size_t DHCPCountFreeIP(const dhcp_t *dhcp)
{
	assert(NULL != dhcp);

	return (CountFree(dhcp->root, dhcp->levels));
}
