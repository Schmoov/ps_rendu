#include "../push_swap.h"

int	insert_find_pos_a(t_stk *a, t_stk *b)
{
	int	pos_a;
	int	pos_min;
	int	i;
	int	val;

	val = b->head->val;
	pos_a = -1;
	i = 0;
	while (i < a->len)
	{
		if (pos_a == -1 && a->head->val > val && a->head->prev->val < val)
			pos_a = i;
		if (a->head->val < a->head->prev->val)
			pos_min = i;
		ps_op_ra(a, b);
		i++;
	}
	if (pos_a == -1)
		pos_a = pos_min;
	return (pos_a);
}

#include <math.h>
int	insert_optimize_rots(int *pos, int *pos_a, t_stk *a, t_stk *b)
{
	int	no_rev;
	int	rev_b;
	int	rev_a;
	int	rev_both;

	no_rev = fmax(*pos, *pos_a);
	rev_b = *pos_a + b->len - *pos;
	rev_a = *pos + a->len - *pos_a;
	rev_both = fmax(b->len - *pos, a->len - *pos_a);
	if (no_rev <= rev_b && no_rev <= rev_a && no_rev <= rev_both)
		return (no_rev);
	if (rev_b <= rev_a && rev_b <= rev_both)
	{
		*pos -= b->len;
		return (rev_b);
	}
	*pos_a -= a->len;
	if (rev_both <= rev_a)
	{
		*pos -= b->len;
		return (rev_both);
	}
	return (rev_a);
}

static void	insert_double_rot(int *pos, int *pos_a, t_sol *sol)
{
	while (*pos > 0 && *pos_a > 0)
	{
		sol_append_one(sol, OP_RR);
		(*pos)--;
		(*pos_a)--;
	}
	while (*pos < 0 && *pos_a < 0)
	{
		sol_append_one(sol, OP_RRR);
		(*pos)++;
		(*pos_a)++;
	}
}

static void	insert_simple_rot(int pos, int pos_a, t_sol *sol)
{
	while (pos > 0)
	{
		sol_append_one(sol, OP_RB);
		pos--;
	}
	while (pos < 0)
	{
		sol_append_one(sol, OP_RRB);
		pos++;
	}
	while (pos_a > 0)
	{
		sol_append_one(sol, OP_RA);
		pos_a--;
	}
	while (pos_a < 0)
	{
		sol_append_one(sol, OP_RRA);
		pos_a++;
	}
}

void	fast_insert(int pos, t_stk *a, t_stk *b, t_sol *sol)
{
	int	i;
	int	pos_a;

	i = 0;
	while (i < pos)
	{
		ps_op_rb(a, b);
		i++;
	}
	pos_a = insert_find_pos_a(a, b);
	i = 0;
	while (i < pos_a)
	{
		ps_op_ra(a, b);
		i++;
	}
	insert_optimize_rots(&pos, &pos_a, a, b);
	insert_double_rot(&pos, &pos_a, sol);
	insert_simple_rot(pos, pos_a, sol);
	ps_op_pa(a, b);
	sol_append_one(sol, OP_PA);
}
