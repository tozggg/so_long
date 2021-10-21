/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taejkim <taejkim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/21 13:44:06 by taejkim           #+#    #+#             */
/*   Updated: 2021/10/21 13:44:32 by taejkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

static int	is_obj(t_obj *obj, int x, int y)
{
	t_obj *node;

	node = obj;
	while (node)
	{
		if (x == node->x && y == node->y)
			return (1);
		node = node->next;
	}
	return (0);
}

void	action(t_game *game, int x, int y, int dir)
{
	if (game->state.playing == FALSE || game->state.moving == TRUE)
		return ;
	if (is_obj(game->wall, x, y) || (is_obj(game->exit, x, y) && !(game->fish_count == game->fish_max)))
		return ;
	else
	{
		if (is_obj(game->exit, x, y) && (game->fish_count == game->fish_max))
			game->state.move_place = MOVE_EXIT;
		else if (is_obj(game->fish, x, y))
			game->state.move_place = MOVE_FISH;
		else
			game->state.move_place = MOVE_TILE;
		game->state.moving = TRUE;
		game->state.move_dir = dir;
		game->state.move_x = x;
		game->state.move_y = y;
		print_move(++(game->state.move_count));
		display_update_move(game);
	}
}
