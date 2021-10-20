#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include "get_next_line.h"

char	*ft_returnline(char *current_buf);
char	*ft_nextstr(char *current_buf);
t_list	**ft_cleanlst(t_list **lst_arr);
t_list	**ft_getlist(int fd, t_list **lst_arr);
int	ft_has_nl(char *buf);
char	*ft_newbuf(int fd);
char	*ft_concat(char *old_buf, char *new_buf);
int	ft_strlen(char *str);

char	*get_next_line(int fd)
{
	static	t_list	**lst_arr;
	t_list			**lst_ptr;
	char			*current_buf;
	char			*new_buf;

	if (lst_arr == NULL)
	{
		lst_arr = (t_list **)malloc(sizeof(t_list *));
		*lst_arr = NULL;
	}
	lst_ptr = ft_getlist(fd, lst_arr);
	current_buf = (*lst_ptr)->str;
	while (ft_has_nl(current_buf) == 0)
	{
		new_buf = ft_newbuf(fd);
		if (new_buf == NULL)
			break ;
		current_buf = ft_concat(current_buf, new_buf);
	}
	new_buf = ft_returnline(current_buf);
	(*lst_ptr)->str = ft_nextstr(current_buf);
	lst_arr = ft_cleanlst(lst_arr);
	return (new_buf);
}

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

int	ft_has_nl(char *buf)
{
	int	len;

	len = 0;
	if (buf == NULL)
		return (0);
	while (*buf != '\n' && *buf != 0)
	{
		len++;
		if (*buf == '\n')
			return (len);
		buf++;
	}
	return (0);
}

char	*ft_newbuf(int fd)
{
	char	*buf;
	char	*retstr;
	int		i;
	int		byte;

	buf = (char *)malloc(sizeof(char) * BUFFER_SIZE);
	byte = read(fd, buf, BUFFER_SIZE);
	printf("byte= %d\n",byte);
	if (byte <= 0)
	{
		free(buf);
		return (NULL);
	}
	retstr = (char *)malloc(sizeof(char) * (byte + 1));
	if (retstr == NULL)
		return (NULL);
	i = 0;
	while (byte-- > 0)
	{
		retstr[i] = buf[i];
		i++;
	}
	retstr[i] = 0;
	printf("retstr= %s", retstr);
	free(buf);
	return (retstr);
}

int	ft_strlen(char *str)
{
	int	len;

	len = 0;
	if (str == NULL)
		return (0);
	while (*str++)
		len++;
	return (len);
}

char	*ft_concat(char *old_buf, char *new_buf)
{
	char	*retstr;
	char	*copy_retstr;
	char	*copy_buf;

	retstr = (char *)malloc(ft_strlen(old_buf) + ft_strlen(new_buf) + 1);
	if (retstr == NULL)
		return (NULL);
	copy_buf = old_buf;
	copy_retstr = retstr;	
	while (old_buf && *old_buf)
		*copy_retstr++ = *old_buf++;
	free(copy_buf);
	copy_buf = new_buf;
	while (*new_buf)
		*copy_retstr++ = *new_buf++;
	free(copy_buf);
	*copy_retstr = 0;
	return (retstr);
}