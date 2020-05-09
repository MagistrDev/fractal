/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecelsa <ecelsa@studen.21-school.ru>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/01 16:00:17 by Ecelsa            #+#    #+#             */
/*   Updated: 2020/05/09 21:13:02 by ecelsa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include <stdio.h>
# include <math.h>
# include <stdlib.h>
# include <pthread.h>
# include "mlx.h"
# include "mlx_int.h"
# include "libft.h"
# include "ubuntu.h"

typedef unsigned char	t_uchar;

typedef struct			s_complex
{
	double	x;
	double	y;
}						t_complex;

typedef struct			s_mouse_event
{
	t_complex	l_cursor;
	int			mouse_press;
	int			mouse_release;
	int			btn_press;
}						t_m_event;

typedef struct			s_color
{
	int			color;
	int			smooth;
	t_complex	z;
	int			func;
}						t_color;

typedef struct			s_thread
{
	pthread_t		tid;
	pthread_attr_t	attr;
}						t_thread;


typedef struct			s_window
{
	t_thread	tread[16];
	void		*mlx_ptr;
	void		*win_ptr;
	void		*img_ptr;
	int			*img;
	int			width;
	int			height;
	double		re_min;
	double		re_max;
	double		d_re;
	double		im_min;
	double		im_max;
	double		d_im;
	int			fractal;
	double		scale;
	int			bpp;
	int			btn_d;
	int			size_line;
	int			endian;
	int			iter;
	int			mouse_pres;
	t_color		color;
	t_complex	c;
	int			calc_ok;
	t_m_event	mouse;
}						t_window;
 
int						key_press(int key, t_window *win);
int						mouse_move(int x, int y, t_window *win);
int						mouse_press(int button, int x, int y, t_window *win);
int						mouse_release(int button, int x, int y, t_window *win);
void					draw_fractal(t_window *win);
void					scale(int x, int y, int sc, t_window *win);

#endif
