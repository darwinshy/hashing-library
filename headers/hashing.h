/* 
________________________________________________________________________________________
*   Hashing
-------------------------------------------------------------
*   Implemented for listed Data Structures 
*   1.  Integer 
*   2.  String (array of characters)
-------------------------------------------------------------
*  Hash Table
*   1.  Implementation through array
*   2.  Open and Closed Hashing
-------------------------------------------------------------
________________________________________________________________________________________
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/* 
________________________________________________________________________________________
*   Predefining some values
-------------------------------------------------------------
*   1.max_modulo value to prevent overflow of integer Value
*   2.max_capacity is maximum size of our Hash Table.
-------------------------------------------------------------
________________________________________________________________________________________
*/

#define max_modulo 10000007
#define max_capacity 60000

/* 
________________________________________________________________________________________
*   Defining Types of Structure and Functions
_________________________________________________________________________
*/

/*  Structs------------------------------------------------------*/

typedef struct HashTable_S HashTable_S;
typedef struct ht_item_string ht_item_string;
typedef struct LinkedList LinkedList;

/*  String-------------------------------------------------------*/

unsigned long hash_function_string(char *str);
HashTable_S *create_HT_string(int size);
ht_item_string *create_HT_item_string(char *key, char *value);
void insertTo_HT_string(HashTable_S *table, char *key, char *value);
void delete_HT_item_string(HashTable_S *table, char *key);
char *searchIn_HT_string(HashTable_S *table, char *key);

/*  Integer------------------------------------------------------*/

unsigned long hash_function_integer(int *int_value);

/*  Misc---------------------------------------------------------*/

void print_search(HashTable_S *table, char *key);
void print_table(HashTable_S *table);
void handle_collision_HT_string(HashTable_S *table, unsigned long index, ht_item_string *item);
static LinkedList **create_overflow_buckets(HashTable_S *table);
void free_overflow_buckets(HashTable_S *table);
void free_item(ht_item_string *item);
void free_table(HashTable_S *table);
LinkedList *allocate_list();
static void free_linkedlist(LinkedList *list);
LinkedList *linkedlist_insert(LinkedList *list, ht_item_string *item);
static ht_item_string *linkedlist_remove(LinkedList *list);

/* 
________________________________________________________________________________________
*   Hash Table (string)
-------------------------------------------------------------
*   Our hash table includes 3 items. 
*   1.  items, an array of pointers which themselves point to
*        ht_item_string, so it is a double-pointer.
*   2.  size, the user defined size of our hash table.
*   3.  count, the number of items currently in the hashtable
-------------------------------------------------------------
_____________________________________________________________
*/
struct HashTable_S
{
    ht_item_string **items;
    LinkedList **overflow_buckets;
    int size;
    int count;
};

/* 
________________________________________________________________________________________
*   Hash Table Item (ht_item_string)
-------------------------------------------------------------
*   This is an item that will be stored in out Hash Table.
*   We have two items in ht_item_string
*   1. key will contain the address of the value.
*   2. value will store the pointer to the data/string.
-------------------------------------------------------------
_____________________________________________________________
*/
struct ht_item_string
{
    char *key;
    char *value;
};
/* 
________________________________________________________________________________________
*   Linked List Struct for handling collisions
-------------------------------------------------------------
_____________________________________________________________
*/
struct LinkedList
{
    ht_item_string *item;
    LinkedList *next;
};
/*
_______________________________________________________________________________________
*   Hashing Function (Strings)
-------------------------------------------------------------
*       A very simple hash function, 
*       that is based on ASCII value of the string.
-------------------------------------------------------------
_____________________________________________________________
*/

unsigned long hash_function_string(char *str)
{
    unsigned long i = 0;
    for (int j = 0; str[j]; j++)
        i += str[j];
    return i % max_capacity;
}
/* 
________________________________________________________________________________________
*   Creating Hash Table for String (create_table_string)
-------------------------------------------------------------
*   This function assigns memory for the hash table.
*   By default the count of this hashtable is 0 ie number
*   of element in the table.
-------------------------------------------------------------
_____________________________________________________________
*/

HashTable_S *create_HT_string(int size)
{

    HashTable_S *table = (HashTable_S *)malloc(sizeof(HashTable_S));
    table->size = size;
    table->count = 0;
    table->items = (ht_item_string **)calloc(table->size, sizeof(ht_item_string *));
    for (int i = 0; i < table->size; i++)
        table->items[i] = NULL;
    table->overflow_buckets = create_overflow_buckets(table);

    return table;
}

/* 
________________________________________________________________________________________
*   Creating Hash Table Item for String (create_item_string)
-------------------------------------------------------------
*   Allocate memory using malloc function and assign
*   the pointer to ht_item_string. Same to the key
*   value. Assign the input values to allocated memory.
*   Return the newly created item.
-------------------------------------------------------------
_____________________________________________________________
*/

