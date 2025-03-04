/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: riyano <riyano@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 13:21:36 by riyano            #+#    #+#             */
/*   Updated: 2025/02/26 16:04:22 by riyano           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

static void	print_error(void)
{
	ft_putstr_fd("Usage: ./fractol mandlebrot | \
./fractol julia <real number> <imaginary number>\n", 2);
}

int	main(int ac, char **av)
{
	t_fractal	fractal;

	if (parse_args(&fractal, ac, av) == -1)
	{
		print_error();
		return (0);
	}
	init_fractal(&fractal);
	init_mlx(&fractal);
	draw_fractal(&fractal);
	mlx_hook(fractal.win, WINDOW_CLOSE, 1L << 2, close_fractal, &fractal);
	mlx_mouse_hook(fractal.win, handle_zoom, &fractal);
	mlx_key_hook(fractal.win, handle_key, &fractal);
	mlx_loop_hook(fractal.mlx, render_frame, &fractal);
	mlx_loop(fractal.mlx);
	return (0);
}
