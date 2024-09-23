/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_checker.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: parden <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 20:57:07 by parden            #+#    #+#             */
/*   Updated: 2024/09/23 15:15:58 by parden           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../push_swap.h"

static void	parse_moves(t_sol *moves)
{
	char	*line;

	line = get_next_line(0);
	while (line)
	{
		line[ft_strlen(line) - 1] = 0;
		sol_append_one(moves, ps_str_to_op(line));
		free(line);
		if (moves->val[moves->len - 1] == NB_OP)
		{
			free(moves->val);
			moves->size = -1;
			break ;
		}
		line = get_next_line(0);
	}
}

static bool	checkering(t_sol *moves, t_node *nodes, int len)
{
	t_stk	a;
	t_stk	b;

	stks_init(nodes, len, &a, &b);
	stks_execute(moves->val, moves->len, &a, &b);
	return (stks_is_solved(&a, &b));
}

int	main(int argc, char **argv)
{
	t_node	*nodes;
	t_sol	moves;

	if (argc == 1)
		return (0);
	nodes = parse_nodes(argv + 1, argc - 1);
	if (!nodes)
		return (write(2, "Error\n", 6));
	sol_init(&moves);
	parse_moves(&moves);
	if (moves.size == -1)
		return (free(nodes), write(2, "Error\n", 6));
	if (checkering(&moves, nodes, argc - 1))
		write(1, "OK\n", 3);
	else
		write(1, "KO\n", 3);
	free(nodes);
	free(moves.val);
}
