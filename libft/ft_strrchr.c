/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpontici <rpontici@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 18:56:46 by rpontici          #+#    #+#             */
/*   Updated: 2024/12/20 15:57:17 by rpontici         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *string, int c)
{
	char	*r;
	int		i;

	r = NULL;
	i = 0;
	while (string[i])
	{
		if (string[i] == (char)c)
			r = (char *)&string[i];
		i++;
	}
	if (string[i] == (char)c)
		r = (char *)&string[i];
	return (r);
}
/*
#include <stdio.h>

int	main(void)
{
	const char *str = "Hello, world!";
	char c = 'o';
	char *result = ft_strrchr(str, c);

	if (result)
		printf("Ultima occorrenza di '%c' trovata in posizione: %ld\n", c,
			result - str);
	else
		printf("Carattere '%c' non trovato.\n", c);

	return (0);
}*/
