/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taejkim <taejkim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/21 13:58:05 by taejkim           #+#    #+#             */
/*   Updated: 2021/10/21 20:58:29 by taejkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long_bonus.h"

static int	check_first_line(char *str, t_map *map, int *i)
{
	while (str[*i] && str[*i] != '\n')
	{
		if (str[*i] != '1')
			error_out("invalid map: enclosing wall\n");
		++map->prev_len;
		++(*i);
	}
	if (!str[*i] || !str[*i + 1])
		return (0);
	return (1);
}

static int	check_last_line(char *str, t_map *map, int *i)
{
	int		j;

	j = 1;
	while (j <= map->prev_len)
	{
		if (str[*i - j] != '1')
			error_out("invalid map: enclosing wall\n");
		++j;
	}
	return (0);
}

static int	check_line(char *str, t_map *map, int *i)
{
	if (str[*i] != '1')
		error_out("invalid map: enclosing wall\n");
	while (str[*i] && str[*i] != '\n')
	{
		if (!(str[*i] == '0' || str[*i] == '1' || str[*i] == 'P' || \
				str[*i] == 'E' || str[*i] == 'C'))
			error_out("invalid map: abnormal object\n");
		if (str[*i] == 'P')
			++map->start;
		if (str[*i] == 'E')
			++map->end;
		if (str[*i] == 'C')
			++map->fish;
		++map->curr_len;
		++(*i);
	}
	if (map->curr_len != map->prev_len)
		error_out("invalid map: not rectangle\n");
	map->curr_len = 0;
	if (!str[*i] || !str[*i + 1])
		return (check_last_line(str, map, i));
	if (str[*i - 1] != '1')
		error_out("invalid map: enclosing wall\n");
	return (1);
}

static void	check_map_element(t_map map)
{
	if (map.start != 1)
		error_out("invalid map: insufficient object\n");
	if (map.end != 1)
		error_out("invalid map: insufficient object\n");
	if (!(map.fish >= 1))
		error_out("invalid map: insufficient object\n");
}

void	check_map(char *str)
{
	t_map	map;
	int		i;
	int		flag;

	init_map(&map);
	i = 0;
	flag = check_first_line(str, &map, &i);
	while (flag)
	{
		++i;
		flag = check_line(str, &map, &i);
	}
	check_map_element(map);
}
