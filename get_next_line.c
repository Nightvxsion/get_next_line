/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marcgar2 <marcgar2@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 19:31:48 by marcgar2          #+#    #+#             */
/*   Updated: 2024/11/12 19:41:11 by marcgar2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_joinfree(char *buffer, char *new)
{
	char	*result;

	result = ft_strjoin(buffer, new);
	if (!result)
	{
		free(buffer);
		return (NULL);
	}
	free(buffer);
	return (result);
}

char	*ft_nextline(char *old)
{
	int		i;
	int		j;
	char	*line;

	i = 0;
	j = 0;
	while (old[i] && old[i] != '\n')
		i++;
	if (!old)
		return (NULL);
	line = malloc((ft_strlen(old) - i + 1) * sizeof(char));
	if (!line)
		return (NULL);
	i++;
	while (old[i])
		line[j++] = old[i++];
	line[j] = '\0';
	free(old);
	return (line);
}

char	*ft_complete_line(char *buffer)
{
	int		i;
	char	*new;

	i = 0;
	if (!buffer)
		return (NULL);
	while (buffer[i] && buffer[i] != '\n')
		i++;
	new = malloc((i + 2) * sizeof(char));
	if (!new)
		return (NULL);
	i = 0;
	while (buffer[i] && buffer[i] != '\n')
	{
		new[i] = buffer[i];
		i++;
	}
	if (buffer[i] == '\n')
		new[i++] = '\n';
	new[i] = '\0';
	return (new);
}

char	*ft_read_fd(int fd, char *all)
{
	char	*buffer;
	int		read_bytes;

	buffer = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buffer)
		return (NULL);
	read_bytes = 1;
	while (read_bytes > 0)
	{
		read_bytes = read(fd, buffer, BUFFER_SIZE);
		if (read_bytes == -1)
		{
			free(buffer);
			return (NULL);
		}
		buffer[read_bytes] = '\0';
		all = ft_joinfree(all, buffer);
		if (ft_strchr(buffer, '\n'))
			break ;
	}
	free(buffer);
	return (all);
}

char	*get_next_line(int fd)
{
	static char	*buffer;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0))
		return (NULL);
	buffer = ft_read_fd(fd, buffer);
	if (!buffer)
	{
		free(buffer);
		return (NULL);
	}
	line = ft_complete_line(buffer);
	if (!line)
	{
		free(buffer);
		return (NULL);
	}
	buffer = ft_nextline(buffer);
	return (line);
}

char	*ft_line(char *buffer)
{
	char	*new;
	int		i;

	i = 0;
	if (!buffer)
		return (NULL);
	while(buffer[i] && buffer[i] != '\n')
		i++;
	new = malloc(i + 2 * sizeof(char));
	while(buffer[i] && buffer[i] != '\n')

}
