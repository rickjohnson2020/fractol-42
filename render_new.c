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
	iter = 1;
	//TODO: check the condition here.
	if (*dst == 0)
	{
		if (fractal->type == MANDELBROT)
			iter = calculate_mandelbrot(x, y, fractal);
		else if (fractal->type == JULIA)
			iter = calculate_julia(x, y, fractal);
		*(unsigned int *)dst = calculate_color(iter, fractal);
		//*(unsigned int *)dst = hsv2rgb(fractal->color + sqrt(fractal->calc_count[pixel_idx] * 10) * 10, 255, 255);
	}
	return (iter);
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
		while (i < fractal->total_pixels)
		{
			fractal->z_real[i] = 0.0;
			fractal->z_imag[i] = 0.0;
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
		//if all pixels are filled or iter count is reached limit 
		if (pixel_idx >= fractal->total_pixels - 1 || iter > OPE_PER_FLAME)
		{
			mlx_put_image_to_window(fractal->mlx, fractal->win, fractal->data.img, 0, 0);
			if (pixel_idx >= fractal->total_pixels - 1)
				init_iter(fractal, 0);
			return (0);
		}
		//put color to dst
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
	render_frame(fractal);
}

int	calculate_mandelbrot(int x, int y, t_fractal *fractal)
{
	double		temp;
	int			iter;
	double		c_real;
	double		c_imag;
	int			idx;

	idx = y * WIDTH + x;
	c_real = (double)(x - WIDTH / 2) / fractal->zoom - fractal->offset_x;
	c_imag = (double)(y - HEIGHT / 2) / fractal->zoom - fractal->offset_y;
	iter = 0;
	while (fractal->z_real[idx] * fractal->z_real[idx] + fractal->z_imag[idx] * fractal->z_imag[idx] <= 4)
	{
		temp = fractal->z_real[idx] * fractal->z_real[idx] - fractal->z_imag[idx] * fractal->z_imag[idx] + c_real;
		fractal->z_imag[idx] = 2 * fractal->z_real[idx] * fractal->z_imag[idx] + c_imag;
		fractal->z_real[idx] = temp;
		if (++iter >= fractal->max_iter)
			break ;
	}
	fractal->calc_count[idx] += iter;
	return (iter);
}

int	calculate_julia(int x, int y, t_fractal *fractal)
{
	double	temp;
	int		iter;
	double	z_real;
	double	z_imag;
	int		idx;

	idx = y * WIDTH + x;
	z_real = ((double)x - WIDTH / 2.0) / fractal->zoom - fractal->offset_x;
	z_imag = ((double)y - HEIGHT / 2.0) / fractal->zoom - fractal->offset_y;

	iter = 0;
	//if (fractal->calc_count[idx] == 0)
	//{
	//	fractal->z_real[idx] = fractal->julia_c_real;
	//	fractal->z_imag[idx] = fractal->julia_c_imag;
	//}
	//z = &(fractal->z[(y * WIDTH + x) * 2]);
	//while (fractal->z_real[idx] * fractal->z_real[idx] + fractal->z_imag[idx] * fractal->z_imag[idx] <= 4)
	//{
	//	temp = fractal->z_real[idx] * fractal->z_real[idx] - fractal->z_imag[idx] * fractal->z_imag[idx] + fractal->julia_c_real;
	//	fractal->z_imag[idx] = 2 * fractal->z_real[idx] * fractal->z_imag[idx] + fractal->julia_c_imag;
	//	fractal->z_real[idx] = temp;
	//	if (++iter >= fractal->max_iter)
	//		break ;
	//}
	while (z_real * z_real + z_imag * z_imag <= 4)
	{
		temp = z_real * z_real - z_imag * z_imag + fractal->julia_c_real;
		z_imag = 2 * z_real * z_imag + fractal->julia_c_imag;
		z_real = temp;
		if (++iter >= fractal->max_iter)
			break ;
	}
	fractal->calc_count[idx] += iter;
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

void	to_z(int x, int y, double z[], t_fractal *fractal)
{
	z[0] = (double)(x - WIDTH / 2) / fractal->zoom - fractal->offset_x;
	z[1] = (double)(y - HEIGHT / 2) / fractal->zoom - fractal->offset_y;
}