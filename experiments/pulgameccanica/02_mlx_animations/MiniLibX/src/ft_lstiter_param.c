#include "animation.h"

void ft_lstiter_param(t_list *lst, void (*f)(void *, void *), void *ptr) {
  t_list *temp;

  temp = lst;
  while (temp != NULL) {
    f(temp->content, ptr);
    temp = temp->next;
  }
}