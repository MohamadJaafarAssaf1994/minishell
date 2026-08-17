/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_copy.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohassaf <mohassaf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/11 19:08:12 by mohassaf          #+#    #+#             */
/*   Updated: 2026/08/11 19:08:15 by mohassaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header/minishell.h"

static int	copy_status(t_expand *ex)
{
	char	*status;
	int		k;

	status = ft_itoa(ex->sh->exit_status);
	if (status == NULL)
		return (FAILURE);
	k = 0;
	while (status[k])
		ex->dst[ex->j++] = status[k++];
	free(status);
	ex->i += 2;
	return (SUCCESS);
}

int	copy_variable(t_expand *ex)
{
	char	*value;
	int		start;
	int		k;

	if (ex->src[ex->i + 1] == '?')
		return (copy_status(ex));
	if (!is_name_start(ex->src[ex->i + 1]))
		return (ex->dst[ex->j++] = ex->src[ex->i++], SUCCESS);
	start = ex->i + 1;
	ex->i = start;
	while (is_name_char(ex->src[ex->i]))
		ex->i++;
	value = env_value_span(ex->sh->env, ex->src, start, ex->i - start);
	k = 0;
	while (value && value[k])
		ex->dst[ex->j++] = value[k++];
	return (SUCCESS);
}

int	copy_expanded(char *dst, char *word, t_shell *sh, int allow_vars)
{
	t_expand	ex;
	char		quote;

	init_expand(&ex, word, dst, sh);
	quote = 0;
	while (ex.src[ex.i])
	{
		if (is_quote(ex.src[ex.i]) && (!quote || quote == ex.src[ex.i]))
			quote = (quote == 0) * ex.src[ex.i++];
		else if (allow_vars && ex.src[ex.i] == '$' && quote != '\'')
		{
			if (copy_variable(&ex) == FAILURE)
				return (FAILURE);
		}
		else
			ex.dst[ex.j++] = ex.src[ex.i++];
	}
	ex.dst[ex.j] = '\0';
	return (SUCCESS);
}

char	*expand_word(char *word, t_shell *sh, int allow_vars)
{
	char	*expanded;
	int		len;

	len = expanded_len(word, sh, allow_vars);
	if (len < 0)
		return (NULL);
	expanded = malloc(sizeof(char) * (len + 1));
	if (expanded == NULL)
		return (NULL);
	if (copy_expanded(expanded, word, sh, allow_vars) == FAILURE)
		return (free(expanded), NULL);
	return (expanded);
}
