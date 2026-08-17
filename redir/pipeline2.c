/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohassaf <mohassaf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/13 12:17:18 by hammeah           #+#    #+#             */
/*   Updated: 2026/08/17 12:27:05 by mohassaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header/minishell.h"

static void	close_child_fds(t_cmd *cmd)
{
	t_redir	*redir;
	int		close_stdin;
	int		close_stdout;

	close_stdin = 0;
	close_stdout = 0;
	if (cmd->prev_fd != -1)
		close_stdin = 1;
	if (cmd->next != NULL)
		close_stdout = 1;
	redir = cmd->redirs;
	while (redir)
	{
		if (redir->type == REDIR_IN || redir->type == HEREDOC)
			close_stdin = 1;
		if (redir->type == REDIR_OUT || redir->type == REDIR_APPEND)
			close_stdout = 1;
		redir = redir->next;
	}
	if (close_stdin)
		close(STDIN_FILENO);
	if (close_stdout)
		close(STDOUT_FILENO);
}

static void	child_exit(t_cmd *cmd, t_cmd *cmds, t_shell *sh, int status)
{
	close_child_fds(cmd);
	free_cmds(cmds);
	cleanup_shell(sh);
	exit(status);
}

static void	command_not_found(t_cmd *cmd, t_cmd *cmds, t_shell *sh)
{
	write(2, "minishell: ", 11);
	write(2, cmd->args[0], ft_strlen(cmd->args[0]));
	write(2, ": command not found\n", 20);
	child_exit(cmd, cmds, sh, 127);
}

static void	exec_external(t_cmd *cmd, t_cmd *cmds, t_shell *sh)
{
	char		*path;
	int			status;
	struct stat	st;

	path = get_cmd_path(cmd->args[0], sh->env);
	if (path == NULL)
		command_not_found(cmd, cmds, sh);
	if (stat(path, &st) == 0 && S_ISDIR(st.st_mode))
	{
		write(2, "minishell: ", 11);
		write(2, cmd->args[0], ft_strlen(cmd->args[0]));
		write(2, ": Is a directory\n", 17);
		free(path);
		child_exit(cmd, cmds, sh, 126);
	}
	execve(path, cmd->args, sh->env);
	status = errno;
	if (status == ENOEXEC)
		exec_shell_script(path, cmd->args, sh->env);
	write(2, "minishell: ", 11);
	perror(cmd->args[0]);
	free(path);
	if (status == ENOENT)
		child_exit(cmd, cmds, sh, 127);
	child_exit(cmd, cmds, sh, 126);
}

void	exec_child(t_cmd *cmd, t_cmd *cmds, t_shell *sh)
{
	int	status;

	if (cmd == NULL)
		exit(0);
	setup_signals_child();
	close_other_heredocs(cmds, cmd);
	if (apply_redirections(cmd) == FAILURE)
		child_exit(cmd, cmds, sh, 1);
	if (cmd->args == NULL || cmd->args[0] == NULL)
		child_exit(cmd, cmds, sh, 0);
	if (is_builtin(cmd))
	{
		status = exec_builtin(cmd, sh);
		child_exit(cmd, cmds, sh, status);
	}
	exec_external(cmd, cmds, sh);
}
