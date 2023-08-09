/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils5.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miandrad <miandrad@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 15:22:41 by miandrad          #+#    #+#             */
/*   Updated: 2023/08/09 17:14:57 by miandrad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_gntnr_helper(char chr, int *in_quotes, char *current_quote)
{
	if (chr == '\'' || chr == '\"')
	{
		if (*in_quotes == 0 || *current_quote == chr)
		{
			*in_quotes = !(*in_quotes);
			if (in_quotes)
				*current_quote = chr;
			else
				*current_quote = '\0';
		}
	}
}

void	ft_gtlnr_helper(int *len, char *ts, char *delimiters, char cq)
{
	int	in_quotes;

	in_quotes = 0;
	while (*ts)
	{
		if (in_quotes == 0 && ft_strchr(delimiters, *ts))
			break ;
		if (*ts == '\'' || *ts == '\"')
		{
			if (in_quotes == 0 || cq == *ts)
			{
				in_quotes = !in_quotes;
				if (in_quotes)
					cq = *ts;
				else
					cq = '\0';
			}
		}
		ts++;
		(*len)++;
	}
}

void	ft_rq_helper(char *str, char *new_str, int *i)
{
	int		j;
	int		in_quotes;
	char	current_quote;

	j = 0;
	in_quotes = -1;
	current_quote = '\0';
	while (str[j])
	{
		if ((in_quotes == 1 && current_quote != str[j])
			|| (str[j] != '\"' && str[j] != '\''))
			new_str[(*i)++] = str[j];
		if ((str[j] == '\'' || str[j] == '\"')
			&& (in_quotes == -1 || current_quote == str[j]))
		{
			in_quotes *= -1;
			if (in_quotes == 1)
				current_quote = str[j];
			else
				current_quote = '\0';
		}
		j++;
	}
}
