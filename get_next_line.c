/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrybalko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/15 15:32:05 by vrybalko          #+#    #+#             */
/*   Updated: 2016/12/21 20:23:06 by vrybalko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int		nl_free(char **line, t_buf *lst, int *is_sec)
{
	char	*tmp;

	if (*is_sec == 0)
	{
		*line = ft_strdup((const char*)lst->text);
		ft_bzero(lst->text, BUFF_SIZE + 1);
		*is_sec = 1;
		return (0);
	}
	else
	{
		tmp = *line;
		*line = ft_strjoin((const char*)tmp, (const char*)lst->text);
		ft_bzero(lst->text, BUFF_SIZE + 1);
		free(tmp);
		return (0);
	}
	return (0);
}

int		proc_buf(char **line, t_buf *lst, int *is_sec)
{
	char	*nl;
	char	*tmp;

	if (((char*)(lst->text))[0] == '\0')
		return (0);
	if ((nl = ft_strchr((const char*)lst->text, '\n')) == NULL)
		return (nl_free(line, lst, is_sec));
	*nl = '\0';
	if (*is_sec == 0)
	{
		*line = ft_strdup((const char*)lst->text);
		lst->text = ft_strcpy((char*)lst->text, (const char*)(nl + 1));
		return (1);
	}
	else
	{
		tmp = *line;
		*line = ft_strjoin((const char*)tmp, (const char*)lst->text);
		lst->text = ft_strcpy((char*)lst->text, (const char*)(nl + 1));
		free(tmp);
		return (1);
	}
	return (0);
}

t_buf	*ft_buf_new(void *content, const int fd)
{
	t_buf	*new;

	new = (t_buf *)malloc(sizeof(t_buf));
	new->text = (char *)malloc(BUFF_SIZE + 1);
	new->text = ft_strcpy(new->text, (const char *)content);
	new->fd = (int)fd;
	return (new);
}

t_list	*find_fd(t_list *lst, const int fd)
{
	t_list	*tmp;
	t_buf	*tmp_buf;
	char	*tmp1;

	if (!lst)
	{
		tmp1 = ft_strnew(BUFF_SIZE + 1);
		tmp_buf = ft_buf_new(tmp1, fd);
		lst = ft_lstnew(tmp_buf, sizeof(tmp_buf));
		((t_buf *)lst->content)->fd = fd;
		free(tmp1);
		free(tmp_buf);
		return (lst);
	}
	while (lst->next)
	{
		if (((t_buf *)(lst->content))->fd == fd)
			return (lst);
		lst = lst->next;
	}
	tmp1 = ft_strnew(BUFF_SIZE + 1);
	tmp_buf = ft_buf_new(tmp1, fd);
	tmp = ft_lstnew(tmp_buf, BUFF_SIZE + 5);
	((t_buf *)tmp->content)->fd = fd;
	free(tmp1);
	free(tmp_buf);
	lst->next = tmp;
	return (lst->next);
}

int		get_next_line(const int fd, char **line)
{
	static t_list	*lst;
	t_list			*tmp;
	int				is_sec;
	int				i;

	if (fd < 0)
		return (-1);
	i = 0;
	is_sec = 0;
	tmp = find_fd(lst, fd);
	if (proc_buf(line, (t_buf *)(tmp->content), &is_sec))
		return (1);
	while ((i = read(fd, ((t_buf *)(tmp->content))->text, BUFF_SIZE)) > 0)
		if (proc_buf(line, (t_buf *)(tmp->content), &is_sec))
			return (1);
	if (proc_buf(line, (t_buf *)(tmp->content), &is_sec))
		return (1);
	if (i == -1)
		return (-1);
	if (is_sec != 0)
	{
		is_sec = 0;
		return (1);
	}
	ft_bzero(*line, ft_strlen(*line));
	return (0);
}
