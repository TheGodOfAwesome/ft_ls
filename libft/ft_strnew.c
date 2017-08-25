/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmuvezwa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/24 20:28:55 by kmuvezwa          #+#    #+#             */
/*   Updated: 2017/08/12 16:07:38 by kmuvezwa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnew(size_t size)
{
	char	*str;

	str = (char*)ft_memalloc(sizeof(*str) * size + 1);
	if (!str)
		return (NULL);
	ft_memset(str, 0, size + 1);
	return (str);
}
