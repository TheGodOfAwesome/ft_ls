/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmuvezwa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/08 15:28:25 by kmuvezwa          #+#    #+#             */
/*   Updated: 2017/09/27 14:50:56 by kmuvezwa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int			*count_files(char *dirs, char *opts)
{
	DIR				*dp;
	int				cnt;
	static int		max[7];
	struct dirent	*dirp;
	struct stat		sb;

	cnt = 0;
	max[5] = 0;
	dp = opendir(dirs);
	while ((dirp = readdir(dp)) != NULL)
	{
		if (!(!ft_strchr(opts, 'a') && dirp->d_name[0] == '.'))
		{
			max[0] = (ft_strlen(dirp->d_name) > max[0])
				? ft_strlen(dirp->d_name) : max[0];
			sb = get_stats(dirp->d_name, dirs);
			max[1] = (ft_intlen(sb.st_nlink, 10) > max[1])
				? ft_intlen(sb.st_nlink, 10) : max[1];
			max[2] = (ft_strlen(getpwuid(sb.st_uid)->pw_name) > max[2])
				? ft_strlen(getpwuid(sb.st_uid)->pw_name) : max[2];
			max[3] = (ft_strlen(getgrgid(sb.st_gid)->gr_name) > max[3])
				? ft_strlen(getgrgid(sb.st_gid)->gr_name) : max[3];
			max[4] = (ft_intlen((int)sb.st_size, 10) > max[4])
				? ft_intlen((int)sb.st_size, 10) : max[4];
			max[5] = ((int)sb.st_blocks > 0)
				? (max[5] + (int)sb.st_blocks) : max[5];
			cnt++;
		}
	}
	max[6] = cnt;
	closedir(dp);
	return (max);
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
	struct dirent	*dirp;

	flags = "-Ralrt1";
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
	{
		dp = opendir(".");
		while ((dirp = readdir(dp)) != NULL)
		{
			if (ft_strstr(dirp->d_name, dirs) != NULL)
			{
				(ft_strchr(opts, 'l'))
					? display_stats(".", dirs, opts) : ft_putendl(dirs);
				return ;
			}
		}
		print_error(2, dirs, "");
	}
	else
		check_flags(dirs, opts);
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
