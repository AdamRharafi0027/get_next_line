/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arharafi <arharafi@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/11 10:08:14 by arharafi          #+#    #+#             */
/*   Updated: 2026/11/17 07:54:55 by arharafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	if (!s)
		return (0);
	i = 0;
	while (s[i])
		i++;
	return (i);
}

char	*ft_strchr(const char *s, int c)
{
	size_t	i;

	if (!s)
		return (NULL);
	i = 0;
	while (i < ft_strlen(s) + 1)
	{
		if ((unsigned char)s[i] == (unsigned char)c)
			return ((char *)&s[i]);
		i++;
	}
	return (NULL);
}

char	*ft_strjoin(const char *s1, const char *s2)
{
	char	*res;
	size_t	i;
	size_t	j;

	if (!s2)
		return (NULL);
	res = malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!res)
		return (NULL);
	i = 0;
	while (s1 && s1[i])
	{
		res[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j])
		res[i++] = s2[j++];
	res[i] = '\0';
	return (res);
}

char	*gnl_get_line(const char *rem)
{
	size_t	i;
	char	*line;

	if (!rem)
		return (NULL);
	i = 0;
	while (rem[i] && rem[i] != '\n')
		i++;
	if (rem[i] == '\n')
		i++;
	line = malloc(i + 1);
	if (!line)
		return (NULL);
	line[i] = '\0';
	while (i--)
		line[i] = rem[i];
	return (line);
}

char	*gnl_get_remin(const char *rem)
{
	size_t	i;
	size_t	j;
	char	*res;

	if (!rem)
		return (NULL);
	i = 0;
	while (rem[i] && rem[i] != '\n')
		i++;
	if (!rem[i] || !rem[i + 1])
		return (NULL);
	res = malloc(ft_strlen(rem + i + 1) + 1);
	if (!res)
		return (NULL);
	i++;
	j = 0;
	while (rem[i])
		res[j++] = rem[i++];
	res[j] = '\0';
	return (res);
}
