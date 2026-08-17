/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_loop.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohassaf <mohassaf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/11 19:09:13 by mohassaf          #+#    #+#             */
/*   Updated: 2026/08/14 11:40:33 by mohassaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header/minishell.h"

static void	update_signal_status(t_shell *sh)
{
	if (g_signal != 0)
	{
		sh->exit_status = 128 + g_signal;
		g_signal = 0;
	}
}

static void	run_line(t_shell *sh, char *line)
{
	t_cmd	*cmds;
	int		parse_status;

	parse_status = 0;
	cmds = parse_line(line, &parse_status);
	if (cmds == NULL)
	{
		if (parse_status != 0)
			sh->exit_status = parse_status;
		return ;
	}
	if (expand_commands(cmds, sh) == FAILURE)
		sh->exit_status = FAILURE;
	else
	{
		setup_signals_exec();
		sh->exit_status = execute(cmds, sh);
		if (g_signal != 0)
		{
			sh->exit_status = 128 + g_signal;
			g_signal = 0;
		}
	}
	free_cmds(cmds);
}

void	shell_loop(t_shell *sh)
{
	char	*line;

	while (1)
	{
		setup_signals_prompt();
		line = readline("minishell$ ");
		if (line == NULL)
			break ;
		update_signal_status(sh);
		if (*line)
			add_history(line);
		run_line(sh, line);
		free(line);
	}
	write(1, "exit\n", 5);
}

int	execute(t_cmd *cmds, t_shell *sh)
{
	if (cmds == NULL)
		return (sh->exit_status);
	if (prepare_heredocs(cmds, sh) == FAILURE)
		return (1);
	if (cmds->next == NULL && is_parent_builtin(cmds))
	{
		if (cmds->redirs == NULL)
			return (exec_parent_builtin(cmds, sh));
		return (exec_parent_builtin_with_redir(cmds, sh));
	}
	return (exec_pipeline(cmds, sh));
}
