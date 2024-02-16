#include "animation.h"

t_list *ft_lstget(t_list *lst, int index) {
  t_list *n;
  int i;

  i = 0;
  n = lst;
  if (n == NULL)
    return (NULL);
  if (n->next == NULL)
    return (n);
  while (n != NULL) {
    if (i >= index)
      return (n);
    n = n->next;
    i++;
  }
  return (NULL);
}