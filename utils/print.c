/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hammeah <hammeah@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/31 20:31:20 by mohassaf          #+#    #+#             */
/*   Updated: 2026/07/03 15:09:21 by hammeah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header/minishell.h"

static	void	print_redir_type(t_redir_type type)
{
	if (type == REDIR_IN)
		printf("REDIR_IN (<)");
	else if (type == REDIR_OUT)
		printf("REDIR_OUT (>)");
	else if (type == REDIR_APPEND)
		printf("REDIR_APPEND (>>)");
	else if (type == HEREDOC)
		printf("HEREDOC (<<)");
	else
		printf("UNKNOWN");
}

static	void	print_redirs(t_redir *redirs)
{
	int	i;

	i = 0;
	if (redirs == NULL)
	{
		printf("  redirs: NULL\n");
		return ;
	}
	printf("  redirs:\n");
	while (redirs)
	{
		printf("    redir[%d]\n", i);
		printf("      type: ");
		print_redir_type(redirs->type);
		printf("\n");
		printf("      file: %s\n", redirs->file);
		redirs = redirs->next;
		i++;
	}
}

static	void	print_args(char **args)
{
	int	i;

	i = 0;
	if (args == NULL)
	{
		printf("  args: NULL\n");
		return ;
	}
	printf("  args:\n");
	while (args[i])
	{
		printf("    args[%d] = [%s]\n", i, args[i]);
		i++;
	}
	printf("    args[%d] = NULL\n", i);
}

void	print_cmds(t_cmd *cmds)
{
	int	i;

	i = 0;
	if (cmds == NULL)
	{
		printf("cmds: NULL\n");
		return ;
	}
	while (cmds)
	{
		printf("========== CMD %d ==========\n", i);
		print_args(cmds->args);
		print_redirs(cmds->redirs);
		cmds = cmds->next;
		i++;
	}
	printf("===========================\n");
}
