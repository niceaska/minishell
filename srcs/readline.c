/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgigi <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/01 10:58:40 by lgigi             #+#    #+#             */
/*   Updated: 2019/06/04 22:49:02 by lgigi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*g_commands[] = {
	"cat", "cd", "delete", "ls", "clear", "pwd",
	"valgrind", "mkdir", "rm", "rmdir", "gcc", "cp",
	"env", "setenv", "unsetenv", "emacs", "vim", "touch",
	"man", "mv", "exit", "echo", (char *)NULL,
};

static char	*args_generator(const char *text, int state)
{
    static int		index;
	static int		len;
    char			*command;

    if (!state)
	{
        index = 0;
        len = ft_strlen(text);
    }
    while ((command = g_commands[index++]))
	{
        if (ft_strncmp(command, text, len) == 0)
            return (ft_strdup(command));
    }
    return (0);
}

char	**ag_compl(const char *text, int start, int end)
{
    rl_attempted_completion_over = 0;
    (void)end;
    return (!start ?
		rl_completion_matches(text, args_generator) : 0);
}
