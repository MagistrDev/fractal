/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecelsa <ecelsa@studen.21-school.ru>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/28 14:19:06 by ecelsa            #+#    #+#             */
/*   Updated: 2020/07/28 16:08:34 by ecelsa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	create_win(t_window *win)
{
	win->height = 1000;
	win->width = 1000;
	win->color.func = 0;
	win->color.smooth = 0;
	set_fractal(ONE, win);
	win->mlx_ptr = mlx_init();
	win->win_ptr = mlx_new_window(win->mlx_ptr, win->width,
		win->height, "1");
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
	draw_fractal(win);
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
	t_window	win[3];
	t_thread	t[4];
	char		*buf;
	char		**st;
	int			i;

	i = 0;
	if ((argc == 2) && (ft_strequ("1", argv[1]) || ft_strequ("2", argv[1]) ||\
		ft_strequ("3", argv[1])))
	{
		win[0].fractal = ft_atoi(argv[1]);
		create_win(&win[0]);
		pthread_attr_init(&t[0].attr);
		pthread_create(&t[0].tid, &t[0].attr, potok, (void*)&win[0]);
		t[3].flag = 1;
		while (t[3].flag)
		{
			get_next_line(0, &buf);
			if (ft_strequ(buf,"quit"))
				quit(&win[0]);
			else
			{
				st = ft_strsplit(buf,' ');
				while(*(st+i))
					i++;
				if (i == 1 && ft_strequ(st[0],"quit"))
					quit(&win[0]);
				ft_putnbr(i);
				ft_arrdel(&st, i);
				i = 0;
			}
			free(buf);
			
		}
		
		pthread_join(t[0].tid, NULL);
	}
	else
	{
		write(1, "You use : ./fractol [num_fractal]\n", 34);
		write(1, "\t1\tMandelbrot\n\t2\tJulia\n\t3\tBurningship\n", 38);
	}
	return (0);
}
