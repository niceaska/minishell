/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgigi <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/01 19:39:52 by lgigi             #+#    #+#             */
/*   Updated: 2019/06/01 19:47:23 by lgigi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	signal_exec_handler(int sig)
{
	if (sig == SIGINT)
		write(1, "\n", 1);
}
 
void	signal_handler(int sig)
{
	if (sig == SIGINT)
	{
		write(1, "\n$> ", 4);
	}
}

void	free_tab(char **tab)
{
	unsigned int i;

	i = 0;
	if (tab)
	{
		while (tab[i])
			if (tab[i])
				free(tab[i++]);
		free(tab);
	}
}

void	ft_exit(char **tab, char **parse, t_env *e, short fl)
{
	if (tab)
		free_tab(tab);
	if (parse)
		free_tab(parse);
	if (e)
	{
		free_tab(e->e);
		free(e);
	}
	exit(fl);
}

char	**cpy_envv(char **ev)
{
	char			**new;
	int				i;

	i = 0;
	if (!(new = (char **)malloc(sizeof(char *) * (tab_size(ev) + 1))))
		return (NULL);
	while (ev[i])
	{
		new[i] = ft_strdup(ev[i]);
		i++;
	}
	new[i] = NULL;
	return (new);
}