ht_item_string *create_HT_item_string(char *key, char *value)
{
    // Creates a pointer to a new hash table item
    ht_item_string *item = (ht_item_string *)malloc(sizeof(ht_item_string));
    item->key = (char *)calloc(strlen(key) + 1, sizeof(char));
    item->value = (char *)calloc(strlen(value) + 1, sizeof(char));

    strcpy(item->key, key);
    strcpy(item->value, value);

    return item;
}

/* 
________________________________________________________________________________________
*   Inserting hash item into the hash table. (ht_insert_s)
-------------------------------------------------------------
*   Create a hash item corresponding to the key and value.
*   he pointer to ht_item_string. Same to the key
*   value. Assign the input values to allocated memory.
*   Return the newly created item.
-------------------------------------------------------------
_____________________________________________________________
*/

void insertTo_HT_string(HashTable_S *table, char *key, char *value)
{
    // Create the item
    ht_item_string *item = create_HT_item_string(key, value);

    // Compute the index
    int index = hash_function_string(key);

    ht_item_string *current_item = table->items[index];

    if (current_item == NULL)
    {
        // Key does not exist.
        if (table->count == table->size)
        {
            // Hash Table Full
            printf("Insert Error: Hash Table is full\n");
            // Remove the create item
            free_item(item);
            return;
        }

        // Insert directly
        table->items[index] = item;
        table->count++;
    }

    else
    {
        // Scenario 1: We only need to update value
        if (strcmp(current_item->key, key) == 0)
        {
            free(table->items[index]->value);
            table->items[index]->value = (char *)calloc(strlen(value) + 1, sizeof(char));
            strcpy(table->items[index]->value, value);
            free_item(item);
            return;
        }

        else
        {
            // Scenario 2: Collision
            handle_collision_HT_string(table, index, item);
            return;
        }
    }
}

/* 
________________________________________________________________________________________
*   Searching in the hash table (ht_search_string)
-------------------------------------------------------------
*   Searches the key in the hashtable
*   and returns NULL if it doesn't exist
*   and also rnsure that we move to a non NULL item
-------------------------------------------------------------
_____________________________________________________________
*/
char *searchIn_HT_string(HashTable_S *table, char *key)
{
    int index = hash_function_string(key);
    ht_item_string *item = table->items[index];
    LinkedList *head = table->overflow_buckets[index];

    // Ensure that we move to items which are not NULL
    while (item != NULL)
    {
        if (strcmp(item->key, key) == 0)
            return item->value;
        if (head == NULL)
            return NULL;
        item = head->item;
        head = head->next;
    }
    return NULL;
}
/* 
________________________________________________________________________________________
*   Deletion from the Hash Table
-------------------------------------------------------------
*   Compute the hash index and get the item
*   Otherwise, after comparing keys, if there is no collision chain for that 
*    index, simply remove the item from the table
*   If a collision chain exists, we must remove that element and shift the 
*    links accordingly o(n)
-------------------------------------------------------------
_____________________________________________________________
*/
void delete_HT_item_string(HashTable_S *table, char *key)
{
    int index = hash_function_string(key);
    ht_item_string *item = table->items[index];
    LinkedList *head = table->overflow_buckets[index];

    if (item == NULL)
    {
        // Does not exist. Return
        return;
    }
    else
    {
        if (head == NULL && strcmp(item->key, key) == 0)
        {
            // No collision chain. Remove the item
            // and set table index to NULL
            table->items[index] = NULL;
            free_item(item);
            table->count--;
            return;
        }
        else if (head != NULL)
        {
            // Collision Chain exists
            if (strcmp(item->key, key) == 0)
            {
                // Remove this item and set the head of the list
                // as the new item

                free_item(item);
                LinkedList *node = head;
                head = head->next;
                node->next = NULL;
                table->items[index] = create_HT_item_string(node->item->key, node->item->value);
                free_linkedlist(node);
                table->overflow_buckets[index] = head;
                return;
            }

            LinkedList *curr = head;
            LinkedList *prev = NULL;

            while (curr)
            {
                if (strcmp(curr->item->key, key) == 0)
                {
                    if (prev == NULL)
                    {
                        // First element of the chain. Remove the chain
                        free_linkedlist(head);
                        table->overflow_buckets[index] = NULL;
                        return;
                    }
                    else
                    {
                        // This is somewhere in the chain
                        prev->next = curr->next;
                        curr->next = NULL;
                        free_linkedlist(curr);
                        table->overflow_buckets[index] = head;
                        return;
                    }
                }
                curr = curr->next;
                prev = curr;
            }
        }
    }
}
/* 
________________________________________________________________________________________
*   Printing Hash Tables
_____________________________________________________________
*/
void print_search(HashTable_S *table, char *key)
{
    char *val;
    if ((val = searchIn_HT_string(table, key)) == NULL)
    {
        printf("%s does not exist\n", key);
        return;
    }
    else
    {
        printf("Key:%s, Value:%s\n", key, val);
    }
}

