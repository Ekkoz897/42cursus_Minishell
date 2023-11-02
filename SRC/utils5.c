/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils5.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apereira <apereira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 15:22:41 by miandrad          #+#    #+#             */
/*   Updated: 2023/11/02 14:06:54 by apereira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_get_next_token_noredirection_helper(char chr,
	int *in_quotes, char *current_quote)
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

void	ft_get_token_l_noredirection_helper(int *len, char *token_start, \
	char *delimiters, char current_quote)
{
	int	in_quotes;

	in_quotes = 0;
	while (*token_start)
	{
		if (in_quotes == 0 && ft_strchr(delimiters, *token_start))
			break ;
		if (*token_start == '\'' || *token_start == '\"')
		{
			if (in_quotes == 0 || current_quote == *token_start)
			{
				in_quotes = !in_quotes;
				if (in_quotes)
					current_quote = *token_start;
				else
					current_quote = '\0';
			}
		}
		token_start++;
		(*len)++;
	}
}

void	ft_remove_quotes_helper(char *str, char *new_str, int *i)
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

int	str_is_spaces_only(char *input)
{
	int	i;

	i = 0;
	while (input[i])
	{
		if (input[i] != ' ')
			return (0);
		i++;
	}
	return (1);
}

int	find_env_line_nbr(t_vars *vars, char *name)
{
	int		i;
	int		name_len;

	name_len = ft_strlen(name);
	i = 0;
	while (vars->my_environ[i])
	{
		if (ft_strncmp(vars->my_environ[i], name, name_len) == 0
			&& vars->my_environ[i][name_len] == '=')
			return (i);
		i++;
	}
	return (-1);
}
