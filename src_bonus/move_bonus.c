/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taejkim <taejkim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/21 13:11:36 by taejkim           #+#    #+#             */
/*   Updated: 2021/10/21 20:59:06 by taejkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long_bonus.h"

static void	remove_fish(t_game *game, int x, int y)
{
	t_obj	*node;
	t_obj	*next;

	node = game->fish;
	if (x == node->x && y == node->y)
		game->fish = node->next;
	else
	{
		next = node->next;
		while (next)
		{
			if (x == next->x && y == next->y)
			{
				node->next = next->next;
				node = next;
				break ;
			}
			node = node->next;
			next = node->next;
		}
	}
	free(node);
	if ((++(game->fish_count)) == game->fish_max)
		mlx_put_image_to_window(game->mlx, game->win, game->img[IMG_EXIT], \
			TILE_SIZE * game->exit->x, TILE_SIZE * game->exit->y);
}

void	standing(t_game *game)
{
	if (game->state.frame % 1000 == 0)
	{
		if ((++(game->state.motion)) == 9)
			game->state.motion = 1;
		display_player(game);
	}
	if ((++(game->state.frame)) == 8000)
		game->state.frame = 0;
}

void	move_tile(t_game *game)
{
	if (game->state.move_dir == UP)
		display_up(game, IMG_TILE0);
	else if (game->state.move_dir == DOWN)
		display_down(game, IMG_TILE0);
	else if (game->state.move_dir == LEFT)
		display_left(game, IMG_TILE0);
	else if (game->state.move_dir == RIGHT)
		display_right(game, IMG_TILE0);
	if (game->state.mvf == 32)
	{
		game->x = game->state.move_x;
		game->y = game->state.move_y;
		init_state(game);
		return ;
	}
	++(game->state.mvf);
}

void	move_fish(t_game *game)
{
	if (game->state.move_dir == UP)
		display_up(game, IMG_TILE0);
	else if (game->state.move_dir == DOWN)
		display_down(game, IMG_TILE0);
	else if (game->state.move_dir == LEFT)
		display_left(game, IMG_TILE0);
	else if (game->state.move_dir == RIGHT)
		display_right(game, IMG_TILE0);
	if (game->state.mvf == 32)
	{
		game->x = game->state.move_x;
		game->y = game->state.move_y;
		init_state(game);
		remove_fish(game, game->x, game->y);
		display_update_fish(game);
		return ;
	}
	++(game->state.mvf);
}

void	move_exit(t_game *game)
{
	if (game->state.move_dir == UP)
		display_up(game, IMG_EXIT);
	else if (game->state.move_dir == DOWN)
		display_down(game, IMG_EXIT);
	else if (game->state.move_dir == LEFT)
		display_left(game, IMG_EXIT);
	else if (game->state.move_dir == RIGHT)
		display_right(game, IMG_EXIT);
	if (game->state.mvf == 32)
	{
		game->state.playing = FALSE;
		display_ending(game);
		return ;
	}
	++(game->state.mvf);
}