void print_table(HashTable_S *table)
{
    printf("\n_____________________________________________________________n");
    for (int i = 0; i < table->size; i++)
    {
        if (table->items[i])
        {
            printf("Index:%d, Key:%s, Value:%s", i, table->items[i]->key, table->items[i]->value);
            if (table->overflow_buckets[i])
            {
                printf(" => Overflow Bucket => ");
                LinkedList *head = table->overflow_buckets[i];
                while (head)
                {
                    printf("Key:%s, Value:%s ", head->item->key, head->item->value);
                    head = head->next;
                }
            }
            printf("\n");
        }
    }
    printf("_____________________________________________________________\n");
}
/* 
________________________________________________________________________________________
*   Handling Collisions
-------------------------------------------------------------
*   There are two scenarios here. 
*   If the overflow bucket list for the item does not exist, 
*   we need to create one such list and add the item to it.
*   Otherwise, we can simply insert the item to the list.
-------------------------------------------------------------
_____________________________________________________________
*/
void handle_collision_HT_string(HashTable_S *table, unsigned long index, ht_item_string *item)
{
    LinkedList *head = table->overflow_buckets[index];

    if (head == NULL)
    {
        // We need to create the list
        head = allocate_list();
        head->item = item;
        table->overflow_buckets[index] = head;
        return;
    }
    else
    {
        // Insert to the list
        table->overflow_buckets[index] = linkedlist_insert(head, item);
        return;
    }
}
/* 
________________________________________________________________________________________
*   Creating Overflow Buckets for Collisions
-------------------------------------------------------------
*   Whenever there is a collision, we will add incoming items that 
*   collide on the same index on an Overflow Bucket List. 
*   Thus, we will not have to delete any existing records on our hash table.
-------------------------------------------------------------
*   Note :
*   Due to linked lists having O(n) time complexity for insertion, searching and deletion, 
*   in case of a collision, we will have a worst-case access time of O(n) as well. 
*   The advantage of this method is that it is a good choice if your hash table 
*   has a "low capacity".
_____________________________________________________________
*/

static LinkedList **create_overflow_buckets(HashTable_S *table)
{
    // Create the overflow buckets; an array of linkedlists
    LinkedList **buckets = (LinkedList **)calloc(table->size, sizeof(LinkedList *));
    for (int i = 0; i < table->size; i++)
        buckets[i] = NULL;
    return buckets;
}

/* 
________________________________________________________________________________________
*   Functions to release memory
-------------------------------------------------------------
*   Since we are using mallac and calloc, we must ensure that
*   we free the alloted memory once we are done with the item
*   or want to delete the item.
-------------------------------------------------------------
_____________________________________________________________
*/
void free_overflow_buckets(HashTable_S *table)
{
    // Free all the overflow bucket lists
    LinkedList **buckets = table->overflow_buckets;
    for (int i = 0; i < table->size; i++)
        free_linkedlist(buckets[i]);
    free(buckets);
}

void free_item(ht_item_string *item)
{
    // Frees an item
    free(item->key);
    free(item->value);
    free(item);
}

void free_table(HashTable_S *table)
{
    // Frees the table
    for (int i = 0; i < table->size; i++)
    {
        ht_item_string *item = table->items[i];
        if (item != NULL)
            free_item(item);
    }

    // Free the overflow bucket linked linkedlist and it's items
    free_overflow_buckets(table);
    free(table->items);
    free(table);
}
/* 
________________________________________________________________________________________
*   Linked List Implementation for Separate Chaining (Collision Handling)
-------------------------------------------------------------
*   Separate Chaining aims to create independent chains for all items that have 
*   the same hash index.
-------------------------------------------------------------
_____________________________________________________________
*/

LinkedList *allocate_list()
{
    // Allocates memory for a Linkedlist pointer
    LinkedList *list = (LinkedList *)calloc(1, sizeof(LinkedList));
    return list;
}

LinkedList *linkedlist_insert(LinkedList *list, ht_item_string *item)
{
    if (!list)
    {
        LinkedList *head = allocate_list();
        head->item = item;
        head->next = NULL;
        list = head;
        return list;
    }

    else if (list->next == NULL)
    {
        LinkedList *node = allocate_list();
        node->item = item;
        node->next = NULL;
        list->next = node;
        return list;
    }

    LinkedList *temp = list;
    while (temp->next)
    {
        temp = temp->next;
    }

    LinkedList *node = allocate_list();
    node->item = item;
    node->next = NULL;
    temp->next = node;

    return list;
}
static ht_item_string *linkedlist_remove(LinkedList *list)
{
    // Removes the head from the linked list
    // and returns the item of the popped element
    if (!list)
        return NULL;
    if (!list->next)
        return NULL;
    LinkedList *node = list->next;
    LinkedList *temp = list;
    temp->next = NULL;
    list = node;
    ht_item_string *it = NULL;
    memcpy(temp->item, it, sizeof(ht_item_string));
    free(temp->item->key);
    free(temp->item->value);
    free(temp->item);
    free(temp);
    return it;
}
static void free_linkedlist(LinkedList *list)
{
    LinkedList *temp = list;
    while (list)
    {
        temp = list;
        list = list->next;
        free(temp->item->key);
        free(temp->item->value);
        free(temp->item);
        free(temp);
    }
}