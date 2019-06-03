/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_env_bulltin.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgigi <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/03 21:03:12 by lgigi             #+#    #+#             */
/*   Updated: 2019/06/03 21:12:24 by lgigi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void		fill_envv(char **parse, char **envv, int i)
{
	while (parse[++i])
		if (!ft_strchr(parse[i], '='))
			break ;
		else
			envv = ft_setenv(parse[i], "", envv);
	exec_program(parse[i], parse + i, envv);
	free_tab(evv);
}

void		process_env_bull(char **parse, t_env **e, int j)
{
	char	**evv;
	int		size;
	int		i;

	if (!parse[1])
		return (print_env((*e)->e));
	i = (!ft_strcmp(parse[1], "-i")) ? 1 : 0;
	if (!ft_strcmp(parse[1], "-i"))
	{
		if (!parse[2])
			return ;
		if (!ft_strchr(parse[2], '='))
			return (process_exec(parse + 2, e, 0));
		if ((size = tab_size(parse)) < 0)
			size = 1;
		if (!(evv = (char **)malloc(sizeof(char *) * (size + 1))))
			return ;
		evv[j++] = ft_strdup("PATH=");
		evv[j] = 0;
	}
	else
		evv = cpy_envv((*e)->e);
	return (fill_envv(parse, evv, i));
}
