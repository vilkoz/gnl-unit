/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrybalko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/15 15:32:05 by vrybalko          #+#    #+#             */
/*   Updated: 2016/12/19 20:30:16 by vrybalko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int		proc_buf(char **line, t_list *lst, int *is_sec)
{
	char	*nl;

	if (((char*)(lst->content))[0] == '\0')
		return (0);
	else
	{
		if ((nl = ft_strchr((const char*)lst->content, '\n')) == NULL)
		{
			if (*is_sec == 0)
			{
				*line = ft_strdup((const char*)lst->content);
				ft_bzero(lst->content, BUFF_SIZE + 1);
				*is_sec = 1;
				return (0);
			}
			else
			{
				*line = ft_strjoin((const char*)*line, (const char*)lst->content);
				ft_bzero(lst->content, BUFF_SIZE + 1);
				return (0);
			}
		}
		*nl = '\0';
		if (*is_sec == 0)
		{
			*line = ft_strdup((const char*)lst->content);
			lst->content =
				ft_strcpy((char*)lst->content, (const char*)(nl + 1));
			return (1);
		}
		else
		{
			*line = ft_strjoin((const char*)*line, (const char*)lst->content);
			lst->content =
				ft_strcpy((char*)lst->content, (const char*)(nl + 1));
			return (1);
		}
	}
	return (0);
}

int		get_next_line(const int fd, char **line)
{
	static t_list	*lst;
	int				is_sec;
	int				i;

	if (fd < 0)
		return (-1);
	i = 0;
	is_sec = 0;
	if (lst == NULL)
		lst = ft_lstnew((const void *)ft_strnew(BUFF_SIZE + 1), BUFF_SIZE + 1);
	if (proc_buf(line, lst, &is_sec))
		return (1);
	while ((i = read(fd, lst->content, BUFF_SIZE)) > 0)
	{
		if (proc_buf(line, lst, &is_sec))
			return (1);
	}
	if (proc_buf(line, lst, &is_sec))
		return (1);
	if (i == -1)
		return (-1);
	if (is_sec != 0)
	{
		is_sec = 0;
		return (1);
	}
	ft_bzero(*line, BUFF_SIZE + 1);
	return (0);
}
