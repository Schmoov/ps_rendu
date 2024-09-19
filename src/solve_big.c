#include "../push_swap.h"

void	solve_big_divide(t_stk *a, t_stk *b, t_sol *sol)
{
	int	i;
	int lo = a->len / 6;
	int hi = a->len / 3;
	static bool first_pass = true;
	int	rb_debt = 0;

	while (a->len > 2)
	{
		i = 0;
		int len = a->len;
		if (!first_pass)
		{
			lo = a->len / 4 + b->len;
			hi = a->len / 2 + b->len;
		}
		first_pass = false;
		while (i < len)
		{
			if (a->head->val < lo)
			{
				while (rb_debt)
				{
					ps_op_rb(a,b);
					sol_append_one(sol, OP_RB);
					rb_debt--;
				}
				ps_op_pb(a,b);
				sol_append_one(sol, OP_PB);
			}
			else if (a->head->val < hi)
			{
				ps_op_pb(a,b);
				sol_append_one(sol, OP_PB);
				rb_debt++;
			}
			else
			{
				if (rb_debt)
				{
					ps_op_rr(a,b);
					sol_append_one(sol, OP_RR);
					rb_debt--;
				}
				else
				{
					ps_op_ra(a,b);
					sol_append_one(sol, OP_RA);
				}
			}
			i++;
		}
	}
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

int		insert_find_a_pos(int pos, t_stk *a, t_stk *b)
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
	if (pos_a > a->len - pos_a)
		pos_a = pos_a - a->len;
	return (pos_a);
}

int		insert_cost(int pos, t_stk *a, t_stk *b)
{
	int res;
	int pos_a;

	if (insert_bucket_filter(pos, a, b))
		return (INT_MAX);
	pos_a = insert_find_a_pos(pos, a, b);
	if (pos > b->len - pos)
		pos = pos - b->len;
	if (pos >= 0 && pos_a >= 0)
		return fmax(pos, pos_a);
	if (pos <= 0 && pos_a <= 0)
		return fmax(-pos, -pos_a);
	if (pos > 0 && pos_a < 0)
		return fmin(pos - pos_a, fmin(fmax(pos, a->len + pos_a), fmax(b->len-pos, -pos_a)));
	return fmin(pos_a - pos, fmin(fmax(pos_a, b->len + pos), fmax(a->len - pos_a, -pos)));
}

void	fast_insert(int pos, t_stk *a, t_stk *b, t_sol *sol)
{
	int c_rb = 0;
	int c_ra = 0;
	for (int i = 0; i < pos; i++)
	{
		ps_op_rb(a,b);
		c_rb++;
	}

	int val = b->head->val;
	int posA = -1;
	int posMin;
	for (int i = 0; i < a->len; i++)
	{
		if (posA == -1 && a->head->val > val && a->head->prev->val < val)
			posA = i;
		if (a->head->val < a->head->prev->val)
			posMin = i;
		ps_op_ra(a,b);
	}
	if (posA == -1) posA = posMin;
	for (int i = 0; i < posA; i++)
	{
		ps_op_ra(a,b);
		c_ra++;
	}
	if (c_rb > b->len - c_rb) c_rb = c_rb - b->len;
	if (c_ra > a->len - c_ra) c_ra = c_ra - a->len;
	if (c_ra > 0 && c_rb < 0 && fmax(c_ra, b->len + c_rb) < c_ra - c_rb) c_rb = b->len + c_rb;
	else if (c_rb > 0 && c_ra < 0 && fmax(c_ra, b->len + c_rb) < c_ra - c_rb) c_ra = a->len + c_ra;
	if (c_rb > 0 && c_ra > 0)
	{
		while(c_rb && c_ra)
		{
			sol_append_one(sol, OP_RR);
			c_rb--;
			c_ra--;
		}
	}
	if (c_rb < 0 && c_ra < 0) 
	{
		while(c_rb && c_ra)
		{
			sol_append_one(sol, OP_RRR);
			c_rb++;
			c_ra++;
		}
	}
	while(c_rb>0)
	{
		sol_append_one(sol, OP_RB);
		c_rb--;
	}
	while(c_rb<0)
	{
		sol_append_one(sol, OP_RRB);
		c_rb++;
	}
	while(c_ra>0)
	{
		sol_append_one(sol, OP_RA);
		c_ra--;
	}
	while(c_ra<0)
	{
		sol_append_one(sol, OP_RRA);
		c_ra++;
	}
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
