/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmuvezwa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/08 15:28:25 by kmuvezwa          #+#    #+#             */
/*   Updated: 2017/09/09 09:29:39 by kmuvezwa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include "ft_ls.h"

void	print_permissions(mode_t mode)
{
	ft_putchar((mode & S_IRUSR) ? 'r' : '-');
	ft_putchar((mode & S_IWUSR) ? 'w' : '-');
	ft_putchar((mode & S_IXUSR) ? 'x' : '-');
	ft_putchar((mode & S_IRGRP) ? 'r' : '-');
	ft_putchar((mode & S_IWGRP) ? 'w' : '-');
	ft_putchar((mode & S_IXGRP) ? 'x' : '-');
	ft_putchar((mode & S_IROTH) ? 'r' : '-');
	ft_putchar((mode & S_IWOTH) ? 'w' : '-');
	ft_putchar((mode & S_IXOTH) ? 'x' : '-');
}

void	print_filetype(mode_t mode)
{
	if (mode & S_IFREG) 
		ft_putchar('-');
	if (mode & S_IFDIR) 
		ft_putchar('d');
	if (mode & S_IFLNK)
		ft_putchar('l');
	if (mode & S_IFCHR)
		ft_putchar('c');
	if (mode & S_IFBLK)
		ft_putchar('b');
	if (mode & S_IFSOCK)
		ft_putchar('s');
	if (mode & S_IFIFO)
		ft_putchar('f');
}

void	print_time(time_t mod_time)
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
}

struct stat get_stats(const char *filename, char *dir)
{
	char	*path;
	struct stat sb;

	path = ft_strjoin(dir, "/");
	path = ft_strjoin(path, filename);
	if (lstat(path, &sb) < 0)
	{
		perror(path);
		exit(0);
	}
	return sb;
}

/*int cmp_time(const void* p1, const void* p2, char *dir)
  {
  const char* str1 = *(const char**)p1;
  const char* str2 = *(const char**)p2;

  time_t time1 = get_stats(str1, dir).st_mtime;
  time_t time2 = get_stats(str2, dir).st_mtime;
  return time1 < time2;
  }*/

int     is_dir(const char* filename, char *dir)
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

