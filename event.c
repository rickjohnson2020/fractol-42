#include "./fractol.h"

int	handle_zoom(int button, int x, int y, void *param)
{
	t_fractal	*fractal;

	x = 0;//TODO:
	y = 0;//TODO:
	fractal = (t_fractal *)param;
	if (button == MOUSE_DOWN)
		fractal->zoom *= 0.9;
	else if (button == MOUSE_UP)
		fractal->zoom *= 1.1;
	draw_fractal(fractal);
	return (0);
}

int	handle_key(int keycode, void *param)
{
	t_fractal	*fractal;

	fractal = (t_fractal *)param;
	if (keycode == KEY_ESC)
	{
		mlx_destroy_window(fractal->mlx, fractal->win);
		mlx_destroy_image(fractal->mlx, fractal->data.img);
		mlx_loop_end(fractal->mlx);
		exit(0);
	}
	else if (keycode == KEY_LEFT)
	{
		fractal->offset_x -= fractal->offset_step * fractal->zoom;
		draw_fractal(fractal);
	}
	else if (keycode == KEY_RIGHT)
	{
		fractal->offset_x += fractal->offset_step * fractal->zoom;
		draw_fractal(fractal);
	}
	else if (keycode == KEY_UP)
	{
		fractal->offset_y -= fractal->offset_step * fractal->zoom;
		draw_fractal(fractal);
	}
	else if (keycode == KEY_DOWN)
	{
		fractal->offset_y += fractal->offset_step * fractal->zoom;
		draw_fractal(fractal);
	}
	return (0);
}
