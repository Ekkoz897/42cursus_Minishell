/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apereira <apereira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 11:38:06 by apereira          #+#    #+#             */
/*   Updated: 2023/07/17 11:39:43 by apereira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//Creates a temporary fd to 
void	process_heredoc(t_vars *vars, char *doc_file, int fd)
{
	char	*str;

	write(1, "> ", 2);
	str = get_next_line(0);
	while (ft_strncmp(str, doc_file, ft_strlen(str)) != 0)
	{
		write(fd, str, ft_strlen(str));
		free(str);
		write(1, "> ", 2);
		str = get_next_line(0);
	}
	free(str);
	str = NULL;
	get_next_line(-1);
	free(doc_file);
	ft_free_vars(vars);
	exit(0);
}

void	open_doc_file(t_vars *vars, char *doc_file, int *j)
	{
	int	id;

	vars->here_doc_fd[*j] = open(vars->temp, O_CREAT | O_TRUNC \
		| O_RDWR, 0000644);
	if (vars->here_doc_fd[*j] == -1)
		perror(vars->temp);
	id = fork();
	if (id == 0)
		process_heredoc(vars, doc_file, vars->here_doc_fd[*j]);
	wait(NULL);
	free(doc_file);
	vars->here_doc_fd[*j] = open(vars->temp, O_RDONLY, 0000644);
}

void	open_doc(t_vars *vars, char *commands, int *j)
	{
	char	*doc_file;
	int		i;

	i = 0;
	commands = ft_strchr(commands, '<');
	commands += 2;
	while (*commands == ' ' || *commands == '	')
		commands++;
	while (commands[i] != '<' && commands[i] != '>' && commands[i] != ' ' \
		&& commands[i] != '	' && commands[i])
		i++;
	doc_file = ft_strndup(commands, i);
	vars->temp = doc_file;
	doc_file = ft_strjoin(doc_file, "\n");
	open_doc_file(vars, doc_file, j);
}

void	handle_heredoc(t_vars *vars, char *tmp, int *j)
{
	while (ft_strchr(tmp, '<') && *(ft_strchr(tmp, '<') + 1) == '<')
	{
		open_doc(vars, tmp, j);
		tmp = ft_strchr(tmp, '<') + 2;
		if (ft_strchr(tmp, '<') && *(ft_strchr(tmp, '<') + 1) == '<')
		{
			close(vars->here_doc_fd[*j]);
			unlink(vars->temp);
			free(vars->temp);
		}
	}
}

//Searches the commands matrix for '<<'
//and calls open_doc
void	here_doc(t_vars *vars, char **commands)
{
	char	*tmp;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (commands[i])
	{
		if (ft_strrchr(commands[i], '<') && *(ft_strrchr(commands[i], '<') - 1) \
			== '<')
			j++;
		i++;
	}
	vars->here_doc_fd = malloc(sizeof(char) * j + 1);
	vars->here_doc_fd[j] = '\0';
	i = 0;
	j = 0;
	while (commands[i])
	{
		tmp = commands[i];
		handle_heredoc(vars, tmp, &j);
		j++;
		i++;
	}
}
