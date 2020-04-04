/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   control.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Ecelsa <ecelsa@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/01 16:04:23 by Ecelsa            #+#    #+#             */
/*   Updated: 2020/04/04 22:43:23 by Ecelsa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int		key_press(int key, t_window *win)
{
	(void)key;
	(void)win;
	if (key == ESC)
		exit(0);
	if (key == NUMPLU)
		win->iter += 5;
	if (key == NUMMIN)
		win->iter -= 5;
	if (key == ONE)
		win->fractal = 1;
	if (key == TWO)
		win->fractal = 2;
	if (key == THRE)
		win->fractal = 3;
	if (key == Q)
	{
		win->im_min = -2;
		win->im_max = 2;
		win->re_min = -2; 
		win->re_max = 2;
	}
	if (key == C)
		win->color = (win->color) ? 0 : 0xffffff;
	if (key == NUMENT)
	{
		for (int bla = 0; bla < 600*600 ; bla++)
		{
			win->img_x[bla] = 0xff0000ff;
			//win->img_x[bla] |= 128 << 16;
		}
		mlx_put_image_to_window(win->mlx_ptr, win->win_ptr, win->img_ptr_x, win->width >> 1, win->height >> 1);
	}
	draw_fractal(win);
	return (0);
}

int		mouse_move(int x, int y, t_window *win)
{
	if (win->calc_ok == 0)
	{
		if (win->mouse_pres == 3)
		{
			printf("%i/%i\n", x,y);
			win->calc_ok = 1;
			win->c.y = win->im_max - (win->d_im * y);
			win->c.x = win->re_min + (win->d_re * x);
			draw_fractal(win);
		}
	}
	return(0);
}

int		mouse_press(int button, int x, int y, t_window *win)
{
	(void)x;
	(void)y;
	(void)button;
	(void)win;
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
	printf("btn - %i x - %i y - %i\n",button, x, y);
	draw_fractal(win);
	return (0);
}

int		mouse_release(int button, int x, int y, t_window *win)
{
	(void)x;
	(void)y;
	(void)button;
	(void)win;
	win->mouse.btn_press |= (1 << button); 
	//if (button == 3)
	//	win->mouse_pres = 0;
	return(0);

}