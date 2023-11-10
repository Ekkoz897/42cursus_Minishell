/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils6.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miandrad <miandrad@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 13:04:22 by miandrad          #+#    #+#             */
/*   Updated: 2023/11/10 13:04:33 by miandrad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*funcao_nova(char *str, char *delimiters)
{
	while (*str && ft_strchr(delimiters, *str))
		str++;
	while (*str && !ft_strchr(delimiters, *str))
		str++;
	while (*str && ft_strchr(delimiters, *str))
		str++;
	str--;
	return (str);
}