/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlufulua <tlufulua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/26 11:46:43 by tlufulua          #+#    #+#             */
/*   Updated: 2022/11/01 02:54:12 by tlufulua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pipex.h>

/*El programa debe hacer lo mismo que el comando: 
 < archivo1 comando1 | comando2 > archivo2 
 pero ejecuta:
 ./pipex archivo1 "comando1" "comando2" archivo2*/

 int	main(int argc, char **argv, char **env)
 {
	int	fd[2];
	pid_t	fr;

	argc = 0;
	pipe(fd);
	fr = fork();
	if (!fr) //hijo
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
	waitpid(fr, NULL, 0);
	if (fr) //padre
	{
 		int	outfile;
		
		outfile = open(argv[4], O_WRONLY | O_CREAT, 0777);
		dup2(fd[0], STDIN_FILENO);
		dup2(outfile, STDOUT_FILENO);
		close(fd[1]);
		execve("/usr/bin/wc", ft_split(argv[3], ' '), env);
	}
	return (0);
 }
