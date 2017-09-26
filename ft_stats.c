/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_stats.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmuvezwa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/26 13:20:42 by kmuvezwa          #+#    #+#             */
/*   Updated: 2017/09/26 13:49:56 by kmuvezwa         ###   ########.fr       */
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
}

void		print_filetype(mode_t mode)
{
	if (mode & S_IFREG)
		ft_putchar('-');
	else if (mode & S_IFDIR)
		ft_putchar('d');
	else if (mode & S_IFLNK)
		ft_putchar('l');
	else if (mode & S_IFCHR)
		ft_putchar('c');
	else if (mode & S_IFBLK)
		ft_putchar('b');
	else if (mode & S_IFSOCK)
		ft_putchar('s');
	else if (mode & S_IFIFO)
		ft_putchar('f');
}

void		print_time(time_t mod_time)
{
	time_t curr_time;
	time(&curr_time);
	struct tm* t = localtime(&curr_time);
	const int curr_mon = t->tm_mon;
	const int curr_yr = 1970 + t->tm_year;
	t = localtime(&mod_time);
	const int mod_mon = t->tm_mon;
	const int mod_yr = 1970 + t->tm_year;
	const char* format = ((mod_yr == curr_yr)
			&& (mod_mon >= (curr_mon - 6)))
		? "%b %e %H:%M"
		: "%b %e  %Y";
	char time_buf[128];
	strftime(time_buf, sizeof(time_buf), format, t);
	ft_putstr(time_buf);
	ft_putchar(' ');
}

struct stat	get_stats(const char *filename, char *dir)
{
	char		*path;
	struct stat	sb;

	path = ft_strjoin(dir, "/");
	path = ft_strjoin(path, filename);
	if (lstat(path, &sb) < 0)
	{
		perror(path);
		exit(0);
	}
	free(path);
	return sb;
}

int			cmp_time(const void *p1, const void *p2, char *dir)
{
	char			*s1;
	char			*s2;
	int				ret;
	time_t			time1;
	time_t			time2;
	struct stat		sb;
	struct stat		nb;

	ret = 0;
	s1 = (char *)p1;
	s2 = (char *)p2;
	sb = get_stats(s1, dir);
	nb = get_stats(s2, dir);
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
