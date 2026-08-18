/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils_1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohassaf <mohassaf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/31 17:36:18 by mohassaf          #+#    #+#             */
/*   Updated: 2026/08/10 20:37:38 by mohassaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header/minishell.h"

static char	*join_path_cmd(char *dir, char *cmd)
{
	char	*tmp;
	char	*full_path;

	tmp = ft_strjoin(dir, "/");
	full_path = ft_strjoin(tmp, cmd);
	free(tmp);
	return (full_path);
}

static char	*find_path(char **paths, char *cmd)
{
	char	*full_path;
	int		i;

	i = 0;
	while (paths[i])
	{
		full_path = join_path_cmd(paths[i], cmd);
		if (full_path && access(full_path, X_OK) == 0)
			return (full_path);
		free(full_path);
		i++;
	}
	return (NULL);
}

int	get_exit_status(int status)
{
	int	sig;

	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	if (WIFSIGNALED(status))
	{
		sig = WTERMSIG(status);
		if (sig == SIGINT)
			write(1, "\n", 1);
		else if (sig == SIGQUIT)
			write(1, "Quit\n", 5);
		return (128 + sig);
	}
	return (1);
}

char	*get_env_value(char **env, char *key)
{
	int	index;
	int	len;

	index = get_env_index(env, key);
	if (index == -1)
		return (NULL);
	len = ft_strlen(key);
	return (env[index] + len + 1);
}

char	*get_cmd_path(char *cmd, char **env)
{
	char	**paths;
	char	*path_value;
	char	*full_path;

	if (cmd == NULL || cmd[0] == '\0')
		return (NULL);
	if (ft_strchr(cmd, '/'))
		return (ft_strdup(cmd));
	path_value = get_env_value(env, "PATH");
	if (path_value == NULL)
		return (NULL);
	paths = ft_split(path_value, ':');
	if (paths == NULL)
		return (NULL);
	full_path = find_path(paths, cmd);
	free_tab(paths);
	return (full_path);
}
