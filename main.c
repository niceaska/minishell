/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgigi <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/29 10:52:16 by lgigi             #+#    #+#             */
/*   Updated: 2019/06/02 20:32:04 by lgigi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_env	*init_env(char **ev)
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
	e->flags = 1;
	return (e);
}

static char		**process_prompt(t_env *e)
{
	char	*line;
	int		rd;
	char	buf;
	char	**parse;

	if ((e->flags & FL_AUTO))
	{
		rl_readline_name = "Minishell";
		rl_attempted_completion_function = ag_compl;
		line = readline("$> ");
		if (line && ft_strlen(line) > 0)
			add_history(line);
	}
	(!(e->flags & FL_AUTO)) ? write(1, "$> ", 3) : 0;
	parse = ((e->flags & FL_AUTO) && line) ? ft_strsplit(line, ';') : 0;
	if (!(e->flags & FL_AUTO) && \
		(rd = get_next_line(0, &line)) == 1)
		parse = ft_strsplit(line, ';');
	ft_memdel((void *)&line);
	return (parse);
}

static void		ft_run_commands(char **tab, char **parse, t_env **env)
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
		ft_exit(tab, parse, *env, 0);
	else if (!ft_strcmp(parse[0], "echo"))
		bull_echo(parse, env);
	else
		process_exec(parse, env);
}

static void		process_input(char **tab, t_env **env)
{
	char	**parse;
	int		i;
	
	i = -1;
	while (tab[++i])
	{
		if (!(parse = ft_splitwhitesp(tab[i])))
		{
			write(2, "minishell: malloc error\n", 24);
			ft_exit(tab, parse, *env, 1);
			return ;
		}
		if (*parse)
			ft_run_commands(tab, parse, env);
		free_tab(parse);
	}
}

int				main(int ac, char **ag, char **ev)
{
	t_env	*env;
	char	**tab;

	if (!(env = init_env(ev)))
		return (1);
	write(1, "Minishell v0.9b\n", 16);
	while (1)
	{
		signal(SIGINT, signal_handler);
		if (!(tab = process_prompt(env)))
		{
			ft_exit(tab, 0, env, 1);
			write(2, "minishell: malloc error\n", 24);
		}
		process_input(tab, &env);
		free_tab(tab);
	}
}