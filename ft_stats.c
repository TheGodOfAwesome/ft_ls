/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_stats.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmuvezwa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/26 13:20:42 by kmuvezwa          #+#    #+#             */
/*   Updated: 2017/10/01 01:42:52 by kmuvezwa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void		print_permissions(mode_t mode)
{
	ft_putchar((mode & S_IRUSR) ? 'r' : '-');
	ft_putchar((mode & S_IWUSR) ? 'w' : '-');
	if (mode & S_ISUID)
		ft_putchar('S');
	else
		ft_putchar((mode & S_IXUSR) ? 'x' : '-');
	ft_putchar((mode & S_IRGRP) ? 'r' : '-');
	ft_putchar((mode & S_IWGRP) ? 'w' : '-');
	if (mode & S_ISGID)
		ft_putchar('S');
	else
		ft_putchar((mode & S_IXGRP) ? 'x' : '-');
	ft_putchar((mode & S_IROTH) ? 'r' : '-');
	ft_putchar((mode & S_IWOTH) ? 'w' : '-');
	if (mode & S_ISVTX)
		ft_putchar('T');
	else
		ft_putchar((mode & S_IXOTH) ? 'x' : '-');
	ft_putchar(' ');
}

void		print_filetype(mode_t mode)
{
	if ((mode & S_IFMT) == S_IFLNK)
		ft_putchar('l');
	else if ((mode & S_IFMT) == S_IFDIR)
		ft_putchar('d');
	else if ((mode & S_IFMT) == S_IFCHR)
		ft_putchar('c');
	else if ((mode & S_IFMT) == S_IFBLK)
		ft_putchar('b');
	else if ((mode & S_IFMT) == S_IFSOCK)
		ft_putchar('s');
	else if ((mode & S_IFMT) == S_IFIFO)
		ft_putchar('f');
	else if ((mode & S_IFMT) == S_IFREG)
		ft_putchar('-');
}

void		print_time(time_t mod_time)
{
	ft_putstr(ft_strsub(ctime(&mod_time), 4, 12));
	ft_putchar(' ');
}

struct stat	get_stats(const char *filename, char *dir)
{
	char		*path;
	char		*path2;
	struct stat	sb;

	path = ft_strjoin(dir, "/");
	path2 = ft_strjoin(path, filename);
	if (lstat(path2, &sb) < 0)
	{
		perror(path2);
		exit(0);
	}
	return (sb);
}

int			cmp_time(const void *p1, const void *p2, char *dir)
{
	int				ret;
	time_t			time1;
	time_t			time2;
	struct stat		sb;
	struct stat		nb;

	ret = 0;
	sb = get_stats((char *)p1, dir);
	nb = get_stats((char *)p2, dir);
	time1 = sb.st_mtime;
	time2 = nb.st_mtime;
	if (time1 < time2)
		ret = 1;
	if (time1 > time2)
		ret = -1;
	if (time1 == time2)
		ret = 0;
	return (ret);
}
