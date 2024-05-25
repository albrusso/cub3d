/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albrusso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 14:49:49 by albrusso          #+#    #+#             */
/*   Updated: 2024/05/25 17:03:04 by albrusso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	main(int argc, char *argv[])
{
	t_data	d;
	int		i;

	if (argc != 2)
		return (write(1, "Error: Bad args\n", 16));
	i = ft_strlen(argv[1]);
	if (argv[1][i - 3] != 'c' || argv[1][i - 2] != 'u' || argv[1][i - 1] != 'b')
		return (write(1, "Error: Bad ext\n", 15));
	initialize(&d, argv[1]);
	loop(&d);
	cleanup(&d);
	return (EXIT_SUCCESS);
}