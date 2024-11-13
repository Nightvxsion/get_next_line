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
	char	result;

	result = ft_strjoin(buffer, new);
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
	if (!old) // if EOL is \0
	{
		free(old);
		return (NULL);
	}
	line = malloc((ft_strlen(old) - i + 1) * sizeof(char)); 
	i++;
	while (old[i])
		line[j++] = old[i++];
	free(old);
	return(line);
}
