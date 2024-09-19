#include "../push_swap.h"

void	stks_init(t_node *nodes, int input_len, t_stk *stk_a, t_stk *stk_b)
{
	int		i;
	t_node	*tmp;

	stk_a->len = input_len;
	stk_a->head = nodes;
	stk_b->len = 0;
	stk_b->head = NULL;
	nodes[0].prev = nodes + (input_len-1);
	nodes[0].next = nodes + 1;
	nodes[input_len-1].prev = nodes + (input_len-2);
	nodes[input_len-1].next = nodes;
	i = 1;
	while (i < input_len - 1)
	{
		nodes[i].next = nodes + i + 1;
		nodes[i].prev = nodes + i - 1;
		i++;
	}
}

void	stks_destroy(t_stk *stk_a, t_stk *stk_b)
{
}

bool	stks_is_solved(t_stk *stk_a, t_stk *stk_b)
{
	t_node	*tmp;

	if (stk_b->len)
		return (false);
	if (!stk_a->head || stk_a->head->val)
		return (false);
	tmp = stk_a->head;
	while (tmp->next->val)
	{
		if (tmp->val > tmp->next->val)
			return (false);
		tmp = tmp->next;
	}
	return (true);
}

void	stks_execute(t_op *moves, int moves_len, t_stk *stk_a, t_stk *stk_b)
{
	int	i;

	i = 0;
	while (i < moves_len)
	{
		ps_op_to_func(moves[i])(stk_a, stk_b);
		i++;
	}
}

void	stks_print(t_stk *a, t_stk *b)
{
	t_node	*tmp = a->head;
	for (int i = 0; i < a->len; i++)
	{
		ft_printf("%d ", tmp->val);
		tmp = tmp->next;
	}
	ft_printf("|");
	tmp = b->head;
	for (int i = 0; i < b->len; i++)
	{
		ft_printf("%d ", tmp->val);
		tmp = tmp->next;
	}
	ft_printf("\n");
}
