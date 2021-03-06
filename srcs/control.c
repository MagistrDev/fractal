/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   control.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecelsa <ecelsa@studen.21-school.ru>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/01 16:04:23 by Ecelsa            #+#    #+#             */
/*   Updated: 2020/05/10 04:15:40 by ecelsa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int		key_press(int key, t_window *win)
{
	if (key == ESC)
		quit(win);
	if (key == KEY_NUMPLU || key == ZERO)
		win->iter += 5;
	if (key == KEY_NUMMIN || key == NINE)
		win->iter -= (win->iter < 10) ? 0 : 5;
	if (key == ONE || key == TWO || key == THRE)
		set_fractal(key, win);
	if (key == KEY_S)
		win->color.smooth = (win->color.smooth) ? 0 : 1;
	if (key == KEY_W)
		win->color.func = 0;
	if (key == KEY_E)
		win->color.func = 1;
	if (key == KEY_R)
		win->color.func = 2;
	draw_fractal(win);
	return (0);
}

int		mouse_move(int x, int y, t_window *win)
{
	if (win->mouse_pres == 3)
	{
		win->c.y = win->im_max - (win->d_im * y);
		win->c.x = win->re_min + (win->d_re * x);
		draw_fractal(win);
	}
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
