/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_debug.c                                       :+:      :+:    :+:   */
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
	int	*input;
	char	**splitted = ft_split(argv[1], ' ');
	int	spl_len = 0;
	t_stk	stk_a;
	t_stk	stk_b;
	t_ps_op_handler	*func;


	while (splitted[spl_len])
		spl_len++;
	input = parse_and_compress(splitted, spl_len);
	stks_init(input, spl_len, &stk_a, &stk_b);
	while (i < argc)
	{
		func = ps_op_to_func(ps_str_to_op(argv[i]));
		stks_print(&stk_a, &stk_b);
		func(&stk_a, &stk_b);
		i++;
	}
	stks_print(&stk_a, &stk_b);
	stks_destroy(&stk_a, &stk_b);

	free(input);
}
