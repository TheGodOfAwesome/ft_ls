/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmuvezwa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/08 15:28:25 by kmuvezwa          #+#    #+#             */
/*   Updated: 2017/10/01 01:46:30 by kmuvezwa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int			set_max(int cur, int max)
{
	int		ret;

	ret = 0;
	ret = (cur > max) ? cur : max;
	return (ret);
}

int			*count_files(char *dirs, char *opts)
{
	DIR				*dp;
	int				cnt;
	static int		mx[7];
	struct dirent	*dirp;
	struct stat		sb;

	cnt = 0;
	mx[5] = 0;
	dp = opendir(dirs);
	while ((dirp = readdir(dp)) != NULL)
		if (!(!ft_strchr(opts, 'a') && dirp->d_name[0] == '.'))
		{
			sb = get_stats(dirp->d_name, dirs);
			mx[0] = set_max(ft_strlen(dirp->d_name), mx[0]);
			mx[1] = set_max(ft_intlen(sb.st_nlink, 10), mx[1]);
			mx[2] = set_max(ft_strlen(getpwuid(sb.st_uid)->pw_name), mx[2]);
			mx[3] = set_max(ft_strlen(getgrgid(sb.st_gid)->gr_name), mx[3]);
			mx[4] = set_max(ft_intlen((int)sb.st_size, 10), mx[4]);
			mx[5] = ((int)sb.st_blocks) ? (mx[5] + (int)sb.st_blocks) : mx[5];
			cnt++;
		}
	mx[6] = cnt;
	closedir(dp);
	return (mx);
}

void		check_flags(char *dir, char *opts)
{
	DIR		*dp;

	if (ft_strchr(opts, 'R'))
	{
		recurse_dirs(dir, opts, 0);
	}
	else
	{
		dp = opendir(dir);
		print_dirs(dp, opts, dir);
	}
}

void		check_usage(char *dirs, char *opts)
{
	char			*flags;
	char			*test;
	DIR				*dp;

	flags = "-ABCFGHLOPRSTUWabcdefghiklmnopqrstuwx1";
	test = opts;
	while (*test != '\0')
	{
		if (!ft_strchr(flags, *test) && *test != '-')
		{
			print_error(1, test, flags);
			exit(0);
		}
		test++;
	}
	if ((dp = opendir(dirs)) == NULL)
		print_one(dirs, opts);
	else
		check_flags(dirs, opts);
	return ;
}

int			main(int ac, char **av)
{
	char	*opts;
	int		i;
	int		x;

	opts = "";
	i = 1;
	x = 0;
	if (ac == 1)
		check_usage("./", opts);
	else if (ac == 2)
		check_usage(((av[1][0] == '-') ? "./" : (av[1])),
				((av[1][0] == '-') ? av[1] : ""));
	else if (ac >= 2)
	{
		while (x++ < ac - 1)
			opts = (av[x][0] == '-') ? ft_strjoin(opts, av[x]) : opts;
		x = 0;
		while (x++ < ac - 1)
		{
			((av[x][0] != '-') && x > 1 && i != x) ? ft_putstr("\n") : "";
			(av[x][0] != '-') ? check_usage(av[x], opts) : i++;
		}
		(i == x) ? check_usage("./", opts) : "i++";
	}
	return (0);
}
