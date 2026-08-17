/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohassaf <mohassaf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/11 19:07:05 by mohassaf          #+#    #+#             */
/*   Updated: 2026/08/13 13:55:05 by mohassaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header/minishell.h"

static void	advance_pipe(t_cmd *cmd, int pipe_fd[2], int *prev_fd)
{
	if (*prev_fd != -1)
		close(*prev_fd);
	if (cmd->next != NULL)
	{
		close(pipe_fd[1]);
		*prev_fd = pipe_fd[0];
	}
	else
		*prev_fd = -1;
}

int	exec_pipeline(t_cmd *cmds, t_shell *sh)
{
	t_cmd	*cmd;
	pid_t	last_pid;
	int		pipe_fd[2];
	int		status;
	int		prev_fd;

	cmd = cmds;
	last_pid = -1;
	prev_fd = -1;
	while (cmd)
	{
		cmd->prev_fd = prev_fd;
		if (create_pipe_if_needed(cmd, pipe_fd) == FAILURE)
			return (1);
		last_pid = fork_pipeline_child(cmd, cmds, sh, pipe_fd);
		if (last_pid == -1)
			return (1);
		advance_pipe(cmd, pipe_fd, &prev_fd);
		cmd = cmd->next;
	}
	waitpid(last_pid, &status, 0);
	while (wait(NULL) > 0)
		;
	return (get_exit_status(status));
}
