/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_len.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohassaf <mohassaf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/11 19:08:43 by mohassaf          #+#    #+#             */
/*   Updated: 2026/08/11 19:08:48 by mohassaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header/minishell.h"

static int	status_len(int *i, t_shell *sh)
{
	char	*status;
	int		len;

	status = ft_itoa(sh->exit_status);
	if (status == NULL)
		return (-1);
	len = ft_strlen(status);
	free(status);
	*i += 2;
	return (len);
}

int	variable_len(char *word, int *i, t_shell *sh)
{
	char	*value;
	int		start;

	if (word[*i + 1] == '?')
		return (status_len(i, sh));
	if (!is_name_start(word[*i + 1]))
		return ((*i)++, 1);
	start = *i + 1;
	*i = start;
	while (is_name_char(word[*i]))
		(*i)++;
	value = env_value_span(sh->env, word, start, *i - start);
	if (value == NULL)
		return (0);
	return (ft_strlen(value));
}

static int	add_var_len(char *word, int *i, t_shell *sh, int *len)
{
	int	add;

	add = variable_len(word, i, sh);
	if (add < 0)
		return (FAILURE);
	*len += add;
	return (SUCCESS);
}

int	expanded_len(char *word, t_shell *sh, int allow_vars)
{
	int		i;
	int		len;
	char	quote;

	i = 0;
	len = 0;
	quote = 0;
	while (word[i])
	{
		if (is_quote(word[i]) && (!quote || quote == word[i]))
			quote = (quote == 0) * word[i++];
		else if (allow_vars && word[i] == '$' && quote != '\'')
		{
			if (add_var_len(word, &i, sh, &len) == FAILURE)
				return (-1);
		}
		else
			len += (i++, 1);
	}
	return (len);
}

int	heredoc_len(char *line, t_shell *sh)
{
	int	i;
	int	len;
	int	add;

	i = 0;
	len = 0;
	while (line[i])
	{
		if (line[i] == '$')
		{
			add = variable_len(line, &i, sh);
			if (add < 0)
				return (-1);
			len += add;
		}
		else
			len += (i++, 1);
	}
	return (len);
}
