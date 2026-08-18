/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hammeah <hammeah@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/31 19:41:00 by mohassaf          #+#    #+#             */
/*   Updated: 2026/07/03 00:43:12 by hammeah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header/minishell.h"

static int	open_redirection(t_redir *redir)
{
	if (redir->type == REDIR_IN)
		return (open(redir->file, O_RDONLY));
	if (redir->type == REDIR_OUT)
		return (open(redir->file, O_WRONLY | O_CREAT | O_TRUNC, 0644));
	if (redir->type == REDIR_APPEND)
		return (open(redir->file, O_WRONLY | O_CREAT | O_APPEND, 0644));
	if (redir->type == HEREDOC)
		return (redir->fd);
	return (-1);
}

static int	dup_redirection(t_redir *redir, int fd)
{
	if ((redir->type == REDIR_IN || redir->type == HEREDOC) && dup2(fd,
			STDIN_FILENO) == -1)
		return (FAILURE);
	if ((redir->type == REDIR_OUT || redir->type == REDIR_APPEND) && dup2(fd,
			STDOUT_FILENO) == -1)
		return (FAILURE);
	return (SUCCESS);
}

int	apply_redirections(t_cmd *cmd)
{
	t_redir	*redir;
	int		fd;

	if (cmd == NULL)
		return (FAILURE);
	redir = cmd->redirs;
	while (redir)
	{
		fd = open_redirection(redir);
		if (fd == -1)
			return (perror(redir->file), FAILURE);
		if (dup_redirection(redir, fd) == FAILURE)
			return (perror("dup2"), close(fd), FAILURE);
		close(fd);
		if (redir->type == HEREDOC)
			redir->fd = -1;
		redir = redir->next;
	}
	return (SUCCESS);
}
