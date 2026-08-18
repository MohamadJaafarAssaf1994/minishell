/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohassaf <mohassaf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/17 12:24:05 by mohassaf          #+#    #+#             */
/*   Updated: 2026/08/17 12:27:18 by mohassaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header/minishell.h"

int	fill_heredoc_pipe(int pipe_fd[2], t_redir *redir, t_shell *sh, t_cmd *cmds)
{
	pid_t	pid;
	int		status;

	if (redir == NULL || redir->file == NULL)
		return (FAILURE);
	pid = fork();
	if (pid < 0)
		return (FAILURE);
	if (pid == 0)
		heredoc_child_loop(pipe_fd, redir, sh, cmds);
	waitpid(pid, &status, 0);
	if (WIFSIGNALED(status))
	{
		g_signal = WTERMSIG(status);
		write(1, "\n", 1);
		return (FAILURE);
	}
	if (WIFEXITED(status) && WEXITSTATUS(status) == 130)
	{
		g_signal = SIGINT;
		return (FAILURE);
	}
	if (WIFEXITED(status) && WEXITSTATUS(status) != SUCCESS)
		return (FAILURE);
	return (SUCCESS);
}

int	prepare_one_heredoc(t_redir *redir, t_shell *sh, t_cmd *cmds)
{
	int	pipe_fd[2];

	(void)sh;
	if (redir == NULL || redir->file == NULL)
		return (FAILURE);
	if (pipe(pipe_fd) < 0)
		return (FAILURE);
	if (fill_heredoc_pipe(pipe_fd, redir, sh, cmds) == FAILURE)
	{
		close_pipe(pipe_fd);
		return (FAILURE);
	}
	close(pipe_fd[1]);
	redir->fd = pipe_fd[0];
	return (SUCCESS);
}

void	close_other_heredocs(t_cmd *cmds, t_cmd *skip)
{
	t_cmd	*cmd;
	t_redir	*redir;

	cmd = cmds;
	while (cmd)
	{
		if (cmd != skip)
		{
			redir = cmd->redirs;
			while (redir)
			{
				if (redir->type == HEREDOC && redir->fd >= 0)
				{
					close(redir->fd);
					redir->fd = -1;
				}
				redir = redir->next;
			}
		}
		cmd = cmd->next;
	}
}

int	prepare_heredocs(t_cmd *cmds, t_shell *sh)
{
	t_cmd	*tmp_cmd;
	t_redir	*tmp_redir;

	if (cmds == NULL)
		return (SUCCESS);
	tmp_cmd = cmds;
	while (tmp_cmd)
	{
		tmp_redir = tmp_cmd->redirs;
		while (tmp_redir)
		{
			if (tmp_redir->type == HEREDOC)
			{
				if (prepare_one_heredoc(tmp_redir, sh, cmds) == FAILURE)
				{
					close_other_heredocs(cmds, NULL);
					return (FAILURE);
				}
			}
			tmp_redir = tmp_redir->next;
		}
		tmp_cmd = tmp_cmd->next;
	}
	return (SUCCESS);
}
