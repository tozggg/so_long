/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taejkim <taejkim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/21 14:00:26 by taejkim           #+#    #+#             */
/*   Updated: 2021/10/21 14:00:58 by taejkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

void	init_map(t_map *map)
{
	map->prev_len = 0;
	map->curr_len = 0;
	map->start = 0;
	map->end = 0;
	map->fish = 0;
}

void	init_state(t_game *game)
{
	game->state.playing = TRUE;
	game->state.moving = FALSE;
	game->state.move_place = 0;
	game->state.move_dir = 0;
	game->state.move_x = 0;
	game->state.move_y = 0;
	game->state.mvf = 0;
}

void	init_game(t_game *game)
{
	game->mlx = NULL;
	game->win = NULL;
	game->wall = NULL;
	game->exit = NULL;
	game->fish = NULL;
	game->fish_max = 0;
	game->fish_count = 0;
	game->col = 0;
	game->row = 0;
	game->x = 0;
	game->y = 0;
	init_state(game);
	game->state.motion = 1;
	game->state.frame = 0;
	game->state.move_count = 0;
}
