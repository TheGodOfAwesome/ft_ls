/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_checks.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmuvezwa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/26 15:26:19 by kmuvezwa          #+#    #+#             */
/*   Updated: 2017/10/01 01:43:17 by kmuvezwa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void		ft_timesortstr(char **str, int max, char *dir)
{
	int		i;
	int		pairs_count;
	char	*temp;

	i = -1;
	pairs_count = 1;
	while (pairs_count)
	{
		pairs_count = 0;
		i = 0;
		while (i + 1 < max)
		{
			if (*(str + 1) != NULL)
			{
				if (cmp_time(&str[i][0], &str[i + 1][0], dir) == 1)
				{
					temp = str[i];
					str[i] = str[i + 1];
					str[i + 1] = temp;
					pairs_count++;
				}
			}
			i++;
		}
	}
}

void		ft_rtimesortstr(char **str, int max, char *dir)
{
	int		i;
	int		pairs_count;
	char	*temp;

	i = -1;
	pairs_count = 1;
	while (pairs_count)
	{
		pairs_count = 0;
		i = 0;
		while (i + 1 < max)
		{
			if (*(str + 1) != NULL)
			{
				if (cmp_time(&str[i][0], &str[i + 1][0], dir) == -1)
				{
					temp = str[i];
					str[i] = str[i + 1];
					str[i + 1] = temp;
					pairs_count++;
				}
			}
			i++;
		}
	}
}

int			is_dir(const char *filename, char *dir)
{
	struct stat sb;

	sb = get_stats(filename, dir);
	if (lstat(filename, &sb) < 0)
	{
		perror(filename);
		return (0);
	}
	return (sb.st_mode & S_IFDIR) ? 1 : 0;
}

int			is_in_dir(const char *dir, const char *filename)
{
	DIR				*dfd;
	struct dirent	*dp;

	dfd = opendir(dir);
	if (!dfd)
	{
		perror(dir);
		return (0);
	}
	dp = readdir(dfd);
	while (dp)
	{
		if (ft_strcmp(filename, dp->d_name) == 0)
		{
			closedir(dfd);
			return (1);
		}
		dp = readdir(dfd);
	}
	ft_putstr("file ");
	ft_putstr(filename);
	ft_putstr("not found\n");
	closedir(dfd);
	return (0);
}

int			can_recurse_dir(char *parent, char *curr)
{
	static char		*path;
	static char		*path2;
	struct stat		sb;

	if (!ft_strcmp(".", curr) || !ft_strcmp("..", curr))
		return (0);
	path = ft_strjoin(parent, "/");
	path2 = ft_strjoin(path, curr);
	if (lstat(path2, &sb) < 0)
	{
		perror(path2);
		return (0);
	}
	return (S_ISDIR(sb.st_mode));
}
