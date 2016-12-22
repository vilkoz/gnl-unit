/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrybalko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/19 18:32:06 by vrybalko          #+#    #+#             */
/*   Updated: 2016/12/21 19:40:40 by vrybalko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>
#include <fcntl.h>

int		main(void)
{
	int		i;
	int		fd;
	int		fd1;
	int		big_fd;
	int		tmp;
	char	*line;
	char	*big_line;
	int		res;

	i = 25;
	line = NULL;
	big_fd = open("one_big_fat_line.txt", O_RDONLY);
	get_next_line(big_fd, &big_line);
	fd1 = open("test1.txt", O_RDONLY);
	fd = open("test2.txt", O_RDONLY);
	while (i > 0)
	{
		if (i % 2 == 0)
			tmp = fd;
		else
			tmp = fd1;
		res = get_next_line(tmp, &line);
		printf("str is %d = |%s|\n", res, line);
		i--;
	}
	free(big_line);
	free(line);
	close(fd);
	close(big_fd);
	close(fd1);
	return (0);
}
/*
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
   }*/
/*
int		main(void)
{
	char    *line;
	int     out;
	int     p[2];
	int     fd;
	int     ret;

	out = dup(1);
	pipe(p);

	fd = 1;
	dup2(p[1], fd);
	write(fd, "abcd\n", 5); 
	write(fd, "efgh\n", 5); 
	close(p[1]);
	dup2(out, fd);
	get_next_line(p[0], &line);

	printf("\n-------------\n");
	printf("\nmy line = |%s|\n", line);
	printf("\n-------------\n");

	get_next_line(p[0], &line);

	printf("\n-------------\n");
	printf("\nmy line = |%s|\n", line);
	printf("\n-------------\n");

	ret = get_next_line(p[0], &line);

	printf("\n-------------\n");
	printf("\nret = %d my line = |%s|\n", ret, line);
	printf("\n-------------\n");


}*/
