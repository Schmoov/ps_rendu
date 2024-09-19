#include "push_swap.h"

bool	is_sorted(t_node *nodes, int size)
{
	for (int i = 0; i < size - 1; i++)
		if (nodes[i].val > nodes[i+1].val)
			return false;
	return true;
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
