/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlufulua <tlufulua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/26 11:46:43 by tlufulua          #+#    #+#             */
/*   Updated: 2022/11/01 16:42:37 by tlufulua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pipex.h>

char	*path(char *str, char **env)
{
	char	*aux;
	int		i;
	char	**path;
	char	*cmd;

	i = 0;
	aux = 0;
	cmd = 0;
	while (!aux && env[i])
		aux = ft_strnstr(env[i++], "PATH", 5);
	if (!aux)
		error("\033[31merror:\033[0m path not found");
	aux += 5;
	path = ft_split(aux, ':');
	i = 0;
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
	if (access(cmd, F_OK))
		error("\033[31merror:\033[0m path not found");
	return (cmd);
}

void	error(char	*str)
{
	perror(str);
	exit(EXIT_FAILURE);
}
void	child(int *fd, char **argv, char **env)
{
	int		infile;
	char	*cmd;
	char	**vec;

	infile = open(argv[1], O_RDONLY, 0777);
		//dup redirecciona una vez que tengo la entrada (infile) y la salida
		//(fd[1]) abiertas.
	dup2(fd[1], STDOUT_FILENO);
	dup2(infile, STDIN_FILENO);
	close(fd[0]);
	vec = ft_split(argv[2], ' ');
	cmd = path(vec[0], env); //liberar
	execve(cmd, vec, env);
}

void	father(int *fd, char **argv, char **env)
{
	int	outfile;
	char	*cmd;
	char	**vec;
			
	outfile = open(argv[4], O_WRONLY | O_CREAT, 0777);
	dup2(fd[0], STDIN_FILENO);
	dup2(outfile, STDOUT_FILENO);
	close(fd[1]);
	vec = ft_split(argv[3], ' ');
	cmd = path(vec[0], env); //liberar
	execve(cmd, vec, env);
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
			error("\033[31merror\033[0m: fork failure\n");
		if (fr == 0) //hijo
			child(fd, argv, env);
		waitpid(fr, NULL, 0); //no lo entiendo
		if (fr) //padre
			father(fd, argv, env);
	}
	else
		error("\033[31merror:\033[0m wrong number of arguments, expected 4\n"); 
	return (0);
 }
