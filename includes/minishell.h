/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgigi <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/29 10:53:36 by lgigi             #+#    #+#             */
/*   Updated: 2019/06/04 22:46:42 by lgigi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_MINISHELL_H
# define FT_MINISHELL_H

# include <libft.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <errno.h>
# include <dirent.h>
# include <sys/dir.h>
# include <limits.h>
# include <sys/wait.h>
# include <linux/limits.h>
# include <stdio.h>
# include <signal.h> 
# include <readline/history.h>
# include <readline/readline.h>

# define FL_AUTO (1 << 0)

typedef struct	s_env
{
	char	*home;
	char	**e;
	short	flags;
}				t_env;

char			*get_pathname(char **e, char *var);
int				print_currpath(char **parse);
unsigned int	tab_size(char **tab);
char			*add_slash(char *path);
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
void			process_exec(char **parse, t_env **e, int fl);
char			**ft_splitwhitesp(char const *s);
char			**ag_compl(const char *text, int start, int end);
void			signal_handler(int sign);
void			signal_exec_handler(int sig);
void			ft_exit(char **tab, char **parse, t_env *e, int fl);
char			**cpy_envv(char **ev);
void			exec_program(char *path, char **args, char **env);
void			process_env_bull(char **parse, t_env **e, int j);
void			process_exit(char **tab, char **parse, t_env *e);



#endif