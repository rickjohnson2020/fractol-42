/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: riyano <riyano@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 13:33:57 by riyano            #+#    #+#             */
/*   Updated: 2025/02/12 17:34:58 by riyano           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include <stdio.h> //TODO: delete
# include <stdlib.h>
# include <unistd.h>
# include <math.h>
# include "./minilibx-linux/mlx.h"
# include "./libft/libft.h"

# define ERROR_MESSAGE "Usage: \"./fractol mandelbrot\" or \"./fractol julia <value_1> <value_2>\""

# define WIDTH 800
# define HEIGHT 800

typedef struct	s_complex
{
	double	real;
	double	imag;
}	t_complex;

typedef struct	s_img
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		endian;
	int		line_len;
}	t_img;

typedef struct	s_fractal
{
	char	*name;
	void	*mlx;
	void	*win;
	t_img	img;
	long	za;
	long	zb;
	long	ca;
	long	cb;
}	t_fractal;

void	init_fractal(t_fractal *fractal);
void	draw_fractal(t_fractal *fractal);

#endif