/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpontici <rpontici@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 23:16:41 by rpontici          #+#    #+#             */
/*   Updated: 2024/12/21 18:30:24 by rpontici         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*r;

	if (nmemb != 0 && size > SIZE_MAX / nmemb)
		return (NULL);
	r = malloc(nmemb * size);
	if (!r)
		return (NULL);
	ft_bzero(r, nmemb * size);
	return (r);
}
