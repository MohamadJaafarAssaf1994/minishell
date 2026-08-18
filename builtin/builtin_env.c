/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohassaf <mohassaf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/30 20:21:24 by mohassaf          #+#    #+#             */
/*   Updated: 2026/08/07 17:24:17 by mohassaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header/minishell.h"

int	builtin_env(t_cmd *cmds, t_shell *sh)
{
	int	i;

	if (cmds->args[1] != NULL)
	{
		write(2, "minishell: env: too many arguments\n", 35);
		return (1);
	}
	i = 0;
	while (sh->env[i])
	{
		write(1, sh->env[i], ft_strlen(sh->env[i]));
		write(1, "\n", 1);
		i++;
	}
	return (0);
}
