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

# define WIDTH 1080
# define HEIGHT 1080
// # define MAX_ITER 50

# define COLOR_BLACK 0x000000
# define COLOR_WHITE 0xFFFFFFFF
# define COLOR_RED 0xFF0000
# define COLOR_GREEN 0x00FF00
# define COLOR_BLUE 0x0000FF

# define MOUSE_DOWN 4
# define MOUSE_UP 5
# define KEY_ESC 65307
# define KEY_LEFT 65361
# define KEY_UP 65362
# define KEY_RIGHT 65363
# define KEY_DOWN 65364



typedef enum	e_fractal_type
{
	MANDELBROT,
	JULIA
}				t_fractal_type;

typedef struct	s_complex
{
	double	real;
	double	imag;
}				t_complex;

typedef struct	s_data
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		endian;
	int		line_len;
}				t_data;

typedef struct	s_fractal
{
	void			*mlx;
	void			*win;
	t_data			data;
	t_fractal_type	type;
	t_complex		julia_c;
	double			zoom;
	double			offset_x;
	double			offset_y;
	double			offset_step;
	int				max_iter;
	int				target_iter;
	int				current_x;
	int				current_y;
	long long		calc_count;
	int				pixels_processed;
	int				total_pixels;
	int				needs_redraw;
	long long		iter_chunk;
	//int				reset_requested;
}				t_fractal;

void	init_mlx(t_fractal *fractal);
void	init_fractal(t_fractal *fractal, t_fractal_type type, t_complex *julia_c);
int		draw_fractal(t_fractal *fractal);
int		handle_zoom(int button, int x, int y, void *param);
int		handle_key(int keycode, void *param);
int		render_frame(void *param);

#endif
