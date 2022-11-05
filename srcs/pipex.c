/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlufulua <tlufulua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/26 11:46:43 by tlufulua          #+#    #+#             */
/*   Updated: 2022/11/05 20:41:58 by tlufulua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pipex.h>

void	child(int infile, int *fd, char **argv, char **env)
{
	char	*cmd;
	char	**vec;

	dup2(fd[1], STDOUT_FILENO);
	dup2(infile, STDIN_FILENO);
	close(fd[0]);
	vec = ft_split(argv[2], ' ');
	cmd = get_cmd(vec[0], env);
	if (execve(cmd, vec, env) == -1)
	{
		free(cmd);
		free_split(vec);
		ft_error("\033[31merror:\033[0m execve failed");
	}
}

void	father(int *fd, char **argv, char **env)
{
	int		outfile;
	char	*cmd;
	char	**vec;

	outfile = open(argv[4], O_WRONLY | O_CREAT, 0777);
	if (outfile == -1)
		ft_error("\033[31merror:\033[0m can´t create or open the outfile");
	dup2(fd[0], STDIN_FILENO);
	dup2(outfile, STDOUT_FILENO);
	close(fd[1]);
	vec = ft_split(argv[3], ' ');
	cmd = get_cmd(vec[0], env);
	execve(cmd, vec, env);
	if (execve(cmd, vec, env) == -1)
	{
		free(cmd);
		free_split(vec);
		ft_error("\033[31merror:\033[0m execve failed");
	}
}

int	main(int argc, char **argv, char **env)
{
	int		fd[2];
	int		infile;
	pid_t	fr;

	if (argc == 5)
	{
		check_arg(argv);
		infile = open(argv[1], O_RDONLY, 0777);
		if (infile == -1)
			ft_error("\033[31merror:\033[0m can´t open the infile");
		pipe(fd);
		fr = fork();
		if (fr == -1)
			ft_error("\033[31merror\033[0m: fork failure");
		if (fr == 0)
			child(infile, fd, argv, env);
		if (fr)
			father(fd, argv, env);
	}
	else
		ft_error("\033[31merror:\033[0m wrong number of arguments, expected 4");
	return (0);
}
