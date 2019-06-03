/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_whitspaces.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgigi <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/30 21:50:31 by lgigi             #+#    #+#             */
/*   Updated: 2019/05/30 21:55:21 by lgigi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		count_words(char *s)
{
	int		inword;
	int		words;

	words = 0;
	inword = 0;
	while (*s != '\0')
	{
		if (!inword && !ft_isspace(*s))
		{
			words++;
			inword = 1;
		}
		else if (inword && ft_isspace(*s))
			inword = 0;
		s++;
	}
	return (words);
}

static void		free_tab(char **tab)
{
	unsigned int i;

	i = 0;
	if (tab != NULL)
	{
		while (tab[i])
			if (tab[i] != NULL)
				free(tab[i++]);
		free(tab);
	}
}

static char		**split(char *s, int i, char **tab)
{
	size_t	size;
	size_t	k;
	size_t	j;

	k = 0;
	while (++i < count_words(s))
	{
		size = 0;
		while (*(s + k) && ft_isspace(*(s + k)))
			k++;
		while (*(s + k + size) && !ft_isspace(*(s + k + size)))
			size++;
		if ((tab[i] = ft_strnew(size)) == NULL)
		{
			free_tab(tab);
			return (NULL);
		}
		k += size;
		j = k - 1;
		while (size && !ft_isspace((*(s + j)) || j != 0))
			tab[i][--size] = *(s + j--);
	}
	tab[i] = NULL;
	return (tab);
}

char			**ft_splitwhitesp(char const *s)
{
	char			**tab;
	unsigned int	size;

	if (!s)
		return (NULL);
	size = count_words((char *)s);
	if (!(tab = (char **)malloc(sizeof(char *) * (size + 1))))
		return (NULL);
	if (!size)
	{
		tab[0] = 0;
		return (tab);
	}
	tab = split((char *)s, -1, tab);
	return (tab);
}
