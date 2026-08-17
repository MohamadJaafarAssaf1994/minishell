/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohassaf <mohassaf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/30 20:25:26 by mohassaf          #+#    #+#             */
/*   Updated: 2026/08/11 15:25:28 by mohassaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header/minishell.h"

static int	is_n_option(char *arg)
{
	int	i;

	if (arg == NULL || arg[0] != '-' || arg[1] != 'n')
		return (0);
	i = 2;
	while (arg[i])
	{
		if (arg[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

int	builtin_echo(t_cmd *cmds, t_shell *sh)
{
	int	i;
	int	newline;

	(void)sh;
	i = 1;
	newline = 1;
	while (cmds->args[i] && is_n_option(cmds->args[i]))
	{
		newline = 0;
		i++;
	}
	while (cmds->args[i])
	{
		write(1, cmds->args[i], ft_strlen(cmds->args[i]));
		if (cmds->args[i + 1])
			write(1, " ", 1);
		i++;
	}
	if (newline)
		write(1, "\n", 1);
	return (0);
}
