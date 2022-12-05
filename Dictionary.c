#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "S_LinkedList.h"

enum typeData
{
    INT,
    CHAR,
    FLOAT,
    DOUBLE
};

size_t djb33x_hash(const char *key, const size_t keylen)
{
    size_t hash = 5381;
    for (size_t i = 0; i < keylen; i++)
    {
        hash = ((hash << 5) + hash) ^ key[i];
    }
    return hash;
}

struct set_node
{
    void *key;
    struct set_node *next;
    size_t key_len;
    void *value;
    int typeData; //for debugging print
};
struct set_table
{
    struct set_node **nodes;
    size_t hashmap_size;
};

struct set_table *set_table_new(const size_t hashmap_size)
{
    struct set_table *table = malloc(sizeof(struct set_table));
    if (!table)
    {
        return NULL;
    }
    table->hashmap_size = hashmap_size;
    table->nodes = calloc(table->hashmap_size, sizeof(struct set_node *));
    if (!table->nodes)
    {
        free(table);
        return NULL;
    }
    return table;
}
struct set_node *search_at_index(struct set_table *table, void *key, const size_t key_len, size_t hashmap_size)
{
    size_t index = djb33x_hash(key, key_len) % hashmap_size;

    struct set_node *current_node = table->nodes[index];

    while (current_node)
    {
        if (current_node->key == key)
        {
            printf("Got you: %p \n", current_node->key);
            return current_node;
        }
        current_node = current_node->next;
    }
    printf("Search not found\n");

    return current_node;
}

void print_by_data(struct set_node *current, size_t index)
{

    switch (current->typeData)
    {
    case INT:
        printf("Index: [%zu]\t Key: [%d]\t Value: [%s]\n", index, *((int *)current->key), (char*)current->value);
        break;
    case CHAR:
        printf("Index: [%zu]\t Key: [%s]\t Value: [%d]\n", index, (char *)current->key, *((int *)current->value));
        break;
    case FLOAT:
        printf("Index: [%zu]\t Key: [%f]\t Value: [%f]\n", index, *((float *)current->key), *((float*)current->value));
        break;
    case DOUBLE:
        printf("Index: [%zu]\t key: [%lf]\t Value: [%f]\n", index, *((double *)current->key), *((double*)current->value));
        break;
    default:
        printf("PIZZAAA \n");
        break;
    }
}

int *set_insert(struct set_table *table, void *key, const size_t key_len, void *value, int typeData)
{
    size_t hash = djb33x_hash(key, key_len);
    size_t index = hash % table->hashmap_size;
    struct set_node *head = table->nodes[index];
    struct set_node *current = table->nodes[index];

    while (head)
    {
        if (current->key == key)
        {
            return NULL;
        }
        head = head->next;
    }

    if (!table->nodes[index])
    {
        table->nodes[index] = (struct set_node *)addToEmpty((node_t *)table->nodes[index], key);
        table->nodes[index]->key_len = key_len;
        table->nodes[index]->value = value;
        table->nodes[index]->typeData = typeData;
    }
    else
    {
        current = (struct set_node *)add_at_end((node_t *)table->nodes[index], key);
        current->key_len = key_len;
        current->value = value;
        current->typeData = typeData;
    }
    return 0;
}

int remove_at_index(struct set_table *table, void *key, const size_t key_len, size_t hashmap_size)
{
    size_t index = djb33x_hash(key, key_len) % hashmap_size;

    struct set_node *current_node = table->nodes[index];
    struct set_node *previous_node;
    int counter = 0;
    while (current_node)
    {
        if (current_node->key == key)
        {
            if (!current_node->next)
            {
                //printf("Removed the last Key \"%p\" at index [%zu]\n", current_node->key, index);
                table->nodes[index] = (struct set_node *)del_last((node_t *)table->nodes[index]);
                return 0;
            }
            else if (!previous_node)
            {
                //printf("Removed the first Key \"%p\" at index [%zu]\n", current_node->key, index);
                table->nodes[index] = (struct set_node *)del_first((node_t *)table->nodes[index]);
                return 0;
            }
            else
            {
                //printf("Removed a mid Key \"%p\" at index [%zu]\n", current_node->key, index);
                table->nodes[index] = (struct set_node *)del_at_pos((node_t *)table->nodes[index], counter);
                return 0;
            }
        }
        counter++;
        previous_node = current_node;
        current_node = current_node->next;
    }
    printf("Remove not found\n");
    return -1;
}
void print(struct set_table *table)
{

    for (size_t i = 0; i < table->hashmap_size; i++)
    {
        struct set_node *current = table->nodes[i];

        while (current)
        {
            print_by_data(current, i);
            current = current->next;
        }
    }
}
int main(int argc, char const *argv[])
{
    int hashmap_size = 2, node_value = 1, i_key = 7, i_key2 = 17, i_key3 = 23;

    char ciao[] = "Ciao", gatto[] = "Gatto", value[] = "Hello";
    float f_key = 25.2593, f_value = 21.4;
    double d_key = 3.64, d_value = 7.17;
    struct set_table *table = set_table_new(hashmap_size);

    set_insert(table, &i_key, sizeof(int), &value, INT);
    set_insert(table, ciao, 4, &node_value, CHAR);
    set_insert(table, &f_key, sizeof(float), &f_value, FLOAT);
    set_insert(table, &i_key2, sizeof(int), &value, INT);
    set_insert(table, &d_key, sizeof(double), &d_value, DOUBLE);

    set_insert(table, &i_key3, sizeof(int), &value, INT);
    set_insert(table, gatto, 5, &node_value, CHAR);


    remove_at_index(table, &gatto, 5, hashmap_size);
    //remove_at_index(table, &i_key, sizeof(int), hashmap_size);

    search_at_index(table, &ciao, 4, hashmap_size);
    //search_at_index(table, &i_key2, sizeof(int), hashmap_size);


    print(table);

    return 0;
}
