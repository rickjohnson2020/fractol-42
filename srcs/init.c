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

#include "../includes/fractol.h"

static void	malloc_error(void)
{
	perror("Malloc Error");
	exit(EXIT_FAILURE);
}

void	init_mlx(t_fractal *fractal)
{
	fractal->mlx = mlx_init();
	fractal->data.img = NULL;
	if (fractal->mlx == NULL)
		malloc_error();
	fractal->win = mlx_new_window(fractal->mlx, WIDTH, HEIGHT, "fract'ol");
	if (fractal->win == NULL)
	{
		mlx_destroy_display(fractal->mlx);
		free(fractal->mlx);
		malloc_error();
	}
}

void	init_iter(t_fractal *fractal, int iter)
{
	int	i;

	fractal->pixels_processed = 0;
	if (iter == 0)
	{
		if (fractal->max_iter < INT_MAX / 1.5)
			fractal->max_iter = fractal->max_iter * 1.5;
	}
	else
	{
		fractal->max_iter = iter;
		i = 0;
		while (i < fractal->total_pixels)
		{
			fractal->z_real[i] = 0.0;
			fractal->z_imag[i] = 0.0;
			i++;
		}
	}
}

void	init_fractal(t_fractal *fractal)
{
	fractal->zoom = 200;
	fractal->offset_x = 0.0;
	fractal->offset_y = 0.0;
	fractal->offset_step = 100;
	fractal->total_pixels = HEIGHT * WIDTH;
	fractal->z_real = malloc(sizeof(double) * fractal->total_pixels);
	fractal->z_imag = malloc(sizeof(double) * fractal->total_pixels);
}
