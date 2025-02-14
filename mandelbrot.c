#include "fractol.h"

int	calculate_mandelbrot(double a, double b);

void	put_color_to_pixel(t_img *img, int x, int y, int color)
{
	char	*dst;

	dst = img->addr + (y * img->line_len + x * (img->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

double	map(double to_scale, double old_min, double old_max, double new_min, double new_max)
{
	return ((new_max - new_min) * (to_scale - old_min) / (old_max - old_min) + new_min);
}

void	draw_fractal(t_fractal *fractal)
{
	int	x;
	int	y;
	int	color;

	y = 0;
	while (y <= HEIGHT)
	{
		x = 0;
		while (x <= WIDTH)
		{
			color = calculate_mandelbrot(map(x, 0, WIDTH, -2, 2), map(y, 0, HEIGHT, -2, 2));
			put_color_to_pixel(&fractal->img, x, y, color);
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(fractal->mlx, fractal->win, fractal->img.img, 0, 0);
}

int	calculate_mandelbrot(t_fractal *fractal, t_complex *complex)
{
	t_complex	z;
	t_complex	c;
	double	temp;
	int		count;

	
	z.real = 0.0;
	z.imag = 0.0;

	//c.real = map(complex->real, 0, WIDTH, -2, 2);

	count = 0;
	while (z.real * z.real + z.imag * z.imag <= 4)
	{
		temp = z.real * z.real - z.imag * z.imag + complex->real;
		z.imag = 2 * z.real * z.imag + complex->imag;
		z.real = temp;
		if (count++ >= 500)
			break ;
	}
	if (count >= 500)
	{
		//TODO: set color to black
		//put_color_to_pixel(fractal->img, x, y, color: black);
		//printf("djfi");
		return (0x000000);
	}
	else
	{
		//TODO: set color to white
		//put_color_to_pixel(fractal->img, x, y, color: white);
		//return color depending on how many iterations
		return (map(count, 0, 500, 0, 0x00FFFF));
		//return (0x00F0FF);
	}
}


// int	calculate_mandelbrot(double a, double b)
// {
// 	double	za;
// 	double	zb;
// 	double	temp;
// 	int		count;

// 	za = a;
// 	zb = b;
// 	count = 0;
// 	while (za * za + zb * zb <= 4)
// 	{
// 		temp = za * za - zb * zb + a;
// 		zb = 2 * za * zb + b;
// 		za = temp;
// 		if (count++ >= 500)
// 			break ;
// 	}
// 	if (count >= 500)
// 	{
// 		//TODO: set color to black
// 		//put_color_to_pixel(fractal->img, x, y, color: black);
// 		//printf("djfi");
// 		return (0x000000);
// 	}
// 	else
// 	{
// 		//TODO: set color to white
// 		//put_color_to_pixel(fractal->img, x, y, color: white);
// 		//return color depending on how many iterations
// 		return (map(count, 0, 500, 0, 0x00FFFF));
// 		//return (0x00F0FF);
// 	}
// }