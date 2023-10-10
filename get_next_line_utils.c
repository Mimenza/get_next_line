/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emimenza <emimenza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 09:22:23 by emimenza          #+#    #+#             */
/*   Updated: 2023/10/10 13:39:06 by emimenza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

	//CLEANS ALL THE NODES OF THE LIST AND SET NEW NODE AS FIRST IF HAS SMTH
void	free_list(t_list **list, t_list *new_node, char *buf, int mode)
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

	//COPY THE CONTENT OF THE NODES OF THE LIST IN STR TILL THE JUMP LINE
void	copy_str(t_list *list, char *str)
{
	int	i;
	int	k;

	if (list == NULL)
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
int	size_to_newline(t_list *list)
{
	int	count;
	int	i;

	if (list == NULL)
		return (0);
	count = 0;
	while (list)
	{
		i = 0;
		while (list->buffer[i])
		{
			if (list->buffer[i] == '\n')
			{
				count ++;
				return (count);
			}
			count++;
			i++;
		}
		list = list->next;
	}
	return (count);
}

	//FOUND IF THERES ANY JUMP LINE IN ANY OF THE NODES
int	found_newline(t_list *list)
{
	int	i;

	if (NULL == list)
		return (0);
	while (list)
	{
		i = 0;
		while (list->buffer[i] && i < BUFFER_SIZE)
		{
			if (list->buffer[i] == '\n')
			{
				return (1);
			}
			i++;
		}
		list = list->next;
	}
	return (0);
}

	//RETURN THE LAST NODE OF THE LIST 
t_list	*list_last_node(t_list *lst)
{
	while (lst)
	{
		if (!lst->next)
			return (lst);
		lst = lst->next;
	}
	return (lst);
}
