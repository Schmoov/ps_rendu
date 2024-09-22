#include "../push_swap.h"

bool	is_sorted(t_node *nodes, int size)
{
	int	i;

	i = 0;
	while (i < size - 1)
	{
		if (nodes[i].val > nodes[i + 1].val)
			return (false);
		i++;
	}
	return (true);
}

bool	is_solution(t_node *nodes, int input_len, t_op *moves, int moves_len)
{
	t_stk	stk_a;
	t_stk	stk_b;
	bool	res;

	stks_init(nodes, input_len, &stk_a, &stk_b);
	stks_execute(moves, moves_len, &stk_a, &stk_b);
	res = stks_is_solved(&stk_a, &stk_b);
	stks_destroy(&stk_a, &stk_b);
	return (res);
}

bool	is_valid(t_op *sol, int curr)
{
	if (sol[curr] == OP_RB || sol[curr] == OP_RRB || sol[curr] == OP_RRR
		|| sol[curr] == OP_RR || sol[curr] == OP_SB)
		return (false);
	if (sol[curr] == OP_RA)
		return (!curr || sol[curr - 1] != OP_RRA);
	if (sol[curr] == OP_RRA)
		return (!curr || sol[curr - 1] != OP_RA);
	if (sol[curr] == OP_SA)
		return (!curr || sol[curr - 1] != OP_SA);
	if (sol[curr] == OP_PA)
		return (!curr || sol[curr - 1] != OP_PB);
	if (sol[curr] == OP_PB)
		return (!curr || sol[curr - 1] != OP_PA);
	if (sol[curr] == OP_SS)
		return (curr && sol[curr - 1] != OP_SS);
	return (420);
}

bool	solve_iddfs_rec(t_node *nodes, int size, t_op *sol, int step)
{
	t_op	op;

	if (sol[step] == (t_op)-1)
		return (is_solution(nodes, size, sol, step));
	op = 0;
	while (op < NB_OP)
	{
		sol[step] = op;
		if (is_valid(sol, step))
			if (solve_iddfs_rec(nodes, size, sol, step + 1))
				return (true);
		op++;
	}
	return (false);
}

void	solve_backtrack(t_node *nodes, int size, t_sol *sol)
{
	int		depth;
	t_op	arr_sol[32];

	if (is_sorted(nodes, size))
		return ;
	depth = 1;
	ft_memset(arr_sol, 0, 32 * sizeof(t_op));
	arr_sol[depth] = -1;
	while (!solve_iddfs_rec(nodes, size, arr_sol, 0))
	{
		depth++;
		ft_memset(arr_sol, 0, 32 * sizeof(t_op));
		arr_sol[depth] = -1;
	}
	sol_append_arr(sol, arr_sol, depth);
}
