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

bool	ps_parse(int *res, char **nums, int size)
{
	int		i;
	bool	err;

	i = 0;
	err = false;
	while (i < size)
	{
		if (!ps_atoi(nums[i], res + i))
			return (false);
		i++;
	}
	return (true);
}

bool	compress(int *res, int size)
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

int	*parse_and_compress(char **nums, int size)
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

t_node	*parsed_to_nodes(int *parsed, int size)
{
	t_node	*res;
	int		i;

	res = malloc(size * sizeof(t_node));
	i = 0;
	while (i < size)
	{
		res[i].val = parsed[i];
		res[i].next = res + ((i + 1) % size);
		res[i].prev = res + ((i - 1 + size) % size);
		i++;
	}
	return (res);
}
