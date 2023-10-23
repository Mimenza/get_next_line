/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emimenza <emimenza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 11:00:51 by emimenza          #+#    #+#             */
/*   Updated: 2023/10/23 08:56:35 by emimenza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

	//clean all the nodes and create a new one if a jumpline is found;
void	ft_clean_list(t_list **list)
{
	t_list	*new_node;
	t_list	*last_node;
	char	*tmp;
	int		i;
	int		k;

	tmp = malloc(BUFFER_SIZE + 1);
	new_node = malloc(sizeof(t_list));
	if (!tmp || !new_node)
		return ;
	last_node = ft_list_last_node(*list);
	i = 0;
	k = 0;
	while (last_node->buffer[i] && last_node->buffer[i] != '\n')
		++i;
	while (last_node->buffer[i] && last_node->buffer[++i])
		tmp[k++] = last_node->buffer[i];
	tmp[k] = '\0';
	new_node->buffer = tmp;
	new_node->next = NULL;
	ft_free_list(list, new_node, tmp, 0);
}

	//returns a char containing the line clean
char	*ft_get_line(t_list *list)
{
	char	*line;
	int		size;

	if (!list)
		return (NULL);
	size = ft_size_to_newline(list);
	line = malloc(size + 1);
	if (!line)
		return (NULL);
	ft_copy_str(list, line);
	return (line);
}

	//create a new node and add to the list
void	ft_add_to_list(int fd, t_list **list, char *buf)
{
	t_list	*new_node;
	t_list	*last_node;

	last_node = ft_list_last_node(list[fd]);
	new_node = malloc(sizeof(t_list));
	if (!new_node)
		return ;
	if (!last_node)
		list[fd] = new_node;
	else
		last_node->next = new_node;
	new_node->buffer = buf;
	new_node->next = NULL;
}

	//create a list with the buffer information
void	ft_create_list(t_list **list, int fd)
{
	char	*buffer;
	int		bytes;

	while (!ft_found_newline(list[fd]))
	{
		buffer = malloc(BUFFER_SIZE + 1);
		if (!buffer)
			return ;
		bytes = read(fd, buffer, BUFFER_SIZE);
		if (bytes == 0)
		{
			free(buffer);
			return ;
		}
		if (bytes == -1)
		{
			ft_free_list(&list[fd], NULL, NULL, 1);
			free(buffer);
			return ;
		}
		buffer[bytes] = '\0';
		ft_add_to_list(fd, list, buffer);
	}
}

char	*get_next_line(int fd)
{
	static t_list	*list[4096];
	char			*line;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, &line, 0) < 0 || fd > 4096)
		return (NULL);
	ft_create_list(list, fd);
	if (list[fd] == NULL)
		return (NULL);
	line = ft_get_line(list[fd]);
	ft_clean_list(&list[fd]);
	return (line);
}
