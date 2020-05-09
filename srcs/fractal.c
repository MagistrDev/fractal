/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractal.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecelsa <ecelsa@studen.21-school.ru>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/02 16:44:07 by Ecelsa            #+#    #+#             */
/*   Updated: 2020/05/09 23:08:07 by ecelsa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	set_fractal(int key, t_window *win)
{
	win->im_min = -2;
	win->im_max = 2;
	win->re_min = -2;
	win->re_max = 2;
	win->d_re = (win->re_max - win->re_min) / win->width;
	win->d_im = (win->im_max - win->im_min) / win->height;
	win->c = (t_complex){0, 0};
	win->color.z = (t_complex){0, 0};
	win->color.color = 0xffffff;
	win->iter = 25;
	if (key == ONE)
	{
		win->fractal = 1;
		win->mouse_pres = 0;
	}
	if (key == TWO)
	{
		win->fractal = 2;
		win->mouse_pres = 3;
	}
	if (key == THRE)
	{
		win->fractal = 3;
		win->mouse_pres = 0;
	}
}

int		col_iter(double i, t_window *win)
{
	t_complex	z;
	int			color;
	double		sn;
	double		t;

	t = i / (double)win->iter;
	if (win->color.smooth)
	{
		z = win->color.z;
		sn = logf(logf(z.x * z.x + z.y * z.y) / logf(2)) / logf(2);
		sn = ((sn > 2.0) ? 2.0 : sn) - 1;
		t = (t > 0.998) ? 0.998 : (1.0f / win->iter * (1.0 - sn) / 1.0 + t);
	}
	color = ((int)(9 * (1 - t) * t * t * t * 255)) << 16;
	color |= ((int)(15 * (1 - t) * (1 - t) * t * t * 255)) << 8;
	color |= ((int)(8.5 * (1 - t) * (1 - t) * (1 - t) * t * 255));
	return (color);
}

/*
** Z' = pow(Z,2) + c; c' = c/2 + Z'
*/

int		if_func(t_complex z, t_window *win)
{
	int ret;

	ret = 0;
	if (win->color.func == 0)
		ret = (z.x * z.x + z.y * z.y <= 4) ? 1 : 0;
	if (win->color.func == 1)
		ret = (z.x * z.x - z.y * z.y <= 4) ? 1 : 0;
	if (win->color.func == 2)
		ret = (fabsl(z.x - z.y) <= 4) ? 1 : 0;
	return (ret);
}

int		mandelbrot(t_complex c, t_window *win)
{
	t_complex	z;
	double		d;
	int			i;

	z = c;
	i = win->iter;
	i = -1;
	while (++i < win->iter && if_func(z, win))
	{
		d = z.x * z.x - z.y * z.y + c.x;
		z.y = 2 * z.x * z.y + c.y;
		z.x = d;
	}
	win->color.z = z;
	return (i);
}

/*
** Zn+1 = sqr(Zn) + c
*/

int		julia(t_complex c, t_window *win)
{
	t_complex	z;
	double		d;
	int			i;

	z = c;
	i = -1;
	while (++i < win->iter && if_func(z, win))
	{
		d = z.x * z.x - z.y * z.y + win->c.x;
		z.y = 2 * z.x * z.y + win->c.y;
		z.x = d;
	}
	win->color.z = z;
	return (i);
}

int		burningship(t_complex c, t_window *win)
{
	t_complex	z;
	double		d;
	int			i;

	z = (t_complex){.x = 0, .y = 0};
	i = -1;
	while (++i < win->iter && if_func(z, win))
	{
		d = z.x;
		z.x = fabsl(d * d) - z.y * z.y + c.x;
		z.y = 2 * fabsl(d * z.y) - c.y;
	}
	win->color.z = z;
	return (i);
}

void	draw_fractal(t_window *win)
{
	int			color;
	t_complex	pt;
	t_complex	c;

	color = 0;
	pt.y = -1;
	XSync(((t_xvar*)(win->mlx_ptr))->display, True);
	while (++pt.y <= win->height)
	{
		pt.x = -1;
		while (++pt.x <= win->width)
		{
			c.y = win->im_max - (win->d_im * pt.y);
			c.x = win->re_min + (win->d_re * pt.x);
			if (win->fractal == 1)
				color = col_iter(mandelbrot(c, win), win);
			if (win->fractal == 2)
				color = col_iter(julia(c, win), win);
			if (win->fractal == 3)
				color = col_iter(burningship(c, win), win);
			win->img[(int)(pt.y * win->width + pt.x)] = color;
		}
	}
	mlx_put_image_to_window(win->mlx_ptr, win->win_ptr, win->img_ptr, 0, 0);
	win->calc_ok++;
}

void	scale(int x, int y, int sc, t_window *win)
{
	double	tmp;

	tmp = win->d_re * (1 - win->scale * sc);
	win->re_min += tmp * (x * win->d_re / tmp - x);
	win->d_re = tmp;
	win->re_max = win->re_min + win->d_re * win->width;
	tmp = win->d_im * (1 - win->scale * sc);
	win->im_max -= tmp * (y * win->d_im / tmp - y);
	win->d_im = tmp;
	win->im_min = win->im_max - win->d_im * win->height;
}
