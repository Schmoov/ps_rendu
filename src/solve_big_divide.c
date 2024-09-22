/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solve_big_divide.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: parden <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 20:57:07 by parden            #+#    #+#             */
/*   Updated: 2024/09/22 20:57:39 by parden           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../push_swap.h"

static void	solve_big_divide_lo(t_stk *a, t_stk *b, t_sol *sol, int *rb_debt)
{
	while (*rb_debt)
	{
		ps_op_rb(a, b);
		sol_append_one(sol, OP_RB);
		(*rb_debt)--;
	}
	ps_op_pb(a, b);
	sol_append_one(sol, OP_PB);
}

static void	solve_big_divide_mid(t_stk *a, t_stk *b, t_sol *sol, int *rb_debt)
{
	ps_op_pb(a, b);
	sol_append_one(sol, OP_PB);
	(*rb_debt)++;
}

static void	solve_big_divide_hi(t_stk *a, t_stk *b, t_sol *sol, int *rb_debt)
{
	if (*rb_debt)
	{
		ps_op_rr(a, b);
		sol_append_one(sol, OP_RR);
		(*rb_debt)--;
	}
	else
	{
		ps_op_ra(a, b);
		sol_append_one(sol, OP_RA);
	}
}

static void	solve_big_divide_pass(t_stk *a, t_stk *b, t_sol *sol, int *rb_debt)
{
	int	i;
	int	len;
	int	lo;
	int	mid;

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
