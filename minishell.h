/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miandrad <miandrad@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 13:40:10 by apereira          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2023/03/28 16:40:27 by apereira         ###   ########.fr       */
=======
/*   Updated: 2023/03/28 15:45:34 by miandrad         ###   ########.fr       */
>>>>>>> 56b1de3169b8ef3910aed0ead5ea2c7bb849b26b
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "libft/libft.h"
# include "ft_printf/ft_printf.h"

<<<<<<< HEAD
char	*check_valid_cmd(char *argv, char **envp);

=======
char	*check_cmd(char *cmd1, char **env);
>>>>>>> 56b1de3169b8ef3910aed0ead5ea2c7bb849b26b

#endif