#include "../push_swap.h"

void	ps_op_rrr(t_stk *a, t_stk *b)
{
	ps_op_rra(a, b);
	ps_op_rrb(a, b);
}
