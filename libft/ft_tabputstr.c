/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tabputstr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmuvezwa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/13 15:13:52 by kmuvezwa          #+#    #+#             */
/*   Updated: 2017/09/13 15:25:53 by kmuvezwa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_tabputstr(int pre, char *str, int post)
{
	while (pre > 0)
	{
		ft_putchar(' ');
		pre--;
	}
	ft_putstr(str);
	while (post > 0)
	{
		ft_putchar(' ');
		post--;
	}
	ft_putchar(' ');
}
