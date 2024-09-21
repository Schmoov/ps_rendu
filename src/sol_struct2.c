#include "push_swap.h"

void	sol_print(t_sol	sol)
{
	int	i;

	i = 0;
	while (i < sol.len)
	{
		ft_printf("%s\n", ps_op_to_str(sol.val[i]));
		i++;
	}
}

void	sol_destroy(t_sol sol)
{
	free(sol.val);
}
