#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
typedef struct s_list{
	int				fd;
	char			*str;
	struct s_list	*next_list;
} t_list;
char	*get_next_line(int fd);
#endif