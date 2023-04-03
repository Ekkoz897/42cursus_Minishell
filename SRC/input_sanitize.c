/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_sanitize.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apereira <apereira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 16:34:56 by apereira          #+#    #+#             */
/*   Updated: 2023/04/03 08:07:57 by apereira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int get_token_length(const char *str, const char *delimiters) {
    int length = 0;
    while (str[length] && !ft_strchr(delimiters, str[length])) {
        length++;
    }
    return length;
}

const char *get_next_token(const char *str, const char *delimiters) {
    while (*str && ft_strchr(delimiters, *str)) {
        str++;
    }
    return *str ? str : NULL;
}

char **split_commands(const char *input, int *cmd_count) {
    int i, count = 0;
    const char *token;
    char **commands;

    // Count the number of commands
    for (i = 0; input[i] != '\0'; i++) {
        if (input[i] == '|') {
            count++;
        }
    }
    count++;

    // Allocate memory for commands array
    commands = (char **)malloc((count + 1) * sizeof(char *));

    // Split input string into commands
    i = 0;
    token = input;
    while (token) {
        int length = get_token_length(token, "|");
        commands[i] = ft_strndup(token, length);
        i++;

        token = get_next_token(token + length, "|");
    }
    commands[i] = NULL;
    *cmd_count = i;

    return commands;
}

// Checks if the command received in ARGV is valid by
// searching for it in the bin folder
char	*check_valid_cmd(char *command, char **envp)
{
	int		i;
	char	**split_paths;
	char	*path;
	char	*temp;
	char	*cmd;

	cmd = find_path(envp);
	split_paths = ft_split(cmd, ':');
	i = 0;
	while (split_paths[i])
	{
		temp = ft_strjoin(split_paths[i], "/");
		path = ft_strjoin(temp, command);
		free (temp);
		if (access(path, 0) == 0)
		{
			ft_free(split_paths);
			return (path);
		}
		free (path);
		i++;
	}
	ft_free (split_paths);
	ft_printf("Command not found: %s\n", command);
	return (NULL);
}
