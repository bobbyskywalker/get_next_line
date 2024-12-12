#include "get_next_line.h"

int	get_line_len(char *buf)
{
	int	len;

	len = 0;
	while (*buf != '\n' && *buf)
	{
		len++;
		buf++;
	}
	return (len + 1);
}

void	save_remains(char *buf, char **remains)
{
	int	i;
	int	len;

	i = 0;
	len = get_line_len(buf);
	*remains = malloc((len + 1) * sizeof(char));
	if (!*remains)
		return ;
	while (*buf)
	{
		(*remains)[i++] = *buf;
		buf++;
	}
	(*remains)[i] = '\0';
}

char	*extract_line(char *buf, char **remains)
{
	char	*line;
	int		i;

	i = 0;
	line = malloc((get_line_len(buf) + 1) * sizeof(char));
	if (!line)
		return (NULL);
	while (*buf)
	{
		line[i] = *buf;
		buf++;
		i++;
		if (*buf == '\n')
		{
			line[i++] = '\n';
			line[i] = '\0';
			buf++;
			break ;
		}
	}
	save_remains(buf, remains);
	return (line);
}

char	*get_next_line(int fd)
{
	char		*buf;
	int			len;
	static char	*remains;
	char		*line;

	remains = NULL;
	buf = malloc(BUFFER_SIZE);
	if (!buf)
		return (NULL);
	len = read(fd, buf, BUFFER_SIZE);
	if (len < 0)
	{
		free(buf);
		return (NULL);
	}
	while (len > 0)
	{
		if (ft_strchr(buf, '\n') || ft_strchr(buf, '\0'))
		{
			line = extract_line(buf, &remains);
			free(buf);
			if (remains)
				return ft_strjoin(remains, line);
			return (line);
		}
		len = read(fd, buf, BUFFER_SIZE);
	}
	free(buf);
	return (NULL);
}

int	main(void)
{
	int		fd;
	char	*line;

	fd = open("testfile.txt", O_RDONLY);
	if (fd == -1)
	{
		perror("Error opening file");
		return (1);
	}
	for (int i = 0; i < 4; i++)
	{
		line = get_next_line(fd);
		if (line)
		{
			printf("Read line: %s", line);
			free(line);
		}
	}
	close(fd);
	return (0);
}
