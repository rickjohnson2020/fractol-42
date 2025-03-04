/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mandelbrot.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: riyano <riyano@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 13:25:02 by riyano            #+#    #+#             */
/*   Updated: 2025/02/26 13:25:58 by riyano           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

// Computes the number of iterations for the Mandelbrot formula
// at a given pixel (x, y). It uses the stored state in the fractal structure,
// where each pixel's current complex value is maintained in z_real and z_imag.
// Maps the pixel (x, y) to a complex constant c, then repeatedly applies
// the Mandelbrot formula: z = z² + c, until the magnitude of z exceeds 2
// (|z|² > 4) or the maximum number of iterations is reached.
// The number of iterations is then returned.
int	calculate_mandelbrot(int x, int y, t_fractal *fractal)
{
	double		temp;
	int			iter;
	double		c_real;
	double		c_imag;
	int			idx;

	idx = y * WIDTH + x;
	c_real = (double)(x - WIDTH / 2) / fractal->zoom + fractal->offset_x;
	c_imag = (double)(y - HEIGHT / 2) / fractal->zoom + fractal->offset_y;
	iter = 0;
	while (fractal->z_real[idx] * fractal->z_real[idx]
		+ fractal->z_imag[idx] * fractal->z_imag[idx] <= 4)
	{
		temp = fractal->z_real[idx] * fractal->z_real[idx]
			- fractal->z_imag[idx] * fractal->z_imag[idx] + c_real;
		fractal->z_imag[idx]
			= 2 * fractal->z_real[idx] * fractal->z_imag[idx] + c_imag;
		fractal->z_real[idx] = temp;
		if (++iter >= fractal->max_iter)
			break ;
	}
	return (iter);
}
