/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecelsa <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/18 18:52:03 by ecelsa            #+#    #+#             */
/*   Updated: 2019/09/18 19:44:37 by ecelsa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

size_t	ft_strlen(const char *s)
{
	size_t		size;
	char		*str;

	str = (char*)s;
	size = 0;
	while (*str++ != 0)
		size++;
	return (size);
}
