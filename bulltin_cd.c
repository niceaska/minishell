/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bulltin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgigi <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/29 14:20:45 by lgigi             #+#    #+#             */
/*   Updated: 2019/05/30 16:21:48 by lgigi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

int		print_currpath(char **parse)
{
	char *path;

	if (parse[1])
	{
		write(2, "pwd: too many arguments\n", 24);
		return (1);
	}
	if (!(path = getcwd(0, 0)))
		return (0);
	ft_putendl(path);
	free(path);
	return (1);
}

void	process_cd(char *path, t_env **e)
{
	char	currpath[PATH_MAX];
	char	*pathname;

	getcwd(currpath, PATH_MAX);
	if (!path || (path[0] == '~' && !path[1]))
		pathname = ft_strdup((*e)->home);
	else if (path[0] == '-' && !path[1])
		pathname = ft_strdup(get_pathname((*e)->e, "OLDPWD"));
	else if (path[0] == '~' && path[1])
		pathname = ft_strjoin((*e)->home, path + 1);
	else if (path[0] == '$' && path[1])
	{
		if (!(pathname = get_pathname((*e)->e, path + 1)))
			pathname = ft_strdup((*e)->home);
		else
			pathname = ft_strdup(get_pathname((*e)->e, path + 1));
	}
	else
		pathname = ft_strdup(path);	
	chdir(pathname);
	(*e)->e = ft_setenv("OLDPWD", currpath, (*e)->e);
	getcwd(currpath, PATH_MAX);
	(*e)->e = ft_setenv("PWD", currpath, (*e)->e);
	free(pathname);
}

void	bulltin_cd(char **parse, t_env **e)
{
	if (parse[1] && parse[2])
	{
		write(2, "cd: too many arguments\n", 23);
		return ;
	}
	parse[1] = clear_path(parse[1]);
	if (parse[1] && parse[1][0] != '-' && parse[1][0] != '~'\
		&& !(parse[1][0]  == '$' && parse[1][1]) \
		&& access(parse[1], F_OK | R_OK))
	{
		write(2, "cd: ", 4);
		if (errno == EACCES)
			write(2, "permission denied\n", 18);
		else if (errno == ENOTDIR)
			write(2, "not a directory\n", 16);
		else if (errno == ENOENT)
			write(2, "no such file or directory\n", 26);
		else if (errno == ENAMETOOLONG)
			write(2, "pathname is too long\n", 21);
		return ;
	}
	return (process_cd(parse[1], e));
}