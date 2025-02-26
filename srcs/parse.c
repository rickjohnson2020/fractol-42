/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: riyano <riyano@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 14:30:25 by riyano            #+#    #+#             */
/*   Updated: 2025/02/26 14:39:20 by riyano           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

static int	validate_f(const char *str)
{
	int		dot_num;

	if (*str == '+' || *str == '-')
		str++;
	if (*str == '\0')
		return (-1);
	if (*str == '.')
		return (-1);
	dot_num = 0;
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

static double	to_f(const char *str, double *d)
{
	int		sign;
	long	i;
	double	f;
	double	decimal_place;

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
	decimal_place = 1;
	while (*str)
	{
		decimal_place /= 10;
		f += (*str++ - '0') * decimal_place;
	}
	*d = (i + f) * sign;
	return (0);
}

static double	ft_atof(const char *str, double *d)
{
	if (validate_f(str) == -1)
		return (-1);
	return (to_f(str, d));
}

static int	set_fractal_type(char *str, t_fractal_type *type)
{
	int	len;

	len = ft_strlen(str);
	if (ft_strncmp(str, "mandelbrot", len) == 0)
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
		if (ft_atof(av[2], &fractal->julia_c_real) == -1)
			return (-1);
		if (ft_atof(av[3], &fractal->julia_c_imag) == -1)
			return (-1);
	}
	else
	{
		if (ac > 2)
			return (-1);
	}
	return (0);
}
