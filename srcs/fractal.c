/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractal.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecelsa <ecelsa@studen.21-school.ru>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/02 16:44:07 by Ecelsa            #+#    #+#             */
/*   Updated: 2020/05/07 23:17:23 by ecelsa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int		col_iter(int i, t_window *win)
{
	int		color;
	float	t;

	t = (float)i / (float)win->iter;
	color = ((int)(9 * (1 - t) * t * t * t * 255)) << 16;
	color |= ((int)(15 * (1 - t) * (1 - t) * t * t * 255)) << 8;
	color |= ((int)(8.5 * (1 - t) * (1 - t) * (1 - t) * t * 255));
	return (color);
}

int		smooth_color(t_complex p, float iter, t_window *win)
{
	int		color;
	float	t;

	/*
	double i;
	double zn;
	double nu;
	zn = log(p.x * p.x + p.y * p.y) / 2.0f;
	nu = log(zn / log(2)) / log(2);
	i = p.y + 1 - nu;
	if (i < 0)
		i = 0;*/
	iter = iter - log(log(p.x * p.x + p.y * p.y) / log(2)) / log(2);
	t = iter / (float)win->iter;
	color = ((int)(9 * (1 - t) * t * t * t * 255)) << 16;
	color |= ((int)(15 * (1 - t) * (1 - t) * t * t * 255)) << 8;
	color |= ((int)(8.5 * (1 - t) * (1 - t) * (1 - t) * t * 255));
	return (color);
}

int		man_smooth(t_complex c, t_window *win)
{
	t_complex	z;
	float		d;
	float		i;
	float		t;
	float		sn;
	int		bla;

	z = c;
	i = -1;
	while (++i < win->iter && (z.x * z.x + z.y * z.y) <= 4)
	{
		d = z.x * z.x - z.y * z.y + c.x;
		z.y = 2 * z.x * z.y + c.y;
		z.x = d;
	}
	sn = logf(logf(z.x * z.x + z.y * z.y) / logf(2)) / logf(2);
	//i = fabs(i - ((i < sn) ? 0 : sn));
	t = i / (float)win->iter;
	/*
	*/
	(void)t;
	(void)bla;
	sn = ((sn > 2.0) ? 2.0 : sn) - 1;
	//printf("<%f %f %f %f> \t",sn, (1.0 - sn),(1.0 - sn) / 2.0,255*(1.0f/(float)win->iter*(1.0 - sn) / 1.0 + t));
	//bla = (i /(float)win->iter)*255;
	t = (t > 0.998) ? 0.998 : (1.0f/(float)win->iter*(1.0 - sn) / 1.0 + t);
	bla = ((int)(9 * (1 - t) * t * t * t * 255)) << 16;
	bla |= ((int)(15 * (1 - t) * (1 - t) * t * t * 255)) << 8;
	bla |= ((int)(8.5 * (1 - t) * (1 - t) * (1 - t) * t * 255));
	return (bla);
}

/*
** Z' = pow(Z,2) + c; c' = c/2 + Z'
*/

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
		while (++i < win->iter && fabs(z.x * z.x + z.y * z.y) <= 4)
		{
			d = z.x * z.x - z.y * z.y + c.x;
			z.y = 2 * z.x * z.y + c.y;
			z.x = d;
		}
	}
	return (i);
}


/*
** Zn+1 = sqr(Zn) + c
*/

int		julia(t_complex c, t_window *win)
{
	t_complex	z;
	float		d;
	int			i;

	z = c;
	i = -1;
	while (++i < win->iter && fabs(z.x - z.y) < 5)
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
		z.y = 2 * fabs(d * z.y) - c.y;
	}
	return (i);
}

void	draw_fractal(t_window *win)
{
	int			x;
	int			y;
	int			i =0;
	int			color;
	t_complex	c;

	mlx_do_sync(win->mlx_ptr);
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
			//if (win->color)
			//	color = (i == win->iter) ? win->color : 0;
			color = col_iter(i, win);
			if (win->fractal == 4)
				color = man_smooth(c, win);
			
			win->img[y * win->width + x] = color;
		}
	}
	mlx_put_image_to_window(win->mlx_ptr, win->win_ptr, win->img_ptr, 0, 0);
	win->calc_ok = 0;
	mlx_do_sync(win->mlx_ptr);
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
