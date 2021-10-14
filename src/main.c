/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taejkim <taejkim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/14 06:06:08 by taejkim           #+#    #+#             */
/*   Updated: 2021/10/15 05:58:37 by taejkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>



#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/types.h>

#include "../mlx/mlx.h"

#define BUFFER_SIZE 1
#define TILE_SIZE 64

#define IMG_FISH 0
#define IMG_PG1 1
#define IMG_PG2 2
#define IMG_PG3 3
#define IMG_PG4 4
#define IMG_PG5 5
#define IMG_PG6 6
#define IMG_TILE0 7
#define IMG_TILE1 8
#define IMG_END 9
#define IMG_EXIT 10




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
	void			*mlx;
	void			*win;
	void			*img[11];
	struct s_obj	*wall;
	struct s_obj	*exit;
	struct s_obj	*fish;
	int				fish_count;
	int				x;
	int				y;
	int				player_x;
	int				player_y;
	int				mvmt;
	int				status;
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
	game->mlx = NULL;
	game->win = NULL;
	game->wall = NULL;
	game->exit = NULL;
	game->fish = NULL;
	game->fish_count = 0;
	game->x = 0;
	game->y = 0;
	game->player_x = 0;
	game->player_y = 0;
	game->mvmt = 0;
	game->status = 0;
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
			error_out("invalid map: enclosing wall\n");
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
			error_out("invalid map: enclosing wall\n");
		++j;
	}
	return (0);
}

int		check_line(char *str, t_map *map, int *i)
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

void	check_map_element(t_map map)
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
	
	y = 0;
	while (*str)
	{
		x = 0;
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
	game->x = x;
	game->y = y;
}

// Display ---------------------------------------------------------------------------------------------
void	get_xpm_img(t_game *game)
{
	int img64;

	img64 = 64;
	game->img[IMG_FISH] = mlx_xpm_file_to_image(game->mlx, "../image/fish.xpm", &img64, &img64);
	game->img[IMG_PG1] = mlx_xpm_file_to_image(game->mlx, "../image/pg1.xpm", &img64, &img64);
	game->img[IMG_PG2] = mlx_xpm_file_to_image(game->mlx, "../image/pg2.xpm", &img64, &img64);
	game->img[IMG_PG3] = mlx_xpm_file_to_image(game->mlx, "../image/pg3.xpm", &img64, &img64);
	game->img[IMG_PG4] = mlx_xpm_file_to_image(game->mlx, "../image/pg4.xpm", &img64, &img64);
	game->img[IMG_PG5] = mlx_xpm_file_to_image(game->mlx, "../image/pg5.xpm", &img64, &img64);
	game->img[IMG_PG6] = mlx_xpm_file_to_image(game->mlx, "../image/pg6.xpm", &img64, &img64);
	game->img[IMG_TILE0] = mlx_xpm_file_to_image(game->mlx, "../image/tile0.xpm", &img64, &img64);
	game->img[IMG_TILE1] = mlx_xpm_file_to_image(game->mlx, "../image/tile1.xpm", &img64, &img64);
	game->img[IMG_END] = mlx_xpm_file_to_image(game->mlx, "../image/end.xpm", &img64, &img64);
	game->img[IMG_EXIT] = mlx_xpm_file_to_image(game->mlx, "../image/exit.xpm", &img64, &img64);
}

void	display_background(t_game *game)
{
	int i;
	int j;

	j = 0;
	while (j < game->y)
	{
		i = 0;
		while (i < game->x)
		{
			mlx_put_image_to_window(game->mlx, game->win, game->img[IMG_TILE0], TILE_SIZE * i, TILE_SIZE * j);
			++i;
		}
		++j;
	}
}

void	display_obj(t_game *game)
{
	t_obj *node;

	node = game->wall;
	while (node)
	{
		mlx_put_image_to_window(game->mlx, game->win, game->img[IMG_TILE1], TILE_SIZE * node->x, TILE_SIZE * node->y);
		node = node->next;
	}
	node = game->fish;
	while (node)
	{
		mlx_put_image_to_window(game->mlx, game->win, game->img[IMG_FISH], TILE_SIZE * node->x, TILE_SIZE * node->y);
		node = node->next;
	}
	node = game->exit;
	mlx_put_image_to_window(game->mlx, game->win, game->img[IMG_END], TILE_SIZE * node->x, TILE_SIZE * node->y);
	mlx_put_image_to_window(game->mlx, game->win, game->img[IMG_PG1], TILE_SIZE * game->player_x, TILE_SIZE * game->player_y);			
}

void	display_game(t_game *game)
{
	game->mlx = mlx_init();
	game->win = mlx_new_window(game->mlx, TILE_SIZE * game->x, TILE_SIZE * game->y, "so_long");
	get_xpm_img(game);
	display_background(game);
	display_obj(game);
}
// --------------------------------------------------------------------------------------------------------

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
	display_game(&game);


	mlx_loop(game.mlx);
	return (0);
}
