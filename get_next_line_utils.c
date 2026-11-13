/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arharafi <arharafi@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/11 10:08:14 by arharafi          #+#    #+#             */
/*   Updated: 2026/11/12 19:10:07 by arharafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

char	*ft_strchr(const char *s, int c)
{
	size_t	i;

	i = 0;
	while (i < ft_strlen(s) + 1)
	{
		if ((unsigned char)s[i] == (unsigned char)c)
			return ((char *)&s[i]);
		i++;
	}
	return (NULL);
}

static void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t				i;
	unsigned char		*dest_ptr;
	unsigned const char	*src_ptr;

	i = 0;
	dest_ptr = (unsigned char *)dest;
	src_ptr = (unsigned const char *)src;
	while (i < n)
	{
		dest_ptr[i] = src_ptr[i];
		i++;
	}
	return (dest);
}

static char	*ft_strdup(const char *s)
{
	char	*dest;
	size_t	s_len;

	if (!s)
		return (NULL);
	s_len = ft_strlen(s);
	dest = malloc(s_len + 1);
	if (!dest)
		return (NULL);
	ft_memcpy(dest, s, s_len + 1);
	return (dest);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	s1_len;
	size_t	s2_len;
	char	*dest;

	if (!s1 && !s2)
		return (ft_strdup(""));
	if (!s1)
		return (ft_strdup(s2));
	if (!s2)
		return (ft_strdup(s1));
	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	dest = malloc((s1_len + s2_len) + 1);
	if (!dest)
		return (NULL);
	ft_memcpy(dest, s1, s1_len);
	ft_memcpy(dest + s1_len, s2, s2_len + 1);
	return (dest);
}
