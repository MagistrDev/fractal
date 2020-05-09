/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecelsa <ecelsa@studen.21-school.ru>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/28 14:19:06 by ecelsa            #+#    #+#             */
/*   Updated: 2020/05/09 04:33:03 by ecelsa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	create_win(t_window *win, int argc, char **argv)
{
	(void)argc;
	win->height = 600;
	win->width = 600;
	win->im_min = -2;
	win->im_max = 2;
	win->re_min = -2;
	win->re_max = 2;
	win->color.color = 0;
	win->color.smooth = 0;
	win->color.func = 0;
	win->color.z = (t_complex){0, 0};
	win->d_re = (win->re_max - win->re_min) / win->width;
	win->d_im = (win->im_max - win->im_min) / win->height;
	win->mlx_ptr = mlx_init();
	win->win_ptr = mlx_new_window(win->mlx_ptr, win->width,
		win->height, argv[0]);
	win->img_ptr = mlx_new_image(win->mlx_ptr, win->width, win->height);
	win->img = (int*)mlx_get_data_addr(win->img_ptr, &win->bpp,
		&win->size_line, &win->endian);
	win->iter = 25;
	win->btn_d = 0;
	win->mouse_pres = 0;
	win->scale = 0.25;
	mlx_hook(win->win_ptr, 4, (1L << 2), mouse_press, win);
	mlx_hook(win->win_ptr, 5, (1L << 3), mouse_release, win);
	mlx_hook(win->win_ptr, 6, (1L << 6), mouse_move, win);
	mlx_hook(win->win_ptr, 2, 1, key_press, win);
}

void	*potok(void *www)
{
	t_window	*win;

	win = (t_window*)www;
	mlx_loop(win->mlx_ptr);
	pthread_exit(0);
}

int		main(int argc, char **argv)
{
	t_window		win;
	pthread_t		tid;
	pthread_attr_t	attr;

	create_win(&win, argc, argv);
	pthread_attr_init(&attr);
	pthread_create(&tid, &attr, potok, (void*)&win);
	pthread_join(tid, NULL);
	return (0);
}
