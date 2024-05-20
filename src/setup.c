/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albrusso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 14:52:44 by albrusso          #+#    #+#             */
/*   Updated: 2024/05/20 16:24:34 by albrusso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	setup(t_data *d, int argc, char *argv[])
{
	if (argc != 2 /*|| !is_dotcub(argv[1])*/)
		handle_error(d, "To run: ./cub3d path/to/map.cub");
	initialize(d, argv[1]);
}