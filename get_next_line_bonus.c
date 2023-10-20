/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emimenza <emimenza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 11:00:51 by emimenza          #+#    #+#             */
/*   Updated: 2023/10/19 10:18:58 by emimenza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

	//clean all the nodes and create a new one if a jumpline is found;
void	clean_list(t_list **list)
{
	t_list	*new_node;
	t_list	*last_node;
	char	*tmp;
	int		i;
	int		k;

	tmp = malloc(BUFFER_SIZE + 1);
	new_node = malloc(sizeof(t_list));
	if (tmp == NULL || new_node == NULL)
		return ;
	last_node = list_last_node(*list);
	i = 0;
	k = 0;
	while (last_node->buffer[i] && last_node->buffer[i] != '\n')
		++i;
	while (last_node->buffer[i] && last_node->buffer[++i])
		tmp[k++] = last_node->buffer[i];
	tmp[k] = '\0';
	new_node->buffer = tmp;
	new_node->next = NULL;
	free_list(list, new_node, tmp, 0);
}

	//returns a char containing the line clean
char	*ft_get_line(t_list *list)
{
	char	*line;
	int		size;

	if (list == NULL)
		return (NULL);
	size = size_to_newline(list);
	line = malloc(size + 1);
	if (!line)
		return (NULL);
	copy_str(list, line);
	return (line);
}

	//create a new node and add to the list
void	add_to_list(int fd, t_list **list, char *buf)
{
	t_list	*new_node;
	t_list	*last_node;

	last_node = list_last_node(list[fd]);
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
void	create_list(t_list **list, int fd)
{
	char	*buffer;
	int		bytes;

	while (!found_newline(list[fd]))
	{
		buffer = malloc(BUFFER_SIZE + 1);
		if (buffer == NULL)
			return ;
		bytes = read(fd, buffer, BUFFER_SIZE);
		if (bytes == 0)
		{
			free(buffer);
			return ;
		}
		if (bytes == -1)
		{
			free_list(&list[fd], NULL, NULL, 1);
			free(buffer);
			return ;
		}
		buffer[bytes] = '\0';
		add_to_list(fd, list, buffer);
	}
}

char	*get_next_line(int fd)
{
	static t_list	*list[4096];
	char			*line;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, &line, 0) < 0 || fd > 4096)
		return (NULL);
	create_list(list, fd);
	if (list[fd] == NULL)
		return (NULL);
	line = ft_get_line(list[fd]);
	clean_list(&list[fd]);
	return (line);
}

// int	main(void)
// {
// 	int fd;
// 	char	*tmp;

// 	tmp = "a";
// 	fd =  open("file1.txt", O_RDWR);
// 	while(tmp)
// 	{
// 		tmp = get_next_line(fd);
// 		printf("%s", tmp);
// 	}
// }