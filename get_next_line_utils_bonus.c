/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emimenza <emimenza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 11:01:04 by emimenza          #+#    #+#             */
/*   Updated: 2023/10/23 08:44:06 by emimenza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

	//CLEANS ALL THE NODES OF THE LIST AND SET NEW NODE AS FIRST IF HAS SMTH
void	ft_free_list(t_list **list, t_list *new_node, char *buf, int mode)
{
	t_list	*tmp;

	if (*list == NULL)
		return ;
	while (*list)
	{
		tmp = (*list)->next;
		if (mode == 1)
			*((*list)->buffer) = 0;
		free((*list)->buffer);
		free(*list);
		*list = tmp;
	}
	*list = NULL;
	if (new_node && new_node->buffer[0])
		*list = new_node;
	else
	{
		if (buf)
			free(buf);
		if (new_node)
			free(new_node);
	}
}

	//COPY THE buffer OF THE NODES OF THE LIST IN STR TILL THE JUMP LINE
void	ft_copy_str(t_list *list, char *str)
{
	int	i;
	int	k;

	if (!list)
		return ;
	k = 0;
	while (list)
	{
		i = 0;
		while (list->buffer[i])
		{
			if (list->buffer[i] == '\n')
			{
				str[k++] = '\n';
				str[k] = '\0';
				return ;
			}
			str[k++] = list->buffer[i++];
		}
		list = list->next;
	}
	str[k] = '\0';
}

	//RETURNS THE NBR OF CHARS TILL THE JUMP LINE
int	ft_size_to_newline(t_list *list)
{
	t_list	*current;
	int		count;
	char	*buffer;

	current = list;
	count = 0;
	while (current != NULL)
	{
		buffer = current->buffer;
		while (*buffer != '\0')
		{
			if (*buffer == '\n')
			{
				count++;
				return (count);
			}
			count++;
			buffer++;
		}
		current = current->next;
	}
	return (count);
}

	//FOUND IF THERES ANY JUMP LINE IN ANY OF THE NODES
int	ft_found_newline(t_list *list)
{
	t_list	*current;
	char	*buffer;

	current = list;
	while (current != NULL)
	{
		buffer = current->buffer;
		while (*buffer != '\0')
		{
			if (*buffer == '\n')
			{
				return (1);
			}
			buffer++;
		}
		current = current->next;
	}
	return (0);
}

	//RETURN THE LAST NODE OF THE LIST 
t_list	*ft_list_last_node(t_list *lst)
{
	while (lst)
	{
		if (!lst->next)
			return (lst);
		lst = lst->next;
	}
	return (lst);
}
