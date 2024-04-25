// test linkedlist ************************

// compil avec gcc testLibft.c libft.a

#include <stdlib.h>
#include <unistd.h>
#include "libft.h"
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>

static void print(t_list *elem)
{
    int len;

    len = 0;
    while (((char *)elem->content)[len])
        len++;
    write(1, ((char *)elem->content), len);
    write(1, "\n", 1);
}

static void print_all(t_list *elem)
{
    print(elem);
    while (elem->next)
    {
        elem = elem->next;
        print(elem);
    }
}

static void del(void *content)
{
    free(content);
}

static void *transform_content(void *content)
{
    // Check if the content pointer is valid
    if (content == NULL)
        return NULL;

    char *str = (char *)content;
    char *result = strdup(str); // Duplicate the original content
    // Convert each character in the duplicated string to uppercase
    for (size_t i = 0; result[i]; i++)
    { 
        if (i%2)
            result[i] = toupper(result[i]);
    }
    return result;
}

int main(void)
{
    t_list *elem;
    t_list *elem2;
    t_list *elem3;
    t_list *elem4;

    t_list *first;
    t_list *mapped;

    char *str = ft_strdup("lorem");
    char *str2 = ft_strdup("ipsum");
    char *str3 = ft_strdup("dolor");
    char *str4 = ft_strdup("sit");

    elem = ft_lstnew(str);
    elem2 = ft_lstnew(str2);
    elem3 = ft_lstnew(str3);
    elem4 = ft_lstnew(str4);

    

    if (!elem || !elem2 || !elem3 || !elem4)
        return (0);

    

    elem->next = elem2;
    elem2->next = elem3;
    elem3->next = elem4;

    first = elem;

    print_all(first);

    if (!(mapped = ft_lstmap(elem, &transform_content, &del)))
        return (0);
    if (mapped == first)
        write(1, "A new list is not returned\n", 27);

    print_all(mapped);
    print_all(first);

    ft_lstclear(&first, del);
    ft_lstclear(&mapped, del);

    if (!first)
        ft_putendl_fd("First deleted", 1);
        else
        ft_putendl_fd("First always there", 1);
    if (!elem)
        ft_putendl_fd("Elem deleted", 1);
    else
        ft_putendl_fd("Elem always there : OK - not set to Null", 1);
    if (!mapped)
        ft_putendl_fd("Mapped deleted", 1);
        else
        ft_putendl_fd("Mapped always there", 1);
  

    return (0);
}