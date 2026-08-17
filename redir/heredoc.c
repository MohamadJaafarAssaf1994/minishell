/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohassaf <mohassaf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/11 19:07:49 by mohassaf          #+#    #+#             */
/*   Updated: 2026/08/17 12:28:31 by mohassaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header/minishell.h"

static int	write_heredoc_line(int fd, char *line, t_shell *sh, int expand)
{
	char	*expanded;

	if (!expand)
	{
		ft_putendl_fd(line, fd);
		return (SUCCESS);
	}
	expanded = expand_heredoc_line(line, sh);
	if (expanded == NULL)
		return (FAILURE);
	ft_putendl_fd(expanded, fd);
	free(expanded);
	return (SUCCESS);
}

static void	handle_sigint_heredoc(int sig)
{
	g_signal = sig;
	write(STDOUT_FILENO, "\n", 1);
	close(STDIN_FILENO);
}

static void	heredoc_child_exit(int pipe_fd[2], t_cmd *cmds, t_shell *sh,
		int status)
{
	close(pipe_fd[1]);
	free_cmds(cmds);
	cleanup_shell(sh);
	exit(status);
}

static int	process_heredoc_line(int fd, char *line, t_redir *redir,
		t_shell *sh)
{
	if (ft_strncmp(redir->file, line, ft_strlen(redir->file) + 1) == 0)
		return (1);
	if (write_heredoc_line(fd, line, sh, redir->heredoc_expand) == FAILURE)
		return (-1);
	return (0);
}

void	heredoc_child_loop(int pipe_fd[2], t_redir *redir, t_shell *sh,
		t_cmd *cmds)
{
	char	*line;
	int		status;

	status = 0;
	close(pipe_fd[0]);
	close_other_heredocs(cmds, NULL);
	g_signal = 0;
	signal(SIGINT, handle_sigint_heredoc);
	signal(SIGQUIT, SIG_IGN);
	while (1)
	{
		line = readline("> ");
		if (g_signal == SIGINT)
			return (free(line), heredoc_child_exit(pipe_fd, cmds, sh, 130));
		if (line == NULL)
			break ;
		status = process_heredoc_line(pipe_fd[1], line, redir, sh);
		free(line);
		if (status != 0)
			break ;
	}
	if (status < 0)
		heredoc_child_exit(pipe_fd, cmds, sh, FAILURE);
	heredoc_child_exit(pipe_fd, cmds, sh, SUCCESS);
}
