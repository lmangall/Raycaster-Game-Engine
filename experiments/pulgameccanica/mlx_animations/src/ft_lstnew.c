#include "animations.h"

t_list *ft_lstnew(void *content) {
  t_list *elt;

  if (!(elt = (t_list *)malloc(sizeof(*elt))))
    return (NULL);
  elt->content = content;
  elt->next = NULL;
  return (elt);
}