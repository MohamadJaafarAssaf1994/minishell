/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_heredoc.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohassaf <mohassaf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/11 19:08:29 by mohassaf          #+#    #+#             */
/*   Updated: 2026/08/11 19:08:34 by mohassaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header/minishell.h"

static int	copy_heredoc_expanded(t_expand *ex)
{
	while (ex->src[ex->i])
	{
		if (ex->src[ex->i] == '$')
		{
			if (copy_variable(ex) == FAILURE)
				return (FAILURE);
		}
		else
			ex->dst[ex->j++] = ex->src[ex->i++];
	}
	ex->dst[ex->j] = '\0';
	return (SUCCESS);
}

char	*expand_heredoc_line(char *line, t_shell *sh)
{
	t_expand	ex;
	char		*expanded;
	int			len;

	len = heredoc_len(line, sh);
	if (len < 0)
		return (NULL);
	expanded = malloc(sizeof(char) * (len + 1));
	if (expanded == NULL)
		return (NULL);
	init_expand(&ex, line, expanded, sh);
	if (copy_heredoc_expanded(&ex) == FAILURE)
		return (free(expanded), NULL);
	return (expanded);
}
