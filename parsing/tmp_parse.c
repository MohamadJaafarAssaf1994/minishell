/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tmp_parse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohassaf <mohassaf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/01 17:23:31 by mohassaf          #+#    #+#             */
/*   Updated: 2026/08/12 11:32:24 by mohassaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header/minishell.h"

int	is_pipe_token(char *s)
{
	if (s == NULL)
		return (0);
	if (ft_strncmp(s, "|", 2) == 0)
		return (1);
	return (0);
}

int	is_redir_token(char *s)
{
	if (s == NULL)
		return (0);
	if (ft_strncmp(s, "<<", 3) == 0)
		return (1);
	if (ft_strncmp(s, ">>", 3) == 0)
		return (1);
	if (ft_strncmp(s, "<", 2) == 0)
		return (1);
	if (ft_strncmp(s, ">", 2) == 0)
		return (1);
	return (0);
}

t_redir_type	get_redir_type(char *s)
{
	if (ft_strncmp(s, "<<", 3) == 0)
		return (HEREDOC);
	if (ft_strncmp(s, ">>", 3) == 0)
		return (REDIR_APPEND);
	if (ft_strncmp(s, "<", 2) == 0)
		return (REDIR_IN);
	return (REDIR_OUT);
}

t_redir	*create_redir(t_redir_type type, char *file)
{
	t_redir	*redir;

	if (file == NULL)
		return (NULL);
	redir = malloc(sizeof(t_redir));
	if (redir == NULL)
		return (NULL);
	redir->type = type;
	redir->file = ft_strdup(file);
	if (redir->file == NULL)
	{
		free(redir);
		return (NULL);
	}
	redir->fd = -1;
	if (type == HEREDOC)
		redir->heredoc_expand = !has_quotes(file);
	else
		redir->heredoc_expand = 0;
	redir->next = NULL;
	return (redir);
}

void	add_redir_back(t_redir **redirs, t_redir *new_redir)
{
	t_redir	*tmp;

	if (redirs == NULL || new_redir == NULL)
		return ;
	if (*redirs == NULL)
	{
		*redirs = new_redir;
		return ;
	}
	tmp = *redirs;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new_redir;
}
