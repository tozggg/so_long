/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taejkim <taejkim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/21 13:51:18 by taejkim           #+#    #+#             */
/*   Updated: 2021/10/21 13:54:35 by taejkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

static void	get_xpm_img1(t_game *game)
{
	int img64;

	img64 = 64;
	game->img[IMG_FISH] = mlx_xpm_file_to_image\
		(game->mlx, "../image/fish.xpm", &img64, &img64);
	game->img[IMG_PG1] = mlx_xpm_file_to_image\
		(game->mlx, "../image/pg1.xpm", &img64, &img64);
	game->img[IMG_PG2] = game->img[IMG_PG1];
	game->img[IMG_PG3] = game->img[IMG_PG1];
	game->img[IMG_PG4] = mlx_xpm_file_to_image\
		(game->mlx, "../image/pg2.xpm", &img64, &img64);
	game->img[IMG_PG5] = mlx_xpm_file_to_image\
		(game->mlx, "../image/pg3.xpm", &img64, &img64);
	game->img[IMG_PG6] = mlx_xpm_file_to_image\
		(game->mlx, "../image/pg4.xpm", &img64, &img64);
	game->img[IMG_PG7] = mlx_xpm_file_to_image\
		(game->mlx, "../image/pg5.xpm", &img64, &img64);
	game->img[IMG_PG8] = mlx_xpm_file_to_image\
		(game->mlx, "../image/pg6.xpm", &img64, &img64);
}

static void	get_xpm_img2(t_game *game)
{
	int	img64;

	img64 = 64;
	game->img[IMG_TILE0] = mlx_xpm_file_to_image\
		(game->mlx, "../image/tile0.xpm", &img64, &img64);
	game->img[IMG_TILE1] = mlx_xpm_file_to_image\
		(game->mlx, "../image/tile1.xpm", &img64, &img64);
	game->img[IMG_END] = mlx_xpm_file_to_image\
		(game->mlx, "../image/end.xpm", &img64, &img64);
	game->img[IMG_EXIT] = mlx_xpm_file_to_image\
		(game->mlx, "../image/exit.xpm", &img64, &img64);
	game->img[IMG_MOVE_BLACK] = mlx_xpm_file_to_image\
		(game->mlx, "../image/move_black.xpm", &img64, &img64);
	game->img[IMG_FISH_BLACK] = mlx_xpm_file_to_image\
		(game->mlx, "../image/fish_black.xpm", &img64, &img64);
}

static void	add_obj(t_obj **obj, int x, int y)
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

static void	make_game_child(t_game *game, char *str, int x, int y)
{
	if (*str == '1')
		add_obj(&(game->wall), x, y);
	else if (*str == 'E')
		add_obj(&(game->exit), x, y);
	else if (*str == 'C')
	{
		add_obj(&(game->fish), x, y);
		++(game->fish_max);
	}
	else if (*str == 'P')
	{
		game->x = x;
		game->y = y;
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
	game->col = x;
	game->row = y;
	game->mlx = mlx_init();
	get_xpm_img1(game);
	get_xpm_img2(game);
	game->win = mlx_new_window(game->mlx, TILE_SIZE * game->col, TILE_SIZE * game->row + 16, "so_long");
}
