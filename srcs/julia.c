/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   julia.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: riyano <riyano@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 13:26:08 by riyano            #+#    #+#             */
/*   Updated: 2025/02/26 13:27:25 by riyano           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

int	calculate_julia(int x, int y, t_fractal *fractal)
{
	double	temp;
	int		iter;
	double	z_real;
	double	z_imag;
	int		idx;

	idx = y * WIDTH + x;
	z_real = (double)(x - WIDTH / 2.0) / fractal->zoom - fractal->offset_x;
	z_imag = (double)(y - HEIGHT / 2.0) / fractal->zoom - fractal->offset_y;
	iter = 0;
	while (z_real * z_real + z_imag * z_imag <= 4)
	{
		temp = z_real * z_real - z_imag * z_imag + fractal->julia_c_real;
		z_imag = 2 * z_real * z_imag + fractal->julia_c_imag;
		z_real = temp;
		if (++iter >= fractal->max_iter)
			break ;
	}
	//fractal->calc_count[idx] += iter;
	return (iter);
}
