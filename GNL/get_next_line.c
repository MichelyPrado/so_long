/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msilva-p <msilva-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/29 21:17:08 by msilva-p          #+#    #+#             */
/*   Updated: 2022/11/12 20:54:12 by msilva-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	check_buffer(char **buffer, char **line)
{
	char	*aux;
	int		i;

	i = 0;
	if (*buffer)
	{
		while (((*buffer)[i] != '\n') && ((*buffer)[i] != '\0'))
			i++;
		if ((*buffer)[i] == '\0')
			*line = *buffer;
		else
		{
			aux = *buffer;
			*line = ft_substr(*buffer, 0, i + 1);
			if ((*buffer)[i + 1] != '\0')
				*buffer = ft_strdup(*buffer + i + 1);
			else
				*buffer = NULL;
			free(aux);
			return (0);
		}
	}
	*buffer = NULL;
	return (1);
}

int	check_n_line(char **buffer, char **line, char **text, int i)
{
	char	*aux;

	if ((*text)[i] == '\n')
	{
		*buffer = *line;
		aux = ft_substr(*text, 0, i + 1);
		*line = ft_strjoin(*line, aux);
		if (*buffer != NULL)
			free(*buffer);
		free(aux);
		if ((*text)[i + 1] != '\0')
			*buffer = ft_strdup (*text + i + 1);
		else
			*buffer = NULL;
		return (0);
	}
	else
	{
		aux = *line;
		*line = ft_strjoin(*line, *text);
		free(aux);
	}
	return (1);
}

int	check_file(char **buffer, char **line, int fd)
{
	int		i;
	ssize_t	reader;
	char	*text;

	text = (char *)malloc(BUFFER_SIZE + 1);
	if (!text)
		return (1);
	reader = read (fd, text, BUFFER_SIZE);
	if (reader < 0)
		return (free (*buffer), free(text), 1);
	while (reader > 0)
	{
		i = 0;
		text[reader] = '\0';
		while (text[i] != '\n' && text[i] != '\0')
			i++;
		i = check_n_line (buffer, line, &text, i);
		if (i == 0)
			break ;
		else
			reader = read (fd, text, BUFFER_SIZE);
	}
	return (free(text), 0);
}

char	*get_next_line(int fd)
{
	static char	*buffer;
	char		*line;

	line = NULL;
	if (BUFFER_SIZE > 0 && fd >= 0)
	{
		if (check_buffer(&buffer, &line) == 1)
			check_file(&buffer, &line, fd);
	}
	return (line);
}
