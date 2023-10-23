/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emimenza <emimenza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 09:22:02 by emimenza          #+#    #+#             */
/*   Updated: 2023/10/23 09:00:27 by emimenza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 5
# endif

# include <fcntl.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>

typedef struct s_list
{
	char			*buffer;
	struct s_list	*next;
}				t_list;

int		ft_found_newline(t_list *list);
t_list	*ft_list_last_node(t_list *list);
char	*ft_get_line(t_list *list);
void	ft_copy_str(t_list *list, char *str);
int		ft_size_to_newline(t_list *list);
void	ft_clean_list(t_list **list);
char	*get_next_line(int fd);
void	ft_free_list(t_list **list, t_list *clean_node, char *buf, int mode);
void	ft_create_list(t_list **list, int fd);

#endif