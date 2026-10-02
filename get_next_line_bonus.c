/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: besaipid <besaipid@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/02 03:19:50 by besaipid          #+#    #+#             */
/*   Updated: 2026/10/02 11:52:46 by besaipid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

int	has_newline(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == 10)
			return (i);
		i++;
	}
	return (-1);
}

char	*get_line(char *buffer, char **static_buffer)
{
	char	*temp;
	char	*line;
	int		index;

	line = NULL;
	if (!*static_buffer)
		temp = ft_strdup(buffer);
	else
		temp = ft_strjoin(*static_buffer, buffer);
	index = has_newline(temp);
	if (index != -1)
	{
		index++;
		line = ft_substr(temp, index);
		free(*static_buffer);
		*static_buffer = ft_strdup(&temp[index]);
		free(temp);
		return (line);
	}
	free(*static_buffer);
	*static_buffer = ft_strdup(temp);
	return (free(temp), line);
}

char	*ft_handler(char **static_buffer, char **line, char **buffer)
{
	if (*static_buffer && *static_buffer[0])
	{
		*line = ft_strdup(*static_buffer);
		free(*static_buffer);
		*static_buffer = NULL;
		free(*buffer);
		return (*line);
	}
	free(*static_buffer);
	free(*buffer);
	*static_buffer = NULL;
	*line = NULL;
	return (*line);
}

char	*read_line(int fd, char **buffer, ssize_t bytes)
{
	char			*temp;
	char			*line;
	static char		*static_buffer[MAX_FD];

	temp = *buffer;
	line = NULL;
	while (line == NULL)
	{
		if (static_buffer[fd] && has_newline(static_buffer[fd]) != -1)
		{
			line = get_line("", &static_buffer[fd]);
			break ;
		}
		bytes = read(fd, temp, BUFFER_SIZE);
		if (bytes < 0)
		{
			line = NULL;
			break ;
		}
		if (bytes == 0)
			return (ft_handler(&static_buffer[fd], &line, &temp));
		temp[bytes] = '\0';
		line = get_line(temp, &static_buffer[fd]);
	}
	return (free(temp), line);
}

char	*get_next_line(int fd)
{
	char	*res;
	char	*buffer;
	ssize_t	bytes;

	bytes = 0;
	if (fd < 0 || fd > MAX_FD)
		return (NULL);
	if (fd > 999 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer = malloc((sizeof(char) * BUFFER_SIZE) + 1);
	if (!buffer)
		return (NULL);
	res = read_line(fd, &buffer, bytes);
	return (res);
}
/*
int	main(void)
{
	int fd1 = open("./test/123.txt", O_RDONLY);
	char *res;

	while (1)
	{
		res =  get_next_line(fd1);
		if (res == NULL)
		{
			printf("NULL");
			break ;
		}
		free(res);
	}
	return (0);
}*/
