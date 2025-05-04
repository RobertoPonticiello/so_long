/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpontici <rpontici@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 19:29:01 by rpontici          #+#    #+#             */
/*   Updated: 2024/12/20 14:53:01 by rpontici         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *buf, int c, size_t count)
{
	const unsigned char	*p;
	unsigned char		uc;
	size_t				i;

	p = (const unsigned char *)buf;
	uc = (unsigned char)c;
	i = 0;
	while (i < count)
	{
		if (p[i] == uc)
			return ((void *)&p[i]);
		i++;
	}
	return (NULL);
}
/*
#include <stdio.h>
#include <string.h>

int	main(void)
{
	char data[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
	int to_find = 5;

	void *result = memchr(data, to_find, sizeof(data));

	if (result) {
		printf("Byte trovato in posizione: %ld\n", (unsigned char *)result
			- (unsigned char *)data);
	} else {
		printf("Byte non trovato.\n");
	}

	return (0);
}*/
