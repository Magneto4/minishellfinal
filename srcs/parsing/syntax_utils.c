/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyujung <hyujung@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 09:34:53 by hyujung           #+#    #+#             */
/*   Updated: 2022/10/28 20:41:58 by hyujung          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

extern int	g_ret;

char	*ft_getenv2(char **envp, char *var)
{
	int		index;
	int		j;
	char	*tmp;

	index = -1;
	if (!var)
		return (NULL);
	while (envp[++index])
	{
		j = 0;
		while (envp[index][j] != '=')
			j++;
		if ((int)(ft_strlen(var)) > j)
			j = ft_strlen(var);
		if (ft_strncmp(envp[index], var, j) == 0)
		{
			if (*(1 + ft_strchr(envp[index], '=')) == '\0')
				return (NULL);
			tmp = ft_strdup(1 + ft_strchr(envp[index], '='));
			if (!tmp)
				return ("\0");
			return (tmp);
		}
	}
	return (NULL);
}

t_token	*ft_fail(void)
{
	write(2, "Syntax error\n", 13);
	return (NULL);
}

int	interate_non_whitespace(t_token *token, int i, char ***envp)
{
	char	*s;

	s = token->s;
	if (is_incld(s[i], " \t\n\v\f\r"))
		i++;
	else
	{
		i = lexical_analysis2(token, i);
		if (i == -1)
		{
			g_ret = SYNTAX_ERROR;
			free_token(&token);
			return (0);
		}
		if (i == -2)
			ft_free_and_exit(token, *envp);
	}
	return (i);
}

int	check_endcmd(t_token *token, char *buf, int fd)
{
	char	*endcmd;
	int		len;

	endcmd = token->next->str;
	if (!(ft_strlen(buf) == ft_strlen(endcmd)))
		return (0);
	len = ft_strlen(endcmd);
	ft_strncmp(buf, endcmd, len);
	if (!ft_strncmp(buf, endcmd, len))
	{
		close(fd);
		return (1);
	}
	return (0);
}

void	*set_global_ret_null(int global)
{
	g_ret = global;
	return (NULL);
}
