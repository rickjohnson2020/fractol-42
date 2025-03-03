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

static char	*get_pixel(int x, int y, t_data *data)
{
	return (data->addr + (y * data->line_len + x * (data->bits_per_pixel / 8)));
}

static int	calculate_color(int iter, t_fractal *fractal)
{
	int	r;
	int	g;
	int	b;

	if (iter == fractal->max_iter)
		return (COLOR_BLACK);
	else
	{
		double t = (double)iter / fractal->max_iter;
		r = (int)(255 * t);
		g = (int)(255 * (1 - t));
		b = 128;
		return ((r << 16) | (g << 8) | b);
	}
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
		//if all pixels are filled or iter count is reached limit 
		if (pixel_idx >= fractal->total_pixels - 1 || iter > OPE_PER_FLAME)
		{
			mlx_put_image_to_window(
				fractal->mlx, fractal->win, fractal->data.img, 0, 0);
			if (pixel_idx >= fractal->total_pixels - 1)
				init_iter(fractal, 0);
			return (0);
		}
		//put color to dst
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