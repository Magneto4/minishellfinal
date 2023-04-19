/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config_signal.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunahjung <hyunahjung@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 22:30:57 by hyunahjung        #+#    #+#             */
/*   Updated: 2022/11/01 11:26:23 by hyunahjung       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include <signal.h>
#include <readline/readline.h>
#include <readline/history.h>

extern int	g_ret;

void	restore_prompt(int sig, siginfo_t *theinfo, void *foo)
{
	g_ret = 130;
	(void)sig;
	(void)foo;
	if ((int)theinfo->si_pid != 0)
	{
		write(1, "\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
}

void	ctrl_c(int sig)
{
	g_ret = 130;
	(void)sig;
}

void	back_slash(int sig)
{
	if (g_ret == DONT_IGNORE)
	{
		printf("Quit (core dumped)\n");
		g_ret = 131;
		(void)sig;
	}
}

void	hd_sign(int sig)
{
	if (sig == SIGINT)
	{
		close(0);
		g_ret = 130;
	}
	else if (sig == SIGQUIT)
		back_slash(sig);
}

void	run_signals(int sig)
{
	struct sigaction	sa;

	if (sig == 1)
	{
		ft_memset(&sa, 0, sizeof(sa));
		sigemptyset(&sa.sa_mask);
		sa.sa_sigaction = restore_prompt;
		sa.sa_flags = SA_SIGINFO;
		sigaction(SIGINT, &sa, NULL);
		signal(SIGQUIT, SIG_IGN);
	}
	if (sig == 2)
	{
		signal(SIGINT, ctrl_c);
		signal(SIGQUIT, back_slash);
	}
	if (sig == 4)
		signal(SIGINT, hd_sign);
	if (sig == 5)
	{
		signal(SIGINT, SIG_IGN);
		signal(SIGQUIT, SIG_IGN);
	}
}
