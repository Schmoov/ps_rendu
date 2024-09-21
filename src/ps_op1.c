#include "../push_swap.h"

void	ps_op_pa(t_stk *a, t_stk *b)
{
	if (b->len)
		stk_push_node(a, stk_pop_node(b));
}

void	ps_op_pb(t_stk *a, t_stk *b)
{
	if (a->len)
		stk_push_node(b, stk_pop_node(a));
}

void	ps_op_sa(t_stk *a, t_stk *b)
{
	t_node	*tmp;

	(void) *b;
	if (a->len > 1)
	{
		tmp = stk_pop_node(a);
		a->head = a->head->next;
		stk_push_node(a, tmp);
		a->head = a->head->prev;
	}
}

void	ps_op_sb(t_stk *a, t_stk *b)
{
	t_node	*tmp;

	(void) *a;
	if (b->len > 1)
	{
		tmp = stk_pop_node(b);
		b->head = b->head->next;
		stk_push_node(b, tmp);
		b->head = b->head->prev;
	}
}

void	ps_op_ss(t_stk *a, t_stk *b)
{
	ps_op_sa(a, b);
	ps_op_sb(a, b);
}
