/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hammeah <hammeah@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/30 20:35:37 by mohassaf          #+#    #+#             */
/*   Updated: 2026/07/03 00:42:00 by hammeah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header/minishell.h"

static int	remove_env_var(t_shell *sh, int index)
{
	int	i;

	if (sh == NULL || sh->env == NULL || index < 0)
		return (FAILURE);
	if (sh->env[index] == NULL)
		return (FAILURE);
	free(sh->env[index]);
	i = index;
	while (sh->env[i + 1])
	{
		sh->env[i] = sh->env[i + 1];
		i++;
	}
	sh->env[i] = NULL;
	return (SUCCESS);
}

int	builtin_unset(t_cmd *cmds, t_shell *sh)
{
	int	i;
	int	index;
	int	status;

	i = 0;
	status = 0;
	if (cmds->args[1] == NULL)
		return (0);
	while (cmds->args[++i])
	{
		if (is_valid_identifier(cmds->args[i]) == 0 || ft_strchr(cmds->args[i],
				'='))
		{
			write(2, "minishell: unset: not a valid identifier\n", 41);
			status = 1;
		}
		else
		{
			index = get_env_index(sh->env, cmds->args[i]);
			if (index >= 0)
				remove_env_var(sh, index);
		}
	}
	return (status);
}
