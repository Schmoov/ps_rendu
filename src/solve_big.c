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
int		insert_cost(int pos, t_stk *a, t_stk *b)
{
	int res;
	int posA = -1;
	int posMin;
	int val = b->head->val;
	int size = a->len + b->len;
	if (b->len > size/3 && val < size/3) return (INT_MAX);
	if (b->len > size/6 && val < size/6) return (INT_MAX);
	if (b->len > 2*size/3 && val < 2*size/3) return (INT_MAX);
	if (b->len > 1*size/2 && val < 1*size/2) return (INT_MAX);
	if (b->len > 5*size/6 && val < 5*size/6) return (INT_MAX);
	if (b->len > 3*size/4 && val < 3*size/4) return (INT_MAX);

	for (int i = 0; i < a->len; i++)
	{
		if (posA == -1 && a->head->val > val && a->head->prev->val < val)
			posA = i;
		if (a->head->val < a->head->prev->val)
			posMin = i;
		ps_op_ra(a,b);
	}
	if (posA == -1) posA = posMin;
	if (pos > b->len - pos) pos = pos - b->len;
	if (posA > a->len - posA) posA = posA - a->len;

	if (pos >= 0 && posA >= 0) return fmax(pos,posA);
	if (pos <= 0 && posA <= 0) return fmax(-pos,-posA);
	if (pos > 0 && posA < 0) return fmin(pos-posA, fmin(fmax(pos, a->len + posA), fmax(b->len-pos, -posA)));
	return fmin(posA-pos, fmin(fmax(posA, b->len + pos), fmax(a->len-posA, -pos)));
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
	while (a->len < 2)
	{
		ps_op_pa(a,b);
		sol_append_one(sol, OP_PA);
	}
	while (b->len)
	{
		int	pos;
		int best = INT_MAX;
		int best_val = b->head->val;
		for (int i = 0; i < b->len; i++)
		{
			int cost = insert_cost(i, a, b);
			if (b->head->val >= b->len - 1) cost -= 5*(b->head->val - b->len + 1)/8;
			if (cost < best || (cost==best && b->head->val > best_val))
			{
				pos = i;
				best = cost;
				best_val = b->head->val;
			}
			ps_op_rb(a,b);
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
