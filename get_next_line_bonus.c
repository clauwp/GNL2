#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include "get_next_line_bonus.h"

char	*get_next_line(int fd)
{
	static t_list	**lst_arr;
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

int	ft_has_nl(char *buf)
{
	int	len;

	len = 0;
	if (buf == NULL)
		return (0);
	while (*buf != '\n' && *buf != 0)
	{
		len++;
		buf++;
	}
	if (*buf == '\n')
		return (len);
	else
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
