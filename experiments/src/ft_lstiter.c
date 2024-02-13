#include "animations.h"

void ft_lstiter(t_list *lst, void (*f)(void *)) {
  if (!lst)
    return;
  while (lst) {
    f(lst->content);
    lst = lst->next;
  }
}