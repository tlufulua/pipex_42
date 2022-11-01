/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlufulua <tlufulua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/26 11:46:43 by tlufulua          #+#    #+#             */
/*   Updated: 2022/11/01 01:38:11 by tlufulua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pipex.h>

//Con este main, al ejecutar ./pipex ls, hará lo mismo que si ponemos ls en la
//terminal.

void	duplicate(char *argv)
{
	int	fd;

	fd = open(argv, O_WRONLY | O_CREAT, 0777);
	dup2(fd, 1);
}

int	main(int argc, char **argv, char **env)
{
	char	*path;

	duplicate(argv[argc - 1]); //va a redireccionar la salida a un archivo (es por practicar)
	path = "/bin/ls";
	argv[argc - 1] = NULL; //elimino el último argumento ya que va a ser el
						   //archivo donde se guarda el output.
	argv += 1;
	execve(path, argv, env);
	//No escribe "Hola" porque execve ejecuta el proceso al que llama acabando
	//el proceso en el que está antes
	write(1, "Hola\n", 5);
	return (0);
}
