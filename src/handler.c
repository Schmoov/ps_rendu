#include "../push_swap.h"

t_ps_op_handler	ps_op_to_func(t_op move)
{
	static t_ps_op_handler	arr[11] = {
		ps_op_sa,
		ps_op_ra,
		ps_op_rra,
		ps_op_pb,
		ps_op_pa,
		ps_op_ss,
		ps_op_rrr,
		ps_op_rr,
		ps_op_sb,
		ps_op_rb,
		ps_op_rrb};

	return (arr[move]);
}

char	*ps_op_to_str(t_op move)
{
	static char	*arr[11] = {
		"sa",
		"ra",
		"rra",
		"pb",
		"pa",
		"ss",
		"rrr",
		"rr",
		"sb",
		"rb",
		"rrb"};

	return (arr[move]);
}

t_op	ps_str_to_op(char *move)
{
	int			i;
	static char	*arr[11] = {
		"sa",
		"ra",
		"rra",
		"pb",
		"pa",
		"ss",
		"rrr",
		"rr",
		"sb",
		"rb",
		"rrb"};

	i = 0;
	while (ft_strncmp(move, arr[i], 3))
		i++;
	return (i);
}
