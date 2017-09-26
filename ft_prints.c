/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_prints.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmuvezwa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/26 16:31:43 by kmuvezwa          #+#    #+#             */
/*   Updated: 2017/09/26 17:04:02 by kmuvezwa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

char		*append_str(int *cnt, char *str, char *opts, DIR *dp)
{
	struct dirent	*dirp;

	if ((dirp = readdir(dp)) != NULL)
	{
		if (ft_strchr(opts, 'l'))
		{
			ft_putstr("total ");
			ft_putendl(ft_itoa(cnt[5]));
		}
		while ((dirp = readdir(dp)) != NULL)
		{
			if(!(!ft_strchr(opts, 'a') && dirp->d_name[0] == '.'))
			{
				ft_strcat(str, dirp->d_name);
				ft_strcat(str, ",");
			}
		}
	}
	return (str);
}

void		print(char *str, char *opts, char *dir, int *cnt)
{
	char		**ls;

	ls = ft_strsplit(str, ',');
	(ft_strchr(opts, 'r')) 
		? ft_revsortstr(ls, cnt[6]) : ft_sortstr(ls, cnt[6]);
	((ft_strchr(opts, 'r') && ft_strchr(opts, 't')))
		? ft_rtimesortstr(ls, cnt[6], dir) : str;
	(!ft_strchr(opts, 't')) 
		? str : ft_timesortstr(ls, cnt[6], dir);
	(ft_strchr(opts, 'l'))
		? print_stats(ls, cnt[6], opts, dir) : ft_putstrs(ls, cnt[6]);
}

void		print_dirs(DIR *dp, char *opts, char *dir)
{
	char			*str;
	int				*cnt;

	ft_putstr(dir);
	ft_putendl(":");
	cnt = count_files(dir, opts);
	str = "";
	str = (char *)ft_memalloc(sizeof(char) * (cnt[5] * cnt[0]));
	if (ft_strchr(opts, 'a'))
		ft_strcat(str, ".,");
	str = append_str(cnt, str, opts, dp);
	print(str, opts, dir, cnt);
	free(str);
	closedir(dp);
}
