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

static int	is_append_assignment(char *arg)
{
	int	i;

	i = 0;
	while (arg[i] && arg[i] != '=')
	{
		if (arg[i] == '+' && arg[i + 1] == '=')
			return (1);
		i++;
	}
	return (0);
}

static char	*export_arg_to_env_line(char *arg)
{
	char	*plus;
	char	*key;
	char	*line;

	if (is_append_assignment(arg) == 0)
		return (ft_strdup(arg));
	plus = ft_strchr(arg, '+');
	key = ft_substr(arg, 0, plus - arg);
	if (key == NULL)
		return (NULL);
	line = ft_strjoin(key, plus + 1);
	free(key);
	return (line);
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
	new_env[size] = export_arg_to_env_line(arg);
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
	if (is_append_assignment(arg))
		new_line = ft_strjoin(sh->env[index], ft_strchr(arg, '=') + 1);
	else
		new_line = ft_strdup(arg);
	if (new_line == NULL)
		return (FAILURE);
	free(sh->env[index]);
	sh->env[index] = new_line;
	return (SUCCESS);
}
