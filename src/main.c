/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taejkim <taejkim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/14 06:06:08 by taejkim           #+#    #+#             */
/*   Updated: 2021/10/21 17:49:59 by taejkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

int	close_game(t_game *game)
{
	mlx_destroy_window(game->mlx, game->win);
	exit(0);
}

int	key_press(int keycode, t_game *game)
{
	if (keycode == KEY_ESC)
		close_game(game);
	else if (keycode == KEY_W)
		action(game, game->x, game->y - 1, UP);
	else if (keycode == KEY_A)
		action(game, game->x - 1, game->y, LEFT);
	else if (keycode == KEY_S)
		action(game, game->x, game->y + 1, DOWN);
	else if (keycode == KEY_D)
		action(game, game->x + 1, game->y, RIGHT);
	return (0);
}

int	loop(t_game *game)
{
	if (game->state.playing == FALSE)
		return (0);
	if (game->state.moving == FALSE)
		standing(game);
	else
	{
		if (game->state.move_place == MOVE_TILE)
			move_tile(game);
		else if (game->state.move_place == MOVE_FISH)
			move_fish(game);
		else if (game->state.move_place == MOVE_EXIT)
			move_exit(game);
	}
	return (0);
}

int	main(int ac, char *av[])
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
	mlx_hook(game.win, X_EVENT_KEY_EXIT, 0, &close_game, &game);
	mlx_hook(game.win, X_EVENT_KEY_PRESS, 0, &key_press, &game);
	mlx_loop_hook(game.mlx, &loop, &game);
	mlx_loop(game.mlx);
	return (0);
}
