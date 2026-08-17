/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tmp_parse_suite.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hammeah <hammeah@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/02 22:46:33 by hammeah           #+#    #+#             */
/*   Updated: 2026/07/03 15:52:07 by hammeah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header/minishell.h"

static int	count_args_until_pipe(char **tokens, int start)
{
	int	count;
	int	i;

	count = 0;
	i = start;
	while (tokens[i] && !is_pipe_token(tokens[i]))
	{
		if (is_redir_token(tokens[i]))
		{
			if (tokens[i + 1])
				i += 2;
			else
				i++;
		}
		else
		{
			count++;
			i++;
		}
	}
	return (count);
}

static int	fill_cmd_next(t_cmd *cmd, char **tokens, int *i, int *j)
{
	cmd->args[*j] = ft_strdup(tokens[(*i)]);
	if (cmd->args[*j] == NULL)
		return (FAILURE);
	(*j)++;
	(*i)++;
	return (SUCCESS);
}

static int	fill_cmd_until_pipe(t_cmd *cmd, char **tokens, int *i)
{
	int		j;
	t_redir	*redir;

	j = 0;
	while (tokens[*i] && !is_pipe_token(tokens[*i]))
	{
		if (is_redir_token(tokens[*i]))
		{
			if (tokens[*i + 1] == NULL)
				return (FAILURE);
			redir = create_redir(get_redir_type(tokens[*i]), tokens[*i + 1]);
			if (redir == NULL)
				return (FAILURE);
			add_redir_back(&cmd->redirs, redir);
			*i += 2;
		}
		else
		{
			if (fill_cmd_next(cmd, tokens, i, &j) == FAILURE)
				return (FAILURE);
		}
	}
	cmd->args[j] = NULL;
	return (SUCCESS);
}

t_cmd	*create_cmd_from_tokens(char **tokens, int *i)
{
	t_cmd	*cmd;
	int		arg_count;
	int		j;

	cmd = malloc(sizeof(t_cmd));
	if (cmd == NULL)
		return (NULL);
	cmd->redirs = NULL;
	cmd->next = NULL;
	arg_count = count_args_until_pipe(tokens, *i);
	cmd->args = malloc(sizeof(char *) * (arg_count + 1));
	if (cmd->args == NULL)
		return (free(cmd), NULL);
	j = 0;
	while (j <= arg_count)
		cmd->args[j++] = NULL;
	if (fill_cmd_until_pipe(cmd, tokens, i) == FAILURE)
		return (free_cmds(cmd), NULL);
	return (cmd);
}

void	add_cmd_back(t_cmd **cmds, t_cmd *new_cmd)
{
	t_cmd	*tmp;

	if (cmds == NULL || new_cmd == NULL)
		return ;
	if (*cmds == NULL)
	{
		*cmds = new_cmd;
		return ;
	}
	tmp = *cmds;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new_cmd;
}
