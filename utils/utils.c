/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohassaf <mohassaf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/31 15:06:42 by mohassaf          #+#    #+#             */
/*   Updated: 2026/08/13 17:02:00 by mohassaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header/minishell.h"

void	free_tab(char **tab)
{
	int	i;

	if (tab == NULL)
		return ;
	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

void	cleanup_shell(t_shell *sh)
{
	if (sh == NULL)
		return ;
	rl_clear_history();
	free_tab(sh->env);
	sh->env = NULL;
}

void	free_cmds(t_cmd *cmds)
{
	t_cmd	*tmp;

	while (cmds)
	{
		tmp = cmds->next;
		free_tab(cmds->args);
		free_redirs(cmds->redirs);
		free(cmds);
		cmds = tmp;
	}
}

void	free_redirs(t_redir *redirs)
{
	t_redir	*tmp;

	while (redirs)
	{
		tmp = redirs->next;
		if (redirs->fd >= 0)
			close(redirs->fd);
		free(redirs->file);
		free(redirs);
		redirs = tmp;
	}
}
