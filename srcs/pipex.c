/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlufulua <tlufulua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/26 11:46:43 by tlufulua          #+#    #+#             */
/*   Updated: 2022/11/01 01:11:56 by tlufulua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pipex.h>

//Con este main, al ejecutar ./pipex ls, hará lo mismo que si ponemos ls en la
//terminal.

int	main(int argc, char **argv, char **env)
{
	char	*path;

	argc = 0;
	path = "/bin/ls";
	argv += 1;
	execve(path, argv, env);
	//No escribe "Hola" porque execve ejecuta el proceso al que llama acabando
	//el proceso en el que está antes
	write(1, "Hola\n", 5);
	return (0);
}
