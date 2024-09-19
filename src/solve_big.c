#include "../push_swap.h"

void	solve_big_divide_lo(t_stk *a, t_stk *b, t_sol *sol, int *rb_debt)
{
	while (*rb_debt)
	{
		ps_op_rb(a,b);
		sol_append_one(sol, OP_RB);
		(*rb_debt)--;
	}
	ps_op_pb(a,b);
	sol_append_one(sol, OP_PB);
}

void	solve_big_divide_mid(t_stk *a, t_stk *b, t_sol *sol, int *rb_debt)
{
	ps_op_pb(a,b);
	sol_append_one(sol, OP_PB);
	(*rb_debt)++;
}

void	solve_big_divide_hi(t_stk *a, t_stk *b, t_sol *sol, int *rb_debt)
{
	if (*rb_debt)
	{
		ps_op_rr(a,b);
		sol_append_one(sol, OP_RR);
		(*rb_debt)--;
	}
	else
	{
		ps_op_ra(a,b);
		sol_append_one(sol, OP_RA);
	}
}

void	solve_big_divide_pass(t_stk *a, t_stk *b, t_sol *sol, int *rb_debt)
{
	int	i;
	int	len;
	int lo;
	int mid;

	i = 0;
	len = a->len;
	mid = len / 3;
	if (b->len)
		mid = len / 2 + b->len;
	lo = len / 6;
	if (b->len)
		lo = len / 4 + b->len;
	while (i < len)
	{
		if (a->head->val < lo)
			solve_big_divide_lo(a, b, sol, rb_debt);
		else if (a->head->val < mid)
			solve_big_divide_mid(a, b, sol, rb_debt);
		else
			solve_big_divide_hi(a, b, sol, rb_debt);
		i++;
	}
}

void	solve_big_divide(t_stk *a, t_stk *b, t_sol *sol)
{
	int	rb_debt;

	rb_debt = 0;
	while (a->len > 2)
		solve_big_divide_pass(a, b, sol, &rb_debt);
}

#include <math.h>
bool	insert_bucket_filter(int pos, t_stk *a, t_stk *b)
{
	int val;
	int size;

	val = b->head->val;
	size = a->len + b->len;
	return (
	(b->len > size/3 && val < size/3) || (b->len > size/6 && val < size/6)
	|| (b->len > 2*size/3 && val < 2*size/3) || (b->len > 1*size/2 && val < 1*size/2) 
	|| (b->len > 5*size/6 && val < 5*size/6) || (b->len > 3*size/4 && val < 3*size/4) 
	);
}

int		insert_find_pos_a(int pos, t_stk *a, t_stk *b)
{
	int	pos_a;
	int	pos_min;
	int i;
	int val;

	val = b->head->val;
	pos_a = -1;
	i = 0;
	while(i < a->len)
	{
		if (pos_a == -1 && a->head->val > val && a->head->prev->val < val)
			pos_a = i;
		if (a->head->val < a->head->prev->val)
			pos_min = i;
		ps_op_ra(a,b);
		i++;
	}
	if (pos_a == -1)
		pos_a = pos_min;
	return (pos_a);
}

int	insert_optimize_rots(int *pos, int *pos_a, t_stk *a, t_stk *b)
{
	int no_rev;
	int rev_b;
	int rev_a;
	int rev_both;

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

int		insert_cost(int pos, t_stk *a, t_stk *b)
{
	int pos_a;

	if (insert_bucket_filter(pos, a, b))
		return (INT_MAX);
	pos_a = insert_find_pos_a(pos, a, b);
	return (insert_optimize_rots(&pos, &pos_a, a, b));
}

void	insert_double_rot(int *pos, int *pos_a, t_sol *sol)
{
	while(*pos > 0 && *pos_a > 0)
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

void	insert_simple_rot(int pos, int pos_a, t_sol *sol)
{
	while(pos>0)
	{
		sol_append_one(sol, OP_RB);
		pos--;
	}
	while(pos<0)
	{
		sol_append_one(sol, OP_RRB);
		pos++;
	}
	while(pos_a>0)
	{
		sol_append_one(sol, OP_RA);
		pos_a--;
	}
	while(pos_a<0)
	{
		sol_append_one(sol, OP_RRA);
		pos_a++;
	}
}

void	fast_insert(int pos, t_stk *a, t_stk *b, t_sol *sol)
{
	int	i;
	int pos_a;

	i = 0;
	while (i < pos)
	{
		ps_op_rb(a,b);
		i++;
	}
	pos_a = insert_find_pos_a(pos, a, b);
	i = 0;
	while (i < pos_a)
	{
		ps_op_ra(a,b);
		i++;
	}
	insert_optimize_rots(&pos, &pos_a, a, b);
	insert_double_rot(&pos, &pos_a, sol);
	insert_simple_rot(pos, pos_a, sol);
	ps_op_pa(a,b);
	sol_append_one(sol, OP_PA);
}

void	solve_big_merge(t_stk *a, t_stk *b, t_sol *sol)
{
	int	i;
	int	pos;
	int cost;
	int best;

	while (a->len < 2)
	{
		ps_op_pa(a,b);
		sol_append_one(sol, OP_PA);
	}
	while (b->len)
	{
		i = 0;
		best = INT_MAX;
		while(i < b->len)
		{
			cost = insert_cost(i, a, b);
			if (b->head->val >= b->len - 1) 
				cost -= 5*(b->head->val - b->len + 1)/8;
			if (cost < best)
			{
				pos = i;
				best = cost;
			}
			ps_op_rb(a,b);
			i++;
		}
		fast_insert(pos, a, b, sol);
	}
}

void	solve_big_last_rot(t_stk *a, t_stk *b, t_sol *sol)
{
	while (a->head->val)
	{
		if (a->head->val < a->len / 2)
		{
			ps_op_rra(a,b);
			sol_append_one(sol, OP_RRA);
		}
		else
		{
			ps_op_ra(a,b);
			sol_append_one(sol, OP_RA);
		}
	}
}

t_sol	solve_big(t_node *parsed, int size)
{
	t_stk	stk_a;
	t_stk	stk_b;
	t_sol	sol;

	sol_init(&sol);
	stks_init(parsed, size, &stk_a, &stk_b);
	solve_big_divide(&stk_a, &stk_b, &sol);
	solve_big_merge(&stk_a, &stk_b, &sol);
	solve_big_last_rot(&stk_a, &stk_b, &sol);
	return (sol);
}
