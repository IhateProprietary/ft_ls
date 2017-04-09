/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jye <jye@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/06 16:54:32 by jye               #+#    #+#             */
/*   Updated: 2017/04/09 21:40:15 by jye              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int		get_file_type(register mode_t st_mode)
{
	if (S_ISBLK(st_mode))
		return ('b');
	else if (S_ISCHR(st_mode))
		return ('c');
	else if (S_ISDIR(st_mode))
		return ('d');
	else if (S_ISFIFO(st_mode))
		return ('p');
	else if (S_ISREG(st_mode))
		return ('-');
	else if (S_ISLNK(st_mode))
		return ('l');
	else if (S_ISSOCK(st_mode))
		return ('s');
	return (-1);
}

void	perm_format(register char *restrict perm, register mode_t st_mode)
{
	0[perm] = get_file_type(st_mode);
	1[perm] = st_mode & S_IRUSR ? 'r' : '-';
	2[perm] = st_mode & S_IWUSR ? 'w' : '-';
	if (st_mode & S_ISUID)
		3[perm] = (st_mode & (S_ISUID + S_IXUSR)) == (S_ISUID + S_IXUSR) \
			? 's' : 'S';
	else
		3[perm] = st_mode & S_IXUSR ? 'x' : '-';
	4[perm] = st_mode & S_IRGRP ? 'r' : '-';
	5[perm] = st_mode & S_IWGRP ? 'w' : '-';
	if (st_mode & S_ISGID)
		6[perm] = (st_mode & (S_ISGID + S_IXGRP)) == (S_ISGID + S_IXGRP) \
			? 's' : 'S';
	else
		6[perm] = st_mode & S_IXGRP ? 'x' : '-';
	7[perm] = st_mode & S_IROTH ? 'r' : '-';
	8[perm] = st_mode & S_IWOTH ? 'w' : '-';
	if (st_mode & S_ISVTX)
		9[perm] = (st_mode & (S_ISVTX + S_IXOTH)) == (S_ISVTX + S_IXOTH) \
			? 't' : 'T';
	else
		9[perm] = st_mode & S_IXOTH ? 'x' : '-';
}

int		main(int ac, char **av)
{
	DIR			*cwd;
	t_dirent	*cf;
	t_stat		*cf_stat;
	t_file		*file_data;

	cwd = opendir(CWD);
	(void)ac;
	(void)av;
	while ((cf = readdir(cwd)) != NULL)
	{
		file_data = malloc(sizeof *file_data);
		memset(file_data, 0, sizeof *file_data);
		file_data->cf_ = cf;
		cf_stat = malloc(sizeof *cf_stat);
		memset(cf_stat, 0, sizeof *cf_stat);
		lstat(cf->d_name, cf_stat);
		file_data->cf_stat_ = cf_stat;
		if (S_ISLNK(cf_stat->st_mode))
			readlink(cf->d_name, file_data->sym_link_, PATH_MAX);
		perm_format(file_data->perm_, cf_stat->st_mode);
		file_data->user_ = getpwuid(cf_stat->st_uid);
		file_data->group_ = getgrgid(cf_stat->st_gid);
		time_format(cf_stat->st_mtimespec.tv_sec, file_data->human_time_);
		printf("%s %s\n", file_data->perm_, cf->d_name);
	}
	return (0);
}
