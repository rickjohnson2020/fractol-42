/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: riyano <riyano@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 15:39:43 by riyano            #+#    #+#             */
/*   Updated: 2025/02/26 15:40:21 by riyano           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

int	handle_zoom(int button, int x, int y, void *param)
{
	t_fractal	*fractal;
	double		mouse_real;
	double		mouse_imag;
	//double		new_zoom;
	
	fractal = (t_fractal *)param;
	mouse_real = map((double)x, WIDTH, -2.0 * fractal->zoom + fractal->offset_x, 2.0 * fractal->zoom + fractal->offset_x);
	mouse_imag = map((double)y, HEIGHT, -2.0 * fractal->zoom + fractal->offset_y, 2.0 * fractal->zoom + fractal->offset_y);
	if (button == MOUSE_UP)
		fractal->zoom *= 0.9;
	else if (button == MOUSE_DOWN)
		fractal->zoom *= 1.1;
	//else
	//	new_zoom = fractal->zoom;
	//fractal->zoom = new_zoom;
	draw_fractal(fractal);
	return (0);
}

int	close_fractal(void *param)
{
	t_fractal	*fractal;

	fractal = (t_fractal *)param;
	free(fractal->calc_count);
	free(fractal->z_real);
	free(fractal->z_imag);
	mlx_destroy_window(fractal->mlx, fractal->win);
	mlx_destroy_image(fractal->mlx, fractal->data.img);
	mlx_loop_end(fractal->mlx);
	mlx_destroy_display(fractal->mlx);
	free(fractal->mlx);
	exit(0);
}

int	handle_key(int keycode, void *param)
{
	t_fractal	*fractal;

	fractal = (t_fractal *)param;
	if (keycode == KEY_ESC)
		close_fractal(param);
	else if (keycode == KEY_LEFT)
		fractal->offset_x += fractal->offset_step / fractal->zoom;
	else if (keycode == KEY_RIGHT)
		fractal->offset_x -= fractal->offset_step / fractal->zoom;
	else if (keycode == KEY_UP)
		fractal->offset_y += fractal->offset_step / fractal->zoom;
	else if (keycode == KEY_DOWN)
		fractal->offset_y -= fractal->offset_step / fractal->zoom;
	draw_fractal(fractal);
	return (0);
}
