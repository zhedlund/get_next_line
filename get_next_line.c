/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zhedlund <zhedlund@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 23:10:38 by zhedlund          #+#    #+#             */
/*   Updated: 2023/06/19 12:23:38 by zhedlund         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	read_line(int fd, char **storage, char **temp)
{
	char	*buf;
	int		read_chars;

	buf = ft_calloc(BUFFER_SIZE + 1, sizeof(*buf));
	if (!buf)
		return ;
	read_chars = 1;
	while (read_chars > 0)
	{
		read_chars = read(fd, buf, BUFFER_SIZE);
		if (read_chars == -1)
		{
			free_strings(&buf, storage, temp);
			return ;
		}
		buf[read_chars] = '\0';
		*temp = ft_strdup(*storage);
		free_strings(storage, 0, 0);
		*storage = join_strings(*temp, buf);
		free_strings(temp, 0, 0);
		if (ft_strchr(*storage, '\n'))
			break ;
	}
	free_strings(&buf, 0, 0);
}

char	*extract_line(char **storage)
{
	char	*line;
	char	*newline_pos;
	size_t	line_length;
	size_t	rest_length;

	line = NULL;
	newline_pos = ft_strchr(*storage, '\n');
	if (newline_pos != NULL)
	{
		line_length = newline_pos - *storage + 1;
		line = ft_calloc(line_length + 1, sizeof(*line));
		ft_memmove(line, *storage, line_length);
		rest_length = ft_strlen(newline_pos + 1);
		ft_memmove(*storage, newline_pos + 1, rest_length + 1);
	}
	else
	{
		line = ft_strdup(*storage);
		free_strings(storage, 0, 0);
	}
	return (line);
}

char	*join_strings(const char *s1, const char *s2)
{
	char	*str;
	size_t	len1;
	size_t	len2;

	if (!s1 || !s2)
		return (NULL);
	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	str = ft_calloc(len1 + len2 + 1, sizeof(*str));
	if (!str)
		return (NULL);
	ft_memmove(str, s1, len1);
	ft_memmove(str + len1, s2, len2);
	return (str);
}

void	free_strings(char **s1, char **s2, char **s3)
{
	if (s1 && *s1)
	{
		free(*s1);
		*s1 = NULL;
	}
	if (s2 && *s2)
	{
		free(*s2);
		*s2 = NULL;
	}
	if (s3 && *s3)
	{
		free(*s3);
		*s3 = NULL;
	}
}

char	*get_next_line(int fd)
{
	static char	*storage = NULL;
	char		*temp;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	temp = NULL;
	line = NULL;
	read_line(fd, &storage, &temp);
	if (storage != NULL && *storage != '\0')
	{
		line = extract_line(&storage);
		free_strings(&temp, 0, 0);
	}
	if (!line || *line == '\0')
	{
		free_strings(&storage, &line, &temp);
		return (NULL);
	}
	return (line);
}

/*#include <stdio.h>

int	main(int argc, char **argv)
{
	int	fd;
	char	*line;

	(void)argc;
	fd = open(argv[1], O_RDONLY);
	line = "";
	while (line != NULL)
	{
		line = get_next_line(fd);
		printf("%s", line);
	}
	fd = close(fd);
	return (0);
}*/
