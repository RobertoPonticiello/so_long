/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpontici <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/21 12:36:42 by rpontici          #+#    #+#             */
/*   Updated: 2024/12/22 16:17:01 by rpontici         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_is_charset(char const c, char sep)
{
	if (c == sep)
		return (1);
	return (0);
}

static int	ft_word_count(char const *s, char c)
{
	int	count;
	int	i;

	i = 0;
	count = 0;
	while (s[i])
	{
		while (s[i] && ft_is_charset(s[i], c))
			i++;
		if (s[i])
		{
			count++;
			while (s[i] && !ft_is_charset(s[i], c))
				i++;
		}
	}
	return (count);
}

static char	*ft_strdup_range(char const *s, int start, int end)
{
	char	*dest;
	int		i;

	dest = (char *)malloc(sizeof(char) * (end - start + 1));
	if (!dest)
		return (NULL);
	i = 0;
	while (start < end)
		dest[i++] = s[start++];
	dest[i] = '\0';
	return (dest);
}

char	**ft_split(char const *s, char c)
{
	char	**arr;
	int		i;
	int		wcount;
	int		windex;
	int		start;

	if (!s)
		return (NULL);
	wcount = ft_word_count(s, c);
	arr = (char **)malloc(sizeof(char *) * (wcount + 1));
	if (!arr)
		return (NULL);
	i = 0;
	windex = 0;
	while (windex < wcount)
	{
		while (s[i] && ft_is_charset(s[i], c))
			i++;
		start = i;
		while (s[i] && !ft_is_charset(s[i], c))
			i++;
		arr[windex++] = ft_strdup_range(s, start, i);
	}
	arr[windex] = NULL;
	return (arr);
}
