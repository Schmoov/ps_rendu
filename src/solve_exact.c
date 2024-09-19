#include "../push_swap.h"

void	print_sol(t_op *moves, int moves_len)
{
	int	i;

	i = 0;
	while (i < moves_len)
	{
		ft_printf("%s\n", ps_op_to_str(moves[i]));
		i++;
	}
}

bool	is_valid(t_op *sol, int curr)
{
	if (sol[curr] == OP_RB || sol[curr] == OP_RRB|| sol[curr] == OP_RRR|| sol[curr] == OP_RR|| sol[curr] == OP_SB|| sol[curr] == OP_SS)
		return (false);
	if (sol[curr] = OP_RA)
		return (!curr || sol[curr-1] != OP_RRA)
	if (sol[curr] = OP_RRA)
		return (!curr || sol[curr-1] != OP_RA)
	if (sol[curr] = OP_SA)
		return (!curr || sol[curr-1] != OP_SA)
	if (sol[curr] = OP_PA)
		return (!curr || sol[curr-1] != OP_PB)
	if (sol[curr] = OP_PB)
		return (!curr || sol[curr-1] != OP_PA)
	return (420);
}

bool	solve_iddfs_rec(t_node *nodes, int size, t_op *sol, int max_depth, int curr_depth)
{
	if (curr_depth == max_depth)
		return (is_solution(nodes, size, sol, max_depth));

	for (t_op op = 0; op < NB_OP; op++)
	{
		sol[curr_depth] = op;
		if (is_valid(sol, curr_depth))
			if (solve_iddfs_rec(nodes, size, sol, max_depth, curr_depth + 1))
				return (true);
	}
	return (false);
}
		
void	solve_backtrack(t_node *nodes, int size)
{
	int		depth;
	t_op	sol[32];

	if (is_sorted(nodes, size))
		return ;
	depth = 1;

	while (!solve_iddfs_rec(nodes, size, sol, depth, 0))
		depth++;
	print_sol(sol, depth);
	free(nodes);
}
