/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrybalko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/15 15:31:58 by vrybalko          #+#    #+#             */
/*   Updated: 2016/12/21 12:17:12 by vrybalko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __GET_NEXT_LINE_H
# define __GET_NEXT_LINE_H

# include <sys/types.h>
# include <sys/uio.h>
# include <unistd.h>
# include <stdlib.h>
# include "libft/libft.h"
# define BUFF_SIZE 20

int					get_next_line(const int fd, char **line);

typedef struct		s_buf
{
	char			*text;
	int				fd;
	struct s_buf	*next;
}					t_buf;

#endif
