/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arharafi <arharafi@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/10 15:55:37 by arharafi          #+#    #+#             */
/*   Updated: 2026/11/16 08:24:43 by arharafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*free_reminder(char **reminder)
{
	free(*reminder);
	*reminder = NULL;
	return (NULL);
}

static char	*get_line(char *reminder)
{
	size_t		i;
	char		*line;

	if (!reminder)
		return (NULL);
	i = 0;
	while (reminder[i] && reminder[i] != '\n')
		i++;
	if (reminder[i] == '\n')
		i++;
	line = malloc(i + 1);
	if (!line)
		return (NULL);
	line[i] = '\0';
	while (i--)
		line[i] = reminder[i];
	return (line);
}

static char	*get_remin(char *reminder)
{
	size_t		i;
	size_t		j;
	char		*rem;

	if (!reminder)
		return (NULL);
	i = 0;
	while (reminder[i] && reminder[i] != '\n')
		i++;
	if (!reminder[i] || !reminder[i + 1])
		return (NULL);
	rem = malloc(ft_strlen(reminder + i + 1) + 1);
	if (!rem)
		return (NULL);
	j = 0;
	i++;
	while (reminder[i])
		rem[j++] = reminder[i++];
	rem[j] = '\0';
	return (rem);
}

static ssize_t	fill_reminder(int fd, char **reminder)
{
	char		*buffer;
	char		*tmp;
	ssize_t		bytes;

	buffer = malloc((size_t)BUFFER_SIZE + 1);
	if (!buffer)
		return (-1);
	bytes = 1;
	while (bytes > 0 && (!*reminder || !ft_strchr(*reminder, '\n')))
	{
		bytes = read(fd, buffer, BUFFER_SIZE);
		if (bytes <= 0)
			break ;
		buffer[bytes] = '\0';
		tmp = ft_strjoin(*reminder, buffer);
		free(*reminder);
		*reminder = tmp;
		if (!tmp)
			bytes = -1;
	}
	free(buffer);
	return (bytes);
}

char	*get_next_line(int fd)
{
	static char	*reminder;
	char		*line;
	char		*tmp;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
		return (free_reminder(&reminder));
	if (fill_reminder(fd, &reminder) < 0)
		return (free_reminder(&reminder));
	if (!reminder || !reminder[0])
		return (free_reminder(&reminder));
	line = get_line(reminder);
	if (!line)
		return (free_reminder(&reminder));
	tmp = get_remin(reminder);
	free(reminder);
	reminder = tmp;
	return (line);
}
