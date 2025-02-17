#include "fractol.h"

int	calculate_mandelbrot(double a, double b);

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

int calculate_color(int iter)
{
	double	t;
	int		r;
	int		g;
	int		b;

	if (iter == MAX_ITER)
        return COLOR_BLACK;
	else
	{
		t = (double)iterations / 100.0;
		r = (int)(9 * (1 - t) * t * t * t * 255);
		g = (int)(15 * (1 - t) * (1 - t) * t * t * 255);
		b = (int)(8.5 * (1 - t) * (1 - t) * (1 - t) * t * 255);
		return (r << 16) | (g << 8) | b; // RGB合成
	}
}

void	draw_fractal(t_fractal *fractal)
{
	int	x;
	int	y;
	int	iter;
	int	color;

	y = 0;
	while (y <= HEIGHT)
	{
		x = 0;
		while (x <= WIDTH)
		{
			if (fractal->type == "MANDELBROT")
				iter = calculate_mandelbrot(x, y, fractal);
			else if (fractal->type == "JULIA")
				iter = calculate_mandelbrot(x, y, fractal);
			color = calculate_color(iter);
			put_color_to_pixel(fractal->data, x, y, color);
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(fractal->mlx, fractal->win, fractal->data.img, 0, 0);
}

// z0 = 0 は固定で、変数cを動かす
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
	c_imag = map((double)y, 0, HEITH,  -1.5 * fractal->zoom + fractal->offset_y, 1.5 * fractal->zoom + fractal->offset_y);
	iter = 0;
	while (z.real * z.real + z.imag * z.imag <= 4)
	{
		temp = z.real * z.real - z.imag * z.imag + c_real;
		z.imag = 2 * z.real * z.imag + c_imag;
		z.real = temp;
		if (iter++ >= MAX_ITER)
			break ;
	}
	return (iter);
}
