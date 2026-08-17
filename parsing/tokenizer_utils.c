/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohassaf <mohassaf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/11 19:09:36 by mohassaf          #+#    #+#             */
/*   Updated: 2026/08/11 19:09:39 by mohassaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header/minishell.h"

int	is_blank(char c)
{
	return (c == ' ' || c == '\t');
}

int	is_operator(char c)
{
	return (c == '|' || c == '<' || c == '>');
}

int	operator_len(char *line, int i)
{
	if ((line[i] == '<' || line[i] == '>') && line[i + 1] == line[i])
		return (2);
	return (1);
}

int	word_end(char *line, int start)
{
	int		i;
	char	quote;

	i = start;
	quote = 0;
	while (line[i])
	{
		if (!quote && (line[i] == '\'' || line[i] == '"'))
			quote = line[i];
		else if (quote && line[i] == quote)
			quote = 0;
		else if (!quote && (is_blank(line[i]) || is_operator(line[i])))
			break ;
		i++;
	}
	if (quote)
		return (-1);
	return (i);
}

int	next_token_end(char *line, int i)
{
	if (is_operator(line[i]))
		return (i + operator_len(line, i));
	return (word_end(line, i));
}
