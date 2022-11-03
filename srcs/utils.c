/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlufulua <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/01 16:48:24 by tlufulua          #+#    #+#             */
/*   Updated: 2022/11/03 14:50:00 by tlufulua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pipex.h>

void	ft_error(char *str)
{
	perror(str);
	exit(EXIT_FAILURE);
}

char	**get_path(char **env)
{
	char	**path;
	int		i;

	i = 0;
	while (!ft_strnstr(env[i], "PATH", 5) && env[i])
		i++;
	if (!env[i])
		ft_error("\033[31merror:\033[0m path not found");
	path = ft_split(env[i] + 5, ':');
	return (path);
}

char	*get_cmd(char *str, char **env)
{
	char	*aux;
	int		i;
	char	**path;
	char	*cmd;

	i = 0;
	aux = 0;
	cmd = 0;
	path = get_path(env);
	while (access(cmd, F_OK) && path[i])
	{
		if (cmd)
			free(cmd);
		aux = path[i++];
		cmd = ft_strjoin(aux, "/");
		aux = cmd;
		cmd = ft_strjoin(aux, str);
		free(aux);
	}
	free_split(path);
	if (access(cmd, F_OK))
		ft_error("\033[31merror:\033[0m command not found");
	return (cmd);
}

char	*trim_spc(char *str)
{
	while (*str <= 32 && *str != 0)
		str++;
	return (str);
}

void	check_arg(char **argv)
{
	int	i;

	i = 0;
	while (argv[i])
		if (!*argv[i++])
			ft_error("\033[31merror\033[0m: empty arguments");
	if (!*trim_spc(argv[2]) || !*trim_spc(argv[3]))
		ft_error("\033[31merror\033[0m: empty arguments");
}
