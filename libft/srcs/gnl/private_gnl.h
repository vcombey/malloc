/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   private_gnl.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcombey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/17 17:00:21 by vcombey           #+#    #+#             */
/*   Updated: 2018/06/17 17:00:28 by vcombey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PRIVATE_GNL_H
# define PRIVATE_GNL_H

# include <stdlib.h>
# include <unistd.h>

# define BUFF_SIZE 			128
# define MAX_DESCRIPTORS   	65536

typedef struct		s_buffer
{
	int				fd;
	int				buff_size;
	size_t			l_size;
	char			buffer[BUFF_SIZE + 1];
}					t_buffer;

#endif
