/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmouele <cmouele@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/23 10:31:59 by cmouele           #+#    #+#             */
/*   Updated: 2019/07/17 17:46:21 by lgaultie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** ft_read() reads the file and returns -1 in case of problem, and 0 if the
** file was entirely browsed and no line was found. Else, it fills line with
** what is in static_buff and calls get_next_line() to retrieve a new line.
*/

static int	ft_read(const int fd, char *static_buff, char **line)
{
	int		read_nb;
	char	*tmp;

	read_nb = read(fd, static_buff, BUFF_SIZE);
	if (read_nb == -1)
		return (-1);
	if (read_nb == 0)
		return (0);
	static_buff[read_nb] = '\0';
	tmp = *line;
	*line = ft_strjoin(*line, static_buff);
	if (*line == NULL)
		return (-1);
	ft_strdel(&tmp);
	ft_strclr(static_buff);
	return (1);
}

/*
** ft_n_found() browses line to check if there is a \n. If it does, we fill
** static_buff with what is after \n and clear line after \n.
*/

static int	ft_n_found(char *static_buff, char **line)
{
	int	c;

	c = 0;
	while ((*line)[c] && (*line)[c] != '\n')
		c++;
	if ((*line)[c] == '\n')
	{
		ft_strcpy(static_buff, *line + c + 1);
		ft_strclr(*line + c);
		return (1);
	}
	return (0);
}

/*
** get_next_line() checks if we have something in static_buff. If we do, we put
** it in line and call ft_n_found() to check if we find a \n. Else, we call
** ft_read() and ft_f_found() on the line.
*/

int			get_next_line(const int fd, char **line)
{
	static char	static_buff[FD_MAX + 1][BUFF_SIZE + 1];
	int			ret;

	if (fd < 0 || fd > FD_MAX || line == NULL || BUFF_SIZE < 0 ||
		read(fd, NULL, 0))
		return (-1);
	*line = NULL;
	if (ft_strlen(static_buff[fd]))
	{
		*line = ft_strdup(static_buff[fd]);
		if (*line == NULL)
			return (-1);
		ft_strclr(static_buff[fd]);
		if ((ft_n_found(static_buff[fd], line)) == 1)
			return (1);
	}
	while ((ret = ft_read(fd, static_buff[fd], line)))
		if (ft_strlen(*line))
			if ((ft_n_found(static_buff[fd], line)) == 1)
				return (1);
	if (*line)
		return (1);
	return (ret);
}
