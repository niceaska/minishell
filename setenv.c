/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setenv.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgigi <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/29 15:35:05 by lgigi             #+#    #+#             */
/*   Updated: 2019/05/29 21:29:25 by lgigi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**realloc_env(char **tab, char *str)
{
	unsigned int	new_size;
	char			**new;
	int				i;

	i = 0;
	new_size = tab_size(tab) + 1;
	if (!(new = (char **)malloc(sizeof(char *) * (new_size + 1))))
		return (NULL);
	while (tab[i])
	{
		new[i] = ft_strdup(tab[i]);
		i++;
	}
	new[i++] = ft_strdup(str);
	new[i] = 0;
	free_tab(tab);
	return (new);
}

char	**ft_setenv(char *var, char *value, char **env)
{
	unsigned int	len;
	int				ret;
	char			*val;
	char			*swp;
	char			*putstr;

	val = (!value) ? ft_strdup("\0") : ft_strdup(value);
	len = ft_strlen(var) + ft_strlen(val) + 1;
	putstr = ft_strnew(len);
	ft_strcpy(putstr, var);
	putstr[ft_strlen(putstr)] = '=';
	swp = putstr;
	putstr = ft_strjoin(putstr, val);
	free(swp);
	if ((ret = find_var(env, var)) != -1)
		env = realloc_var(env, putstr, ret);
	else
		env = realloc_env(env, putstr);
	free(putstr);
	free(val);
	return (env);
}

char	**setenv_bulltin(char **parse, char **env)
{
	if (!parse[1])
	{
		print_env(env);
		return (env);
	}
	if (parse[2] != NULL && parse[3] != NULL)
	{
		write(2, "setenv: too many arguments.\n", 28);
		return (env);
	}
	if (!ft_isalpha(parse[1][0]))
	{
		write(2, "setenv: not an identifier: ", 27);
		write(2., parse + 2, ft_strlen(parse[2]));
		write(2, "\n", 1);
		return (env);
	}
	return (ft_setenv(parse[1], parse[2], env));
}

char	**ft_unsetenv(char *var, char **env)
{
	int		i;
	int		j;
	char	**new;
	int		var_ind;

	i = 0;
	j = 0;
	if ((var_ind = find_var(env, var)) == -1)
		return (env);
	if (!(new = (char **)malloc(sizeof(char *) * tab_size(env))))
		return (NULL);
	while (env[i])
	{
		if (i != var_ind)
			new[j++] = ft_strdup(env[i]);
		i++;
	}
	new[j] = NULL;
	free_tab(env);
	return (new);
}

char	**unsetenv_bulltin(char **parse, char **env)
{
	if (!parse[1])
	{
		write(2, "unsetenv: not enough arguments\n", 31);
		return (env);

	}
	if (find_var(env, parse[1]) == -1)
		return (env);
	return (ft_unsetenv(parse[1], env));
}