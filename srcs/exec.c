/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgigi <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/30 18:24:03 by lgigi             #+#    #+#             */
/*   Updated: 2019/06/03 21:03:39 by lgigi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

char	*looking_pathname(char *path, char **env,
							char **path_var, char *swp)
{
	int		i;

	i = -1;
	if (!env || !get_pathname(env, "PATH"))
		return (NULL);
	path_var = ft_strsplit(get_pathname(env, "PATH"), ':');
	while (path_var && path_var[++i])
	{
		path_var[i] = add_slash(path_var[i]);
		swp = path;
		path = ft_strjoin(path_var[i], path);
		if (!access(path, F_OK))
			break ;
		ft_memdel((void *)&path);
		path = swp;
	}
	(!path_var || !path_var[i]) ?\
			write(2, "minishell: command not found\n", 29) : 0;
	(path_var && path_var[i]) ? ft_memdel((void *)&swp) : 0;
	(!path_var || !path_var[i]) ? ft_memdel((void *)&path) : 0;
	(path_var) ? free_tab(path_var) : 0;
	return (path);
}

char	*find_rpath(char *path, char **env)
{
	if (ft_strchr(path, '/'))
	{
		if (access(path, F_OK | R_OK))
		{
			write(2, "minishell: ", 11);
			if (errno == EACCES)
				write(2, "permission denied\n", 18);
			else if (errno == ENOENT)
				write(2, "command not found\n", 18);
		}
		(access(path, F_OK | R_OK)) ? ft_memdel((void *)&path) : 0;
		return (path);
	}
	return (looking_pathname(path, env, NULL, NULL));
}


void	exec_program(char *path, char **args, char **env)
{
	pid_t pid;
	pid_t ch_pid;

	pid = fork();
	signal(SIGINT, signal_exec_handler);
	if (pid == 0)
	{
		execve(path, args, env);
		exit(0);
	}
	else if (pid > 0)
	{
		while ((ch_pid = wait(0)) != -1)
			;
		if (errno != ECHILD)
			write(2, "minishell: wait error\n", 22);
	}
	else
		write(2, "minishell: fork error\n", 22);
}

void	process_exec(char **parse, t_env **e, int fl)
{
	char *pathname;

	parse[0] = clear_path(parse[0]);
	if (!(pathname = find_rpath(ft_strdup(parse[0]), (*e)->e)))
		return ;
	if (pathname && access(pathname, R_OK | X_OK))
	{
		write(2, "minishell: permission denied\n", 29);
		free(pathname);
		return ;
	}
	if (fl)
		exec_program(pathname, parse, (*e)->e);
	else
		exec_program(pathname, parse, 0);
	free(pathname);
}