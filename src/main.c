/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygille <ygille@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 13:43:10 by ygille            #+#    #+#             */
/*   Updated: 2025/05/02 16:30:01 by ygille           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

/*
**	Process arguments, one by one
**	defaulting to a.out if no arguments provided
*/
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
