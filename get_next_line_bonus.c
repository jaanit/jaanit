/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjaanit <rjaanit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/29 20:27:59 by rjaanit           #+#    #+#             */
/*   Updated: 2021/11/30 11:23:56 by rjaanit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*ft_ligne(char *str)
{
	char	*ptr;
	int		i;

	i = 0;
	if (!str[i])
		return (NULL);
	while (str[i] && str[i] != '\n')
		i++;
	ptr = (char *)malloc(sizeof(char) * (i + 2));
	if (!ptr)
		return (NULL);
	i = 0;
	while (str[i] && str[i] != '\n')
	{
	ptr[i] = str[i];
		i++;
	}
	if (str[i] == '\n')
	{
		ptr[i] = str[i];
		i++;
	}
	ptr[i] = '\0';
	return (ptr);
}

char	*ft__next(char *str)
{
	char	*ptr;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (str[i] && str[i] != '\n')
		i++;
	if (!str[i])
	{
		free (str);
		return (NULL);
	}
	ptr = (char *)malloc(sizeof(char) * (ft_strlen(str) - i + 1));
	if (!ptr)
		return (NULL);
	i++;
	while (str[i])
	{
		ptr[j++] = str[i++];
	}
	ptr[j] = '\0';
	free(str);
	return (ptr);
}

char	*ft_readfile(char *str, int fd)
{
	char	*buff;
	int		lire;

	lire = 1;
	buff = malloc(BUFFER_SIZE + 1);
	if (!buff)
		return (NULL);
	while (!ft_strchr(str, '\n') && lire != 0)
	{
		lire = read(fd, buff, BUFFER_SIZE);
		if (lire == -1)
		{
			free (buff);
			return (NULL);
		}
	buff[lire] = '\0';
	str = ft_strjoin(str, buff);
	}
	free (buff);
	return (str);
}

char	*get_next_line(int fd)
{
	static char		*str[10240];
	char			*ligne;

	if (fd < 0 || fd >= 10240 || BUFFER_SIZE <= 0)
		return (0);
	str[fd] = ft_readfile(str[fd], fd);
	if (!str[fd])
		return (NULL);
	ligne = ft_ligne(str[fd]);
	str[fd] = ft__next(str[fd]);
	return (ligne);
}
