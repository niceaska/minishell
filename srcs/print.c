/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgigi <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/30 16:49:37 by lgigi             #+#    #+#             */
/*   Updated: 2019/05/30 17:38:31 by lgigi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void 	print_env(char **env)
{
	int i;

	i = 0;
	while (env[i])
		ft_putendl(env[i++]);
}

void	bull_echo(char **parse, t_env **e)
{
	int				i;
	unsigned int	size;

	i = (parse[1][0] == '-' && parse[1][1] == 'n'\
							&& !parse[1][2]) ? 2 : 1;
	size = tab_size(parse);
	while (parse[i])
	{
		parse[i] = clear_path(parse[i]);
		if (parse[i][0] == '$' && parse[i][1])
		{
			if ((get_pathname((*e)->e, &parse[i][1])) != NULL)
				ft_putstr(get_pathname((*e)->e, &parse[i][1]));
		}
		else
			ft_putstr(parse[i]);
		if (size > 2 && parse[i + 1])
			write(1, " ", 1);
		if (!(parse[1][0] == '-' && parse[1][1] == 'n'\
			&& !parse[1][2]) && !parse[i + 1])
			write(1, "\n", 1);
		i++;
	}
}