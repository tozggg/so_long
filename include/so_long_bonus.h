/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_bonus.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taejkim <taejkim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/21 13:06:25 by taejkim           #+#    #+#             */
/*   Updated: 2021/10/21 20:57:01 by taejkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_BONUS_H
# define SO_LONG_BONUS_H

# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <sys/types.h>

# include "../libft/libft.h"
# include "../mlx/mlx.h"

# define BUFFER_SIZE 1
# define TILE_SIZE 64

# define IMG_FISH 0
# define IMG_PG1 1
# define IMG_PG2 2
# define IMG_PG3 3
# define IMG_PG4 4
# define IMG_PG5 5
# define IMG_PG6 6
# define IMG_PG7 7
# define IMG_PG8 8
# define IMG_TILE0 9
# define IMG_TILE1 10
# define IMG_END 11
# define IMG_EXIT 12
# define IMG_MOVE_BLACK 13
# define IMG_FISH_BLACK 14

# define X_EVENT_KEY_PRESS 2
# define X_EVENT_KEY_EXIT 17

# define KEY_ESC 53
# define KEY_W 13
# define KEY_A 0
# define KEY_S 1
# define KEY_D 2

# define TRUE 1
# define FALSE 0

# define UP 1
# define DOWN 2
# define LEFT 3
# define RIGHT 4

# define MOVE_TILE 1
# define MOVE_FISH 2
# define MOVE_EXIT 3

typedef struct s_map
{
	int				prev_len;
	int				curr_len;
	int				start;
	int				end;
	int				fish;
}				t_map;

typedef struct s_obj
{
	int				x;
	int				y;
	struct s_obj	*next;	
}				t_obj;

typedef struct s_state
{
	int				playing;
	int				moving;
	int				move_place;
	int				move_dir;
	int				move_x;
	int				move_y;
	int				move_count;
	int				motion;
	int				frame;
	int				mvf;
}				t_state;

typedef struct s_game
{
	void			*mlx;
	void			*win;
	void			*img[15];
	t_obj			*wall;
	t_obj			*exit;
	t_obj			*fish;
	int				fish_max;
	int				fish_count;
	int				col;
	int				row;
	int				x;
	int				y;
	t_state			state;
}				t_game;

char	*read_file(char *pathname);
void	error_out(char *msg);

void	init_map(t_map *map);
void	init_state(t_game *game);
void	init_game(t_game *game);

void	check_map(char *str);

void	make_game(t_game *game, char *str);

void	display_player(t_game *game);
void	display_background(t_game *game);
void	display_obj(t_game *game);
void	display_game(t_game *game);

void	print_move(int num);
void	display_update_fish(t_game *game);
void	display_update_move(t_game *game);
void	display_str(t_game *game);

void	action(t_game *game, int x, int y, int dir);

void	display_up(t_game *game, int imgno);
void	display_down(t_game *game, int imgno);
void	display_left(t_game *game, int imgno);
void	display_right(t_game *game, int imgno);
void	display_ending(t_game *game);

void	standing(t_game *game);
void	move_tile(t_game *game);
void	move_fish(t_game *game);
void	move_exit(t_game *game);

int		close_game(t_game *game);
int		key_press(int keycode, t_game *game);
int		loop(t_game *game);

#endif
