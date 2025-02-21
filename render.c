#include "fractol.h"

int	calculate_mandelbrot(int x, int y, t_fractal *fractal);
int calculate_color(int iter, t_fractal *fractal);
void	put_color_to_pixel(t_data *data, int x, int y, int color);
int	hsv2rgb(int h, int s, int v);
int	calculate_julia(int x, int y, t_fractal *fractal);

static char	*get_pixel(int x, int y, t_data *data)
{
	return (data->addr + (y * data->line_len + x * (data->bits_per_pixel / 8)));
}

static int	calc_pixel(int pixel_idx, t_fractal *fractal)
{
	char	*dst;
	int		x;
	int		y;
	int		iter;

	x = pixel_idx % WIDTH;
	y = pixel_idx / WIDTH;
	dst = get_pixel(x, y, &fractal->data);
	//TODO: check the condition here.
	if (*dst == 0)
	{
		if (fractal->type == MANDELBROT)
			iter = calculate_mandelbrot(x, y, fractal);
		else if (fractal->type == JULIA)
			iter = calculate_julia(x, y, fractal);
		else
			iter = 0;
		*(unsigned int *)dst = calculate_color(iter, fractal);
		//*(unsigned int *)dst = hsv2rgb(fractal->color + sqrt(fractal->calc_count[pixel_idx] * 10) * 10, 255, 255);
		return (iter);
	}
	return (1);
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
	int	pixel_idx;

	iter = 0;
	pixel_idx = fractal->pixels_processed;
	while (pixel_idx < fractal->total_pixels)
	{
		if (pixel_idx >= fractal->total_pixels - 1 || iter > OPE_PER_FLAME)
		{
			mlx_put_image_to_window(fractal->mlx, fractal->win, fractal->data.img, 0, 0);
			if (pixel_idx >= fractal->total_pixels - 1)
				init_iter(fractal, 0);
			return (0);
		}
		iter += calc_pixel(17 * pixel_idx % fractal->total_pixels, fractal);
		fractal->pixels_processed = pixel_idx;
		pixel_idx++;
	}
	return (0);
}

void	draw_fractal(t_fractal *fractal)
{
	t_data	*data;

	init_iter(fractal, INIT_ITER);
	data = &fractal->data;
	if (data->img)
		mlx_destroy_image(fractal->mlx, fractal->data.img);
	data->img = mlx_new_image(fractal->mlx, WIDTH, HEIGHT);
	data->addr = mlx_get_data_addr(fractal->data.img, &fractal->data.bits_per_pixel, &fractal->data.line_len, &fractal->data.endian);
	//ft_memset(data->addr, 0, WIDTH * HEIGHT * (data->bits_per_pixel / 8));
	render_frame(fractal);
}

void	to_z(int x, int y, double z[], t_fractal *fractal)
{
	z[0] = (double)(x - WIDTH / 2) / fractal->zoom - fractal->offset_x;
	z[1] = (double)(y - HEIGHT / 2) / fractal->zoom - fractal->offset_y;
}

int	calculate_mandelbrot(int x, int y, t_fractal *fractal)
{
	//double		c_real;
	//double		c_imag;
	double		*z;
	double		temp;
	int			iter;
	double		c[2];

	to_z(x, y, c, fractal);
	iter = 0;
	z = &(fractal->z[(y * WIDTH + x) * 2]);
	while (z[0] * z[0] + z[1] * z[1] <= 4)
	{
		temp = z[0] * z[0] - z[1] * z[1] + c[0];
		z[1] = 2 * z[0] * z[1] + c[1];
		z[0] = temp;
		if (++iter >= fractal->max_iter)
			break ;
	}
	fractal->calc_count[y * WIDTH + x] += iter;
	return (iter);
}

int	trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

int	hsv2rgb(int h, int s, int v)
{
	int	max;
	int	min;

	h = h % 360;
	max = v;
	min = max - (s * max / 255);
	if (0 <= h && h < 60)
		return (trgb(0, max, h * (max - min) / 60 + min, min));
	else if (60 <= h && h < 120)
		return (trgb(0, (120 - h) * (max - min) / 60, max, min));
	else if (120 <= h && h < 180)
		return (trgb(0, min, max, (h - 120) * (max - min) / 60));
	else if (180 <= h && h < 240)
		return (trgb(0, min, (240 - h) * (max - min) / 60, max));
	else if (240 <= h && h < 300)
		return (trgb(0, (h - 240) * (max - min) / 60, min, max));
	else if (300 <= h && h <= 360)
		return (trgb(0, max, min, (360 - h) * (max - min) / 60));
	else
		return (0);
}

int	calculate_julia(int x, int y, t_fractal *fractal)
{
	double	*z;
	double	temp;
	int		iter;
	double	c[2];
	//double	z_init[2];

	to_z(x, y, c, fractal);
	iter = 0;
	if (fractal->calc_count[y * WIDTH + x] == 0)
	{
		fractal->z[(y * WIDTH + x) * 2 + 0] = c[0];
		fractal->z[(y * WIDTH + x) * 2 + 1] = c[1];
	}
	z = &(fractal->z[(y * WIDTH + x) * 2]);
	while (z[0] * z[0] + z[1] * z[1] <= 4)
	{
		temp = z[0] * z[0] - z[1] * z[1] + fractal->c[0];
		z[1] = 2 * z[0] * z[1] + fractal->c[1];
		z[0] = temp;
		if (++iter >= fractal->max_iter)
			break ;
	}
	fractal->calc_count[y * WIDTH + x] += iter;
	return (iter);
}