#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new_list)
{
	t_list	*lst_last;

	if (lst)
	{
		if (*lst)
		{
			lst_last = ft_lstlast(*lst);
			lst_last->next = new_list;
		}
		else
			*lst = new_list;
	}
}
