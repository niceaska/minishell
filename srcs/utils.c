/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgigi <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/01 19:39:52 by lgigi             #+#    #+#             */
/*   Updated: 2019/06/04 13:52:23 by lgigi            ###   ########.fr       */
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

char	**cpy_envv(char **ev)
{
	char			**new;
	unsigned int	size;
	int				i;

	i = 0;
	size = 0;
	if (!(size = tab_size(ev)))
		size = 1;
	if (!get_pathname(ev, "PATH"))
		size += 1;
	if (!(new = (char **)malloc(sizeof(char *) * (size + 1))))
		return (NULL);
	while (ev && ev[i])
	{
		new[i] = ft_strdup(ev[i]);
		i++;
	}
	if (!get_pathname(ev, "PATH"))
		new[i++] = ft_strdup("PATH=");
	new[i] = NULL;
	return (new);
}
