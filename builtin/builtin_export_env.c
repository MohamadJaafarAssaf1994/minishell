/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export_env.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohassaf <mohassaf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/11 15:29:35 by mohassaf          #+#    #+#             */
/*   Updated: 2026/08/11 15:30:47 by mohassaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header/minishell.h"

static void	copy_env_ptrs(char **new_env, char **old_env)
{
	int	i;

	i = 0;
	while (old_env[i])
	{
		new_env[i] = old_env[i];
		i++;
	}
}

int	add_env_var(t_shell *sh, char *arg)
{
	char	**new_env;
	int		size;

	if (sh == NULL || sh->env == NULL || arg == NULL)
		return (FAILURE);
	size = env_size(sh->env);
	new_env = malloc(sizeof(char *) * (size + 2));
	if (new_env == NULL)
		return (FAILURE);
	copy_env_ptrs(new_env, sh->env);
	new_env[size] = ft_strdup(arg);
	if (new_env[size] == NULL)
	{
		free(new_env);
		return (FAILURE);
	}
	new_env[size + 1] = NULL;
	free(sh->env);
	sh->env = new_env;
	return (SUCCESS);
}

int	replace_env_var(t_shell *sh, int index, char *arg)
{
	char	*new_line;

	if (sh == NULL || sh->env == NULL || arg == NULL)
		return (FAILURE);
	new_line = ft_strdup(arg);
	if (new_line == NULL)
		return (FAILURE);
	free(sh->env[index]);
	sh->env[index] = new_line;
	return (SUCCESS);
}
