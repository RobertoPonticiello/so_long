/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpontici <rpontici@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 22:12:17 by rpontici          #+#    #+#             */
/*   Updated: 2024/12/20 12:12:24 by rpontici         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *str1, const void *str2, size_t n)
{
	const unsigned char	*s1;
	const unsigned char	*s2;
	size_t				i;

	s1 = (const unsigned char *)str1;
	s2 = (const unsigned char *)str2;
	i = 0;
	while (i < n)
	{
		if (s1[i] != s2[i])
		{
			return (s1[i] - s2[i]);
		}
		i++;
	}
	return (0);
}
/*
int	main(void)
{
	char str1[] = "abcdef";
	char str2[] = "1bcdez";

	int result = ft_memcmp(str1, str2, 5); // Confronta i primi 5 byte
	if (result == 0)
		printf("Ia primi 5 byte sono uguali.\n");
	else if (result < 0)
		printf("gtr1 è minore di str2 nei primi 5 byte.\n");
	else
		printf("str1 è maggiore di str2 nei primi 5 byte.\n");

	return (0);
}*/
