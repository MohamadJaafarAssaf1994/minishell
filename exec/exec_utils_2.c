/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hammeah <hammeah@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/31 21:12:45 by mohassaf          #+#    #+#             */
/*   Updated: 2026/08/13 12:01:51 by hammeah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header/minishell.h"

void	close_pipe(int pipe_fd[2])
{
	close(pipe_fd[0]);
	close(pipe_fd[1]);
}

int	create_pipe_if_needed(t_cmd *cmd, int pipe_fd[2])
{
	if (cmd->next == NULL)
	{
		pipe_fd[0] = -1;
		pipe_fd[1] = -1;
		return (SUCCESS);
	}
	if (pipe(pipe_fd) == -1)
	{
		perror("pipe");
		return (FAILURE);
	}
	return (SUCCESS);
}

void	setup_child_pipes(int prev_fd, int pipe_fd[2], t_cmd *cmd)
{
	if (prev_fd != -1)
	{
		if (dup2(prev_fd, STDIN_FILENO) == -1)
			exit(1);
		close(prev_fd);
	}
	if (cmd->next != NULL)
	{
		close(pipe_fd[0]);
		if (dup2(pipe_fd[1], STDOUT_FILENO) == -1)
			exit(1);
		close(pipe_fd[1]);
	}
}

pid_t	fork_pipeline_child(t_cmd *cmd, t_cmd *cmds, t_shell *sh, int pp_fd[2])
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		return (perror("fork"), -1);
	if (pid == 0)
	{
		setup_child_pipes(cmd->prev_fd, pp_fd, cmd);
		exec_child(cmd, cmds, sh);
	}
	return (pid);
}
