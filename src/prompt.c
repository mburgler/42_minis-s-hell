/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mburgler <mburgler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 20:20:16 by mburgler          #+#    #+#             */
/*   Updated: 2023/09/20 20:50:34 by mburgler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void set_custom_cwd(t_msc *msc)
{
    char *home_dir;
    char *cwd;
	char *pos;

    home_dir = getenv("HOME");
    cwd = getcwd(NULL, 0);
    if (home_dir && cwd)
    {
        pos = ft_strnstr(cwd, home_dir, ft_strlen(home_dir));
        if (pos)
        {
            msc->env_custom_cwd = ft_strjoin("~", pos + ft_strlen(home_dir));
            free(cwd);
            return;
        }
    }
    else if (!home_dir && cwd)
    {
        msc->env_custom_cwd = cwd;
		free(cwd);
        return;
    }
    else
        msc->env_custom_cwd = "";
}

void	set_prompt_and_cwd(t_msc *msc)
{
	char 	*tmp;
	char	*tmp2;

	msc->env_cwd = getcwd(NULL, 0);
	if(msc->env_user == NULL)
		msc->env_user = "guest";
	tmp = ft_strjoin(msc->env_user, "@minishell ");
	if(!tmp)
	{
		write(2, "Error: malloc failed\n", 22);
		free_all(msc);
		exit(1);
	}
	set_custom_cwd(msc);
	tmp2 = ft_strjoin(tmp, msc->env_custom_cwd);
	free(tmp);
	if(!tmp2)
	{
		write(2, "Error: malloc failed\n", 22);
		free_all(msc);
		exit(1);
	}
	msc->prompt = ft_strjoin(tmp2, " $ ");
	free(tmp2);
}
