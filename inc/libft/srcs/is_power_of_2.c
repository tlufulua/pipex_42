/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_power_of_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlufulua <tlufulua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/08 19:56:37 by tlufulua          #+#    #+#             */
/*   Updated: 2022/08/08 20:08:31 by tlufulua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
 * This function determines if a given number is a power of 2.
 * is_power_of_2 returns 1 if the given number is a power of 2, otherwise it
 * returns 0.
 *
 * Every number power of 2 only have one bit on. For example: 2 = 00000010,
 * 16 = 00010000. When we use the operator AND (&) with a number power of 2 and
 * his previous number, the result is 0. Otherwise, the result is a number 
 * bigger than 0.
*/

int	is_power_of_2(unsigned int n)
{
	if (n && !(n & (n - 1)))
		return (1);
	return (0);
}
