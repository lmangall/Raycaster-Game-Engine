
#include "animation.h"

void ft_lstadd_back(t_list **alst, t_list *new) {
  t_list *ptr;

  if (alst && *alst) {
    ptr = *alst;
    while (ptr->next)
      ptr = ptr->next;
    ptr->next = new;
  } else if (alst)
    *alst = new;
}