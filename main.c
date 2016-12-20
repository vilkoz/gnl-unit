/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrybalko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/19 18:32:06 by vrybalko          #+#    #+#             */
/*   Updated: 2016/12/19 18:37:14 by vrybalko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>
#include <fcntl.h>
/*int		main(void)
  {
  int		i;
  int		fd;
  char	*line;
  int		res;

  i = 5;
  line = ft_strnew(10000);
  fd = open("test1.txt", O_RDONLY);
  while (i > 0)
  {
  res = get_next_line(fd, &line);
  printf("str is %d = |%s|\n", res, line);
  i--;
  }
  close(fd);
  return (0);
  }*/

int		main(void)
{
	char *line;
	int     out;
	int     p[2];
	int     fd; 
	int     gnl_ret;
	char	line2[5];

	fd = 1;
	out = dup(fd);
	pipe(p);
	dup2(p[1], fd);
	write(fd, "aaa", 3); 
	close(p[1]);
	dup2(out, fd);
	gnl_ret = get_next_line(p[0], &line);
	printf("ret = %d str = |%s|\n", gnl_ret, line);
	gnl_ret = get_next_line(p[0], &line);
	printf("ret = %d str = |%s|\n", gnl_ret, line);
	gnl_ret = get_next_line(p[0], &line);
	printf("ret = %d str = |%s|\n", gnl_ret, line);
}
