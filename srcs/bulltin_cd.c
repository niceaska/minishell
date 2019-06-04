/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bulltin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgigi <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/29 14:20:45 by lgigi             #+#    #+#             */
/*   Updated: 2019/06/04 22:52:33 by lgigi            ###   ########.fr       */
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

static char		*choose_pathname(char *path, t_env **e)
{
	char *pathname;

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
	return (pathname);
}

static int	check_errors(char *arg)
{
	int error;

	error = 0;
	if (arg && access(arg, F_OK | R_OK))
	{
		error = 1;
		write(2, "cd: ", 4);
		if (errno == EACCES)
			write(2, "permission denied\n", 18);
		else if (errno == ENOTDIR)
			write(2, "not a directory\n", 16);
		else if (errno == ENOENT)
			write(2, "no such file or directory\n", 26);
		else if (errno == ENAMETOOLONG)
			write(2, "pathname is too long\n", 21);
	}
	return (error);
}

static void		process_cd(char *path, t_env **e)
{
	char	currpath[PATH_MAX];
	char	*pathname;

	ft_bzero((void *)currpath, PATH_MAX);
	getcwd(currpath, PATH_MAX);
	pathname = choose_pathname(path, e);
	if (check_errors(pathname))
	{
		free(pathname);
		return ;
	}
	chdir(pathname);
	(*e)->e = ft_setenv("OLDPWD", currpath, (*e)->e);
	getcwd(currpath, PATH_MAX);
	(*e)->e = ft_setenv("PWD", currpath, (*e)->e);
	free(pathname);
}

void	bulltin_cd(char **parse, t_env **e)
{
	struct stat		st;

	if (parse[1] && parse[2])
	{
		write(2, "cd: too many arguments\n", 23);
		return ;
	}
	if (parse[1] && (stat(parse[1], &st)) != -1)
		if (!S_ISDIR(st.st_mode) && !S_ISLNK(st.st_mode))
		{
			write(2, "cd: not a directory\n", 20);
			return ;
		}
	return (process_cd(parse[1], e));
}