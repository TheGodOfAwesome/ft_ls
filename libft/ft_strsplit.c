/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmuvezwa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/13 15:19:46 by kmuvezwa          #+#    #+#             */
/*   Updated: 2017/08/13 15:25:57 by kmuvezwa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_words(char const *s, char *c)
{
	int		i;
	int		j;
	int		word;

	i = 0;
	j = 0;
	word = 0;
	if (ft_strstr(s, c) == NULL)
		return (1);
	while (s[i])
	{
		while (s[i] != c[0] && s[i])
		{
			j++;
			i++;
		}
		if (j != 0 && ((s[i] == c[0]) || s[i] == '\0'))
		{
			j = 0;
			word++;
		}
		if (s[i] != '\0')
			i++;
	}
	return (word);
}

static int	word_len(char const *s, char c)
{
	int		letter;
	int		i;

	letter = 0;
	i = 0;
	while (s[i] != c && s[i] != '\0')
	{
		i++;
		letter++;
	}
	return (letter);
}

char		**ft_strsplit(char const *s, char c)
{
	char	**str;
	int		words;
	int		i;
	char	ch[1];

	i = 0;
	ch[0] = c;
	if (s == NULL)
		return (NULL);
	words = count_words(s, ch);
	if (!(str = (char **)malloc(sizeof(*str) * (words + 1))))
		return (NULL);
	if (s[0] == '\0')
		str[i] = ft_strsub(s, 0, word_len(s, c));
	while (words-- && s[0] != '\0')
	{
		while (*s == c && *s)
			s++;
		str[i] = ft_strsub(s, 0, word_len(s, c));
		s = s + word_len(s, c);
		i++;
	}
	str[i] = NULL;
	return (str);
}
