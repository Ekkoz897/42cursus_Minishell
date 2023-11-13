/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils6.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miandrad <miandrad@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 13:04:22 by miandrad          #+#    #+#             */
/*   Updated: 2023/11/13 12:53:20 by miandrad         ###   ########.fr       */
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

char	*setup_output_redirection_help(char **commands, t_vars *vars, \
	char *temp, char *outfile)
{
	int	i;

	i = 0;
	temp = ft_strrchr(commands[0], '>');
	temp++;
	while (*temp == ' ' || *temp == '	')
		temp++;
	while (temp[i] != ' ' && temp[i] != '	' && temp[i])
		i++;
	outfile = ft_strndup(temp, i);
	if (*(ft_strrchr(commands[0], '>') - 1) == '>')
		vars->fd1 = open(outfile, O_CREAT | O_RDWR | O_APPEND, 0000644);
	else
		vars->fd1 = open(outfile, O_TRUNC | O_CREAT | O_RDWR, 0000644);
	return (outfile);
}

char	*ft_strjoin_three_help(char *s1, char *s2, char *s3, char *str)
{
	size_t	len;

	len = ft_strlen(s1) + ft_strlen(s2) + ft_strlen(s3) + 1;
	str = malloc(sizeof(char) * len);
	if (!str)
		return (NULL);
	ft_strlcpy(str, s1, len);
	ft_strlcat(str, s2, len);
	ft_strlcat(str, s3, len);
}
