/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_flag.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jye <jye@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/15 22:08:07 by jye               #+#    #+#             */
/*   Updated: 2017/04/19 03:30:51 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void	usage(const char *prog_name)
{
	(void)prog_name;
	exit(EXIT_FAILURE);
}

int			set_flag(int ac, char **av)
{
	register char	c;
	register int	flag;

	flag = 0;
	while ((c = get_opt(ac, av, LS_FLAGS)) != -1)
	{
		if (c == 'l')
			flag |= ell;
		else if (c == '1')
			flag |= one;
		else if (c == 'R')
			flag |= recursive | show_folder;
		else if (c == 'r')
			flag |= rever_sort;
		else if (c == 'a')
			flag |= show_all;
		else if (c == 't')
			flag |= mtim;
		else if (c == 'u')
			flag = (flag & ~ctim) | atim;
		else if (c == 'U')
			flag = (flag & ~atim) | ctim;
		else if (c == 'f')
			flag = (flag & 0) | (no_sort | show_all);
		else if (c == 'G')
			flag |= color;
		else
			usage(av[0]);
	}
//	if (!isatty(STDOUT_FILENO))
//		flag = (flag & ~(color)) | one;
	return (flag);
}
