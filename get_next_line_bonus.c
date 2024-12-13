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

t_fd_store	*get_fd_store(int fd, t_fd_store fd_store_array[])
{
	int	i;

	i = 0;
	while (i < 100)
	{
		if (fd_store_array[i].fd == fd)
			return (&fd_store_array[i]);
		if (fd_store_array[i].fd == -1)
		{
			fd_store_array[i].fd = fd;
			return (&fd_store_array[i]);
		}
		i++;
	}
	return (NULL);
}

char	*get_next_line(int fd)
{
	static t_fd_store	fd_store_array[100] = {{-1, NULL}};
	t_fd_store			*fd_store;
	char				*buf;
	char				*line;
	char				*tmp_remains;

	fd_store = get_fd_store(fd, fd_store_array);
	if (!fd_store)
		return (NULL);
	line = NULL;
	buf = NULL;
	tmp_remains = NULL;
	buf = malloc(BUFFER_SIZE + 1);
	if (!buf)
		return (NULL);
	fd_store->content = read_file(fd, buf, fd_store->content);
	free(buf);
	if (!fd_store->content || *fd_store->content == '\0')
		return (NULL);
	line = ft_strdup(fd_store->content);
	tmp_remains = handle_content(line);
	free(fd_store->content);
	fd_store->content = tmp_remains;
	return (line);
}
