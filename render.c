#include "fractol.h"

int	calculate_mandelbrot(int x, int y, t_fractal *fractal);
int calculate_color(int iter, t_fractal *fractal);
void	put_color_to_pixel(t_data *data, int x, int y, int color);

static char	*get_pixel(int x, int y, t_data *data)
{
	return (data->addr + (y * data->line_len + x * (data->bits_per_pixel / 8)));
}

static int	calc_pixel(int n, t_fractal *fractal)
{
	char	*dst;
	int		x;
	int		y;
	int		iter;

	iter = 0;
	x = n % WIDTH;
	y = n / WIDTH;
	dst = get_pixel(x, y, &fractal->data);
	if (*dst == 0)
	{
		if (fractal->type == MANDELBROT)
			iter = calculate_mandelbrot(x, y, fractal);
		else
			//TODO: calculate_julia();
		if (iter >= 0)
		{
			*(unsigned int *)dst = calculate_color(iter, fractal);
			return (iter);
		}
		else
		{
			*(unsigned int *)dst = 0;
			return (fractal->max_iter);
		}
	
	}
	return (-1);
}

// static int	process_pixel(t_fractal *fractal, int x, int y)
// {
// 	int	iter;
// 	int	color;

// 	iter = 0;
// 	if (fractal->type == MANDELBROT)
// 		iter = calculate_mandelbrot(x, y, fractal);
// 	// else if (fractal->type == JULIA)
// 	// 	iter = calculate_mandelbrot(x, y, fractal);
// 	color = calculate_color(iter, fractal);
// 	put_color_to_pixel(&fractal->data, x, y, color);
// 	return (iter);
// }

// static void	advance_pixel_coordinates(t_fractal *fractal)
// {
// 	fractal->current_x++;
// 	fractal->pixels_processed++;
// 	// fractal->calc_count = fractal->max_iter;

// 	if (fractal->current_x >= WIDTH)
// 	{
// 		fractal->current_x = 0;
// 		fractal->current_y++;
// 	}
// }

void	put_color_to_pixel(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_len + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

double	map(double to_scale, double old_min, double old_max, double new_min, double new_max)
{
	return ((new_max - new_min) * (to_scale - old_min) / (old_max - old_min) + new_min);
}

int calculate_color(int iter, t_fractal *fractal)
{
	double	t;
	int		r;
	int		g;
	int		b;

	if (iter == fractal->max_iter)
		return COLOR_BLACK;
	else
	{
		t = (double)iter / 100.0;
		r = (int)(9 * (1 - t) * t * t * t * 255);
		g = (int)(15 * (1 - t) * (1 - t) * t * t * 255);
		b = (int)(8.5 * (1 - t) * (1 - t) * (1 - t) * t * 255);
		return (r << 16) | (g << 8) | b;
	}
}

void	init_iter(t_fractal *fractal, int iter)
{
	int	i;

	fractal->pixels_processed = 0;
	if (iter)
	{
		//TODO: check
		fractal->max_iter = iter;
		i = 0;
		while (i < fractal->total_pixels * 2)
		{
			fractal->z[i] = 0.0;
			i++;
		}
		i = 0;
		while (i < fractal->total_pixels)
		{
			fractal->calc_count[i] = 0;
			i++;
		}
	}
	else
	{
		if (fractal->max_iter < INT_MAX / 1.5)
			fractal->max_iter = fractal->max_iter * 1.5;
	}
}

int	render_frame(t_fractal *fractal)
{
	int	iter;
	int	n;

	iter = 0;
	n = fractal->pixels_processed;
	while (n < fractal->total_pixels)
	{
		if (n >= fractal->total_pixels - 1 || iter > OPE_PER_FLAME)
		{
			mlx_put_image_to_window(fractal->mlx, fractal->win, fractal->data.img, 0, 0);
			if (n >= fractal->total_pixels)
				init_iter(fractal, 0);
			return (0);
		}
		iter += calc_pixel(17 * n % (WIDTH * HEIGHT), fractal);
		//fractal->current_x++;
		fractal->pixels_processed = n;
		n++;
	}
	return (0);
}

void	draw_fractal(t_fractal *fractal)
{
	t_data	*data;

	init_iter(fractal, INIT_ITER);
	data = fractal->data.img;
	if (data->img)
		mlx_destroy_image(fractal->mlx, fractal->data.img);
	data->img = mlx_new_image(fractal->mlx, WIDTH, HEIGHT);
	data->addr = mlx_get_data_addr(fractal->data.img, &fractal->data.bits_per_pixel, &fractal->data.line_len, &fractal->data.endian);
	render_frame(fractal);
}

int	calculate_mandelbrot(int x, int y, t_fractal *fractal)
{
	double		c_real;
	double		c_imag;
	double		*z;
	double		temp;
	int			iter;
	int			idx;

	idx = (y * WIDTH + x) * 2;
	z = &(fractal->z[idx]);

	c_real = map((double)x, 0, WIDTH, -2.0 * fractal->zoom + fractal->offset_x, 2.0 * fractal->zoom + fractal->offset_x);
	c_imag = map((double)y, 0, HEIGHT, -2.0 * fractal->zoom + fractal->offset_y, 2.0 * fractal->zoom + fractal->offset_y);
	iter = 0;
	while (z[0] * z[0] + z[1] * z[1] < 4 && iter < fractal->max_iter)
	{
		temp = z[0] * z[0] - z[1] * z[1] + c_real;
		z[1] = 2 * z[0] * z[1] + c_imag;
		z[0] = temp;
		iter++;
	}
	fractal->calc_count[y * WIDTH + x] += iter;
	//if iter is reached to max, return -1 as it is not diverged
	if (iter == fractal->max_iter)
		return (-1);
	return (iter);
}

