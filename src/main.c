/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hammeah <hammeah@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/07 15:28:14 by mohassaf          #+#    #+#             */
/*   Updated: 2026/08/13 12:05:27 by hammeah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header/minishell.h"

int	main(int argc, char **argv, char **env)
{
	t_shell	sh;

	(void)argc;
	(void)argv;
	if (init_shell(&sh, env) == FAILURE)
		return (FAILURE);
	shell_loop(&sh);
	cleanup_shell(&sh);
	return (sh.exit_status);
}
