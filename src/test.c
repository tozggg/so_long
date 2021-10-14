#include "../mlx/mlx.h"
#include <stdio.h>


#define TILE_SIZE 64

int		main(void)
{
	printf("zzzz\n");
	int i = 64;

	void *mlx_ptr = mlx_init();
	void *win_ptr = mlx_new_window(mlx_ptr, TILE_SIZE*10, TILE_SIZE*10, "so_long");
	void *img_ptr0 = mlx_xpm_file_to_image(mlx_ptr, "../image/tile0.xpm", &i, &i);
	void *img_ptr1 = mlx_xpm_file_to_image(mlx_ptr, "../image/tile1.xpm", &i, &i);

	int x = 0;
	int y = 0;
	while (y < 10)
	{
		x = 0;
		while (x < 10)
		{
			mlx_put_image_to_window(mlx_ptr, win_ptr, img_ptr0, TILE_SIZE*x, TILE_SIZE*y);
			++x;
		}
		++y;
	}
	x=0, y=0;
	while (y < 10)
	{
		x = 0;
		while (x < 10)
		{
			if (x == 0 || x == 9 || y == 0 || y == 9)
				mlx_put_image_to_window(mlx_ptr, win_ptr, img_ptr1, TILE_SIZE*x, TILE_SIZE*y);
			if (x == 3 && y == 7)
				mlx_put_image_to_window(mlx_ptr, win_ptr, img_ptr1, TILE_SIZE*x, TILE_SIZE*y);
			if (x == 1 && y == 2)
				mlx_put_image_to_window(mlx_ptr, win_ptr, img_ptr1, TILE_SIZE*x, TILE_SIZE*y);
			if (x == 6 && y == 6)
				mlx_put_image_to_window(mlx_ptr, win_ptr, img_ptr1, TILE_SIZE*x, TILE_SIZE*y);
			if (x == 5 && y == 4)
				mlx_put_image_to_window(mlx_ptr, win_ptr, img_ptr1, TILE_SIZE*x, TILE_SIZE*y);	
			++x;
		}
		++y;
	}
	mlx_loop(mlx_ptr);
	return (0);
}
