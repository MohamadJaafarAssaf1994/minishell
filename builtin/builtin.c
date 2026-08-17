/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hammeah <hammeah@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/30 18:00:58 by mohassaf          #+#    #+#             */
/*   Updated: 2026/07/03 00:42:09 by hammeah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header/minishell.h"

int	is_builtin(t_cmd *cmd)
{
	if (cmd == NULL || cmd->args == NULL || cmd->args[0] == NULL)
		return (0);
	if (ft_strncmp(cmd->args[0], "echo", 5) == 0)
		return (1);
	if (ft_strncmp(cmd->args[0], "cd", 3) == 0)
		return (1);
	if (ft_strncmp(cmd->args[0], "pwd", 4) == 0)
		return (1);
	if (ft_strncmp(cmd->args[0], "export", 7) == 0)
		return (1);
	if (ft_strncmp(cmd->args[0], "unset", 6) == 0)
		return (1);
	if (ft_strncmp(cmd->args[0], "env", 4) == 0)
		return (1);
	if (ft_strncmp(cmd->args[0], "exit", 5) == 0)
		return (1);
	return (0);
}

int	is_parent_builtin(t_cmd *cmd)
{
	if (cmd == NULL || cmd->args == NULL || cmd->args[0] == NULL)
		return (0);
	if (ft_strncmp(cmd->args[0], "cd", 3) == 0)
		return (1);
	if (ft_strncmp(cmd->args[0], "export", 7) == 0)
		return (1);
	if (ft_strncmp(cmd->args[0], "unset", 6) == 0)
		return (1);
	if (ft_strncmp(cmd->args[0], "exit", 5) == 0)
		return (1);
	return (0);
}

int	exec_parent_builtin(t_cmd *cmds, t_shell *sh)
{
	if (cmds == NULL || cmds->args == NULL || cmds->args[0] == NULL)
		return (0);
	if (ft_strncmp(cmds->args[0], "cd", 3) == 0)
		return (builtin_cd(cmds, sh));
	if (ft_strncmp(cmds->args[0], "export", 7) == 0)
		return (builtin_export(cmds, sh));
	if (ft_strncmp(cmds->args[0], "unset", 6) == 0)
		return (builtin_unset(cmds, sh));
	if (ft_strncmp(cmds->args[0], "exit", 5) == 0)
		return (builtin_exit(cmds, sh));
	return (0);
}

int	exec_builtin(t_cmd *cmds, t_shell *sh)
{
	if (cmds == NULL || cmds->args == NULL || cmds->args[0] == NULL)
		return (0);
	if (ft_strncmp(cmds->args[0], "echo", 5) == 0)
		return (builtin_echo(cmds, sh));
	if (ft_strncmp(cmds->args[0], "cd", 3) == 0)
		return (builtin_cd(cmds, sh));
	if (ft_strncmp(cmds->args[0], "pwd", 4) == 0)
		return (builtin_pwd(cmds, sh));
	if (ft_strncmp(cmds->args[0], "export", 7) == 0)
		return (builtin_export(cmds, sh));
	if (ft_strncmp(cmds->args[0], "unset", 6) == 0)
		return (builtin_unset(cmds, sh));
	if (ft_strncmp(cmds->args[0], "env", 4) == 0)
		return (builtin_env(cmds, sh));
	if (ft_strncmp(cmds->args[0], "exit", 5) == 0)
		return (builtin_exit(cmds, sh));
	return (1);
}
