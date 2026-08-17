/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohassaf <mohassaf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/11 19:08:55 by mohassaf          #+#    #+#             */
/*   Updated: 2026/08/11 19:08:57 by mohassaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header/minishell.h"

int	is_quote(char c)
{
	return (c == '\'' || c == '"');
}

int	is_name_start(char c)
{
	return (c == '_' || ft_isalpha(c));
}

int	is_name_char(char c)
{
	return (c == '_' || ft_isalnum(c));
}

char	*env_value_span(char **env, char *word, int start, int len)
{
	int	i;

	i = 0;
	while (env && env[i])
	{
		if (ft_strncmp(env[i], word + start, len) == 0 && env[i][len] == '=')
			return (env[i] + len + 1);
		i++;
	}
	return (NULL);
}

void	init_expand(t_expand *ex, char *src, char *dst, t_shell *sh)
{
	ex->src = src;
	ex->dst = dst;
	ex->i = 0;
	ex->j = 0;
	ex->sh = sh;
}
