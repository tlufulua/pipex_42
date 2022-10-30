/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlufulua <tlufulua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/26 11:46:43 by tlufulua          #+#    #+#             */
/*   Updated: 2022/10/30 19:57:28 by tlufulua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pipex.h>

int	main(int argc, char **argv)
{
	int 	fd;
	int 	fd_copy;
	char	buffer[100];
	char	buffercp[100];

	fd = open(argv[1], O_RDWR);	
	if (argc == 2)
	{
		ft_printf("fd: %d\n", fd);
		read(fd, buffer, 50);
		ft_printf("buffer: %s\n", buffer);
		fd = close(fd);
		ft_printf("close: %d\n", fd);
	}
	else if (argc == 3)
	{
		ft_printf("fd: %d\n", fd);
		write(fd, argv[2], ft_strlen(argv[2]));
		close(fd);
		fd = open(argv[1], O_RDONLY);
		fd_copy = 5; 
		dup2(fd, fd_copy);
		read(fd, buffer, 50);
		ft_printf("buffer: %s\n", buffer);
		fd = close(fd);
		ft_printf("close fd: %d\n", fd);
		ft_printf("fd_copy: %i\n", fd_copy);
		read(fd_copy, buffercp, 50);
		ft_printf("buffercp: %s\n", buffercp);
		fd_copy = close(fd_copy);
		ft_printf("close fd_copy: %d\n", fd);
	}
	return (0);
}
