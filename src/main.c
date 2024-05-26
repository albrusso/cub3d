/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albrusso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 14:49:49 by albrusso          #+#    #+#             */
/*   Updated: 2024/05/26 13:04:40 by albrusso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	main(int argc, char *argv[])
{
	t_data	d;

	setup(&d, argc, argv);
	initialize(&d, argv[1]);
	loop(&d);
	cleanup(&d);
	return (EXIT_SUCCESS);
}