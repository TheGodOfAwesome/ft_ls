/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmuvezwa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/07 16:41:10 by kmuvezwa          #+#    #+#             */
/*   Updated: 2017/08/07 16:44:37 by kmuvezwa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s)
{
	char	*temp;
	int		i;

	i = 0;
	if (s)
	{
		temp = (char *)malloc(sizeof(char *) * ft_strlen((char *)s));	
		while (s[i] != '\0')
		{
			if (s[i] != ' ' || s[i] != '\t' || s[i] != '\n')
				temp[i] = s[i];
			i++;
		}
	}
	temp[i] = '\0';
	return (temp);
}
