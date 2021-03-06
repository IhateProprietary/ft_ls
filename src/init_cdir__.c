/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_cdir__.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jye <jye@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/17 19:25:46 by jye               #+#    #+#             */
/*   Updated: 2017/04/22 21:53:55 by jye              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

t_cdir	*init_dir__(char *path, t_lsenv *ls)
{
	t_cdir	*new_;

	errno = 0;
	if ((new_ = malloc(sizeof(t_cdir))) == NULL)
	{
		ft_dprintf(STDERR_FILENO, "beep boop, can't malloc exiting...\n");
		exit(EXIT_BIG_FAILURE);
	}
	ft_memset(new_, 0, sizeof(t_cdir));
	if ((new_->cur_path = ft_strdup(path)) == NULL)
	{
		perror(ls->pname);
		free(new_);
		return (NULL);
	}
	if ((new_->cwd = opendir(path)) == NULL)
	{
		new_->errno_ = errno;
		return (new_);
	}
	return (new_);
}
