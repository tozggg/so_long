/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taejkim <taejkim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/14 06:06:08 by taejkim           #+#    #+#             */
/*   Updated: 2021/10/14 16:21:51 by taejkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>



#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/types.h>

#include "../mlx/mlx.h"

#define BUFFER_SIZE 32
#define TILE_SIZE 64

typedef struct	s_map
{
	int				prev_len;
	int				curr_len;
	int				start;
	int				end;
	int				fish;
}				t_map;

typedef struct	s_game
{
	struct s_obj	*wall;
	struct s_obj	*exit;
	struct s_obj	*fish;
	int				fish_count;
	int				player_x;
	int				player_y;
	int				mvmt;
}				t_game;

typedef struct	s_obj
{
	int				x;
	int				y;
	struct s_obj	*next;	
}				t_obj;

//Libft ----------------------------------------------------

int		ft_strlen(char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		++i;
	return (i);
}

void	ft_putstr_fd(char *s, int fd)
{
	size_t	len;

	if (fd < 0 || s == NULL)
		return ;
	len = ft_strlen(s);
	write(fd, s, len);
}

char	*ft_strjoin(char *s1, char *s2)
{
	char	*ptr;
	size_t	len;
	int		i;
	int		j;

	len = ft_strlen(s1) + ft_strlen(s2);
	ptr = (char *)malloc(sizeof(char) * (len + 1));
	if (!ptr)
		return (NULL);
	i = 0;
	j = -1;
	while (s1[++j])
		ptr[i++] = s1[j];
	j = -1;
	while (s2[++j])
		ptr[i++] = s2[j];
	ptr[i] = 0;
	free(s1);
	return (ptr);
}

//----------------------------------------------------------

//Utill ----------------------------------------------------
void	error_out(char *msg)
{
	ft_putstr_fd("Error\n", 2);
	ft_putstr_fd(msg, 2);
	exit(1);
}
//----------------------------------------------------------

//Init -----------------------------------------------------
void	init_map(t_map *map)
{
	map->prev_len = 0;
	map->curr_len = 0;
	map->start = 0;
	map->end = 0;
	map->fish = 0;
}

void	init_game(t_game *game)
{
	game->wall = NULL;
	game->exit = NULL;
	game->fish = NULL;
	game->fish_count = 0;
	game->player_x = 0;
	game->player_y = 0;
	game->mvmt = 0;
}
// ---------------------------------------------------------

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
			res = ft_strjoin(res, buf);
		else
		{
			buf[readsize] = 0;
			res = ft_strjoin(res, buf);
		}
		if (!res)
			error_out("strjoin error\n");
	}
	free(buf);
	return (res);
}

//Check -----------------------------------------------------
int		check_first_line(char *str, t_map *map, int *i)
{
	while (str[*i] && str[*i] != '\n')
	{
		if (str[*i] != '1')
			error_out("invalid map\n");
		++map->prev_len;
		++(*i);
	}
	if (!str[*i] || !str[*i + 1])
		return (0);
	return (1);
}

int		check_last_line(char *str, t_map *map, int *i)
{
	int		j;

	j = 1;
	while (j <= map->prev_len)
	{
		if (str[*i - j] != '1')
			error_out("invalid map\n");
		++j;
	}
	return (0);
}

int		check_line(char *str, t_map *map, int *i)
{
	if (str[*i] != '1')
		error_out("invalid map\n");
	while (str[*i] && str[*i] != '\n')
	{
		if (!(str[*i] == '0' || str[*i] == '1' || str[*i] == 'P' || \
				str[*i] == 'E' || str[*i] == 'C'))
			error_out("invalid map\n");
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
		error_out("invalid map\n");
	map->curr_len = 0;
	if (!str[*i] || !str[*i + 1])
		return (check_last_line(str, map, i));
	if (str[*i - 1] != '1')
		error_out("invalid map\n");
	return (1);
}

void	check_map_element(t_map map)
{
	if (map.start != 1)
		error_out("invalid map\n");
	if (map.end != 1)
		error_out("invalid map\n");
	if (!(map.fish >= 1))
		error_out("invalid map\n");
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
//---------------------------------------------------------

void	add_obj(t_obj **obj, int x, int y)
{
	t_obj *next;
	t_obj *node;

	next = (t_obj *)malloc(sizeof(t_obj));
	if (!next)
		error_out("malloc error\n");
	next->x = x;
	next->y = y;
	next->next = NULL;
	if (*obj == NULL)
		*obj = next;
	else
	{
		node = *obj;
		while (node->next)
			node = node->next;
		node->next = next;
	}
}

void	make_game_child(t_game *game, char *str, int x, int y)
{
	if (*str == '1')
		add_obj(&(game->wall), x, y);
	else if (*str == 'E')
		add_obj(&(game->exit), x, y);
	else if (*str == 'C')
	{
		add_obj(&(game->fish), x, y);
		++(game->fish_count);
	}
	else if (*str == 'P')
	{
		game->player_x = x;
		game->player_y = y;
	}
}

void	make_game(t_game *game, char *str)
{
	int		x;
	int		y;
	
	y = 1;
	while (*str)
	{
		x = 1;
		while (*str && *str != '\n')
		{
			make_game_child(game, str, x, y);
			++str;
			++x;
		}
		if (*str == '\n')
			++str;
		++y;
	}
}


int		main(int ac, char *av[])
{
	t_game	game;
	char	*map;

	if (ac != 2)
		error_out("usage: ./so_long [map.ber]\n");
	map = read_file(av[1]);
	check_map(map);
	init_game(&game);
	make_game(&game, map);
	free(map);
	
	
	return (0);
}
