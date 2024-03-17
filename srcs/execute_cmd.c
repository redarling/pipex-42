/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asyvash <asyvash@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 14:34:50 by asyvash           #+#    #+#             */
/*   Updated: 2024/03/17 11:08:01 by asyvash          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (-1);
	while (str[i] != '\0')
		i++;
	return (i);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	while (n && *s1 && (*s1 == *s2))
	{
		s1++;
		s2++;
		n--;
	}
	if (n == 0)
		return (0);
	else
		return (*(unsigned char *)s1 - *(unsigned char *)s2);
}

static char	*ft_strjoin(char *s1, char *s2)
{
	int		i;
	int		j;
	char	*res;

	if (!s1 || !s2)
		return (NULL);
	i = -1;
	res = malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!res)
	{
		free(res);
		return (0);
	}
	j = -1;
	while (s1[++i])
		res[i] = s1[i];
	while (s2[++j])
		res[i + j] = s2[j];
	res[i + j] = '\0';
	return (res);
}

static char	*ft_get_path(char *cmd, char **envp)
{
	int		i;
	char	*cmd_path;
	char	*path;
	char	**paths;

	i = -1;
	while (envp[++i] != NULL)
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
			break ;
	paths = ft_split(envp[i] + 5, ':');
	i = -1;
	while (paths[++i] != NULL)
	{
		path = ft_strjoin(paths[i], "/");
		cmd_path = ft_strjoin(path, cmd);
		free(path);
		if (access(cmd_path, F_OK) == 0)
		{
			ft_free(paths);
			return (cmd_path);
		}
		free(cmd_path);
	}
	ft_free(paths);
	return (NULL);
}

void	ft_execute_cmd(char *cmd, char **envp)
{
	char	*cmd_path;
	char	**cmds;

	cmds = ft_split(cmd, ' ');
	cmd_path = ft_get_path(cmds[0], envp);
	if (cmd_path == NULL)
	{
		perror("Command not found");
		ft_free(cmds);
		free(cmd_path);
		return ;
	}
	if (execve(cmd_path, cmds, envp) == -1)
	{
		ft_free(cmds);
		free(cmd_path);
		ft_error("Execve");
	}
}
