/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractal.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Ecelsa <ecelsa@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/02 16:44:07 by Ecelsa            #+#    #+#             */
/*   Updated: 2020/04/04 23:08:33 by Ecelsa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int		col_iter(int i, t_window *win)
{
	int		color;
	float	t = (float)i / (float)win->iter;
	
	color = ((int)(9 * (1 - t) * pow(t, 3) * 255)) << 16;
	color |= ((int)(15 * pow((1 - t), 2) * pow(t, 2) * 255)) << 8;
	color |= ((int)(8.5 * pow((1 - t), 3) * t * 255));
	return (color);	
}

int		mandelbrot(t_complex c, t_window *win)
{
	t_complex	z;
	float		ro_c;
	float		teta;
	float		ro;
	float		d;
	int			i;

	z = c;
	ro = sqrtf((c.x - 0.25) * (c.x - 0.25) + c.y * c.y);
	teta = atan2f(c.y, c.x - 0.25);
	ro_c = 0.5 - 0.5 * cosf(teta);
	i = win->iter;
	if (ro > ro_c)
	{
		i = -1;
		while (++i < win->iter && fabs(z.x - z.y) < 4)
		{
			d = z.x * z.x - z.y * z.y + c.x;
			z.y = 2 * z.x * z.y + c.y;
			z.x = d;
		}
	}
	return (i);
}

int		julia(t_complex c, t_window *win)
{
	t_complex	z;
	float		d;
	int			i;

	z = c;
	i = -1;
	while (++i < win->iter && fabs(z.x - z.y) < 4)
	{
		d = z.x * z.x - z.y * z.y + win->c.x;
		z.y = 2 * z.x * z.y + win->c.y;
		z.x = d;
	}
	return (i);
}

int		burningship(t_complex c, t_window *win)
{
	t_complex	z;
	float		d;
	int			i;

	z = (t_complex){.x = 0, .y = 0};
	i = -1;
	while (++i < win->iter && fabs(z.x - z.y) < 4)
	{
		d = z.x;
		z.x = fabs(d * d) - z.y * z.y + c.x;
		z.y = 2 * fabs(d * z.y) + c.y;
	}
	return (i);
}

void	draw_fractal(t_window *win)
{
	int			x;
	int			y;
	int			i;
	int			color;
	t_complex	c;

	y = -1;
	while (++y <= win->height)
	{
		x = -1;
		while (++x <= win->width)
		{
			c.y = win->im_max - (win->d_im * y);
			c.x = win->re_min + (win->d_re * x);
			if (win->fractal == 1)
				i = mandelbrot(c, win);
			if (win->fractal == 2)
				i = julia(c, win);
			if (win->fractal == 3)
				i = burningship(c, win);
			if (win->color)
				color = (i == win->iter) ? win->color : 0;
			else
				color = col_iter(i, win);
			win->img[y * win->width + x] = color;
		}
	}
	mlx_put_image_to_window(win->mlx_ptr, win->win_ptr, win->img_ptr, 0, 0);
	win->calc_ok = 0;
}

void	scale(int x, int y, int sc, t_window *win)
{
	float	tmp;

	tmp = win->d_re * (1 - win->scale * sc);
	win->re_min += tmp * (x * win->d_re / tmp - x);
	win->d_re = tmp;
	win->re_max = win->re_min + win->d_re * win->width;
	tmp = win->d_im * (1 - win->scale * sc);
	win->im_max -= tmp * (y * win->d_im / tmp - y);
	win->d_im = tmp;
	win->im_min = win->im_max - win->d_im * win->height;
}
