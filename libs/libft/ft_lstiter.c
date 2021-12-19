#include "libft.h"

void	ft_lstiter(t_list *lst, void (*f)(void *))
{
	t_list	*lst_temp;

	lst_temp = lst;
	while (lst_temp)
	{
		(*f)(lst_temp->content);
		lst_temp = lst_temp->next;
	}
}
