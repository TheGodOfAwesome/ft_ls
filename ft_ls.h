/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmuvezwa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/30 22:27:40 by kmuvezwa          #+#    #+#             */
/*   Updated: 2017/09/26 16:34:23 by kmuvezwa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

# include <unistd.h>
# include <dirent.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <string.h>
# include <stdio.h>
# include <libc.h>
# include <grp.h>
# include <uuid/uuid.h>
# include <pwd.h>
# include "libft/libft.h"

void		recurse_dirs(char *dir, char *opts, int check);
void		print(char *str, char *opts, char *dir, int *cnt);
void		print_stats(char **av, int ac, char *opts, char *dir);
void		print_permissions(mode_t mode);
void		print_filetype(mode_t mode);
void		print_time(time_t mod_time);
void		print_name_or_link(const char* filename, char *opts, mode_t mode);
void		print_error(int condition, char *info, char *infos);
void		print_dirs(DIR *dp, char *opts, char *dir);
void		ft_timesortstr(char **str, int max, char *dir);
void		ft_rtimesortstr(char **str, int max, char *dir);
void		display_stats(char *dir, char *filename, char *opts);
struct stat	get_stats(const char *filename, char *dir);
int			*count_files(char *dirs, char *opts);
int			cmp_time(const void *p1, const void *p2, char *dir);
int			can_recurse_dir(char* parent, char* curr);
int			is_dir(const char* filename, char *dir);
int			is_in_dir(const char* dir, const char* filename);

#endif
