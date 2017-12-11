/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgauther <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/07 16:31:37 by vgauther          #+#    #+#             */
/*   Updated: 2017/12/10 16:48:11 by vgauther         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_re(char *src, int ret)
{
	char	*dest;
	int		i;

	i = 0;
	if (!(dest = malloc(ret + sizeof(char) * ft_strlen(src) + 1)))
		return (NULL);
	while (src[i])
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = 0;
	free(src);
	return (dest);
}

char	*ft_save(int fd, int i, int x, char *save)
{
	char	buf[BUFF_SIZE + 1];
	int		ret;

	while ((ret = read(fd, buf, BUFF_SIZE)) > 0)
	{
		i = -1;
		if (!(buf[ret] = 0) && save == NULL)
		{
			if (!(save = malloc(ret + 1)))
				return (NULL);
			while (buf[++i])
				save[x++] = buf[i];
		}
		else
		{
			if ((save = ft_re(save, ret)) == NULL)
				return (NULL);
			while (buf[++i])
				save[x++] = buf[i];
		}
		save[x] = 0;
	}
	return (save);
}

char	*ft_line(char **line2, char *str)
{
	int i;
	int x;

	x = 0;
	i = 0;
	while (str[i] != '\n' && str[i])
		i++;
	if (!(line2[0] = malloc(sizeof(char) * i + 1)))
		return (NULL);
	i = 0;
	while (str[i] != '\n' && str[i])
	{
		line2[0][i] = str[i];
		i++;
	}
	line2[0][i] = 0;
	i += str[i] != 0 ? 1 : 0;
	while (str[i] != 0)
	{
		str[x] = str[i];
		i++;
		x++;
	}
	str[x] = 0;
	return (str);
}

int		get_next_line(const int fd, char **line)
{
	static char *str[1024];

	if (fd < 0 || line == NULL || fd > 1024 || BUFF_SIZE < 1)
		return (-1);
	if (!(str[fd]))
		str[fd] = ft_save(fd, 0, 0, NULL);
	if (str[fd] == NULL)
		return (-1);
	if (str[fd][0] == 0)
	{
		line[0] = NULL;
		return (0);
	}
	if ((str[fd] = ft_line(line, str[fd])) == NULL)
		return (-1);
	return (1);
}
