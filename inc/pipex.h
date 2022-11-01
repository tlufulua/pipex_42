/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlufulua <tlufulua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/26 11:48:50 by tlufulua          #+#    #+#             */
/*   Updated: 2022/11/01 16:43:06 by tlufulua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H
# include <unistd.h>
# include <stdlib.h>
# include <libft.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <stdio.h>

void	father(int *fd, char **argv, char **env);
void	child(int *fd, char **argv, char **env);
void	error(char *str);

#endif
