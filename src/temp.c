/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taejkim <taejkim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/14 06:06:08 by taejkim           #+#    #+#             */
/*   Updated: 2021/10/20 22:19:15 by taejkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
#define IMG_PG7 7
#define IMG_PG8 8
#define IMG_TILE0 9
#define IMG_TILE1 10
#define IMG_END 11
#define IMG_EXIT 12
#define IMG_MOVE_BLACK 13
#define IMG_FISH_BLACK 14

#define X_EVENT_KEY_PRESS 2
#define X_EVENT_KEY_EXIT 17

#define KEY_ESC 53
#define KEY_W 13
#define KEY_A 0
#define KEY_S 1
#define KEY_D 2

#define TRUE 1
#define FALSE 0

#define UP 1
#define DOWN 2
#define LEFT 3
#define RIGHT 4

#define MOVE_TILE 1
#define MOVE_FISH 2
#define MOVE_EXIT 3

typedef struct	s_map
{
	int		prev_len;
	int		curr_len;
	int		start;
	int		end;
	int		fish;
}				t_map;

typedef struct	s_obj
{
	int				x;
	int				y;
	struct s_obj	*next;	
}				t_obj;

typedef struct	s_state
{
	int		playing;
	int		moving;
	int		move_place;
	int		move_dir;
	int		move_x;
	int		move_y;
	int		move_count;
	int		motion;
	int		frame;
	int		mvf;
}				t_state;

typedef struct	s_game
{
	void	*mlx;
	void	*win;
	void	*img[15];
	t_obj	*wall;
	t_obj	*exit;
	t_obj	*fish;
	int		fish_max;
	int		fish_count;
	int		col;
	int		row;
	int		x;
	int		y;
	t_state	state;
}				t_game;

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

char	*ft_strjoin_free_s1(char *s1, char *s2)
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

char	*ft_strjoin_free_s2(char *s1, char *s2)
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
	free(s2);
	return (ptr);
}



static int	get_size(int n)
{
	int			res;
	long long	tmp;

	if (n == 0)
		return (1);
	res = 0;
	tmp = n;
	if (n < 0)
	{
		res += 1;
		tmp = -tmp;
	}
	while (tmp > 0)
	{
		res += 1;
		tmp /= 10;
	}
	return (res);
}

static void	assign_ptr(char *ptr, int n, int size)
{
	long long	tmp;

	ptr[size] = 0;
	if (n == 0)
	{
		ptr[0] = '0';
		return ;
	}
	tmp = n;
	if (n < 0)
	{
		ptr[0] = '-';
		tmp = -tmp;
	}
	while (tmp > 0)
	{
		ptr[--size] = '0' + (tmp % 10);
		tmp /= 10;
	}
}

char		*ft_itoa(int n)
{
	char	*ptr;
	int		size;

	size = get_size(n);
	ptr = (char *)malloc(sizeof(char) * (size + 1));
	if (!ptr)
		return (NULL);
	assign_ptr(ptr, n, size);
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
			res = ft_strjoin_free_s1(res, buf);
		else
		{
			buf[readsize] = 0;
			res = ft_strjoin_free_s1(res, buf);
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

void	get_xpm_img1(t_game *game)
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

void	get_xpm_img2(t_game *game)
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

void	make_game_child(t_game *game, char *str, int x, int y)
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

// Display ---------------------------------------------------------------------------------------------

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

void	display_str(t_game *game)
{
	char	*str;

	mlx_string_put(game->mlx, game->win, 20, TILE_SIZE * game->row + 12, 0xFFFFFF, "move : 0");
	str = ft_itoa(game->fish_max);
	str = ft_strjoin_free_s2("fish : 0 / ", str);
	mlx_string_put(game->mlx, game->win, 120, TILE_SIZE * game->row + 12, 0xFFFFFF, str);
	free(str);
}

void	display_game(t_game *game)
{
	display_background(game);
	display_obj(game);
	display_str(game);
}

void	display_update_fish(t_game *game)
{
	char *str;
	char *fish;

	mlx_put_image_to_window(game->mlx, game->win, game->img[IMG_FISH_BLACK], 120, TILE_SIZE * game->row);
	fish = ft_itoa(game->fish_count);
	str = ft_strjoin_free_s2("fish : ", fish);
	str = ft_strjoin_free_s1(str, " / ");
	fish = ft_itoa(game->fish_max);
	str = ft_strjoin_free_s1(str, fish);
	mlx_string_put(game->mlx, game->win, 120, TILE_SIZE * game->row + 12, 0xFFFFFF, str);
	free(fish);
	free(str);
}

void	display_update_move(t_game *game)
{
	char *str;

	mlx_put_image_to_window(game->mlx, game->win, game->img[IMG_MOVE_BLACK], 20, TILE_SIZE * game->row);
	str = ft_itoa(game->state.move_count);
	str = ft_strjoin_free_s2("move : ", str);
	mlx_string_put(game->mlx, game->win, 20, TILE_SIZE * game->row + 12, 0xFFFFFF, str);
	free(str);
}

// --------------------------------------------------------------------------------------------------------
void	print_move(int num)
{
	char *str;

	str = ft_itoa(num);
	ft_putstr_fd("move : ", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd("\n", 2);
	free(str);
}
// Move -----------------------------------------------------------------

int		is_obj(t_obj *obj, int x, int y)
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







// --------------------------------------------------------------------


int		close_game(t_game *game)
{
	mlx_destroy_window(game->mlx, game->win);
	exit(0);
}

int		key_press(int keycode, t_game *game)
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


// Loop -------------------------------------------------------------------------------

void	remove_fish(t_game *game, int x, int y)
{
	t_obj *node;
	t_obj *next;

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

void	display_up(t_game *game, int imgno)
{
	mlx_put_image_to_window(game->mlx, game->win, game->img[IMG_TILE0], TILE_SIZE * game->x, TILE_SIZE * game->y);
	mlx_put_image_to_window(game->mlx, game->win, game->img[imgno], TILE_SIZE * game->state.move_x, TILE_SIZE * game->state.move_y);
	mlx_put_image_to_window(game->mlx, game->win, game->img[game->state.motion], TILE_SIZE * game->x, (TILE_SIZE * game->y) - (game->state.mvf * 2));
}

void	display_down(t_game *game, int imgno)
{
	mlx_put_image_to_window(game->mlx, game->win, game->img[IMG_TILE0], TILE_SIZE * game->x, TILE_SIZE * game->y);
	mlx_put_image_to_window(game->mlx, game->win, game->img[imgno], TILE_SIZE * game->state.move_x, TILE_SIZE * game->state.move_y);
	mlx_put_image_to_window(game->mlx, game->win, game->img[game->state.motion], TILE_SIZE * game->x, (TILE_SIZE * game->y) + (game->state.mvf * 2));
}

void	display_left(t_game *game, int imgno)
{
	mlx_put_image_to_window(game->mlx, game->win, game->img[IMG_TILE0], TILE_SIZE * game->x, TILE_SIZE * game->y);
	mlx_put_image_to_window(game->mlx, game->win, game->img[imgno], TILE_SIZE * game->state.move_x, TILE_SIZE * game->state.move_y);
	mlx_put_image_to_window(game->mlx, game->win, game->img[game->state.motion], (TILE_SIZE * game->x) - (game->state.mvf * 2), TILE_SIZE * game->y);
}

void	display_right(t_game *game, int imgno)
{
	mlx_put_image_to_window(game->mlx, game->win, game->img[IMG_TILE0], TILE_SIZE * game->x, TILE_SIZE * game->y);
	mlx_put_image_to_window(game->mlx, game->win, game->img[imgno], TILE_SIZE * game->state.move_x, TILE_SIZE * game->state.move_y);
	mlx_put_image_to_window(game->mlx, game->win, game->img[game->state.motion], (TILE_SIZE * game->x) + (game->state.mvf * 2), TILE_SIZE * game->y);
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

void	display_ending(t_game *game)
{
	int x;
	int y;

	x = TILE_SIZE * game->col / 2;
	y = TILE_SIZE * game->row / 2;

	mlx_clear_window(game->mlx, game->win);
	mlx_string_put(game->mlx, game->win, x - 67, y, 0xFFFFFF, "!!!!!! CLEAR !!!!!!");
	mlx_string_put(game->mlx, game->win, x - 67, y + 16, 0xFFFFFF, "Press [esc] to exit");
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

int		loop(t_game *game)
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
// -------------------------------------------------------------------------------------

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
	mlx_hook(game.win, X_EVENT_KEY_EXIT, 0, &close_game, &game);
	mlx_hook(game.win, X_EVENT_KEY_PRESS, 0, &key_press, &game);
	mlx_loop_hook(game.mlx, &loop, &game);
	mlx_loop(game.mlx);
	return (0);
}
