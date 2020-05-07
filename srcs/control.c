/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   control.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecelsa <ecelsa@studen.21-school.ru>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/01 16:04:23 by Ecelsa            #+#    #+#             */
/*   Updated: 2020/05/07 20:43:20 by ecelsa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int		key_press(int key, t_window *win)
{
	(void)key;
	(void)win;
	if (key == ESC)
		exit(0);
	if (key == KEY_NUMPLU)
		win->iter += 5;
	if (key == KEY_NUMMIN)
		win->iter -= 5;
	if (key == ONE)
		win->fractal = 1;
	if (key == TWO)
		win->fractal = 2;
	if (key == THRE)
		win->fractal = 3;
	if (key == FOUR)
		win->fractal = 4;
	if (key == KEY_Q)
	{
		win->im_min = -2;
		win->im_max = 2;
		win->re_min = -2;
		win->re_max = 2;
	}
	if (key == KEY_C)
		win->color = (win->color) ? 0 : 0xffffff;
	draw_fractal(win);
	return (0);
}

int		mouse_move(int x, int y, t_window *win)
{
	t_complex	c;
	if (win->mouse_pres == 3)
	{
		win->calc_ok = 1;
		win->c.y = win->im_max - (win->d_im * y);
		win->c.x = win->re_min + (win->d_re * x);
		draw_fractal(win);
	}
	c.y = win->im_max - (win->d_im * y);
	c.x = win->re_min + (win->d_re * x);
	(void)c;
	printf("%d %d | %i %i %i\n",x, y, mandelbrot(c, win), (int)((float)mandelbrot(c, win)/(float)win->iter *255), man_smooth(c,win));
	return (0);
}

int		mouse_press(int button, int x, int y, t_window *win)
{
	win->mouse.btn_press |= (1 << button);
	if (button == 3)
		win->mouse_pres = ((win->mouse_pres == 3) ? 0 : 3);
	if (button == 1)
	{
		win->c.y = win->im_max - (win->d_im * y);
		win->c.x = win->re_min + (win->d_re * x);
		win->mouse_pres = 1;
	}
	if (button == 4 || button == 5)
		scale(x, y, ((button % 4) ? -1 : 1), win);
	draw_fractal(win);
	return (0);
}

int		mouse_release(int button, int x, int y, t_window *win)
{
	(void)x;
	(void)y;
	(void)win;
	win->mouse.btn_press |= (1 << button);
	return (0);
}
