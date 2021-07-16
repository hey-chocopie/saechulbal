/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoylee <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/06 13:47:00 by hoylee            #+#    #+#             */
/*   Updated: 2020/07/07 20:23:37 by hoylee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_lstsize(t_list *lst)
{
	int		a;
	t_list	*temp;

	a = 0;
	temp = lst;
	while (temp != 0)
	{
		a++;
		temp = (*temp).next;
	}
	return (a);
}
