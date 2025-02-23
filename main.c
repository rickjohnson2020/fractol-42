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


 int	validate_f(const char *str)
 {
	int		dot_num;

 	if (*str == '+' || *str == '-')
		str++;
 	if (*str++ == '\0')
 		return (-1);
	if (*str == '.')
		return (-1);
 	while (*str)
 	{
		if (*str == '.')
			dot_num++;
		else if (*str < '0' || *str > '9')
 			return (-1);
		str++;
 	}
	if (*(--str) == '.')
		return (-1);
	if (dot_num > 1)
		return (-1);
	return (0);
 }

 double	to_f(const char *str)
 {
 	int		sign;
 	long	i;
	double	f;
	double	decimal_place;

 	result = 0;
 	sign = 1;
 	i = 0;
	f = 0;
 	if (*str == '+' || *str == '-')
 	{
 		if (*str++ == '-')
 			sign = -1;
 	}
 	while (*str && *str != '.')
 		i = i * 10 + (*str++ - '0');
	if (*str == '.')
		str++;
	while (*str)
	{
		decimal_place /= 10;
		f += (*str++ - '0') * decimal_place;
	}
 	return ((i + f) * sign);
 }

double	ft_atof(const char *str)
{
	if (validate_f(str) == -1)
		return (-1);
	return (to_f(str));
}

int	set_fractal_type(char *str, t_fractal_type *type)
{
	int	len;

	len = ft_strlen(str);
	if (ft_strncmp(str, "mandlebrot", len) == 0)
		*type = MANDELBROT;
	else if (ft_strncmp(str, "julia", len) == 0)
		*type = JULIA;
	else
		return (-1);
	return (0);
}

int	parse_args(t_fractal *fractal, int ac, char **av)
{
	if (ac < 2)
		return (-1);
	if (set_fractal_type(av[1], &fractal->type) == -1)
		return (-1);
	if (fractal->type == JULIA)
	{
		if (ac != 4)
			return (-1);
		fractal->julia_c->real = ft_atof(av[2]);
		fractal->julia_c->imag = ft_atof(av[3]);
	}
	else
	{
		if (ac > 2)
			return (-1);
		else
			//TODO: check: `&fractal->julia_c = NULL` work?
			fractal->julia_c = NULL;
	}
	return (0);
}

int	main(int ac, char **av)
{
	t_fractal		fractal;
	t_fractal_type	type;
	t_complex		*julia_c = NULL;

	if (parse_args(fractal, ac, av) == -1)
	{
		print_error();
		return (0);
	}
	//TODO: check if this should be before parse_args
	init_fractal(&fractal);

	init_mlx(&fractal);
	draw_fractal(&fractal);
	mlx_mouse_hook(fractal.win, handle_zoom, &fractal);
	mlx_key_hook(fractal.win, handle_key, &fractal);
	mlx_loop_hook(fractal.mlx, render_frame, &fractal);
	mlx_loop(fractal.mlx);
	return (0);
}
