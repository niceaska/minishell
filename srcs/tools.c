/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgigi <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/29 11:03:48 by lgigi             #+#    #+#             */
/*   Updated: 2019/06/03 20:06:29 by lgigi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char			*get_pathname(char **e, char *var)
{
	unsigned int	i;
	char			*variab;
	char			*envar;

	i = 0;
	if (!var || !*var || !e || !*e)
		return (NULL);
	variab = ft_strjoin(var, "=");
	envar = 0;
	while (e[i])
	{
		if (ft_strstr(e[i], variab) && \
		!ft_strcmp(e[i], ft_strstr(e[i], variab)))
		{
			envar = e[i];
			break ;
		}
		i++;
	}
	free(variab);
	return (envar ? (ft_strchr(envar, '=') + 1) : 0);
}

unsigned int	tab_size(char **tab)
{
	unsigned int i;

	i = 0;
	if (!tab)
		return (0);
	while (tab[i])
		i++;
	return (i);
}

int				find_var(char **tab, char *var)
{
	int		i;
	char	*find;

	i = 0;
	while (tab[i])
	{
		if ((find = ft_strstr(tab[i], var)) != 0)
			if (!ft_strcmp(find, tab[i]))
				break ;
		i++;
	}
	return (tab[i] ? i : -1);
}

char			**realloc_var(char **tab, char *str, int i)
{
	char *swp;

	swp = tab[i];
	tab[i] = ft_strdup(str);
	free(swp);
	return (tab);
}

char			*clear_path(char *path)
{
	char			*swp;
	unsigned int	pth_s;

	pth_s = ft_strlen(path);
	if (path[0] != '"' && \
		path[pth_s - 1] != '"')
		return (path);
	if (path[pth_s - 1] == '"')
		path[pth_s - 1] = '\0';
	if (*path == '"')
	{
		swp = path;
		path = ft_strdup(path + 1);
		free(swp);
	}
	return (path);
}
