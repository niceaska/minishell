/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgigi <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/29 10:52:16 by lgigi             #+#    #+#             */
/*   Updated: 2019/05/30 21:58:07 by lgigi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

t_env	*init_env(char **ev)
{
	t_env *e;

	if (!(e = (t_env *)malloc(sizeof(t_env))))
		return (NULL);
	if (!(e->e = cpy_envv(ev)))
	{
		free(e);
		return (NULL);
	}
	e->home = get_pathname(e->e, "HOME");
	return (e);
}


char	**process_prompt(void)
{
	char	*line;
	int		rd;
	char	**parse;

	line = NULL;
	write(1, "$> ", 3);
	if ((rd = get_next_line(0, &line)) == 1)
		parse = ft_strsplit(line, ';');
	else
		parse = NULL;
	ft_memdel((void *)&line);
	return (parse);
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

void	bulltin_exit(char **tab, char **parse, t_env *e)
{
	free_tab(tab);
	free_tab(parse);
	free_tab(e->e);
	free(e);
	exit(EXIT_SUCCESS);
}

void	process_input(char **tab, t_env **env)
{
	char	**parse;
	int		i;
	
	i = -1;
	while (tab[++i])
	{
		if (!(parse = ft_splitwhitesp(tab[i])))
		{
			// free and error
			return ;
		}
		if (*parse)
		{
			if (!ft_strcmp(parse[0], "pwd"))
				print_currpath(parse);
			else if (!ft_strcmp(parse[0], "env"))
				print_env((*env)->e);
			else if (!ft_strcmp(parse[0], "setenv"))
				(*env)->e = setenv_bulltin(parse, (*env)->e);
			else if (!ft_strcmp(parse[0], "unsetenv"))
				(*env)->e = unsetenv_bulltin(parse, (*env)->e);
			else if (!ft_strcmp(parse[0], "cd"))
				bulltin_cd(parse, env);
			else if (!ft_strcmp(parse[0], "exit"))
				bulltin_exit(tab, parse, *env);
			else if (!ft_strcmp(parse[0], "echo"))
				bull_echo(parse, env);
			else
				process_exec(parse, env);
		}
		free_tab(parse);
	}
}


int		main(int ac, char **ag, char **ev)
{
	t_env	*env;
	char	**tab;

	if (!(env = init_env(ev)))
		return (1);
	write(1, "Minishell v0.1b\n", 16);
	while (1)
	{
		if (!(tab = process_prompt()))
		{
			// free
			write(2, "malloc err\n", 10);
		}
		process_input(tab, &env);
		free_tab(tab);
	}
}