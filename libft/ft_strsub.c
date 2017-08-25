/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmuvezwa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/09 10:55:32 by kmuvezwa          #+#    #+#             */
/*   Updated: 2017/08/04 16:38:08 by kmuvezwa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strsub(char const *s, unsigned int start, size_t len)
{
	char	*substr;
	char	*str;

	substr = ft_strnew(len);
	if (!substr)
		return (NULL);
	if (!s)
		return (NULL);
	str = (char*)s;
	if (ft_strlen(str) >= (int)(start + len))
	{
		str = str + start;
		ft_strncpy(substr, str, len);
	}
	return (substr);
}