int     is_in_dir(const char* dir, const char* filename)
{
	DIR             *dfd;
	struct dirent   *dp;

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

void print_name_or_link(const char* filename, char *opts, mode_t mode)
{
	char	*temp;
	char    link_buf[512];
	int     count;

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

void display_stats(char* dir, char* filename, char *opts)
{
	struct stat     sb;

	if (!is_in_dir(dir, filename))
		return ;
	if (!ft_strcmp(opts, "l"))
	{
		ft_putstr(filename);
		ft_putstr("\n");
		return ;
	}
	sb = get_stats(filename, dir);
	print_filetype(sb.st_mode);
	print_permissions(sb.st_mode);
	ft_putstr(" ");
	ft_putstr(ft_itoa(sb.st_nlink));
	ft_putstr(" ");
	ft_putstr(getpwuid(sb.st_uid)->pw_name);
	ft_putstr(" ");
	ft_putstr(getgrgid(sb.st_gid)->gr_name);
	ft_putstr(" ");
	ft_putstr(ft_itoa((int)sb.st_size));
	ft_putstr(" ");
	print_time(sb.st_mtime);
	ft_putstr(" ");
	print_name_or_link(filename, opts, sb.st_mode);
}

void	check_flags(char *dir, char *opts, char *name)
{
	if (ft_strcmp(opts, "l"))
	{
		if (ft_strcmp(opts, "a"))
		{
			display_stats(dir, name, opts);
		}
	}
}

int		can_recurse_dir(char* parent, char* curr)
{
	static char *path;
	struct stat sb;

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

void    count_files(char *dir_count, char *opts, int check, int file_count)
{
	char            *next;
	DIR             *dfd_count;
	struct dirent   *direntry_count;

	file_count = 0;
	dfd_count = opendir(dir_count);
	direntry_count = readdir(dfd_count);
	while ((direntry_count = readdir(dfd_count)) && check)
	{
		if (direntry_count->d_type == DT_REG)
			file_count++;
		if (can_recurse_dir(dir_count, direntry_count->d_name))
		{
			next = ft_strjoin(dir_count, "/");
			next = ft_strjoin(next, direntry_count->d_name);
			count_files(next, opts, check, file_count);
		}
		check = 0;
	}
	closedir(dfd_count);
	ft_putstr("total ");
	ft_putstr(ft_itoa(file_count));
	ft_putstr("\n");
}

void	recurse_dirs(char *dir, char *opts, int check)
{
	char			*next;
	DIR				*dfd;
	struct dirent	*direntry;
	int 			omit_hidden;

	if (check)
	{
		count_files(dir, opts, 1, 0);
		check = 0;
	}
	dfd = opendir(dir);
	direntry = readdir(dfd);
	ft_putstr("\n");
	ft_putstr(dir);
	ft_putstr("\n");
	while ((direntry = readdir(dfd)))
	{
		omit_hidden = !ft_strcmp(opts, "a");
		if (!omit_hidden)
		{
			//ft_putstr(direntry->d_name);
			display_stats(dir, direntry->d_name, opts);
			//ft_putstr("\n");
		}
		if (can_recurse_dir(dir, direntry->d_name))
		{
			next = ft_strjoin(dir, "/");
			next = ft_strjoin(next, direntry->d_name);
			recurse_dirs(next, opts, check);
		}
	}
	closedir(dfd);
}

void	print_dirs(DIR *dp, char *opts, char *dir_name)
{
	int             count;
	struct dirent	*dirp;

	count = 0;
	ft_putstr("-------");
	ft_putstr(opts);
	ft_putstr("-------\n");
	if ((dirp = readdir(dp)) == NULL)
	{
		perror("Error: ");
		return ;
	}
	else
	{
		while ((dirp = readdir(dp)) != NULL)
		{
			//if (!ft_strcmp(dirp->d_name, ".") || !ft_strcmp(dirp->d_name, ".."))
			//(dirp->d_name[0] == ft_strchr(dirp->d_name, int c));
			//if (ft_strcmp(dirp->d_name[0], ".") && ft_strcmp(opts, "a"))
			if (ft_strcmp(dir_name,"exacalibur"))
				count = 0;
			if ((dirp->d_name[0] == 'x') && ft_strcmp(opts, "a"))
				count++;
			else
			{
				//if(!ft_strcmp(dirp->d_name, "./"))
				//	display_stats(dir_name, dirp->d_name, opts);
				//printf("%s:\n", dir_name);
				ft_putstr(dirp->d_name);
				ft_putstr("\n");
				//display_stats(dir_name, dirp->d_name, opts);
			}
		}
	}
	//recurse_dirs(".", opts, 0);
	closedir(dp);
}

char	*ft_strjoins(char *s1, char *s2)
{
	char	*str;
	int		i;
	int		len1;
	int		len2;

	i = 0;
	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	str = (char*)malloc((sizeof(char) * len1 + len2) + 1);
	if (s1 && s2 && str)
	{
		while (i < len1)
		{
			str[i] = *s1++;
			i++;
		}
		while (i < len1 + len2)
		{
			str[i] = *s2++;
			i++;
		}
		str[i] = '\0';
	}
	return (str);
}

void	print_error(int condition, char *info, char *infos)
{
	if(condition == 1)
	{
		printf("ft_ls: illegal option -- %c\nusage: ft_ls [%s] [file ...]\n",
				*info, infos);
	}
	if(condition == 2)
	{
		printf("ft_ls: %s:  No such file or directory\n", info);
	}
}

void    check_usage(char *dirs, char *opts)
{
	char			*flags;
	char			*test;
	DIR				*dp;

	flags = "ABCFGHLOPRSTUWabcdefghiklmnopqrstuwx1";
	test = opts;
	printf("dirs: %s\n", dirs);
	while (*test != '\0')
	{
		if(!ft_strchr(flags, *test) && *test != '-')
		{
			print_error(1, test, flags);
			exit(0);
		}
		test++;
	}
	if ((dp = opendir(dirs)) == NULL)
		print_error(2, dirs, "");
	else
	{
		ft_putstr(dirs);
		ft_putstr(":\n");
		print_dirs(dp, opts, dirs);
	}
	return ;
}

int		main(int ac, char **av)
{
	char	*opts;
	int		x;

	opts = "";
	x = 1;
	if (ac == 1)
		check_usage("./", opts);
	else if (ac == 2)
		check_usage(((av[x][0] != '-') ? av[x] : "./"), ((av[x][0] == '-') 
					? av[x] : ""));
	else if (ac >= 2)
	{
		while (x++ < ac - 1)
			!(av[x][0] == '-') ? ft_strjoins(opts, av[x]) : ft_strjoins(opts, av[x]);
		x = 1;
		while (x++ < ac - 1)
		{
			((av[x][0] != '-') && x > 2) ? ft_putstr("\n") : ft_putstr("");
			(av[x][0] != '-') ? check_usage(av[x], opts) : ft_strjoins(opts, av[x]);
		}
		printf("opts: %s\n", opts);
	}
	return (0);
}
