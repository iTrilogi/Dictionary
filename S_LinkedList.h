#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NODE struct node
#define NEXT current->link
#define HEAD_NEXT head->link
#define MALLOC(size) malloc(sizeof(size)*4)

NODE *addToEmpty(NODE *head, void* data);

NODE *add_at_end(NODE *current, void* data); 
NODE *add_at_beg(NODE *head, int d);        
NODE *add_at_pos(NODE *head, int data, int pos);

NODE *del_first(NODE *head); 
NODE *del_last(NODE *head);
NODE *del_at_pos(NODE *head, int position);
NODE *del_list(NODE *head);

NODE *reverse(NODE *head);

typedef struct node
{
    void *data;
    NODE *link;
} node_t;


NODE *addToEmpty(NODE *head, void* data)
{
    NODE *temp = MALLOC(NODE);
    temp->data = data;
    temp->link = NULL;

    head = temp;

    return head;
}

NODE *add_at_end(NODE *head, void* data)
{
    NODE *temp = MALLOC(NODE);
    NODE *c_head = head;
    while (c_head->link)
    {
        c_head = c_head->link;
    }

    temp->data = data;
    temp->link = NULL;
    c_head->link = temp;

    return temp;
}

// NODE *add_at_pos(NODE *head, int data, int pos)
// {
//     NODE *current = head;
//     NODE *current2 = MALLOC(NODE);
//     current2->data = data;
//     current2->link = NULL;

//     pos--;
//     while (pos != 1)
//     {
//         current = NEXT;
//         pos--;
//     }
//     current2->link = NEXT;
//     NEXT = current2;
//     return head;
// }

// NODE *add_at_beg(NODE *head, int d)
// {
//   
//     NODE *current = MALLOC(NODE);
//     current->data = d;
//     NEXT = NULL;

//     NEXT = head;
//     head = current;
//     return head;
// }

NODE *del_first(NODE *head)
{

    NODE *temp = head;
    head = HEAD_NEXT;
    free(temp);

    // if (!head)
    // {
    //     printf("List is now Empty");
    // }
    return head;
}

NODE *del_last(NODE *head)
{
    if (!head)
    {
        printf("List is already Empty");
    }
    else if (!HEAD_NEXT)
    {
        free(head);
        head = NULL;
        printf("List is now Empty");
    }
    else
    {
        NODE *temp = head;
        while (temp->link->link)
        {
            temp = temp->link;
        }
        free(temp->link);
        temp->link = NULL;
    }
    return head;
}

NODE *del_at_pos(NODE *head, int position)
{
    NODE *current = head;
    NODE *previous = head;

    if (!head)
    {
        printf("List is already empty!");
    }
     if (position == 1)
    {
        head = NEXT;
        free(current);
        current = NULL;
    }
    else
    {
        while (position != 1)
        {
            previous = current;
            current = NEXT;
            position--;
        }
        previous->link = NEXT;
        free(current);
        current = NULL;
    }
    return head;
}

// NODE *del_list(NODE *head)
// {
//     NODE *temp = head;

//     while (temp)
//     {
//         temp = temp->link;
//         free(head);
//         head = temp;
//     }

//     if (!head)
//     {
//         printf("Linked list deleted succesfully");
//     }

//     return head;
// }

// NODE *reverse(NODE *head)
// {
//     NODE *prev_node = NULL;
//     NODE *next_node = NULL;

//     while (head)
//     {
//         next_node = HEAD_NEXT;
//         HEAD_NEXT = prev_node;
//         prev_node = head;
//         head = next_node;
//     }
//     head = prev_node;

//     return head;
// }
