/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apereira <apereira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 08:09:14 by apereira          #+#    #+#             */
/*   Updated: 2023/04/03 08:14:17 by apereira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char *ft_strndup(const char *s, size_t n) 
{
    size_t len = ft_strlen(s);
    if (n < len) {
        len = n;
    }

    char *new_str = (char *)malloc(len + 1);
    if (new_str == NULL) {
        return NULL;
    }

    ft_memcpy(new_str, s, len);
    new_str[len] = '\0';

    return new_str;
}
