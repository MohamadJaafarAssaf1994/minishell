/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohassaf <mohassaf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/30 19:00:56 by mohassaf          #+#    #+#             */
/*   Updated: 2026/08/11 15:20:58 by mohassaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header/minishell.h"

static int	is_env_key(char *env_line, char *key)
{
	int	len;

	len = ft_strlen(key);
	if (ft_strncmp(env_line, key, len) == 0 && env_line[len] == '=')
		return (1);
	return (0);
}

static int	replace_existing_env(t_shell *sh, char *key, char *new_line)
{
	int	i;

	i = 0;
	while (sh->env[i])
	{
		if (is_env_key(sh->env[i], key))
		{
			free(sh->env[i]);
			sh->env[i] = new_line;
			return (SUCCESS);
		}
		i++;
	}
	return (FAILURE);
}

static	int	update_env_value(t_shell *sh, char *key, char *value)
{
	char	*new_line;

	if (sh == NULL || sh->env == NULL || key == NULL || value == NULL)
		return (FAILURE);
	new_line = join_key_value(key, value);
	if (new_line == NULL)
		return (FAILURE);
	if (replace_existing_env(sh, key, new_line) == SUCCESS)
		return (SUCCESS);
	if (add_env_var(sh, new_line) == FAILURE)
	{
		free(new_line);
		return (FAILURE);
	}
	free(new_line);
	return (SUCCESS);
}

int	builtin_cd(t_cmd *cmd, t_shell *sh)
{
	char	old_pwd[4096];
	char	new_pwd[4096];
	char	*too_many_args;
	char	*path;

	too_many_args = "minishell: cd: too many arguments\n";
	path = cmd->args[1];
	if (path != NULL && cmd->args[2] != NULL)
		return (write(2, too_many_args, ft_strlen(too_many_args)), 2);
	if (path == NULL)
	{
		path = get_env_value(sh->env, "HOME");
		if (path == NULL)
			return (write(2, "minishell: cd: HOME not set\n", 28), 1);
	}
	if (getcwd(old_pwd, sizeof(old_pwd)) == NULL)
		return (perror("minishell: cd"), 1);
	if (chdir(path) == -1)
		return (perror("minishell: cd"), 1);
	if (getcwd(new_pwd, sizeof(new_pwd)) == NULL)
		return (perror("minishell: cd"), 1);
	update_env_value(sh, "OLDPWD", old_pwd);
	update_env_value(sh, "PWD", new_pwd);
	return (0);
}

char	*join_key_value(char *key, char *value)
{
	char	*tmp;
	char	*result;

	tmp = ft_strjoin(key, "=");
	if (tmp == NULL)
		return (NULL);
	result = ft_strjoin(tmp, value);
	if (result == NULL)
		return (NULL);
	free(tmp);
	return (result);
}
