/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgigi <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/30 18:24:03 by lgigi             #+#    #+#             */
/*   Updated: 2019/05/30 21:40:58 by lgigi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

char	*add_slash(char *path)
{
	char *swp;

	swp = path;
	path = ft_strjoin(path, "/");
	free(swp);
	return (path);
}

char	*looking_pathname(char *path, char **env,
							char **path_var, char *swp)
{
	int		i;

	i = -1;
	path_var = ft_strsplit(get_pathname(env, "PATH"), ':');
	while (path_var[++i])
	{
		path_var[i] = add_slash(path_var[i]);
		swp = path;
		path = ft_strjoin(path_var[i], path);
		if (!access(path, F_OK))
		{
			if (access(path, R_OK))
				write(2, "minishell: permission denied\n", 29);
			break ;
		}
		ft_memdel((void *)&path);
		path = swp;
	}
	(!path_var || !path_var[i]) ?\
			write(2, "minishell: command not found\n", 29) : 0;
	(path_var[i]) ? ft_memdel((void *)&swp) : 0;
	(!path_var || !path_var[i] || access(path, R_OK)) ?\
								ft_memdel((void *)&path) : 0;
	free_tab(path_var);
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
	if (pid == 0)
	{
		execve(path, args, env);
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

void	process_exec(char **parse, t_env **e)
{
	char *pathname;

	parse[0] = clear_path(parse[0]);
	if (!(pathname = find_rpath(ft_strdup(parse[0]), (*e)->e)))
		return ;
	if (pathname && access(pathname, R_OK))
		write(2, "minishell: permission denied\n", 29);
	exec_program(pathname, parse, (*e)->e);
	free(pathname);
}