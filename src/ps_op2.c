#include "../push_swap.h"

void	ps_op_ra(t_stk *a, t_stk *b)
{
	(void) *b;
	if (a->len > 1)
		a->head = a->head->next;
}

void	ps_op_rb(t_stk *a, t_stk *b)
{
	(void) *a;
	if (b->len > 1)
		b->head = b->head->next;
}

void	ps_op_rr(t_stk *a, t_stk *b)
{
	ps_op_ra(a, b);
	ps_op_rb(a, b);
}

void	ps_op_rra(t_stk *a, t_stk *b)
{
	(void) *b;
	if (a->len > 1)
		a->head = a->head->prev;
}

void	ps_op_rrb(t_stk *a, t_stk *b)
{
	(void) *a;
	if (b->len > 1)
		b->head = b->head->prev;
}
