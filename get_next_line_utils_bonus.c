#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include "get_next_line_bonus.h"

char	*ft_returnline(char *current_buf)
{
	char	*retstr;
	char	*copy_retstr;
	int		i;

	i = 0;
	if (current_buf == NULL)
		return (NULL);
	while (current_buf[i] != '\n' && current_buf[i] != 0)
		i++;
	if (current_buf[i] == '\n')
		i += 1;
	retstr = (char *)malloc(i + 1);
	if (retstr == NULL)
		return (NULL);
	copy_retstr = retstr;
	while (i-- > 0)
		*copy_retstr++ = *current_buf++;
	*copy_retstr = 0;
	return (retstr);
}

char	*ft_nextstr(char *current_buf)
{
	char	*retstr;
	char	*copy_retstr;
	char	*copy_buf;

	if (current_buf == NULL)
		return (NULL);
	copy_buf = current_buf;
	retstr = NULL;
	while (*current_buf != '\n' && *current_buf != 0)
		current_buf++;
	if (*current_buf == '\n')
		current_buf++;
	if (ft_strlen(current_buf) != 0)
	{
		retstr = (char *)malloc(ft_strlen(current_buf) + 1);
		if (retstr == NULL)
			return (NULL);
		copy_retstr = retstr;
		while (*current_buf != 0)
			*copy_retstr++ = *current_buf++;
		*copy_retstr = 0;
	}
	free(copy_buf);
	return (retstr);
}

t_list	**ft_cleanlst(t_list **lst_arr)
{
	t_list	**copy_lstarr;
	t_list	*temp_lst;

	copy_lstarr = lst_arr;
	while (*lst_arr != NULL)
	{
		if ((*lst_arr)->str == NULL)
		{
			temp_lst = (*lst_arr)->next_list;
			free(*lst_arr);
			*lst_arr = temp_lst;
		}
		else
			lst_arr = &((*lst_arr)->next_list);
	}
	if (*copy_lstarr == NULL)
	{
		free(lst_arr);
		return (NULL);
	}
	return (copy_lstarr);
}

t_list	**ft_getlist(int fd, t_list **lst_arr)
{
	t_list	*lst_ptr;

	while (*lst_arr != NULL)
	{
		if ((*lst_arr)->fd == fd)
			return (lst_arr);
		lst_arr = &((*lst_arr)->next_list);
	}
	lst_ptr = (t_list *)malloc(sizeof(t_list));
	lst_ptr->fd = fd;
	lst_ptr->str = NULL;
	lst_ptr->next_list = NULL;
	*lst_arr = lst_ptr;
	return (lst_arr);
}
