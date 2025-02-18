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

// double	ft_atod(const char *str)
// {
// 	long	result;
// 	int		sign;
// 	int		i;

// 	result = 0;
// 	sign = 1;
// 	i = 0;
// 	if (str[i] == '+' || str[i] == '-')
// 	{
// 		if (str[i++] == '-')
// 			sign = -1;
// 	}
// 	if (str[i] == '\0')
// 		return (-1);
// 	while (str[i])
// 	{
// 		if (str[i] < '0' || str[i] > '9')
// 			return (-1);
// 		result = result * 10 + (str[i++] - '0');
// 		if ((sign == 1 && result > INT_MAX)
// 			|| (sign == -1 && -(result) < INT_MIN))
// 			return (-1);
// 	}
// 	return (result * sign);
// }

int	main(int ac, char **av)
{
	t_fractal		fractal;
	t_fractal_type	type;
	t_complex		*julia_c = NULL;

	if (ac < 2)
	{
		ft_putstr_fd(ERROR_MESSAGE, STDERR_FILENO);
		exit(EXIT_FAILURE);
	}
	if (ft_strncmp(av[1], "mandelbrot", ft_strlen(av[1])) == 0)
	{
		type = MANDELBROT;
		if (ac > 2)
			ft_putstr_fd("Warning: Julia parameters are ignored for Mandelbrot set.\n", 2);
	}
	else if (ft_strncmp(av[1], "julia", ft_strlen(av[1])) == 0)
	{
		type = JULIA;
		if (ac == 4)
		{
			// julia_c->real = ft_atod(av[2]); //TODO:
			// julia_c->imag = ft_atod(av[3]);//TODO:
		}
		else
			ft_putstr_fd("Usage for Julia set: ./fractol julia <julia_real> <julia_imag>", 2);
	}
	else
	{
		ft_putstr_fd("Invalid fractal type. Choose 'mandelbrot' or 'julia'.", 2);
		exit(EXIT_FAILURE);
	}
	init_mlx(&fractal);
	init_fractal(&fractal, type, julia_c);
	draw_fractal(&fractal);
	mlx_mouse_hook(fractal.win, handle_zoom, &fractal);
	mlx_key_hook(fractal.win, handle_key, &fractal);

	mlx_loop(fractal.mlx);
	return (0);
}

