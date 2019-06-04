/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_bulltin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgigi <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/04 13:51:38 by lgigi             #+#    #+#             */
/*   Updated: 2019/06/04 14:34:05 by lgigi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


void	ft_exit(char **tab, char **parse, t_env *e, int fl)
{
	if (tab)
		free_tab(tab);
	if (parse)
		free_tab(parse);
	if (e)
	{
		if (e->home)
			free(e->home);
		if (e->e)
			free_tab(e->e);
		free(e);
	}
	exit(fl);
}

void	process_exit(char **tab, char **parse, t_env *e)
{
	int flag;

	if (parse[1] && parse[2])
	{
		write(2, "exit: too many arguments\n", 25);
		return ;
	}
	if (parse[1])
		flag = ft_atoi(parse[1]);
	else
		flag = 0;
	return (ft_exit(tab, parse, e, flag));
}