/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmuvezwa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/08 15:28:25 by kmuvezwa          #+#    #+#             */
/*   Updated: 2017/09/24 05:52:03 by kmuvezwa         ###   ########.fr       */
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

int			*count_files(char *dirs, char *opts)
{
	DIR				*dp;
	int				cnt;
	int				omit_hidden;
	static int		max[7];
	struct dirent	*dirp;
	struct stat		sb;

	cnt = 0;
	max[5] = 0;
	dp = opendir(dirs);
	while ((dirp = readdir(dp)) != NULL)
	{
		if (!(omit_hidden = !ft_strchr(opts, 'a') && dirp->d_name[0] == '.'))
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

int			cmp_time(const void* p1, const void* p2, char *dir)
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

int			is_dir(const char* filename, char *dir)
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

int			is_in_dir(const char* dir, const char* filename)
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

void		print_name_or_link(const char* filename, char *opts, mode_t mode)
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
			ft_putstr(" ");
			ft_putstr(filename);
			ft_putstr(" -> ");
			ft_putstr(link_buf);
			ft_putstr(" \n");
			return ;
		}
	}
	ft_putstr(filename);
	ft_putstr("\n");
}

void		display_stats(char *dir, char *filename, char *opts)
{
	int				*max;
	struct stat		sb;

	if (!is_in_dir(dir, filename))
		return ;
	if (!ft_strcmp(opts, "l"))
	{
		ft_putstr(filename);
		ft_putstr("\n");
		return ;
	}
	sb = get_stats(filename, dir);
	max = count_files(dir, opts);
	print_filetype(sb.st_mode);
	print_permissions(sb.st_mode);
	ft_putstr(" ");
	ft_tabputstr(max[1] - ft_intlen(sb.st_nlink, 10), ft_itoa(sb.st_nlink), 0);
	ft_tabputstr(0, getpwuid(sb.st_uid)->pw_name, 
			max[2] - ft_strlen(getpwuid(sb.st_uid)->pw_name) + 1);
	ft_tabputstr(0, getgrgid(sb.st_gid)->gr_name, 
			max[3] - ft_strlen(getgrgid(sb.st_gid)->gr_name) + 1);
	ft_tabputstr(max[4] - ft_intlen((int)sb.st_size, 10), 
			ft_itoa((int)sb.st_size), 0);
	print_time(sb.st_mtime);
	print_name_or_link(filename, opts, sb.st_mode);
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

void		print_dirs(DIR *dp, char *opts, char *dir)
{
	char			**ls;
	char			*str;
	int				*cnt;
	int				omit_hidden;
	struct dirent	*dirp;

	ft_putstr(dir);
	ft_putendl(":");
	cnt = count_files(dir, opts);
	str = "";
	str = (char *)ft_memalloc(sizeof(char) * (cnt[5] * cnt[0]));
	if (ft_strchr(opts, 'a'))
		ft_strcat(str, ".,");
	if ((dirp = readdir(dp)) != NULL)
	{
		if (ft_strchr(opts, 'l'))
		{
			ft_putstr("total ");
			ft_putendl(ft_itoa(cnt[5]));
		}
		while ((dirp = readdir(dp)) != NULL)
		{
			if(!(omit_hidden = !ft_strchr(opts, 'a') && dirp->d_name[0] == '.'))
			{
				ft_strcat(str, dirp->d_name);
				ft_strcat(str, ",");
			}
		}
	}
	ls = ft_strsplit(str, ',');
	(ft_strchr(opts, 'r')) ? ft_revsortstr(ls, cnt[6]) : ft_sortstr(ls, cnt[6]);
	((ft_strchr(opts, 'r') && ft_strchr(opts, 't'))) 
		? ft_rtimesortstr(ls, cnt[6], dir) : str;
	(!ft_strchr(opts, 't')) ? : ft_timesortstr(ls, cnt[6], dir);
	(ft_strchr(opts, 'l')) 
		? print_stats(ls, cnt[6], opts, dir) : ft_putstrs(ls, cnt[6]);
	free(str);
	closedir(dp);
}

int			can_recurse_dir(char* parent, char* curr)
{
	static char		*path;
	struct stat		sb;

	if (!ft_strcmp(".", curr) || !ft_strcmp("..", curr))
		return (0);
	path = ft_strjoin(parent, "/");
	path = ft_strjoin(path, curr);
	if (lstat(path, &sb) < 0)
	{
		perror(path);
		return (0);
	}
	return S_ISDIR(sb.st_mode);
}

void		recurse_dirs(char *dir, char *opts, int check)
{
	char			*next;
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
			next = ft_strjoin(dir, "/");
			next = ft_strjoin(next, direntry->d_name);
			recurse_dirs(next, opts, check);
		}
	}
	closedir(dfd);
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

void		check_usage(char *dirs, char *opts)
{
	char			*flags;
	char			*test;
	DIR				*dp;
	struct dirent	*dirp;

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
	{
		dp = opendir(".");
		while ((dirp = readdir(dp)) != NULL)
		{
			if(ft_strstr(dirp->d_name, dirs) != NULL)
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
		(i == x) ?  check_usage("./", opts) : "i++";
	}
	return (0);
}
