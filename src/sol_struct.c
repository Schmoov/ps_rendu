#include "push_swap.h"

void	sol_init(t_sol *sol)
{
	sol->val = malloc(2000 * sizeof(t_op));
	if (sol->val)
		sol->size = 2000;
	else
		sol->size = -1;
	sol->len = 0;
}

static void	sol_realloc(t_sol *sol)
{
	t_op	*new_val;

	if (sol->size == -1)
		return ;
	new_val = malloc(2 * sol->size * sizeof(t_op));
	ft_memcpy(new_val, sol->val, sol->len * sizeof(t_op));
	sol->size *= 2;
	free(sol->val);
	sol->val = new_val;
}

void	sol_append_one(t_sol *sol, t_op op)
{
	if (sol->size == -1)
		return ;
	if (sol->len == sol->size)
		sol_realloc(sol);
	sol->val[sol->len] = op;
	(sol->len)++;
}

void	sol_append_arr(t_sol *sol, t_op *op, int size)
{
	int	i;

	if (sol->size == -1)
		return ;
	i = 0;
	while (i < size)
		sol_append_one(sol, op[i++]);
}
