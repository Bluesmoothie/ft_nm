/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygille <ygille@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 13:43:10 by ygille            #+#    #+#             */
/*   Updated: 2025/05/01 14:08:30 by ygille           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

int	main(int argc, char **argv)
{
	if (argc == 1)
		ft_nm("a.out");
	else for (int i = 1;i < argc;i++)
		ft_nm(argv[i]);
	return (0);
}

int	pexit(char *msg)
{
	perror(msg);
	exit(errno);
}
