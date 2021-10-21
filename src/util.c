/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taejkim <taejkim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/21 13:55:14 by taejkim           #+#    #+#             */
/*   Updated: 2021/10/21 13:59:53 by taejkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

char 	*read_file(char *pathname)
{
	char	*res;
	char	*buf;
	int		fd;
	int		readsize;

	fd = open(pathname, O_RDONLY);
	res = (char *)malloc(sizeof(char));
	res[0] = 0;
	buf = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!res || !buf)
		error_out("malloc error\n");
	while ((readsize = read(fd, buf, BUFFER_SIZE)))
	{
		if (readsize == BUFFER_SIZE)
			res = ft_strjoin_free_s1(res, buf);
		else
		{
			buf[readsize] = 0;
			res = ft_strjoin_free_s1(res, buf);
		}
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
