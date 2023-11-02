/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mburgler <mburgler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 23:02:36 by mburgler          #+#    #+#             */
/*   Updated: 2023/11/01 23:17:29 by mburgler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	ft_envadd_back(t_env **lst, t_env *new)
{
	t_env	*tmp;

	if (lst && new)
	{
		if (*lst)
		{
			tmp = ft_envlast(*lst);
			tmp->next = new;
		}
		else
			*lst = new;
	}
}

t_env	*ft_envlast(t_env *lst)
{
	if (lst != NULL)
	{
		while (lst->next)
			lst = lst->next;
	}
	return (lst);
}

void	ft_envclear(t_env **lst)
{
	t_env	*tmp;

	if (!lst || !(*lst))
		return ;
	while (lst && *lst)
	{
		tmp = (*lst)->next;
		if ((*lst)->key)
			free((*lst)->key);
		if ((*lst)->value)
			free((*lst)->value);
		free(*lst);
		*lst = tmp;
	}
	*lst = NULL;
}