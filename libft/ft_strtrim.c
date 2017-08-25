/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmuvezwa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/13 15:30:44 by kmuvezwa          #+#    #+#             */
/*   Updated: 2017/08/13 15:33:27 by kmuvezwa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s)
{
	char		*result;
	char const	*end;
	char const	*start;

	start = NULL;
	if (s == NULL)
		return (NULL);
	while (*s)
	{
		if (!(*s == ' ' || *s == '\n' || *s == '\t'))
		{
			start = (start == NULL) ? s : start;
			end = s;
		}
		s++;
	}
	if (start == NULL)
		return (ft_strnew(0));
	if ((result = (char *)malloc(sizeof(char) * (end - start + 2))) == NULL)
		return (NULL);
	s = start;
	while (s <= end)
		*result++ = *s++;
	*result = '\0';
	return (result - (end - start + 1));
}
