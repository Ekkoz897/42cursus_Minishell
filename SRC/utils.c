/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miandrad <miandrad@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 08:04:34 by apereira          #+#    #+#             */
/*   Updated: 2023/04/03 13:00:55 by miandrad         ###   ########.fr       */
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
    while (*str && (ft_strchr(delimiters, *str) || *str == '<' || *str == '>'))
    {
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

char	**ft_split_commands_no_redirection(const char *str, const char *delimiters)
{
    int num_words;
    char **words;
    const char *token_start;
    int token_length;
    int i;

    num_words = count_words_no_redirection(str, delimiters);
    words = (char **)malloc((num_words + 1) * sizeof(char *));
    if (!words)
    {
        return (NULL);
    }
    i = 0;
    token_start = get_next_token_no_redirection(str, delimiters);
    while (token_start)
    {
        token_length = get_token_length_no_redirection(token_start, delimiters);
        words[i] = ft_strndup(token_start, token_length);
        if (!words[i++])
        {
            ft_free(words);
            return (NULL);
        }
        token_start = get_next_token_no_redirection(token_start + token_length, delimiters);
        if (token_start && (*token_start == '<' || *token_start == '>'))
        {
            token_start = get_next_token_no_redirection(token_start + 1, delimiters);
        }
    }
    words[num_words] = NULL;
    return (words);
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