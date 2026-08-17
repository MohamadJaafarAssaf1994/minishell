/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohassaf <mohassaf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/11 19:09:04 by mohassaf          #+#    #+#             */
/*   Updated: 2026/08/12 11:32:53 by mohassaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header/minishell.h"

int	has_quotes(char *word)
{
	int	i;

	i = 0;
	while (word && word[i])
	{
		if (is_quote(word[i]))
			return (1);
		i++;
	}
	return (0);
}

static void	remove_arg(char **args, int index)
{
	free(args[index]);
	while (args[index])
	{
		args[index] = args[index + 1];
		index++;
	}
}

static int	expand_redirs(t_redir *redirs, t_shell *sh)
{
	int		allow_vars;
	char	*expanded;

	while (redirs)
	{
		allow_vars = (redirs->type != HEREDOC);
		expanded = expand_word(redirs->file, sh, allow_vars);
		if (expanded == NULL)
			return (FAILURE);
		free(redirs->file);
		redirs->file = expanded;
		redirs = redirs->next;
	}
	return (SUCCESS);
}

static int	expand_args(char **args, t_shell *sh)
{
	int		i;
	char	*expanded;
	int		quoted;

	i = 0;
	while (args && args[i])
	{
		quoted = has_quotes(args[i]);
		expanded = expand_word(args[i], sh, 1);
		if (expanded == NULL)
			return (FAILURE);
		free(args[i]);
		args[i] = expanded;
		if (args[i][0] == '\0' && !quoted)
			remove_arg(args, i);
		else
			i++;
	}
	return (SUCCESS);
}

int	expand_commands(t_cmd *cmds, t_shell *sh)
{
	while (cmds)
	{
		if (expand_args(cmds->args, sh) == FAILURE)
			return (FAILURE);
		if (expand_redirs(cmds->redirs, sh) == FAILURE)
			return (FAILURE);
		cmds = cmds->next;
	}
	return (SUCCESS);
}
