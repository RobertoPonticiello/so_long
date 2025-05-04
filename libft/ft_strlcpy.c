/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpontici <rpontici@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 20:55:23 by rpontici          #+#    #+#             */
/*   Updated: 2024/12/20 16:28:04 by rpontici         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *destination, const char *source, size_t size)
{
	size_t	i;

	if (!destination || !source)
		return (0);
	i = 0;
	if (size > 0)
	{
		while (i < size - 1 && source[i])
		{
			destination[i] = source[i];
			i++;
		}
		destination[i] = '\0';
	}
	while (source[i])
		i++;
	return (i);
}
/*
#include <stdio.h>

int main(void)
{
	char dest[10];
	const char *src = "Hello, World!";
	size_t len;

	len = ft_strlcpy(dest, src, sizeof(dest));

	printf("Source: %s\n", src);
	printf("Destination: %s\n", dest);
	printf("Length of source: %zu\n", len);

	return (0);
}
*/