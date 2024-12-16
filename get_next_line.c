/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agarbacz <agarbacz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 13:51:56 by agarbacz          #+#    #+#             */
/*   Updated: 2024/12/16 17:50:25 by agarbacz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

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

// free if the substr is empty (line 61)
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
	if (!tmp_remains)
		return (NULL);
	if (tmp_remains[0] == '\0')
	{
		free(tmp_remains);
		return (NULL);
	}
	line[i + 1] = '\0';
	return (tmp_remains);
}


char	*get_next_line(int fd)
{
	static char	*content_storage = NULL;
	char		*buf;
	char		*line;
	char		*tmp_remains;

	line = NULL;
	buf = NULL;
	tmp_remains = NULL;
	buf = malloc(BUFFER_SIZE + 1);
	if (!buf)
		return (NULL);
	content_storage = read_file(fd, buf, content_storage);
	free(buf);
	if (!content_storage || *content_storage == '\0')
	{
		free(content_storage);
		return (NULL);
	}
	line = ft_strdup(content_storage);
	tmp_remains = handle_content(line);
	free(content_storage);
	content_storage = tmp_remains;
	return (line);
}

// int main()
// {
// 	int fd = open("tests/testfiles/testfile_basic.txt", O_RDONLY);
// 	char *line;

// 	if (fd < 0)
// 		return (1);

// 	while ((line = get_next_line(fd)) != NULL)
// 	{
// 		printf("%s", line);
// 		free(line);
// 	}
// 	close(fd);
// 	return (0);
// }