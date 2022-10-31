/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlufulua <tlufulua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/26 11:46:43 by tlufulua          #+#    #+#             */
/*   Updated: 2022/10/31 23:18:27 by tlufulua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pipex.h>

//Con este main, al ejecutar ./pipex ls, hará lo mismo que si ponemos ls en la
//terminal.

void	hola(char *path, char **argv, char **env)
{
	execve(path, argv, env);
	//No escribe "Hola" porque execve ejecuta el proceso al que llama acabando
	//el proceso en el que está antes
	write(1, "Hola\n", 5);
}

int	main(int argc, char **argv, char **env)
{
	char	*path;

	argc = 0;
	path = "/bin/ls";
	argv++;
	hola(path, argv, env);
	write(1, "Adiós\n", 6);
	return (0);
}
