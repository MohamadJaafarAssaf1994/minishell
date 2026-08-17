/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohassaf <mohassaf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/30 20:35:37 by mohassaf          #+#    #+#             */
/*   Updated: 2026/08/11 19:10:30 by mohassaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header/minishell.h"

static void	sort_env_ptrs(char **env, int size)
{
	char	*tmp;
	int		i;
	int		j;

	i = 0;
	while (i < size - 1)
	{
		j = 0;
		while (j < size - i - 1)
		{
			if (ft_strncmp(env[j], env[j + 1], ft_strlen(env[j]) + 1) > 0)
			{
				tmp = env[j];
				env[j] = env[j + 1];
				env[j + 1] = tmp;
			}
			j++;
		}
		i++;
	}
}

static void	print_export_line(char *line)
{
	char	*equal;

	equal = ft_strchr(line, '=');
	write(1, "declare -x ", 11);
	if (equal == NULL)
	{
		write(1, line, ft_strlen(line));
		write(1, "\n", 1);
		return ;
	}
	write(1, line, equal - line);
	write(1, "=\"", 2);
	write(1, equal + 1, ft_strlen(equal + 1));
	write(1, "\"\n", 2);
}

static int	print_export(t_shell *sh)
{
	char	**copy;
	int		size;
	int		i;

	size = env_size(sh->env);
	if (size == 0)
		return (SUCCESS);
	copy = malloc(sizeof(char *) * size);
	if (copy == NULL)
		return (FAILURE);
	i = 0;
	while (i < size)
	{
		copy[i] = sh->env[i];
		i++;
	}
	sort_env_ptrs(copy, size);
	i = 0;
	while (i < size)
		print_export_line(copy[i++]);
	free(copy);
	return (SUCCESS);
}

static int	export_one(t_shell *sh, char *arg)
{
	int	index;

	if (is_valid_identifier(arg) == 0)
	{
		write(2, "minishell: export: not a valid identifier\n", 42);
		return (FAILURE);
	}
	if (ft_strchr(arg, '=') == NULL)
		return (SUCCESS);
	index = get_env_index(sh->env, arg);
	if (index >= 0)
		return (replace_env_var(sh, index, arg));
	return (add_env_var(sh, arg));
}

int	builtin_export(t_cmd *cmds, t_shell *sh)
{
	int	i;
	int	status;

	if (cmds == NULL || cmds->args == NULL || sh == NULL)
		return (FAILURE);
	if (cmds->args[1] == NULL)
		return (print_export(sh));
	i = 1;
	status = 0;
	while (cmds->args[i])
	{
		if (export_one(sh, cmds->args[i]) != SUCCESS)
			status = 1;
		i++;
	}
	return (status);
}
