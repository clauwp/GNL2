#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

typedef struct s_list{
	int				fd;
	char			*str;
	struct s_list	*next_list;
}	t_list;
char	*ft_returnline(char *current_buf);
char	*ft_nextstr(char *current_buf);
t_list	**ft_cleanlst(t_list **lst_arr);
t_list	**ft_getlist(int fd, t_list **lst_arr);
int		ft_has_nl(char *buf);
char	*ft_newbuf(int fd);
char	*ft_concat(char *old_buf, char *new_buf);
int		ft_strlen(char *str);
char	*get_next_line(int fd);
#endif