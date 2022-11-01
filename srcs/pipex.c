/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlufulua <tlufulua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/26 11:46:43 by tlufulua          #+#    #+#             */
/*   Updated: 2022/11/01 19:40:34 by tlufulua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pipex.h>

void	child(int *fd, char **argv, char **env)
{
	int		infile;
	char	*cmd;
	char	**vec;

	infile = open(argv[1], O_RDONLY, 0777);
	if (infile == -1)
		ft_error("\033[31merror:\033[0m can´t open the infile");
	//dup redirecciona una vez que tengo la entrada (infile) y la salida
	//(fd[1]) abiertas.
	dup2(fd[1], STDOUT_FILENO);
	dup2(infile, STDIN_FILENO);
	close(fd[0]);
	vec = ft_split(argv[2], ' ');
	cmd = get_cmd(vec[0], env); //liberar
	execve(cmd, vec, env);
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
	cmd = get_cmd(vec[0], env); //liberar
	execve(cmd, vec, env);
}
/*El programa debe hacer lo mismo que el comando: 
 < archivo1 comando1 | comando2 > archivo2 
 pero ejecuta:
 ./pipex archivo1 "comando1" "comando2" archivo2*/

int	main(int argc, char **argv, char **env)
{
	int		fd[2];
	pid_t	fr;

	if (argc == 5)
	{
		check_arg(argv);
		pipe(fd);
		fr = fork();
		if (fr == -1)
			ft_error("\033[31merror\033[0m: fork failure");
		if (fr == 0) //hijo
			child(fd, argv, env);
		if (waitpid(fr, NULL, 0))
			return (-1);
		if (fr) //padre
			father(fd, argv, env);
	}
	else
		ft_error("\033[31merror:\033[0m wrong number of arguments, expected 4");
	return (0);
}
