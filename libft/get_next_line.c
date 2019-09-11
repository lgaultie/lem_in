/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgaultie <lgaultie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/28 12:12:59 by lgaultie          #+#    #+#             */
/*   Updated: 2019/09/11 17:34:23 by lgaultie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char				*readfile(char *str, int fd)
{
	ssize_t	size;
	char	buff[BUFF_SIZE + 1];
	char	*tmp;

	size = 1;
	while (!(ft_strchr(str, '\n')) && size > 0)
	{
		size = read(fd, buff, BUFF_SIZE);
		if (size > 0)
		{
			buff[size] = '\0';
			tmp = str;
			if (!(str = ft_strjoin(tmp, buff)))
				return (NULL);
			free(tmp);
		}
		if (size == -1)
			return (NULL);
	}
	return (str);
}

static int				lastline(char **line, char **str, unsigned int i)
{
	if (i == 0)
	{
		*line = "";
		return (0);
	}
	else
	{
		if (!(*line = ft_strdup(*str)))
			return (-1);
		(*str) = (*str) + i;
		return (1);
	}
}

static int				stock(char **str, char **line)
{
	unsigned int		i;
	char				*save;

	i = 0;
	while ((*str)[i] != '\n' && (*str)[i] != '\0')
		i++;
	if ((*str)[i] == '\n')
	{
		if (!(save = ft_strsub(*str, i + 1, ft_strlen(*str) - i - 1)))
			return (-1);
		(*str)[i] = '\0';
		if (!(*line = ft_strdup(*str)))
			return (-1);
		free(*str);
		*str = save;
		return (1);
	}
	if ((*str)[i] == '\0')
	{
		if (lastline(line, str, i) == 1)
			return (1);
	}

	return (0);
}

int						get_next_line(int const fd, char **line)
{
	static char		*str = NULL;
	char			buf[BUFF_SIZE];
	int			ret;

	if (fd < 0 || BUFF_SIZE < 1 || line == NULL \
	|| read(fd, buf, 0) == -1)
		return (-1);
	if (!str)
	{
		if (!(str = ft_strnew(0)))
			return (-1);
	}
	if ((str = readfile(str, fd)) == NULL)
		return (-1);
	ret = stock(&str, line);
	if (ret == 0)
		free(str);
	return (ret);
}
