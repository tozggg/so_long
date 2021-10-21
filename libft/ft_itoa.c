/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taejkim <taejkim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/21 14:04:38 by taejkim           #+#    #+#             */
/*   Updated: 2021/10/21 14:10:34 by taejkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	get_size(int n)
{
	int			res;
	long long	tmp;

	if (n == 0)
		return (1);
	res = 0;
	tmp = n;
	if (n < 0)
	{
		res += 1;
		tmp = -tmp;
	}
	while (tmp > 0)
	{
		res += 1;
		tmp /= 10;
	}
	return (res);
}

static void	assign_ptr(char *ptr, int n, int size)
{
	long long	tmp;

	ptr[size] = 0;
	if (n == 0)
	{
		ptr[0] = '0';
		return ;
	}
	tmp = n;
	if (n < 0)
	{
		ptr[0] = '-';
		tmp = -tmp;
	}
	while (tmp > 0)
	{
		ptr[--size] = '0' + (tmp % 10);
		tmp /= 10;
	}
}

char		*ft_itoa(int n)
{
	char	*ptr;
	int		size;

	size = get_size(n);
	ptr = (char *)malloc(sizeof(char) * (size + 1));
	if (!ptr)
		return (NULL);
	assign_ptr(ptr, n, size);
	return (ptr);
}
