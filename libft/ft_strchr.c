/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmuvezwa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/11 08:35:50 by kmuvezwa          #+#    #+#             */
/*   Updated: 2017/06/11 09:01:35 by kmuvezwa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	char	*temp;

	temp = (char *)s;
	while (*temp != '\0')
	{
		if (*temp == c)
		{
			return (temp);
		}
		temp++;
	}
	if (*temp == c)
	{
		return (temp);
	}
	return (NULL);
}
