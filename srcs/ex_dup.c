/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ex_dup.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlufulua <tlufulua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/01 01:15:19 by tlufulua          #+#    #+#             */
/*   Updated: 2022/11/01 01:20:00 by tlufulua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pipex.h>

void	duplicate(int argc, char **argv)
{
	int	fd;

	if (argc == 3)
	{
		fd = open(argv[1], O_WRONLY | O_CREAT, 0777);
		dup2(fd, 1);
		write(1, argv[2], ft_strlen(argv[2]));
	}
	else
		write(1, "Error\n", 6);
}
