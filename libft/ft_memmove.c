/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpontici <rpontici@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 17:49:16 by rpontici          #+#    #+#             */
/*   Updated: 2024/12/22 17:46:57 by rpontici         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t count)
{
	size_t			c;
	size_t			i;
	unsigned char	*d;
	unsigned char	*s;

	c = 0;
	i = 1;
	if (!dest || !src)
		return (NULL);
	d = (unsigned char *)dest;
	s = (unsigned char *)src;
	if (dest > src)
	{
		i = -1;
		d += count - 1;
		s += count - 1;
	}
	while (c < count)
	{
		*d = *s;
		d += i;
		s += i;
		c++;
	}
	return (dest);
}
