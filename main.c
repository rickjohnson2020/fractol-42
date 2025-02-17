/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: riyano <riyano@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 13:21:36 by riyano            #+#    #+#             */
/*   Updated: 2025/02/12 17:36:23 by riyano           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./fractol.h"

int	main(int ac, char **av)
{
	t_fractal		fractal;
	t_fractal_type	type;
	t_complex		julia_c = NULL;

	if (ac < 2)
	{
		ft_putstr_fd(ERROR_MESSAGE, STDERR_FILENO);
		exit(EXIT_FAILURE);
	}
	if (ft_strcmp(av[1], "mandelbrot") == 0)
	{
		type = MANDELBROT;
		if (ac > 2)
			ft_putstr_fd("Warning: Julia parameters are ignored for Mandelbrot set.\n", 2);
	}
	else if (ft_strcmp(av[1], "julia") == 0)
	{
		type = JULIA;
		if (ac == 4)
		{
			julia_c.real = ft_atod(av[3]); //TODO:
			julia_c.imag = ft_atod(av[4]);//TODO:
		}
		else
			ft_putstr_fd("Usage for Julia set: ./fractol julia <julia_real> <julia_imag>");
	}
	else
	{
		ft_putstr_fd("Invalid fractal type. Choose 'mandelbrot' or 'julia'.");
		exit(EXIT_FAILURE);
	}
	init_mlx(&fractal);
	init_fractal(&fractal, type, julia_c);
	draw_fractal(&fractal);
	//TODO:
	mlx_mouse_hook(fractal.win, handle_zoom, &fractal);
    mlx_key_hook(fractal.win, handle_key, &fractal);

	mlx_loop(fractal.mlx);
	return (0);
}
