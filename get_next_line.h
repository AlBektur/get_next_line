/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: besaipid <besaipid@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/27 14:12:30 by besaipid          #+#    #+#             */
/*   Updated: 2026/09/30 14:04:18 by besaipid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef 	GET_NEXT_LINE_H
# define 	GET_NEXT_LINE_H

#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdbool.h>

char *get_next_line(int fd);
int ft_strlen(char *s);
char    *ft_strjoin(char *s1, char *s2);
char	*ft_strdup(char *s);
char    *ft_substr(char *str,  int index);

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 1
#endif

#endif
