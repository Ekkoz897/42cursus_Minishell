/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apereira <apereira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 08:04:34 by apereira          #+#    #+#             */
/*   Updated: 2023/04/03 13:38:24 by apereira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int get_token_length_no_redirection(const char *str, const char *delimiters)
{
    int length;

    length = 0;
    while (str[length] && !ft_strchr(delimiters, str[length]) && str[length] != '<' && str[length] != '>')
    {
        length++;
    }
    return (length);
}

const char *get_next_token_no_redirection(const char *str, const char *delimiters)
{
    while (*str && ft_strchr(delimiters, *str))
    {
        str++;
    }
	if (*str == '<')
	{
		str++;
		while (*str && ft_strchr(delimiters, *str))
			str++;
		while (*str && !ft_strchr(delimiters, *str))
			str++;
		while (*str && ft_strchr(delimiters, *str))
			str++;
	}
    if (*str)
    {
        return (str);
    }
    else
    {
        return (NULL);
    }
}

int count_words_no_redirection(const char *str, const char *delimiters)
{
    int count;
    int token_length;
    const char *token_start;

    count = 0;
    token_start = get_next_token_no_redirection(str, delimiters);
    while (token_start)
    {
        count++;
        token_length = get_token_length_no_redirection(token_start, delimiters);
        token_start = get_next_token_no_redirection(token_start + token_length, delimiters);
    }
    return (count);
}

int is_delimiter(char c, const char *delimiters)
{
    while (*delimiters)
    {
        if (c == *delimiters)
            return (1);
        delimiters++;
    }
    return (0);
}

char **ft_split_commands_no_redirection(const char *str, const char *delimiters)
{
	char **tokens;
	int num_words;
	char *token_start;
	int token_length;

	num_words = count_words_no_redirection(str, delimiters);
	tokens = malloc((num_words + 1) * sizeof(char *));
	if (!tokens)
		return (NULL);
	token_start = (char *)str;
	while (*token_start)
	{
		while (is_delimiter(*token_start, delimiters))
			token_start++;
		if (*token_start == '<')
		{
			token_start++;
			while (is_delimiter(*token_start, delimiters))
				token_start++;
			while (!is_delimiter(*token_start, delimiters))
				token_start++;
			while (is_delimiter(*token_start, delimiters))
				token_start++;
			continue;
		}
		if (*token_start)
		{
			token_length = get_token_length(token_start, delimiters);
			*tokens = ft_strndup(token_start, token_length);
			token_start += token_length;
			tokens++;
		}
	}
	*tokens = NULL;
	return (tokens - num_words);
}


// Finds the PATH string in the "envp" text
char	*find_path(char **envp)
{
	while (ft_strncmp("PATH=", *envp, 5))
		envp++;
	return (*envp + 5);
}

void	ft_free(char **array)
{
	int	i;

	i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free (array);
}

int	count_words(const char *str, const char *delimiters)
{
	int			count;
	int			token_length;
	const char	*token_start;

	count = 0;
	token_start = get_next_token(str, delimiters);
	while (token_start)
	{
		count++;
		token_length = get_token_length(token_start, delimiters);
		token_start = get_next_token(token_start + token_length, delimiters);
	}
	return (count);
}