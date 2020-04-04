/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Ecelsa <ecelsa@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/01 16:00:17 by Ecelsa            #+#    #+#             */
/*   Updated: 2020/04/04 22:41:17 by Ecelsa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include <stdio.h>
# include <math.h>
# include <stdlib.h>
# include "mlx.h"
# include "libft.h"
# include "ubuntu.h"

typedef unsigned char	t_uchar;

typedef struct	s_complex
{
	double	x;
	double	y;
}				t_complex;

typedef struct	s_mouse_event
{
	t_complex	l_cursor;
	int			mouse_press;
	int			mouse_release;
	int			btn_press;
}				t_m_event;


typedef struct	s_window
{
	void		*mlx_ptr;
	void		*win_ptr;
	void		*img_ptr; 
	int			*img;
	void		*img_ptr_x; 
	int			*img_x;
	int			width;
	int			height;
	float		re_min;
	float		re_max;
	float		d_re;
	float		im_min;
	float		im_max;
	float		d_im;
	int			fractal;
	float		scale;
	int			bpp;
	int			btn_d;
	int			size_line;
	int			endian;
	int			iter;
	int			mouse_pres;
	int			color;
	t_complex	c;
	int			calc_ok;
	t_m_event	mouse;
}				t_window;


int		key_press(int key, t_window *win);
int		mouse_move(int x, int y, t_window *win);
int		mouse_press(int button, int x, int y, t_window *win);
int		mouse_release(int button, int x, int y, t_window *win);
void	draw_fractal(t_window *win);
void	scale(int x, int y, int sc, t_window *win);

#endif