/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_ps.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: parden <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 20:57:07 by parden            #+#    #+#             */
/*   Updated: 2024/09/22 20:57:39 by parden           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../push_swap.h"

int	main(int argc, char **argv)
{
	t_node	*nodes;
	t_sol	sol;

	nodes = parse_nodes(argv + 1, argc - 1);
	if (!nodes)
		return (write(2, "Error\n", 6));
	sol_init(&sol);
	if (argc - 1 <= 5)
		solve_backtrack(nodes, argc - 1, &sol);
	else
		solve_big(nodes, argc - 1, &sol);
	sol_print(sol);
	sol_destroy(sol);
	free(nodes);
}
