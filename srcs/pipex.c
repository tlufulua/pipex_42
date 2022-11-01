/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlufulua <tlufulua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/26 11:46:43 by tlufulua          #+#    #+#             */
/*   Updated: 2022/11/01 02:06:09 by tlufulua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pipex.h>

//Con este main, al ejecutar ./pipex wc, hará lo mismo que si ponemos wc en la
//terminal.

void	salida(char **argv)
{
	int	fdout;

	fdout = open(*argv, O_WRONLY | O_CREAT, 0777);
	dup2(fdout, 1);
	*(argv) = NULL; //elimino el último argumento ya que va a ser el
					//archivo donde se guarda el output.
}

void	entrada(char *argv)
{
	int	fdin;

	fdin = open(argv, O_RDONLY);
	dup2(fdin, 0);
}
int	main(int argc, char **argv, char **env)
{
	char	*path;

	salida(&argv[argc - 1]); //va a redireccionar la salida a un archivo 
							//(es por practicar)
	entrada(argv[1]); //execve va a usar la información dentro del archivo
					  //que está como segundo parámetro.
	path = "/usr/bin/wc";
	argv += 2;
	execve(path, argv, env);
	//No escribe "Hola" porque execve ejecuta el proceso al que llama acabando
	//el proceso en el que está antes
	write(1, "Hola\n", 5);
	return (0);
}
