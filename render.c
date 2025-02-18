#include "fractol.h"

int	calculate_mandelbrot(int x, int y, t_fractal *fractal);
int calculate_color(int iter, t_fractal *fractal);
void	put_color_to_pixel(t_data *data, int x, int y, int color);

static int	process_pixel(t_fractal *fractal, int x, int y)
{
	int	iter;
	int	color;

	iter = 0;
	if (fractal->type == MANDELBROT)
		iter = calculate_mandelbrot(x, y, fractal);
	// else if (fractal->type == JULIA)
	// 	iter = calculate_mandelbrot(x, y, fractal);
	color = calculate_color(iter, fractal);
	put_color_to_pixel(&fractal->data, x, y, color);
	return (iter);
}

static void	advance_pixel_coordinates(t_fractal *fractal)
{
	fractal->current_x++;
	fractal->pixels_processed++;
	// fractal->calc_count = fractal->max_iter;

	if (fractal->current_x >= WIDTH)
	{
		fractal->current_x = 0;
		fractal->current_y++;
	}
}

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

int	draw_fractal(t_fractal *fractal)
{
	int	iter;

	while (fractal->pixels_processed < fractal->total_pixels &&
			fractal->calc_count < fractal->iter_chunk)
	{
		if (fractal->current_y >= HEIGHT)
			break ;
		iter = process_pixel(fractal, fractal->current_x, fractal->current_y);
		fractal->calc_count += iter;
		advance_pixel_coordinates(fractal);
	}
	return (fractal->pixels_processed < fractal->total_pixels);
}

int	render_frame(void *param)
{
	t_fractal	*fractal;
	int			continue_rendering;

	fractal = (t_fractal *)param;
	if (fractal->needs_redraw)
	{
		if (fractal->pixels_processed >= fractal->total_pixels)
		{
			fractal->pixels_processed = 0;
			fractal->current_x = 0;
			fractal->current_y = 0;
			fractal->calc_count = 0;
		}
		continue_rendering = draw_fractal(fractal);
		mlx_put_image_to_window(fractal->mlx, fractal->win, fractal->data.img, 0, 0);
		if (!continue_rendering)
		{
			fractal->needs_redraw = 0;
			printf("Partial rendering completed. Pixels processed: %d, Total calculations: %lld\n", fractal->pixels_processed, fractal->calc_count);
		}
	}
	return (0);
}

int	calculate_mandelbrot(int x, int y, t_fractal *fractal)
{
	double		c_real;
	double		c_imag;
	t_complex	z;
	double		temp;
	int			iter;

	z.real = 0.0;
	z.imag = 0.0;
	c_real = map((double)x, 0, WIDTH, -2.0 * fractal->zoom + fractal->offset_x, 2.0 * fractal->zoom + fractal->offset_x);
	c_imag = map((double)y, 0, HEIGHT, -2.0 * fractal->zoom + fractal->offset_y, 2.0 * fractal->zoom + fractal->offset_y);
	iter = 0;
	while (z.real * z.real + z.imag * z.imag <= 4)
	{
		temp = z.real * z.real - z.imag * z.imag + c_real;
		z.imag = 2 * z.real * z.imag + c_imag;
		z.real = temp;
		if (++iter >= fractal->max_iter)
			break ;
	}
	return (iter);
}

