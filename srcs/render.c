/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_new.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: riyano <riyano@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 13:39:55 by riyano            #+#    #+#             */
/*   Updated: 2025/02/26 13:52:32 by riyano           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

// Returns a pointer to the pixel at coordinates (x, y) in the image buffer.
// It calculates the memory offset by multiplying the row number (y)
// by the number of bytes per row (line_len)
// and adding the column offset (x times the number of bytes per pixel).
static char	*get_pixel(int x, int y, t_data *data)
{
	return (data->addr + (y * data->line_len + x * (data->bits_per_pixel / 8)));
}

// Computes a simple color based on how many iterations were performed.
// If the pixel reached the maximum number of iterations
// (meaning it likely did not escape),
// it returns black. Otherwise, it calculates a normalized value 't'
// (between 0 and 1) by dividing iter by the maximum iteration count.
// Then it creates a gradient:
// - The red component increases with t.
// - The green component decreases with t.
// - The blue component is set to a constant value (128).
// Finally, the individual RGB values are combined into one 24-bit color value.
static int	calculate_color(int iter, t_fractal *fractal)
{
	double	t;
	int		r;
	int		g;
	int		b;

	if (iter == fractal->max_iter)
		return (COLOR_BLACK);
	else
	{
		t = (double)iter / fractal->max_iter;
		r = (int)(255 * t);
		g = (int)(255 * (1 - t));
		b = 128;
		return ((r << 16) | (g << 8) | b);
	}
}

// Calculates and sets the color for a single pixel identified by 'pixel_idx'.
// It first converts the one-dimensional pixel index
// into two-dimensional coordinates (x, y).
// Then, it obtains a pointer 'dst' to the pixel's location
// in the image buffer using get_pixel().
// If the pixel has not been computed yet, 
// it calls the appropriate fractal calculation function
// to compute the iteration count for that pixel.
// And it calls calculate_color() to determine the pixel's color
// and writes that color into the image buffer at the location pointed by dst.
// Finally, it returns the iteration count for that pixel.
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
	if (*dst == 0)
	{
		if (fractal->type == MANDELBROT)
			iter = calculate_mandelbrot(x, y, fractal);
		else if (fractal->type == JULIA)
			iter = calculate_julia(x, y, fractal);
		*(unsigned int *)dst = calculate_color(iter, fractal);
	}
	return (iter);
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
			mlx_put_image_to_window(
				fractal->mlx, fractal->win, fractal->data.img, 0, 0);
			if (pixel_idx >= fractal->total_pixels - 1)
				init_iter(fractal, 0);
			return (0);
		}
		iter += calc_pixel(11 * pixel_idx % fractal->total_pixels, fractal);
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
	data->addr = mlx_get_data_addr(fractal->data.img,
			&fractal->data.bits_per_pixel,
			&fractal->data.line_len,
			&fractal->data.endian);
	render_frame(fractal);
}
