#include "push_swap.h"

t_node	*node_create(int val)
{
	t_node	*res;

	res = malloc(sizeof(t_node));
	res->val = val;
	res->next = res;
	res->prev = res;
	return (res);
}

void	stk_push_node(t_stk *stk, t_node *node)
{
	if (stk->len)
	{
		stk->head->prev->next = node;
		node->prev = stk->head->prev;
		stk->head->prev = node;
		node->next = stk->head;
	}
	stk->head = node;
	(stk->len)++;
}

t_node	*stk_pop_node(t_stk *stk)
{
	t_node	*res;

	res = stk->head;
	if (stk->len > 1)
	{
		res->next->prev = res->prev;
		res->prev->next = res->next;
		stk->head = res->next;
		res->next = res;
		res->prev = res;
	}
	else
		stk->head = NULL;
	(stk->len)--;
	return (res);
}

void	stk_free_nodes(t_stk *stk)
{
	while (stk->len)
	{
		free(stk_pop_node(stk));
	}
}
