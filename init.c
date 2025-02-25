/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: riyano <riyano@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 17:24:53 by riyano            #+#    #+#             */
/*   Updated: 2025/02/12 17:43:06 by riyano           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./fractol.h"

static void	malloc_error(void)
{
	perror("Malloc Error");
	exit(EXIT_FAILURE);
}

void	init_mlx(t_fractal *fractal)
{
	fractal->mlx = mlx_init();
	if (fractal->mlx == NULL)
		malloc_error();
	fractal->win = mlx_new_window(fractal->mlx, WIDTH, HEIGHT, "fract'ol");
	if (fractal->win == NULL)
	{
		mlx_destroy_display(fractal->mlx);
		free(fractal->mlx);
		malloc_error();
	}
	fractal->data.img = mlx_new_image(fractal->mlx, WIDTH, HEIGHT);
	if (fractal->data.img == NULL)
	{
		mlx_destroy_window(fractal->mlx, fractal->win);
		mlx_destroy_display(fractal->mlx);
		free(fractal->mlx);
		malloc_error();
	}
	fractal->data.addr = mlx_get_data_addr(fractal->data.img, &fractal->data.bits_per_pixel, &fractal->data.line_len, &fractal->data.endian);
}

void	init_fractal(t_fractal *fractal)
{
	//fractal->color = 120;
	fractal->zoom = 200;
	fractal->offset_x = 0.0;
	fractal->offset_y = 0.0;
	fractal->offset_step = 100;
	fractal->max_iter = INIT_ITER;
	fractal->pixels_processed = 0;
	fractal->calc_count = 0;
	fractal->total_pixels = HEIGHT * WIDTH;
	fractal->z_real = malloc(sizeof(double) * fractal->total_pixels);
	fractal->z_imag = malloc(sizeof(double) * fractal->total_pixels);
	fractal->calc_count = malloc(sizeof(int) * fractal->total_pixels);

	//TODO: this can be the problem	
	init_iter(fractal, INIT_ITER);
}
