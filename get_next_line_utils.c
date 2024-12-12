/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agarbacz <agarbacz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 11:55:59 by agarbacz          #+#    #+#             */
/*   Updated: 2024/12/12 14:49:10 by agarbacz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strchr(const char *s, int c)
{
	while (*s)
	{
		if (*s == (char)c)
			return ((char *)s);
		s++;
	}
	if (c == '\0')
		return ((char *)s);
	return (NULL);
}

size_t ft_strlen(const char *str) {
    size_t len;

	len = 0;
    while (str[len] != '\0')
        len++;
    return len;
}

char *ft_strjoin(char const *s1, char const *s2)
{
    size_t s1_len;
    size_t s2_len;
	size_t i = 0;
    char *result;

    if (!s1 || !s2)
        return NULL;

    s1_len = ft_strlen(s1);
    s2_len = ft_strlen(s2);

    result = (char *)malloc((s1_len + s2_len + 1) * sizeof(char));
    if (!result)
        return NULL;
    while (i < s1_len)
    {
        result[i] = s1[i];
        i++;
    }
    size_t j = 0;
    while (j < s2_len)
    {
        result[i + j] = s2[j];
        j++;
    }
    return result;
}