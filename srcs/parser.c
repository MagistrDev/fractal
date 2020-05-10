/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecelsa <ecelsa@studen.21-school.ru>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/10 05:07:46 by ecelsa            #+#    #+#             */
/*   Updated: 2020/05/10 05:56:10 by ecelsa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

typedef struct	s_parser
{
	char	cmd[10];
	char	param[10];
	char	value[10];
}				t_parser;


t_parser parser(char *str)
{
	t_parser	p;
	char		**st;
	int			i;

	i = 0;
	st = ft_strsplit(str, ' ');
	while(*(st + i))141
		i++;
	if (i == 1 && ft_strequ(st[0],"quit"))
	ft_putnbr(i);
	ft_arrdel(&st, i);	
}

int		main()
{
	char		*buf;
	t_parser	p;
	
	while(1)
	{
		get_next_line(0, &buf);
		p = parser(buf);
		free(buf);
	}
	return(0);
}