/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohassaf <mohassaf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/11 19:09:46 by mohassaf          #+#    #+#             */
/*   Updated: 2026/08/11 19:09:48 by mohassaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header/minishell.h"

static int	count_tokens(char *line)
{
	int	i;
	int	end;
	int	count;

	i = 0;
	count = 0;
	while (line[i])
	{
		while (line[i] && is_blank(line[i]))
			i++;
		if (!line[i])
			break ;
		end = next_token_end(line, i);
		if (end == -1)
			return (-1);
		i = end;
		count++;
	}
	return (count);
}

static int	add_token(char **tokens, char *line, int *i, int j)
{
	int	end;

	end = next_token_end(line, *i);
	if (end == -1)
		return (FAILURE);
	tokens[j] = ft_substr(line, *i, end - *i);
	if (tokens[j] == NULL)
		return (FAILURE);
	*i = end;
	return (SUCCESS);
}

static int	fill_tokens(char **tokens, char *line)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (line[i])
	{
		while (line[i] && is_blank(line[i]))
			i++;
		if (!line[i])
			break ;
		if (add_token(tokens, line, &i, j) == FAILURE)
			return (FAILURE);
		j++;
	}
	return (SUCCESS);
}

char	**shell_tokenize(char *line)
{
	char	**tokens;
	int		count;

	count = count_tokens(line);
	if (count < 0)
		return (NULL);
	tokens = ft_calloc(count + 1, sizeof(char *));
	if (tokens == NULL)
		return (NULL);
	if (fill_tokens(tokens, line) == FAILURE)
	{
		free_tab(tokens);
		return (NULL);
	}
	return (tokens);
}
