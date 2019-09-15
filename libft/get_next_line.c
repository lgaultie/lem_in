/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgaultie <lgaultie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/28 12:12:59 by lgaultie          #+#    #+#             */
/*   Updated: 2019/09/15 15:55:07 by lgaultie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// /*
// ** ft_read() reads the file and returns -1 in case of problem, and 0 if the
// ** file was entirely browsed and no line was found. Else, it fills line with
// ** what is in static_buff and calls get_next_line() to retrieve a new line.
// */
//
// static int	ft_read(const int fd, char *static_buff, char **line)
// {
// 	int		read_nb;
// 	char	*tmp;
//
// 	read_nb = read(fd, static_buff, BUFF_SIZE);
// 	if (read_nb == -1)
// 		return (-1);
// 	if (read_nb == 0)
// 		return (0);
// 	static_buff[read_nb] = '\0';
// 	tmp = *line;
// 	*line = ft_strjoin(*line, static_buff);
// 	if (*line == NULL)
// 		return (-1);
// 	ft_strdel(&tmp);
// 	ft_strclr(static_buff);
// 	return (1);
// }
//
// /*
// ** ft_n_found() browses line to check if there is a \n. If it does, we fill
// ** static_buff with what is after \n and clear line after \n.
// */
//
// static int	ft_n_found(char *static_buff, char **line)
// {
// 	int	c;
//
// 	c = 0;
// 	while ((*line)[c] && (*line)[c] != '\n')
// 		c++;
// 	if ((*line)[c] == '\n')
// 	{
// 		ft_strcpy(static_buff, *line + c + 1);
// 		ft_strclr(*line + c);
// 		return (1);
// 	}
// 	return (0);
// }
//
// /*
// ** get_next_line() checks if we have something in static_buff. If we do, we put
// ** it in line and call ft_n_found() to check if we find a \n. Else, we call
// ** ft_read() and ft_f_found() on the line.
// */
//
// int			get_next_line(const int fd, char **line)
// {
// 	static char	static_buff[FD_MAX + 1][BUFF_SIZE + 1];
// 	int			ret;
//
// 	if (fd < 0 || fd > FD_MAX || line == NULL || BUFF_SIZE < 0 ||
// 		read(fd, NULL, 0))
// 		return (-1);
// 	*line = NULL;
// 	if (ft_strlen(static_buff[fd]))
// 	{
// 		*line = ft_strdup(static_buff[fd]);
// 		if (*line == NULL)
// 			return (-1);
// 		ft_strclr(static_buff[fd]);
// 		if ((ft_n_found(static_buff[fd], line)) == 1)
// 			return (1);
// 	}
// 	while ((ret = ft_read(fd, static_buff[fd], line)))
// 		if (ft_strlen(*line))
// 			if ((ft_n_found(static_buff[fd], line)) == 1)
// 				return (1);
// 	if (*line)
// 		return (1);
// 	return (ret);
// }

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
	if (ret == 0 && str)
		ft_memdel((void**)&str);
	return (ret);
}
