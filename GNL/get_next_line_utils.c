/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msilva-p <msilva-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/09 20:11:11 by msilva-p          #+#    #+#             */
/*   Updated: 2022/07/20 19:35:46 by msilva-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(const char *s)
{
	int	i;

	i = 0;
	if (!s)
		return (i);
	while (s[i])
		i++;
	return (i);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		i;
	int		j;
	char	*news;

	i = 0;
	j = 0;
	news = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!news)
		return (NULL);
	while (s1 && s1[i])
	{
		news[i] = s1[i];
		i++;
	}
	while (s2 && s2[j])
	{
		news[i + j] = s2[j];
		j++;
	}
	news[i + j] = '\0';
	return (news);
}

char	*ft_strdup(const char *s)
{
	char	*copy;
	size_t	i;

	i = 0;
	copy = (char *)malloc(sizeof (char) * ft_strlen(s) + 1);
	if (!copy)
		return (NULL);
	while (s[i])
	{
		copy[i] = s[i];
		i++;
	}
	copy[i] = '\0';
	return (copy);
}

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	i;

	i = 0;
	if (!size)
		return (ft_strlen(src));
	while (i + 1 < size && src[i])
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (ft_strlen(src));
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*subs;
	size_t	lenmax;

	if (start > ft_strlen(s))
		return (ft_strdup(""));
	else if (len > ft_strlen(s) - start)
		lenmax = ft_strlen(s) - start;
	else
		lenmax = len;
	if (!s)
		return (NULL);
	subs = (char *)malloc(sizeof(char) * (lenmax + 1));
	if (!subs)
		return (NULL);
	ft_strlcpy(subs, s + start, lenmax + 1);
	return (subs);
}
