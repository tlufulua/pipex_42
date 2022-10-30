/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlufulua <tlufulua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/26 11:46:43 by tlufulua          #+#    #+#             */
/*   Updated: 2022/10/30 11:54:53 by tlufulua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pipex.h>

/*El programa debe hacer lo mismo que el comando: 
 < archivo1 comando1 | comando2 > archivo2
 Un proceso es un programa. Este programa se va a encargar de abrir un fichero
 y pasarselo a un programa. Una vez que este termine se pasa el resultado a
 otro programa y se escribe su resultado en otro fichero. Es un programa que 
 "llama" a otros programas.*/


/*Este main es el proceso padre, el proceso del que van a salir los demás 
procesos.*/
int	main(int argc, char **argv)
{
	pid_t	fr;
	int		fd[2];
	char	result[100];
	int		len;

	len = ft_strlen(argv[argc - 1]);
/*El proceso padre y el hijo se van a comunicar a través de un pipe. Se crean 
dos ficheros ficticios, uno que lee (fd[0]) y otro que escribe (fd[1]). 
El padre "lee" y el hijo "escribe". Puede ser al revés, pero entiendo que en
este caso específico, queremos el resultado de lo queescriba el programa que 
ejecute el hijo.*/
	pipe(fd);
/*La función fork crea un proceso hijo. El fr del hijo es 0*/
	fr = fork();
/*A partir de aquí, hay dos procesos que ejecutan el código, así que cada uno lo
ejecutará según sus condiciones. Por eso pipe() se tiene que declarar antes,
si no, cada proceso tendría una tubería creada que no conecta a ningún sitio*/

/*Si estamos en el proceso hijo, se cumplira el if (!fr) y se cerrará el 
fichero de lectura, pero en el proceso padre se cumplirá el if (fr), 
por lo que se cerrará el fichero de escritura*/
	
	if (fr == -1)
		write(1, "Error\n",6);
	else if (!fr) //hijo
	{
		close(fd[0]);
		write(fd[1], argv[argc - 1], len);
		close(fd[1]); //al acabar, lo correcto es cerrar el descriptor.
	}
	wait(0);
	if (fr) //padre
	{
		close(fd[1]);
		len = read(fd[0], result, len);
		write(1, result, len);
		write(1, "\n", len);
		close(fd[0]);
	}
	return (0);
}
