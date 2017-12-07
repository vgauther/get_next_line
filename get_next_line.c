/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgauther <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/05 14:59:00 by vgauther          #+#    #+#             */
/*   Updated: 2017/12/07 14:41:36 by vgauther         ###   ########.fr       */
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
	char			buf[BUFF_SIZE + 1];
	int				ret;

	while ((ret = read(fd, buf, BUFF_SIZE)) > 0)
	{
		i = -1;
		if (!(buf[ret] = 0) && save == NULL)
		{
			if (!(save = malloc(ret)))
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

int		get_next_line(int const fd, char **line)
{
	static char	*save2;
	int			i;
	int			x;
	char		tmp;

	if (!(i = 0) && ((fd < 0 || line == NULL ||
		!(save2)) && ((save2 = ft_save(fd, 0, 0, NULL)) == NULL)))
		return (-1);
	if (!(x = 0) && save2[0] == 0)
		line[0] = ft_strdup("");
	if (!(x = 0) && save2[0] == 0)
		return (0);
	while (save2[i] != '\n' && save2[i] != 0)
		i++;
	if (!(line[0] = malloc(sizeof(char) * (i + 1))))
		return (-1);
	i = -1;
	while (save2[++i] != 0 && save2[i] != '\n')
		line[0][i] = save2[i];
	line[0][i] = 0;
	i += save2[i] != 0 ? 1 : 0;
	while (save2[i] != 0)
		save2[x++] = save2[i++];
	save2[x] = 0;
	return (1);
}
