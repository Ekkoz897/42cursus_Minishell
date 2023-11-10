/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils6.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apereira <apereira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 13:04:22 by miandrad          #+#    #+#             */
/*   Updated: 2023/11/10 13:16:34 by apereira         ###   ########.fr       */
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

void	handler_quit_ctrlc(int sig)
{
	if (sig == SIGINT || sig == SIGQUIT)
	{
		printf("\n");
	}
}
