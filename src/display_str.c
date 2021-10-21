/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_str.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taejkim <taejkim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/21 13:45:09 by taejkim           #+#    #+#             */
/*   Updated: 2021/10/21 16:29:49 by taejkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

void	print_move(int num)
{
	char	*str;

	str = ft_itoa(num);
	ft_putstr_fd("move : ", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd("\n", 2);
	free(str);
}

void	display_update_fish(t_game *game)
{
	char	*str;
	char	*fish;

	mlx_put_image_to_window(game->mlx, game->win, \
		game->img[IMG_FISH_BLACK], 120, TILE_SIZE * game->row);
	fish = ft_itoa(game->fish_count);
	str = ft_strjoin_free_s2("fish : ", fish);
	str = ft_strjoin_free_s1(str, " / ");
	fish = ft_itoa(game->fish_max);
	str = ft_strjoin_free_s1(str, fish);
	mlx_string_put(game->mlx, game->win, \
		120, TILE_SIZE * game->row + 12, 0xFFFFFF, str);
	free(fish);
	free(str);
}

void	display_update_move(t_game *game)
{
	char	*str;

	mlx_put_image_to_window(game->mlx, game->win, \
		game->img[IMG_MOVE_BLACK], 20, TILE_SIZE * game->row);
	str = ft_itoa(game->state.move_count);
	str = ft_strjoin_free_s2("move : ", str);
	mlx_string_put(game->mlx, game->win, \
		20, TILE_SIZE * game->row + 12, 0xFFFFFF, str);
	free(str);
}

void	display_str(t_game *game)
{
	char	*str;

	mlx_string_put(game->mlx, game->win, \
		20, TILE_SIZE * game->row + 12, 0xFFFFFF, "move : 0");
	str = ft_itoa(game->fish_max);
	str = ft_strjoin_free_s2("fish : 0 / ", str);
	mlx_string_put(game->mlx, game->win, \
		120, TILE_SIZE * game->row + 12, 0xFFFFFF, str);
	free(str);
}
