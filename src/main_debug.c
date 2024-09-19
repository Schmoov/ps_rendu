#include "../push_swap.h"

int	main(int argc, char **argv)
{
	int	*input;
	char	**splitted = ft_split(argv[1], ' ');
	int	spl_len = 0;
	int	i = 2;
	t_stk	stk_a;
	t_stk	stk_b;

	while (splitted[spl_len]) spl_len++;
	input = parse_and_compress(splitted, spl_len);
	stks_init(input, spl_len, &stk_a, &stk_b);
	while (i < argc)
	{
		stks_print(&stk_a, &stk_b);
		ps_op_to_func(ps_str_to_op(argv[i]))(&stk_a, &stk_b);
		i++;
	}
	stks_print(&stk_a, &stk_b);
	stks_destroy(&stk_a, &stk_b);

	free(input);
}
