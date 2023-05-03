/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apereira <apereira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 08:04:34 by apereira          #+#    #+#             */
/*   Updated: 2023/05/02 15:44:27 by apereira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// Finds the PATH string in the "envp" text
char	*find_path(char **envp)
{
	while (ft_strncmp("PATH=", *envp, 5))
		envp++;
	return (*envp + 5);
}

int	count_words(const char *str, const char *delimiters)
{
	int			count;
	int			token_length;
	const char	*token_start;

	count = 0;
	if (!str)
		return (0);
	token_start = get_next_token(str, delimiters);
	while (token_start)
	{
		count++;
		token_length = get_token_length(token_start, delimiters);
		token_start = get_next_token(token_start + token_length, delimiters);
	}
	return (count);
}

// This functions helps preventing a double print
// when using commands that wait for input like "cat"
void	custom_handle_signal(int sign)
{
	(void)sign;
	write(1, "\n", 1);
}
