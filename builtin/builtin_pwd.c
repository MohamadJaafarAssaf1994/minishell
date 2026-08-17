/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hammeah <hammeah@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/30 19:52:37 by mohassaf          #+#    #+#             */
/*   Updated: 2026/07/03 00:41:55 by hammeah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header/minishell.h"

int	builtin_pwd(t_cmd *cmd, t_shell *sh)
{
	char	pwd[4096];

	(void)cmd;
	(void)sh;
	if (getcwd(pwd, sizeof(pwd)) == NULL)
	{
		perror("minishell: pwd");
		return (1);
	}
	write(1, pwd, ft_strlen(pwd));
	write(1, "\n", 1);
	return (0);
}
