/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_copy.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mburgler <mburgler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 18:40:53 by mburgler          #+#    #+#             */
/*   Updated: 2023/11/01 23:23:55 by mburgler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

// //kill getenv
// //change free_stuff.c line 24 & 64

//void	ft_print_env(t_env *env); //Just for testing; delete from final version

void	dup_env_head(t_msc *msc, char **org_env)
{
	t_env	*tmp;
	int		i;

	i = 0;
	if (!org_env || !org_env[i])
		return (dup_env_error(msc, NULL));
	msc->dup_env = ft_dup_envnew(org_env[i], msc);
	while (org_env[++i])
	{
		tmp = ft_dup_envnew(org_env[i], msc);
		ft_envadd_back(&msc->dup_env, tmp);
	}
	//ft_print_env(msc->dup_env); //Just for testing; delete from final version
	//ft_print2d(org_env); //Just for testing; delete from final version
	//printf("### TESTING END ###\n");
}

t_env	*ft_dup_envnew(char *str, t_msc *msc)
{
	t_env	*ret;
	int		i_split;

	ret = malloc(sizeof(t_env));
	if (!ret)
		dup_env_error(msc, NULL);
	ret->key = NULL;
	ret->value = NULL;
	i_split = ft_strchr_i(str, '=');
	if (i_split == -1)
		return (NULL);
	ret->key = ft_substr(str, 0, i_split);
	if (!ret->key)
		dup_env_error(msc, ret);
	if (str[i_split + 1])
	{
		ret->value = ft_substr(str, i_split + 1, ft_strlen(str) - i_split);
		if (!ret->value)
			dup_env_error(msc, ret);
	}	
	ret->next = NULL;
	ret->msc = msc;
	return (ret);
}

void	dup_env_error(t_msc *msc, t_env *current_node)
{
	if (current_node)
	{
		if (current_node->key)
			free(current_node->key);
		if (current_node->value)
			free(current_node->value);
		free(current_node);
	}
	if (msc->dup_env)
		ft_envclear(&msc->dup_env);
	free(msc);
	exit(1);
}

//JUST FOR TESTING; DELETE FROM FINAL VERSION

void	ft_print_env(t_env *env)
{
	t_env	*tmp;

	tmp = env;
	printf("### Printing env (START):\n");
	while (tmp)
	{
		printf("key: %s\n", tmp->key);
		printf("value: %s\n", tmp->value);
		tmp = tmp->next;
	}
	printf("### Printing env (END):\n");
}