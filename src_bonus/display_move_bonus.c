/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_move_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taejkim <taejkim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/21 13:42:16 by taejkim           #+#    #+#             */
/*   Updated: 2021/10/21 20:58:42 by taejkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long_bonus.h"

void	display_up(t_game *game, int imgno)
{
	mlx_put_image_to_window(game->mlx, game->win, \
		game->img[IMG_TILE0], TILE_SIZE * game->x, TILE_SIZE * game->y);
	mlx_put_image_to_window(game->mlx, game->win, \
		game->img[imgno], \
		TILE_SIZE * game->state.move_x, TILE_SIZE * game->state.move_y);
	mlx_put_image_to_window(game->mlx, game->win, \
		game->img[game->state.motion], \
		TILE_SIZE * game->x, (TILE_SIZE * game->y) - (game->state.mvf * 2));
}

void	display_down(t_game *game, int imgno)
{
	mlx_put_image_to_window(game->mlx, game->win, \
		game->img[IMG_TILE0], TILE_SIZE * game->x, TILE_SIZE * game->y);
	mlx_put_image_to_window(game->mlx, game->win, \
		game->img[imgno], \
		TILE_SIZE * game->state.move_x, TILE_SIZE * game->state.move_y);
	mlx_put_image_to_window(game->mlx, game->win, \
		game->img[game->state.motion], \
		TILE_SIZE * game->x, (TILE_SIZE * game->y) + (game->state.mvf * 2));
}

void	display_left(t_game *game, int imgno)
{
	mlx_put_image_to_window(game->mlx, game->win, \
		game->img[IMG_TILE0], TILE_SIZE * game->x, TILE_SIZE * game->y);
	mlx_put_image_to_window(game->mlx, game->win, \
		game->img[imgno], \
		TILE_SIZE * game->state.move_x, TILE_SIZE * game->state.move_y);
	mlx_put_image_to_window(game->mlx, game->win, \
		game->img[game->state.motion], \
		(TILE_SIZE * game->x) - (game->state.mvf * 2), TILE_SIZE * game->y);
}

void	display_right(t_game *game, int imgno)
{
	mlx_put_image_to_window(game->mlx, game->win, \
		game->img[IMG_TILE0], TILE_SIZE * game->x, TILE_SIZE * game->y);
	mlx_put_image_to_window(game->mlx, game->win, \
		game->img[imgno], \
		TILE_SIZE * game->state.move_x, TILE_SIZE * game->state.move_y);
	mlx_put_image_to_window(game->mlx, game->win, \
		game->img[game->state.motion], \
		(TILE_SIZE * game->x) + (game->state.mvf * 2), TILE_SIZE * game->y);
}

void	display_ending(t_game *game)
{
	int	x;
	int	y;

	x = TILE_SIZE * game->col / 2;
	y = TILE_SIZE * game->row / 2;
	mlx_clear_window(game->mlx, game->win);
	mlx_string_put(game->mlx, game->win, x - 67, y, \
		0xFFFFFF, "!!!!!! CLEAR !!!!!!");
	mlx_string_put(game->mlx, game->win, x - 67, y + 16, \
		0xFFFFFF, "Press [esc] to exit");
}
