/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agarbacz <agarbacz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 13:51:56 by agarbacz          #+#    #+#             */
/*   Updated: 2024/12/13 17:10:39 by agarbacz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*read_file(int fd, char *buf, char *content_storage)
{
	ssize_t	n_bytes;
	char	*tmp;

	n_bytes = 1;
	while (n_bytes)
	{
		n_bytes = read(fd, buf, BUFFER_SIZE);
		if (n_bytes < 0)
		{
			free(content_storage);
			return (NULL);
		}
		else if (!n_bytes)
			break ;
		buf[n_bytes] = '\0';
		if (!content_storage)
			content_storage = ft_strdup("");
		tmp = ft_strjoin(content_storage, buf);
		free(content_storage);
		content_storage = tmp;
		if (ft_strchr(buf, '\n'))
			break ;
	}
	return (content_storage);
}

char	*handle_content(char *line)
{
	int		i;
	char	*tmp_remains;

	if (!line)
		return (NULL);
	i = 0;
	while (line[i] != '\n' && line[i] != '\0')
		i++;
	if (line[i] == '\0')
		return (NULL);
	tmp_remains = ft_substr(line, i + 1, ft_strlen(line) - i - 1);
	line[i + 1] = '\0';
	return (tmp_remains);
}

// func to find the now-operating-on-fd element of the list
t_fd_cs	*get_fd_store(int fd, t_fd_cs **head)
{
	t_fd_cs	*current;

	if (!*head)
	{
		current = malloc(sizeof(t_fd_cs));
		if (!current)
			return (NULL);
		*current = (t_fd_cs){fd, NULL, NULL};
		*head = current;
		return (current);
	}
	current = *head;
	while (current)
	{
		if (current->fd == fd)
			return (current);
		current = current->next;
	}
	current = malloc(sizeof(t_fd_cs));
	if (!current)
		return (NULL);
	*current = (t_fd_cs){fd, NULL, *head};
	*head = current;
	return (current);
}

void	delete_fd_node(t_fd_cs **head, int fd)
{
	t_fd_cs	*prev = NULL;
	t_fd_cs	*current = *head;

	while (current)
	{
		if (current->fd == fd)
		{
			if (prev)
				prev->next = current->next;
			else
				*head = current->next;
			free(current->content);
			free(current);
			return;
		}
		prev = current;
		current = current->next;
	}
}

char	*get_next_line(int fd)
{
	static t_fd_cs	*fd_store_list = NULL;
	t_fd_cs			*content_storage;
	char				*buf;
	char				*line;
	char				*tmp_remains;

	content_storage = get_fd_store(fd, &fd_store_list);
	if (!content_storage)
		return (NULL);
	line = NULL;
	buf = NULL;
	tmp_remains = NULL;
	buf = malloc(BUFFER_SIZE + 1);
	if (!buf)
		return (NULL);
	content_storage->content = read_file(fd, buf, content_storage->content);
	free(buf);
	if (!content_storage->content || *content_storage->content == '\0')
		return (NULL);
	line = ft_strdup(content_storage->content);
	tmp_remains = handle_content(line);
	free(content_storage->content);
	content_storage->content = tmp_remains;
	return (line);
}