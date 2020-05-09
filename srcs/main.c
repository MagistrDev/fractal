/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecelsa <ecelsa@studen.21-school.ru>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/28 14:19:06 by ecelsa            #+#    #+#             */
/*   Updated: 2020/05/09 23:01:25 by ecelsa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	create_win(t_window *win, int argc, char **argv)
{
	(void)argc;
	win->height = 600;
	win->width = 600;
	win->color.func = 0;
	win->color.smooth = 0;
	set_fractal(ONE, win);
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

void	*potok2(void *www)
{
	t_window	*win;
	time_t		t;

	t = time(0);
	win = (t_window*)www;
	(void)win;
	while (1)
	{
		if (t != time(0))
		{
			t = time(0);
			printf("%ld %i\n", time(0), win->calc_ok);
			win->calc_ok = 0;
		}
	}
	pthread_exit(0);
}

int		main(int argc, char **argv)
{
	t_window		win;
	t_thread		t[3];

	create_win(&win, argc, argv);
	pthread_attr_init(&t[0].attr);
	pthread_create(&t[0].tid, &t[0].attr, potok, (void*)&win);
	pthread_attr_init(&t[1].attr);
	pthread_create(&t[1].tid, &t[1].attr, potok2, (void*)&win);
	pthread_join(t[0].tid, NULL);
	pthread_join(t[1].tid, NULL);
	return (0);
}
