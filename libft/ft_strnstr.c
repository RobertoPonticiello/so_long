/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpontici <rpontici@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 22:30:03 by rpontici          #+#    #+#             */
/*   Updated: 2024/12/22 17:00:37 by rpontici         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (*little == '\0')
		return ((char *)big);
	if (len == 0)
		return (NULL);
	while (big[i] && i < len)
	{
		j = 0;
		while (big[i + j] && little[j] && (i + j) < len)
		{
			if (big[i + j] != little[j])
				break ;
			j++;
		}
		if (!little[j])
			return ((char *)&big[i]);
		i++;
	}
	return (NULL);
}
/*
int	main(void) {
	const char *haystack = "Helo is a simple test";
	const char *needle = "simple";

	// Cerca "simple" nei primi 20 caratteri di haystack
	char *result = ft_strnstr(haystack, needle, 20);

	if (result)
		printf("Trovato: '%s'\n", result); // Output atteso: "simple test"
	else
		printf("Sottostringa non trovata.\n");
	return (0);
}*/
