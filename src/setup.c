/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albrusso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 14:52:44 by albrusso          #+#    #+#             */
/*   Updated: 2024/05/27 08:53:03 by albrusso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	is_dotcub(char *s)
{
	int	len;

	len = (int)ft_strlen(s);
	if (s[len - 3] != 'c' || s[len - 2] != 'u' || s[len - 1] != 'b')
		return (0);
	return (1);
}

void	setup(t_data *d, int argc, char *argv[])
{
	if (argc != 2 || !is_dotcub(argv[1]))
		handle_error(d, "To run: ./cub3d path/to/map.cub");
	initialize(d, argv[1]);
}
