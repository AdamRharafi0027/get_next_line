/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arharafi <arharafi@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/16 09:56:41 by arharafi          #+#    #+#             */
/*   Updated: 2026/11/17 07:58:27 by arharafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static t_gnl_list	*find_node(t_gnl_list **head, int fd)
{
	t_gnl_list	*cur;

	cur = *head;
	while (cur)
	{
		if (cur->fd == fd)
			return (cur);
		cur = cur->next;
	}
	cur = malloc(sizeof(t_gnl_list));
	if (!cur)
		return (NULL);
	cur->fd = fd;
	cur->reminder = NULL;
	cur->next = *head;
	*head = cur;
	return (cur);
}

static char	*free_node(t_gnl_list **lst, int fd)
{
	t_gnl_list	*current;
	t_gnl_list	*previous;

	if (!lst || !*lst)
		return (NULL);
	current = *lst;
	previous = NULL;
	while (current)
	{
		if (current->fd == fd)
		{
			if (previous)
				previous->next = current->next;
			else
				*lst = current->next;
			free(current->reminder);
			free(current);
			return (NULL);
		}
		previous = current;
		current = current->next;
	}
	return (NULL);
}

static ssize_t	fill_reminder(int fd, t_gnl_list *node)
{
	char	*buffer;
	char	*tmp;
	ssize_t	bytes;

	buffer = malloc((size_t)BUFFER_SIZE + 1);
	if (!buffer)
		return (-1);
	bytes = 1;
	while (bytes > 0 && !ft_strchr(node->reminder, '\n'))
	{
		bytes = read(fd, buffer, BUFFER_SIZE);
		if (bytes <= 0)
			break ;
		buffer[bytes] = '\0';
		tmp = ft_strjoin(node->reminder, buffer);
		free(node->reminder);
		node->reminder = tmp;
		if (!tmp)
			bytes = -1;
	}
	free(buffer);
	return (bytes);
}

char	*get_next_line(int fd)
{
	static t_gnl_list	*head;
	t_gnl_list			*node;
	char				*line;
	char				*tmp;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
		return (free_node(&head, fd));
	node = find_node(&head, fd);
	if (!node)
		return (NULL);
	if (fill_reminder(fd, node) < 0
		|| !node->reminder || !node->reminder[0])
		return (free_node(&head, fd));
	line = gnl_get_line(node->reminder);
	if (!line)
		return (free_node(&head, fd));
	tmp = gnl_get_remin(node->reminder);
	free(node->reminder);
	node->reminder = tmp;
	return (line);
}
