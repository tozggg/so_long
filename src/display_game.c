/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_game.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taejkim <taejkim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/21 13:47:14 by taejkim           #+#    #+#             */
/*   Updated: 2021/10/21 13:47:21 by taejkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

void	display_player(t_game *game)
{
	mlx_put_image_to_window(game->mlx, game->win, game->img[IMG_TILE0], TILE_SIZE * game->x, TILE_SIZE * game->y);
	mlx_put_image_to_window(game->mlx, game->win, game->img[game->state.motion], TILE_SIZE * game->x, TILE_SIZE * game->y);
}

void	display_background(t_game *game)
{
	int i;
	int j;

	j = 0;
	while (j < game->row)
	{
		i = 0;
		while (i < game->col)
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
}


void	display_game(t_game *game)
{
	display_background(game);
	display_obj(game);
	display_str(game);
}
