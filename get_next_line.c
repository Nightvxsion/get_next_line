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

	if (!buffer || !new)
		return (NULL);
	result = ft_strjoin(buffer, new);
	if (!result)
		return (NULL);
	free(buffer);
	return (result);
}

char	*ft_nextline(char *old)
{
	int		i;
	int		j;
	char	*line;

	i = 0;
	if (!old[i])
		return (NULL);
	while (old[i] && old[i] != '\n')
		i++;
	line = ft_calloc((ft_strlen(old) - i), sizeof(char));
	if (!line)
		return (NULL);
	i++;
	j = 0;
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
	if (!buffer || !buffer[i])
	{
		free(buffer);
		return (NULL);
	}
	while (buffer[i] && buffer[i] != '\n')
		i++;
	new = ft_calloc(i + 2, sizeof(char));
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

	buffer = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	if (!buffer)
		return (NULL);
	while (1)
	{
		read_bytes = read(fd, buffer, BUFFER_SIZE);
		if (read_bytes <= 0)
			break ;
		buffer[read_bytes] = '\0';
		all = ft_joinfree(all, buffer);
		if (!all)
		{
			free(buffer);
			return (NULL);
		}
		if (ft_strchr(buffer, '\n'))
			break ;
	}
	if (read_bytes == -1)
		return (NULL);
	free(buffer);
	return (all);
}

char	*get_next_line(int fd)
{
	static char	*buffer;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer = ft_read_fd(fd, buffer);
	if (!buffer)
		return (NULL);
	line = ft_complete_line(buffer);
	buffer = ft_nextline(buffer);
	return (line);
}
/*int	main(void)
{
	char	*line;
	int		i;
	int		fd1;

	fd1 = open("./tests/que.txt", O_RDONLY);
	if (fd1 < 0)
	{
		printf("ERROR OPENING!\n");
		return (1);
	}
	i = 1;
	while (i < 7)
	{
		line = get_next_line(fd1);
		printf("line [%02d]: %s\n", i, line);
		free(line);
		i++;
	}
	close(fd1);
	return (0);
}*/
