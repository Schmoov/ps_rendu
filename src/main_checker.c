/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_checker.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: parden <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 20:57:07 by parden            #+#    #+#             */
/*   Updated: 2024/09/22 22:20:03 by parden           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../push_swap.h"
//TODO	parse_moves(moves, &moves_len);
static bool	checkering(t_op *moves, int moves_len, t_node *nodes, int len)
{
	t_stk	*a;
	t_stk	*b;

	stks_init(nodes, len, a, b);
	stks_execute(moves, moves_len, a, b);
	return (stks_is_solved(a, b));
}

int	main(int argc, char **argv)
{
	t_node	*nodes;
	t_op	*moves;
	int		moves_len;

	nodes = parse_nodes(argv + 1, argc - 1);
	if (!nodes)
		return (write(2, "Error\n", 6));
	parse_moves(moves, &moves_len);
	if (!moves)
		return (free(nodes), write(2, "Error\n", 6));
	if (checkering(moves, moves_len, nodes))
		write(1, "OK\n", 3);
	else
		write(1, "KO\n", 3);
	free(nodes, moves);
}
