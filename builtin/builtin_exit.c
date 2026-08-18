/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohassaf <mohassaf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/31 16:15:01 by mohassaf          #+#    #+#             */
/*   Updated: 2026/08/11 15:19:42 by mohassaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header/minishell.h"

static void	exit_shell(t_cmd *cmds, t_shell *sh, int status)
{
	free_cmds(cmds);
	cleanup_shell(sh);
	exit(status);
}

static	int	is_numeric_arg(char *str)
{
	int	i;

	i = 0;
	if (str == NULL || str[0] == '\0')
		return (0);
	if (str[i] == '+' || str[i] == '-')
		i++;
	if (str[i] == '\0')
		return (0);
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

int	builtin_exit(t_cmd *cmds, t_shell *sh)
{
	int	code;

	write(1, "exit\n", 5);
	if (cmds->args[1] == NULL)
		exit_shell(cmds, sh, sh->exit_status);
	if (is_numeric_arg(cmds->args[1]) == 0)
	{
		write (2, "minishell: exit: numeric argument required\n", 43);
		exit_shell(cmds, sh, 2);
	}
	if (cmds->args[2] != NULL)
	{
		write(2, "minishell: exit: too many arguments\n", 36);
		return (2);
	}
	code = ft_atoi(cmds->args[1]);
	exit_shell(cmds, sh, (unsigned char)code);
	return (0);
}
