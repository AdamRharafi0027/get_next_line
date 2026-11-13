/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arharafi <arharafi@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/12 19:10:37 by arharafi          #+#    #+#             */
/*   Updated: 2026/11/13 08:11:38 by arharafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*free_reminder(char **reminder)
{
	free(*reminder);
	*reminder = NULL;
	return (NULL);
}

char	*get_line(char *reminder)
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

char	*get_remin(char *reminder)
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

ssize_t	fill_reminder(int fd, char **reminder)
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

char	*get_next_line_bonus(int fd)
{
	static char	*reminder[FD_MAX];
	char		*line;
	char		*tmp;

	if (fd < 0 || BUFFER_SIZE <= 0 || fd >= FD_MAX)
		return (NULL);
	if (read(fd, 0, 0) < 0 || fill_reminder(fd, &reminder[fd]) < 0)
		return (free_reminder(&reminder[fd]));
	if (!reminder[fd] || !reminder[fd][0])
		return (free_reminder(&reminder[fd]));
	line = get_line(reminder[fd]);
	if (!line)
		return (free_reminder(&reminder[fd]));
	tmp = get_remin(reminder[fd]);
	free(reminder[fd]);
	reminder[fd] = tmp;
	return (line);
}
