/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_sanitize.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apereira <apereira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 16:34:56 by apereira          #+#    #+#             */
/*   Updated: 2023/07/17 09:55:44 by apereira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// Checks if the command received in ARGV is valid by
// searching for it in the bin folder

char	*check_executable(char *command, char **split_paths)
{
	if (access(command, 0) == 0)
	{
		ft_free(split_paths);
		return (command);
	}
	else
	{
		perror(command);
		return (NULL);
	}
}

char	*check_command(char *command, char **split_paths)
{
	int		i;
	char	*path;
	char	*temp;

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

char	*check_valid_cmd_builtin(char *command, char **split_paths)
{
	char	*builtins[8];
	int		i;

	builtins[0] = "echo";
	builtins[1] = "cd";
	builtins[2] = "pwd";
	builtins[3] = "export";
	builtins[4] = "unset";
	builtins[5] = "env";
	builtins[6] = "exit";
	builtins[7] = "NULL";
	i = 0;
	while (builtins[i])
	{
		if (ft_strcmp(command, builtins[i]) == 0)
		{
			ft_free(split_paths);
			return (command);
		}
		i++;
	}
	return (NULL);
}

char	*check_valid_cmd(char *command, char **envp)
{
	char	*cmd;
	char	**split_paths;
	char	*valid_cmd;

	cmd = find_path(envp);
	split_paths = ft_split(cmd, ':');
	valid_cmd = check_valid_cmd_builtinbuiltin(command, split_paths);
	if (valid_cmd)
		return (valid_cmd);
	if (ft_strchr(command, '/'))
		return (check_executable(command, split_paths));
	else
		return (check_command(command, split_paths));
}
