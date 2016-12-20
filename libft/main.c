/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrybalko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/23 14:40:42 by vrybalko          #+#    #+#             */
/*   Updated: 2016/12/05 17:40:41 by vrybalko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define LONG 10000
#define D_ERROR { printf("Error Line %d, Funct %s ", __LINE__ - 1, __func__); }

static void		ft_printf_array(char **arr)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (arr[i] != 0)
	{
		while (arr[i][j] != '\0')
		{
			printf("%c", arr[i][j]);
			j++;
		}
		printf("\n");
		j = 0;
		i++;
	}
}

static	void	print_mem(const void *src, size_t n)
{
	size_t				i;
	const char			*mem;

	i = 0;
	mem = src;
	while (i < n)
	{
		if (mem[i] > 32 && mem[i] < 126)
			printf("%p   %8u		%c\n", &mem[i], mem[i], mem[i]);
		else
		{
			if (mem[i] == '\0')
				printf("%p   %8u		\\0\n", &mem[i], mem[i]);
			else
				printf("%p   %8u		.\n", &mem[i], mem[i]);
		}
		i++;
	}
}

static	void	print_zero(char *str, int n)
{
	char	*tmp;

	tmp = str;
	while (n--)
	{
		printf("%c", *tmp);
		tmp++;
	}
}

static	void	test_memset()
{
	printf("-----------------------ft_memset\n");
	//char		str[3840]="";
	char		b1[3840]="";
	char		b2[3840]="";

	memset(b1, 'B', 3840 - 1);
	memset(b2, 'B', 3840 - 1);
	memset(b1, 'A', 3);
	ft_memset(b2, 'A', 3);
	if (memcmp(b1, b2, 3840) != 0)
	{
		printf(">>>>>FAIL<<<<<\n");
		printf("   memset = \"%s\"\n", (char *)memset(b1, 'A', 3));
		printf("ft_memset = \"%s\"\n", (char *)ft_memset(b2, 'A', 3) );
	}
	else
		printf(">>>>>SUCCESS<<<<<<\n");
}

static void		test_bzero()
{
	printf("-----------------------ft_bzero\n");
	char		str1[20]="1234567890";
	char		str2[20]="1234567890";

	bzero(str1, 5);
	ft_bzero(str2, 5);
	if (memcmp(str1, str2, 9) != 0)
	{
		printf(">>>>>>>FAIL<<<<<<<\n");
		printf("   bzero = \""); print_zero(str1, 20); printf("\"\n");
		print_mem(str1, 9);
		printf("ft_bzero = \""); print_zero(str2, 20); printf("\"\n");
		print_mem(str2, 9);
	}
	else
		printf(">>>>>SUCCESS<<<<<<\n");
}

static void		test_memcpy()
{
	printf("-----------------------ft_memcpy\n");
	char		str3[20]="1234567890";
	char		str4[20]="1234567890";
	
	memcpy(str3, "GOPA", 4);
	ft_memcpy(str4, "GOPA", 4);
	if (memcmp(str3, str4, 10) != 0)
	{
		printf(">>>>>>>FAIL<<<<<<<\n");
		printf("   memcpy = \"%s\"\n", str3);
		printf("ft_memcpy = \"%s\"\n", str4);
	}
	else
		printf(">>>>>SUCCESS<<<<<<\n");
}

static void		test_memccpy()
{
	printf("-----------------------ft_memccpy\n");
	char		str5[20]="1234567890ABCDEF";
	char		str6[20]="1234567890ABCDEF";

	memccpy((void *)str5, (const void *)"IAcMALIVE", 'c',  15);
	ft_memccpy((void *)str6, (const void *)"IAcMALIVE", 'c',  15);
	if (memcmp(str5, str6, 10) != 0)
	{
		printf(">>>>>>>FAIL<<<<<<<\n");
		printf("   memccpy = \"%s\"\n", (char *)str5);
		printf("ft_memccpy = \"%s\"\n", (char *)str6);
	}
	else
		printf(">>>>>SUCCESS<<<<<\n");
}

static void		test_memccpy1()
{
	char    buff1[] = "abcdefghijklmnopqrstuvwxyz";
	char    buff2[] = "abcdefghijklmnopqrstuvwxyz";
	char    *src = "string with\200inside !";
	char	*begin1 = buff1;
	char	*begin2 = buff2;

	memccpy(buff1, src, '\200', 21);
	ft_memccpy(buff2, src, '\200', 21);
	if (memcmp(buff1, buff2, 25) != 0)
	{
		printf(">>>>>>>FAIL<<<<<<<\n");

		printf("   memccpy = \"%s\"\n", begin1 );
		printf("ft_memccpy = \"%s\"\n", begin2 );
	}
	else
		printf(">>>>>SUCCESS<<<<<\n");
}

static void		test_memmove()
{
	printf("-----------------------ft_memmove\n");
	char *src = "thi\xffs i\xfas \0a g\xde\xadood \0nyan\0cat\0 !\r\n";
	int size = 33;
	char dst1[0xF0];
	char dst2[0xF0];
	char *ret1;
	char *ret2;

	ret1 = memmove(dst1, src, sizeof(dst1));
	ret2 = ft_memmove(dst2, src, size);
	if (memcmp(ret1, ret2, 33) != 0)
	{
		printf(">>>>>>>FAIL<<<<<<<\n");
		printf("   memmove = %s\n", ret1);
		printf("ft_memmove = %s\n", ret2);
	}
	else
		printf(">>>>>SUCCESS<<<<<\n");
}

static void		test_memcmp()
{
	printf("-----------------------ft_memcmp\n");
	uint8_t *s1 = (uint8_t *)"\xff\xaa\xde\x12MACOSX";
	uint8_t *s2 = (uint8_t *)"\xff\xaa\xde\x12MACOSX";
	size_t size = 10;

	printf("   memcmp=\"%d\"\n", memcmp(s1, s2, size));
	printf("ft_memcmp=\"%d\"\n", ft_memcmp(s1, s2, size));

	uint8_t *s3 = (uint8_t *)"3\xff\0\0\xaa\0\xde\xffMACOSX\xff";
	uint8_t *s4 = (uint8_t *)"3\xff\0\0\xaa\0\xde\x00MBS";

	size = 9;
	printf("   memcmp=\"%d\"\n", memcmp(s3, s4, size));
	printf("ft_memcmp=\"%d\"\n", ft_memcmp(s3, s4, size));
}

static void		test_memcmp_extended()
{
	printf("-----------------------ft_memcmp_extended\n");
	char	*s1 = "�Sj�\x9d^�Qo��*���\x1d";
	char	*s2 = "\x92\x83]\\Օ�\x8d\x9c��Sj�\x9d^�Qo��*���\x1d";
	size_t	size = 10;

	if(memcmp(s1, s2, size) != ft_memcmp(s1, s2, size))
	{
		printf("   memcmp=\"%d\"\n", memcmp(s1, s2, size));
		printf("ft_memcmp=\"%d\"\n", ft_memcmp(s1, s2, size));
	}
}

static void		test_memcmp_crash1()
{
	char	b[] = "nyancat under your bed";

	memcmp(b, NULL, 0);
	printf("your function\n");
	ft_memcmp(b, NULL, 0);
	printf("memcmp no chrash:??\n");
}

static void		test_memcmp_crash2()
{
	char	b[] = "nyancat under your bed";

	memcmp(NULL, b, 0);
	printf("your function\n");
	ft_memcmp(NULL, b, 0);
	printf("memcmp no chrash:??\n");
}

static void		uf_test_memcmp(void) {
	char 			ctab[11], ctab2[11];
	int 			itab[11], itab2[11];
	unsigned long 	ltab[11], ltab2[11];
	size_t i, j;

	i = 0;
	while (i < 11) {
		j = 0;
		while (j < 11) {
			ctab[j] = (char) rand();
			ctab2[j] = (char) rand();
			itab[j] = rand();
			itab2[j] = rand();
			ltab[j] = (unsigned long) rand() * LONG;
			ltab2[j] = (unsigned long) rand() * LONG;
			j++;
		}
		if (memcmp(ctab, ctab2, sizeof(ctab)) != ft_memcmp(ctab, ctab2, sizeof(ctab))) D_ERROR
		memcpy(ctab2, ctab, sizeof(ctab));
		if (memcmp(ctab, ctab2, sizeof(ctab)) != ft_memcmp(ctab, ctab2, sizeof(ctab))) D_ERROR
		if (memcmp(itab, itab2, sizeof(itab)) != ft_memcmp(itab, itab2, sizeof(itab))) D_ERROR
		memcpy(itab2, itab, sizeof(itab));
		if (memcmp(itab, itab2, sizeof(itab)) != ft_memcmp(itab, itab2, sizeof(itab))) D_ERROR
		if (memcmp(ltab, ltab2, sizeof(ltab)) != ft_memcmp(ltab, ltab2, sizeof(ltab))) D_ERROR
		memcpy(ltab2, ltab, sizeof(ltab));
		if (memcmp(ltab, ltab2, sizeof(ltab)) != ft_memcmp(ltab, ltab2, sizeof(ltab))) D_ERROR
		++i;
	}
}

static void		test_strdup()
{
	printf("-----------------------ft_strdup\n");
	char 		*s = "HELLO \0 gopa";

	printf("   strdup\n");
	print_mem((const void *)strdup(s), 9);
	printf("ft_strdup\n");
	print_mem((const void *)ft_strdup(s), 9);

	char *tmp = "this is a normal test";

	printf("   strdup\n");
	print_mem((const void *)strdup(tmp), strlen(tmp) + 5);
	printf("ft_strdup\n");
	print_mem((const void *)ft_strdup(tmp), strlen(tmp) + 5);
}

static void		test_strlcat()
{
	printf("-----------------------ft_strlcat\n");
	char	*str = "the cake is a lie !\0I'm hidden lol\r\n";
	char	buff1[0xF00] = "there is no stars in the sky";
	char	buff2[0xF00] = "there is no stars in the sky";
	size_t	max = strlen("the cake is a lie !\0I'm hidden lol\r\n") + 4;

	size_t	size1 = strlcat(buff1, str, max);
	size_t	size2 = ft_strlcat(buff2, str, max);

	printf("   strlcat = \"%s\" num = %zu \n", buff1, size1);
	print_mem((const void *)buff1, strlen(buff1) + 30);
	printf("ft_strlcat = \"%s\" num = %zu \n", buff2, size2);
	print_mem((const void *)buff2, ft_strlen(buff2) + 30);
}

static void		test_strchr()
{
	printf("-----------------------ft_strchr\n");
	char *src = "there is so \0ma\0ny \0 \\0 in t\0his stri\0ng !\0\0\0\0";
	char *d1 = strchr(src, '\0');
	char *d2 = ft_strchr(src, '\0');

	if (d1 != d2)
	{	
		printf(">>>>>>FAIL<<<<<<\n");
		printf("   strlcat = \"%s\", %p \n", d1, d1);
		print_mem((const void *)src, strlen(src) + 30);
		printf("ft_strlcat = \"%s\", %p \n", d2, d2);
		print_mem((const void *)src, ft_strlen(src) + 30);
	}
}

static void		test_strrchr()
{
	printf("-----------------------ft_strrchr\n");
	char *src = "there is so \0ma\0ny \0 \\0 in t\0his stri\0ng !\0\0\0\0";
	char *d1 = strrchr(src, '\0');
	char *d2 = ft_strrchr(src, '\0');

	if (strcmp(d1, d2) != 0)
	{
		printf(">>>>>>FAIL<<<<<<\n");
		printf("   strrchr = \"%s\", %p \n", d1, d1);
		print_mem((const void *)src, strlen(src) + 30);
		printf("ft_strrchr = \"%s\", %p \n", d2, d2);
		print_mem((const void *)src, ft_strlen(src) + 30);
	}
	else
		printf(">>>>>SUCCESS<<<<\n");
}

static void		test_strrchr1()
{
	printf("-----------------------ft_strrchr\n");
	char	*src = "Hello je tesx";
	char	*d1 = strrchr(src, 'H');
	char	*d2 = ft_strrchr(src, 'H');
	int		i;

	i = 0;
	while (src[i] != '\0')
	{
		d1 = strrchr(src, src[i]);
		d2 = ft_strrchr(src, src[i]);
		if (d1 != d2)
		{
			printf(">>>>>>FAIL<<<<<<\n");
			printf("   strrchr = \"%s\", %p \n", d1, d1);
			print_mem((const void *)src, strlen(src) + 3);
			printf("ft_strrchr = \"%s\", %p \n", d2, d2);
			print_mem((const void *)src, ft_strlen(src) + 3);
		}
		i++;
	}
	d1 = strrchr(src, 7);
	d2 = ft_strrchr(src, 7);
	if (d1 && d2)
		if (strcmp(d1, d2) != 0)
		{
			printf(">>>>>>FAIL<<<<<<\n");
			if (d1 != NULL)
				printf("   strrchr = \"%s\", %p \n", d1, d1);
			print_mem((const void *)src, strlen(src) + 5);
			printf("ft_strrchr = \"%s\", %p \n", d2, d2);
			print_mem((const void *)src, ft_strlen(src) + 5);
		}

}

static void		test_strnstr()
{
	printf("-----------------------ft_strnstr\n");
	char *s1 = "MZIRIBMZIRIBMZE123";
	char *s2 = "MZIRIBMZE";
	size_t max = strlen(s2);
	char *i1 = strnstr(s1, s2, max);
	char *i2 = ft_strnstr(s1, s2, max);

	printf("   strnstr = \"%s\", %p \n", i1, i1);
	print_mem((const void *)s1, strlen(s1));
	printf("ft_strnstr = \"%s\", %p \n", i2, i2);
	print_mem((const void *)s1, strlen(s1));
}

static void		test_strnstr1()
{
	printf("-----------------------ft_strnstr1\n");
	char *s1 = "AAAAAAAAAAAAA";
	size_t max = strlen(s1);
	char *i1 = strnstr(s1, s1, max);
	char *i2 = ft_strnstr(s1, s1, max);

	printf("   strnstr = \"%s\", %p \n", i1, i1);
	print_mem((const void *)s1, strlen(s1));
	printf("ft_strnstr = \"%s\", %p \n", i2, i2);
	print_mem((const void *)s1, strlen(s1));
}

static void		test_strncmp()
{
	printf("-----------------------ft_strncmp\n");
	char 	*s1 = "AAAAAAAAAAAAA";
	char 	*s2 = "AAABAAAAAAAAA";
	int 	i1 = strncmp(s1, s2, 4);
	int 	i2 = ft_strncmp(s1, s2, 4);

	printf("   strncmp = \"%d\", %p \n", i1, &i1);
	printf("ft_strncmp = \"%d\", %p \n", i2, &i2);
}

static void		test_strncmp1()
{
	printf("-----------------------ft_strncmp1\n");
	char 	*s1 = "q";
	char 	*s2 = "a";
	int 	i1 = strncmp(s1, s2, 0);
	int 	i2 = ft_strncmp(s1, s2, 0);

	printf("   strncmp = \"%d\", %p \n", i1, &i1);
	printf("ft_strncmp = \"%d\", %p \n", i2, &i2);
}

static char		f_strmap(char	c)
{
	return (c - 1);
}

static void		test_strmap()
{
	printf("-----------------------ft_strmap\n");
	char 	*s1 = "AAAAAAAAAAAAA";
	size_t	size = ft_strlen(s1);
	char	*i1 = (char *)malloc(sizeof(char) * size + 1);
	char 	*i2 = ft_strmap(s1, &f_strmap);
	size_t	i;

	i = 0;
	while (size--)
	{
		i1[i] = f_strmap(s1[i]);
		i++;
	}
	printf("  strnstr = \"%s\", %p \n", i1, &i1);
	print_mem((void *)i1, size + 30);
	printf("ft_strnstr = \"%s\", %p \n", i2, &i2);
	print_mem((void *)i2, size + 30);
}

static void		test_strjoin()
{
	printf("-----------------------ft_strjoin\n");
	char 	*s1 = "where is my";
	char 	*s2 = " malloc???";
	char 	*i2 = ft_strjoin(s1, s2);

	printf("ft_strnstr = \"%s\", %p \n", i2, &i2);
	print_mem(i2, strlen((void *)i2) + 10);
}

static void		test_strtrim()
{
	printf("-----------------------ft_strtrim\n");
	char 	*s1 = "   \t  \n\n \t\t  \n\n\nHello \t  Please\n Trim me !\n   \n \n \t\t\n";
	char	*s2 = "Hello \t  Please\n Trim me !";
	char 	*i2 = ft_strtrim(s1);

	printf("ft_strtrim = \"%s\", %p \n", i2, &i2);
	printf("   strtrim = \"%s\", %p \n", s2, &s2);
	print_mem(i2, strlen((void *)i2) + 10);
}

static void		test_itoa()
{
	printf("-----------------------ft_itoa\n");
	char	*s1;
	long	n;
	int		i;

	i = 0;
	while (++i < 2000)
	{
		n = ((long)rand() % (2147483647l * 2)) - 2147483647l/2;
		s1 = ft_itoa((int)n);
		if (atoi(s1) != n)
		{
			printf(">>>>>FAIL<<<<< n = \"%d\"\n", (int)n);
			print_mem((void *)s1, 20);
			break;
		}
	}
	printf(">>>>>RANDOM SUCCESS<<<<< \n");
	char		*test = "30588740";

	print_mem((void *)ft_itoa(atoi(test)), 10);
	print_mem((void *)test, 10);
	printf("strcmp res = |%d|\n", strcmp(ft_itoa(atoi(test)), test));
	printf("ft_itoa res = |%s|\n", ft_itoa(atoi(test)));
}

static void		test_strsplit()
{
	printf("-----------------------ft_strsplit\n");
	char	str[] = "   asdfjsd a   asdkfjsadk f sd asdad fas d  das kdfja ";
	char	delimiter = ' ';
	char	**res = ft_strsplit((const char *)str, delimiter);

	printf("str = |%s|\n", str);
	ft_printf_array(res);
}

int				main(void)
{
	test_memset();
	test_bzero();
	test_memcpy();
	test_memccpy();
	test_memmove();
	test_memcmp();
	test_memcmp_crash1();
	test_memcmp_crash2();
	test_memcmp_extended();
	test_strdup();
	test_strlcat();
	test_strchr();
	test_strnstr();
	test_strnstr1();
	test_strncmp();
	test_strncmp1();
	test_strmap();
	test_strjoin();
	test_strtrim();
	test_itoa();
	test_strrchr();
	test_strrchr1();
	test_strsplit();

	return (0);
}
