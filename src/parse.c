/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: parden <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 20:57:07 by parden            #+#    #+#             */
/*   Updated: 2024/09/22 21:09:04 by parden           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static bool	ps_atoi(char *nptr, int *n)
{
	long long	res;
	int			i;
	int			sign;

	res = 0;
	i = 0;
	sign = 1;
	if (nptr[i] == '+' || nptr[i] == '-')
	{
		if (nptr[i] == '-')
			sign = -1;
		i++;
	}
	while (ft_isdigit(nptr[i])
		&& sign * res <= INT_MAX && sign * res >= INT_MIN)
	{
		res = 10 * res + nptr[i] - '0';
		i++;
	}
	res *= sign;
	*n = res;
	return (!nptr[i] && res <= INT_MAX && res >= INT_MIN);
}

static bool	ps_parse(int *res, char **nums, int size)
{
	int		i;

	i = 0;
	while (i < size)
	{
		if (!ps_atoi(nums[i], res + i))
			return (false);
		i++;
	}
	return (true);
}

static bool	compress(int *res, int size)
{
	int	*dup;
	int	i;

	i = 0;
	dup = (int *)malloc(size * sizeof(int));
	if (!dup)
		return (false);
	ft_memcpy(dup, res, size * sizeof(int));
	ft_isort(dup, size);
	while (i < size - 1)
	{
		if (dup[i] == dup[i + 1])
			return (free(dup), false);
		i++;
	}
	i = 0;
	while (i < size)
	{
		res[i] = (ft_ibsearch(res[i], dup, size) - dup);
		i++;
	}
	free(dup);
	return (true);
}

static int	*parse_and_compress(char **nums, int size)
{
	int	*res;

	res = (int *)malloc(size * sizeof(int));
	if (!res)
		return (NULL);
	if (!ps_parse(res, nums, size))
		return (free(res), NULL);
	if (!compress(res, size))
		return (free(res), NULL);
	return (res);
}

t_node	*parse_nodes(char **nums, int size)
{
	int		*parsed;
	t_node	*res;
	int		i;

	parsed = parse_and_compress(nums, size);
	res = malloc(size * sizeof(t_node));
	if (!res || !parsed)
		return (free(res), free(parsed), NULL);
	i = 0;
	while (i < size)
	{
		res[i].val = parsed[i];
		res[i].next = res + ((i + 1) % size);
		res[i].prev = res + ((i - 1 + size) % size);
		i++;
	}
	free(parsed);
	return (res);
}
