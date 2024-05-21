/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_char.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albrusso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 17:47:46 by albrusso          #+#    #+#             */
/*   Updated: 2024/03/19 13:48:38 by albrusso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_putchar(char c, t_sc *sc)
{
	sc->len += write (1, &c, 1);
}

void	ft_char(va_list arg, t_sc *sc)
{
	int	c;

	c = va_arg(arg, int);
	sc->len += write (1, &c, 1);
}
