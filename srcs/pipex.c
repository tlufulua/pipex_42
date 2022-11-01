/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlufulua <tlufulua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/26 11:46:43 by tlufulua          #+#    #+#             */
/*   Updated: 2022/11/01 03:48:10 by tlufulua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pipex.h>

void	error()
{
	if (argc != 5)
	{
		ft_putstr_fd("Error: Wrong number of arguments\n", 2);
		return(-1);
	}
	perror("Error");
	exit(-1);
}
void	child(int *fd, char **argv, char **env)
{
	int	infile;

	infile = open(argv[1], O_RDONLY, 0777);
		//dup redirecciona una vez que tengo la entrada (infile) y la salida
		//(fd[1]) abiertas.
	dup2(fd[1], STDOUT_FILENO);
	dup2(infile, STDIN_FILENO);
	close(fd[0]);
	execve("/bin/ls", ft_split(argv[2], ' '), env);
}

void	father(int *fd, char **argv, char **env)
{
	int	outfile;
			
	outfile = open(argv[4], O_WRONLY | O_CREAT, 0777);
	dup2(fd[0], STDIN_FILENO);
	dup2(outfile, STDOUT_FILENO);
	close(fd[1]);
	execve("/usr/bin/wc", ft_split(argv[3], ' '), env);
	
}
/*El programa debe hacer lo mismo que el comando: 
 < archivo1 comando1 | comando2 > archivo2 
 pero ejecuta:
 ./pipex archivo1 "comando1" "comando2" archivo2*/

 int	main(int argc, char **argv, char **env)
 {
	int	fd[2];
	pid_t	fr;

	if (argc == 5)
	{
		pipe(fd);
		fr = fork();
		if (fr == -1)
			error();
		if (fr == 0) //hijo
			child(fd, argv, env);
		waitpid(fr, NULL, 0); //no lo entiendo
		if (fr) //padre
			father(fd, argv, env);
	}
	error();
	return (0);
 }
