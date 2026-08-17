/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parent_builtin_redirs.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hammeah <hammeah@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/31 20:58:22 by mohassaf          #+#    #+#             */
/*   Updated: 2026/07/03 00:42:13 by hammeah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header/minishell.h"

int	exec_parent_builtin_with_redir(t_cmd *cmd, t_shell *sh)
{
	int	save_stdin;
	int	save_stdout;
	int	status;

	save_stdin = dup(STDIN_FILENO);
	save_stdout = dup(STDOUT_FILENO);
	if (save_stdin == -1 || save_stdout == -1)
		return (perror("dup"), 1);
	if (apply_redirections(cmd) == FAILURE)
	{
		close(save_stdin);
		close(save_stdout);
		return (1);
	}
	status = exec_parent_builtin(cmd, sh);
	if (dup2(save_stdin, STDIN_FILENO) == -1)
		perror("dup2");
	if (dup2(save_stdout, STDOUT_FILENO) == -1)
		perror("dup2");
	close(save_stdin);
	close(save_stdout);
	return (status);
}
