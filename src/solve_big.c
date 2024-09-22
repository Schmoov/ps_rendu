/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solve_big.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: parden <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 20:57:07 by parden            #+#    #+#             */
/*   Updated: 2024/09/22 20:57:39 by parden           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../push_swap.h"

static bool	insert_bucket_filter(t_stk *a, t_stk *b)
{
	int	val;
	int	size;

	val = b->head->val;
	size = a->len + b->len;
	return ((b->len > size / 3 && val < size / 3)
		|| (b->len > size / 6 && val < size / 6)
		|| (b->len > 2 * size / 3 && val < 2 * size / 3)
		|| (b->len > 1 * size / 2 && val < 1 * size / 2)
		|| (b->len > 5 * size / 6 && val < 5 * size / 6)
		|| (b->len > 3 * size / 4 && val < 3 * size / 4));
}

int	insert_cost(int pos, t_stk *a, t_stk *b)
{
	int	pos_a;

	if (insert_bucket_filter(a, b))
		return (INT_MAX);
	pos_a = insert_find_pos_a(a, b);
	return (insert_optimize_rots(&pos, &pos_a, a, b));
}

void	solve_big_merge(t_stk *a, t_stk *b, t_sol *sol)
{
	int	i;
	int	pos;
	int	cost;
	int	best;

	while (b->len)
	{
		i = 0;
		best = INT_MAX;
		while (i < b->len)
		{
			cost = insert_cost(i, a, b);
			if (b->head->val >= b->len - 1)
				cost -= 5 * (b->head->val - b->len + 1) / 8;
			if (cost < best)
			{
				pos = i;
				best = cost;
			}
			ps_op_rb(a, b);
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
			ps_op_rra(a, b);
			sol_append_one(sol, OP_RRA);
		}
		else
		{
			ps_op_ra(a, b);
			sol_append_one(sol, OP_RA);
		}
	}
}

void	solve_big(t_node *parsed, int size, t_sol *sol)
{
	t_stk	a;
	t_stk	b;

	stks_init(parsed, size, &a, &b);
	solve_big_divide(&a, &b, sol);
	while (a.len < 2)
	{
		ps_op_pa(&a, &b);
		sol_append_one(sol, OP_PA);
	}
	solve_big_merge(&a, &b, sol);
	solve_big_last_rot(&a, &b, sol);
}
