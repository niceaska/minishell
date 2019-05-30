/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgigi <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/29 10:53:36 by lgigi             #+#    #+#             */
/*   Updated: 2019/05/30 21:55:03 by lgigi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_MINISHELL_H
# define FT_MINISHELL_H

# include "libft/includes/libft.h"
# include <sys/types.h>
# include <errno.h>
# include <dirent.h>
# include <stdio.h>
# include <sys/dir.h>
# include <limits.h>
# include <sys/wait.h>
# include <linux/limits.h>


typedef struct	s_env
{
	char	*currpath;
	char	*home;
	char	**e;
}				t_env;

char			*get_pathname(char **e, char *var);
int				print_currpath(char **parse);
unsigned int	tab_size(char **tab);
int				in_tab(char **tab, char *str);
char 			**ft_setenv(char *var, char *value, char **env);
void 			print_env(char **env);
void			free_tab(char **tab);
char			**setenv_bulltin(char **parse, char **env);
char			**unsetenv_bulltin(char **parse, char **env);
char			**realloc_var(char **tab, char *str, int i);
int				find_var(char **tab, char *var);
void			bulltin_cd(char **parse, t_env **e);
char			*clear_path(char *path);
void			bull_echo(char **parse, t_env **e);
void			process_exec(char **parse, t_env **e);
char			**ft_splitwhitesp(char const *s);

#endif