/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohassaf <mohassaf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/31 14:51:14 by mohassaf          #+#    #+#             */
/*   Updated: 2026/08/07 17:22:51 by mohassaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header/minishell.h"

int	env_size(char **env)
{
	int	i;

	i = 0;
	while (env && env[i])
		i++;
	return (i);
}

int	is_valid_identifier(char *str)
{
	int	i;

	if (str == NULL || str[0] == '\0')
		return (0);
	if (str[0] != '_' && !ft_isalpha(str[0]))
		return (0);
	i = 1;
	while (str[i] && str[i] != '=')
	{
		if (str[i] != '_' && !ft_isalnum(str[i]))
			return (0);
		i++;
	}
	return (1);
}

int	get_env_index(char **env, char *arg)
{
	int	i;
	int	key_len;

	if (env == NULL || arg == NULL)
		return (-1);
	key_len = 0;
	while (arg[key_len] && arg[key_len] != '=')
		key_len++;
	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], arg, key_len) == 0 && env[i][key_len] == '=')
			return (i);
		i++;
	}
	return (-1);
}
