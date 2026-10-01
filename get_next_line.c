/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: besaipid <besaipid@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/27 14:20:29 by besaipid          #+#    #+#             */
/*   Updated: 2026/10/01 15:55:19 by besaipid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int		has_newline(char *str)
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


char *get_line(char *buffer, char **static_buffer)
{
	char	*temp;
	char	*line = NULL;
	int		index;

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
	else
	{
		free(*static_buffer);
		*static_buffer = ft_strdup(temp);
		free(temp);
	}
	return (line);
}

char	*read_line(int fd)
{
	char	*buffer;
	char	*line = NULL;
	size_t bytes;
	static char	*static_buffer = NULL;

	buffer = malloc((sizeof(char) * BUFFER_SIZE) + 1);
	while (true)
	{
		if (static_buffer && has_newline(static_buffer) != -1)
		{
			line = get_line("", &static_buffer);
			free(static_buffer);
			break ;
		}
		bytes = read(fd, buffer, BUFFER_SIZE);
	

		if (bytes == 0)
		{

			if (static_buffer)
			{
				line = ft_strdup(static_buffer);
				free(static_buffer);
				static_buffer = NULL;
				free(buffer);
				return (line);
			}

			else
			{
				free(buffer);
				static_buffer = NULL;
				line = NULL;
				return (line);
			}
	
		}
		else
		{
			buffer[bytes] = '\0';
			line = get_line(buffer, &static_buffer);
		}
		if (line)
			break ;
	}
	free(buffer);
	return (line);
}

char	*get_next_line(int fd)
{
	char *res;

	if (fd < 0 || fd > 999 || BUFFER_SIZE < 0)
		return (NULL);
	res = read_line(fd);
	return (res);
}

/*
int	main(int argc, char *argv[])
{
	int fd = open(argv[1], O_RDONLY);
	char	*res;

	while (1)
	{
		res = get_next_line(fd);
		if (res == NULL)
			break ;
		printf("%s", res);
		free(res);
	}
	return (0);
}*/
