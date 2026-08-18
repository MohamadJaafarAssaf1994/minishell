/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline_script.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohassaf <mohassaf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/11 19:07:35 by mohassaf          #+#    #+#             */
/*   Updated: 2026/08/11 19:07:38 by mohassaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header/minishell.h"

static int	arg_count(char **args)
{
	int	count;

	count = 0;
	while (args && args[count])
		count++;
	return (count);
}

void	exec_shell_script(char *path, char **args, char **env)
{
	char	**shell_args;
	int		i;

	shell_args = malloc(sizeof(char *) * (arg_count(args) + 2));
	if (shell_args == NULL)
		exit(126);
	shell_args[0] = "/bin/sh";
	shell_args[1] = path;
	i = 1;
	while (args[i])
	{
		shell_args[i + 1] = args[i];
		i++;
	}
	shell_args[i + 1] = NULL;
	execve("/bin/sh", shell_args, env);
	free(shell_args);
}
