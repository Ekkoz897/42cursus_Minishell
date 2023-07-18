/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apereira <apereira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 12:53:05 by apereira          #+#    #+#             */
/*   Updated: 2023/07/18 12:55:22 by apereira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_delimiter(char c, char *delimiters)
{
	while (*delimiters)
	{
		if (c == *delimiters)
			return (1);
		delimiters++;
	}
	return (0);
}
