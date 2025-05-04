/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpontici <rpontici@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 17:15:07 by rpontici          #+#    #+#             */
/*   Updated: 2024/12/21 14:12:30 by rpontici         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_len(long n)
{
	int	len;

	len = 0;
	if (n <= 0)
	{
		len++;
		n = -n;
	}
	while (n > 0)
	{
		n /= 10;
		len++;
	}
	return (len);
}

char	*ft_itoa(int nb)
{
	char	*str;
	long	n;
	int		len;

	n = (long)nb;
	len = ft_len(n);
	str = (char *)malloc(sizeof(char) * (len + 1));
	if (!str)
		return (NULL);
	str[len] = '\0';
	if (n < 0)
		n = -n;
	while (len > 0)
	{
		len--;
		str[len] = (n % 10) + '0';
		n /= 10;
		if (n == 0 && nb < 0 && len == 0)
			str[len] = '-';
	}
	return (str);
}
/*
int	main(void)
{
	printf("%s", ft_itoa(-452));
	return (0);
}*/
