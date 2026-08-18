/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_parse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohassaf <mohassaf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/11 19:09:22 by mohassaf          #+#    #+#             */
/*   Updated: 2026/08/11 19:09:24 by mohassaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header/minishell.h"

static int	invalid_syntax(char **tokens)
{
	int	i;

	if (tokens[0] && is_pipe_token(tokens[0]))
		return (1);
	i = 0;
	while (tokens[i])
	{
		if (is_pipe_token(tokens[i]))
		{
			if (tokens[i + 1] == NULL || is_pipe_token(tokens[i + 1]))
				return (1);
		}
		else if (is_redir_token(tokens[i]))
		{
			if (tokens[i + 1] == NULL || is_pipe_token(tokens[i + 1])
				|| is_redir_token(tokens[i + 1]))
				return (1);
			i++;
		}
		i++;
	}
	return (0);
}

static t_cmd	*parse_tokens(char **tokens)
{
	t_cmd	*cmds;
	t_cmd	*new_cmd;
	int		i;

	cmds = NULL;
	i = 0;
	while (tokens[i])
	{
		new_cmd = create_cmd_from_tokens(tokens, &i);
		if (new_cmd == NULL)
			return (free_cmds(cmds), NULL);
		add_cmd_back(&cmds, new_cmd);
		if (tokens[i] && is_pipe_token(tokens[i]))
			i++;
	}
	return (cmds);
}

static int	check_tokens(char **tokens, int *status)
{
	if (tokens[0] == NULL)
		return (SUCCESS);
	if (invalid_syntax(tokens))
	{
		write(2, "minishell: syntax error near unexpected token\n", 46);
		*status = 2;
		return (FAILURE);
	}
	return (SUCCESS);
}

t_cmd	*parse_line(char *line, int *status)
{
	t_cmd	*cmds;
	char	**tokens;

	if (line == NULL || line[0] == '\0')
		return (NULL);
	tokens = shell_tokenize(line);
	if (tokens == NULL)
	{
		write(2, "minishell: syntax error: unclosed quote\n", 40);
		*status = 2;
		return (NULL);
	}
	if (check_tokens(tokens, status) == FAILURE || tokens[0] == NULL)
		return (free_tab(tokens), NULL);
	cmds = parse_tokens(tokens);
	free_tab(tokens);
	return (cmds);
}
