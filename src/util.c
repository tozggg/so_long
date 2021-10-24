/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taejkim <taejkim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/21 13:55:14 by taejkim           #+#    #+#             */
/*   Updated: 2021/10/24 15:45:31 by taejkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

int	is_ber(char *str)
{
	if (str[0] == 'b' && str[1] == 'e' \
			&& str[2] == 'r' && str[3] == 0)
		return (1);
	return (0);
}

int	is_ber_extension(char *pathname)
{
	while (*pathname)
	{
		if (*pathname == '.')
			return (is_ber(++pathname));
		++pathname;
	}
	return (0);
}

char	*read_file(char *pathname)
{
	char	*res;
	char	*buf;
	int		fd;

	if (!is_ber_extension(pathname))
		error_out("map: invalid extention\n");
	fd = open(pathname, O_RDONLY);
	if (fd == -1)
		error_out("map: file does not exist\n");
	res = (char *)malloc(sizeof(char));
	res[0] = 0;
	buf = (char *)malloc(sizeof(char) * 2);
	if (!res || !buf)
		error_out("malloc error\n");
	while (read(fd, buf, 1))
	{
		buf[1] = 0;
		res = ft_strjoin_free_s1(res, buf);
		if (!res)
			error_out("strjoin error\n");
	}
	free(buf);
	return (res);
}

void	error_out(char *msg)
{
	ft_putstr_fd("Error\n", 2);
	ft_putstr_fd(msg, 2);
	exit(1);
}
