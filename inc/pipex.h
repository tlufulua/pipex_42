/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlufulua <tlufulua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/26 11:48:50 by tlufulua          #+#    #+#             */
/*   Updated: 2022/11/01 19:40:32 by tlufulua         ###   ########.fr       */
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

//MAIN
void	father(int *fd, char **argv, char **env);
void	child(int *fd, char **argv, char **env);

//UTILS
void	ft_error(char *str);
char	**get_path(char **env);
char	*get_cmd(char *str, char **env);
void	check_arg(char **argv);
char	*trim_spc(char *str);
#endif
