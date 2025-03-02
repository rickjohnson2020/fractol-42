/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_new.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: riyano <riyano@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 13:39:55 by riyano            #+#    #+#             */
/*   Updated: 2025/02/26 13:52:32 by riyano           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

static char	*get_pixel(int x, int y, t_data *data)
{
	return (data->addr + (y * data->line_len + x * (data->bits_per_pixel / 8)));
}

// static int	calculate_color(int iter, int pixel_idx ,t_fractal *fractal)
// {
// 	double	t;
// 	int		r;
// 	int		g;
// 	int		b;

// 	if (iter == fractal->max_iter)
// 		return (COLOR_BLACK);
// 	else
// 	{
// 		t = (double)iter / 100.0;
// 		r = (int)(9 * (1 - t) * t * t * t * 255);
// 		g = (int)(15 * (1 - t) * (1 - t) * t * t * 255);
// 		b = (int)(8.5 * (1 - t) * (1 - t) * (1 - t) * t * 255);
// 		return ((r << 16) | (g << 8) | b);
// 	}
// }

static int calculate_color(int iter, int pixel_index, t_fractal *fractal)
{
	double t, hue_offset;
	int r, g, b;
	double cc;

	// もし反復回数が最大まで到達していたら、そのピクセルは黒とする
	if (iter == fractal->max_iter)
		return COLOR_BLACK;

	// 基本の t は、反復回数を最大反復回数で割った値（0～1の範囲）
	t = (double)iter / fractal->max_iter;

	// calc_count[pixel_index] はそのピクセルに対してこれまでに計算した反復回数の合計
	cc = fractal->calc_count[pixel_index];

	// calc_count の値に応じて、色相のオフセットを計算する
	// ここでは、sqrt(cc) * 10 をオフセット（度）として計算し、360度で割って0～1に正規化
	hue_offset = sqrt(cc) * 10.0;
	t = fmod(t + hue_offset / 360.0, 1.0);  // 0～1の範囲に保つ

	// t の値を元に、RGB の各成分を決める（これは一例の多項式によるグラデーション）
	r = (int)(9 * (1 - t) * t * t * t * 255);
	g = (int)(15 * (1 - t) * (1 - t) * t * t * 255);
	b = (int)(8.5 * (1 - t) * (1 - t) * (1 - t) * t * 255);

	return ((r << 16) | (g << 8) | b);
}


static int	calc_pixel(int pixel_idx, t_fractal *fractal)
{
	char	*dst;
	int		x;
	int		y;
	int		iter;

	x = pixel_idx % WIDTH;
	y = pixel_idx / WIDTH;
	dst = get_pixel(x, y, &fractal->data);
	iter = 1;
	//TODO: check the condition here.
	if (*dst == 0)
	{
		if (fractal->type == MANDELBROT)
			iter = calculate_mandelbrot(x, y, fractal);
		else if (fractal->type == JULIA)
			iter = calculate_julia(x, y, fractal);
		*(unsigned int *)dst = calculate_color(iter, pixel_idx,fractal);
	}
	return (iter);
}

int	render_frame(t_fractal *fractal)
{
	int	iter;
	int	pixel_idx;

	iter = 0;
	pixel_idx = fractal->pixels_processed;
	while (pixel_idx < fractal->total_pixels)
	{
		//if all pixels are filled or iter count is reached limit 
		if (pixel_idx >= fractal->total_pixels - 1 || iter > OPE_PER_FLAME)
		{
			mlx_put_image_to_window(
				fractal->mlx, fractal->win, fractal->data.img, 0, 0);
			if (pixel_idx >= fractal->total_pixels - 1)
				init_iter(fractal, 0);
			return (0);
		}
		//put color to dst
		iter += calc_pixel(11 * pixel_idx % fractal->total_pixels, fractal);
		fractal->pixels_processed = pixel_idx;
		pixel_idx++;
	}
	return (0);
}

void	draw_fractal(t_fractal *fractal)
{
	t_data	*data;

	init_iter(fractal, INIT_ITER);
	data = &fractal->data;
	if (data->img)
		mlx_destroy_image(fractal->mlx, fractal->data.img);
	data->img = mlx_new_image(fractal->mlx, WIDTH, HEIGHT);
	data->addr = mlx_get_data_addr(fractal->data.img,
			&fractal->data.bits_per_pixel,
			&fractal->data.line_len,
			&fractal->data.endian);
	render_frame(fractal);
}
//
//int	trgb(int t, int r, int g, int b)
//{
//	return (t << 24 | r << 16 | g << 8 | b);
//}
//
//int	hsv2rgb(int h, int s, int v)
//{
//	int	max;
//	int	min;
//
//	h = h % 360;
//	max = v;
//	min = max - (s * max / 255);
//	if (0 <= h && h < 60)
//		return (trgb(0, max, h * (max - min) / 60 + min, min));
//	else if (60 <= h && h < 120)
//		return (trgb(0, (120 - h) * (max - min) / 60, max, min));
//	else if (120 <= h && h < 180)
//		return (trgb(0, min, max, (h - 120) * (max - min) / 60));
//	else if (180 <= h && h < 240)
//		return (trgb(0, min, (240 - h) * (max - min) / 60, max));
//	else if (240 <= h && h < 300)
//		return (trgb(0, (h - 240) * (max - min) / 60, min, max));
//	else if (300 <= h && h <= 360)
//		return (trgb(0, max, min, (360 - h) * (max - min) / 60));
//	else
//		return (0);
//}
//
//void	to_z(int x, int y, double z[], t_fractal *fractal)
//{
//	z[0] = (double)(x - WIDTH / 2) / fractal->zoom - fractal->offset_x;
//	z[1] = (double)(y - HEIGHT / 2) / fractal->zoom - fractal->offset_y;
//}
