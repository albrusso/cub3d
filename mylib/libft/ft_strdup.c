/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albrusso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 14:03:46 by albrusso          #+#    #+#             */
/*   Updated: 2024/04/08 14:08:10 by albrusso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_strdup(const char *s1)
{
	char		*tmp;
	size_t		len;

	len = ft_strlen(s1) + 1;
	tmp = (char *)ft_calloc(sizeof(char), len);
	if (!tmp)
		return (NULL);
	return ((char *)ft_memcpy(tmp, s1, len));
}
