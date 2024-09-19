#include "../push_swap.h"

int	main(int argc, char **argv)
{
	int		*input;
	t_node	*nodes;
	t_sol	sol;

	input = parse_and_compress(argv + 1, argc - 1);
	nodes = parsed_to_nodes(input, argc - 1);
	sol = solve_big(nodes, argc - 1);
	sol_print(sol);
	sol_destroy(sol);

}
