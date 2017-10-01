/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmuvezwa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/26 13:52:48 by kmuvezwa          #+#    #+#             */
/*   Updated: 2017/10/01 01:51:22 by kmuvezwa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void		display_stats(char *dir, char *filename, char *opts)
{
	int				c;
	int				*max;
	struct stat		sb;

	if (!is_in_dir(dir, filename))
		return ;
	if (!ft_strcmp(opts, "l"))
	{
		ft_putendl(filename);
		return ;
	}
	sb = get_stats(filename, dir);
	max = count_files(dir, opts);
	print_filetype(sb.st_mode);
	print_permissions(sb.st_mode);
	ft_tabputstr(max[1] - ft_intlen(sb.st_nlink, 10) + 1,
			ft_itoa(sb.st_nlink), 0);
	ft_tabputstr(0, getpwuid(sb.st_uid)->pw_name,
			max[2] - ft_strlen(getpwuid(sb.st_uid)->pw_name) + 1);
	ft_tabputstr(0, getgrgid(sb.st_gid)->gr_name,
			max[3] - ft_strlen(getgrgid(sb.st_gid)->gr_name) + 1);
	ft_tabputstr(max[4] - (c = (ft_intlen((int)sb.st_size, 10) == 0)
			? 1 : ft_intlen((int)sb.st_size, 10)), ft_itoa((int)sb.st_size), 0);
	print_time(sb.st_mtime);
	print_name_or_link(filename, opts, sb.st_mode);
}

void		print_name_or_link(const char *filename, char *opts, mode_t mode)
{
	char	*temp;
	char	link_buf[512];
	int		count;

	temp = opts;
	if (mode & S_IFLNK)
	{
		count = readlink(filename, link_buf, sizeof(link_buf));
		if (count >= 0)
		{
			link_buf[count] = '\0';
			ft_putstr(filename);
			ft_putstr(" -> ");
			ft_putendl(link_buf);
			return ;
		}
	}
	ft_putstr(filename);
	ft_putstr("\n");
}

void		print_stats(char **av, int ac, char *opts, char *dir)
{
	int		i;

	i = 0;
	while (i < ac)
	{
		if (av[i])
		{
			display_stats(dir, av[i], opts);
		}
		i++;
	}
}

void		print_error(int condition, char *info, char *infos)
{
	if (condition == 1)
	{
		ft_putstr("ft_ls: illegal option -- ");
		ft_putchar(*info);
		ft_putstr("\nusage: ft_ls [");
		ft_putstr(infos);
		ft_putstr("] [file ...]\n");
	}
	if (condition == 2)
	{
		ft_putstr("ft_ls: ");
		ft_putstr(info);
		ft_putstr(":  No such file or directory\n");
	}
}

void		recurse_dirs(char *dir, char *opts, int check)
{
	char			*next;
	char			*next2;
	DIR				*dfd;
	struct dirent	*direntry;

	if (check)
		ft_putstr("\n");
	check++;
	dfd = opendir(dir);
	print_dirs(dfd, opts, dir);
	dfd = opendir(dir);
	while ((direntry = readdir(dfd)))
	{
		if (can_recurse_dir(dir, direntry->d_name))
		{
			if (!(!ft_strchr(opts, 'a') && direntry->d_name[0] == '.'))
			{
				next = (ft_strchr(dir + ft_strlen(dir) - 1, '/'))
					? ft_strjoin(dir, "") : ft_strjoin(dir, "/");
				next2 = ft_strjoin(next, direntry->d_name);
				recurse_dirs(next2, opts, check);
			}
		}
	}
	closedir(dfd);
}
