/* 
_________________________________________________________________________________
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
_________________________________________________________________________________
*/

#include <stdio.h>

/* 
_________________________________________________________________________________
*   Predefining some values
-------------------------------------------------------------
*   1.max_modulo value to prevent overflow of Integer Value
*   2.max_capacity is maximum size of our Hash Table.
-------------------------------------------------------------
_________________________________________________________________________________
*/

#define max_modulo 10000007
#define max_capacity 60000

/* 
_________________________________________________________________________________
*   Define Types of Structure.
_________________________________________________________________________________
*/

typedef struct HashTable_S HashTable_S;
typedef struct ht_item_string ht_item_string;

/* 
_________________________________________________________________________________
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
        i = i * i + str[j];
    return i % max_capacity;
}

unsigned long hash_function_integer(int *int_value);

/* 
_________________________________________________________________________________
*   Hash Table (string)
-------------------------------------------------------------
*   Our hash table includes 3 items. 
*   1.  items, an array of pointers which themselves point to
        ht_item_string, so it is a double-pointer.
*   2.  size, the user defined size of our hash table.
*   3.  count, the number of items currently in the hashtable
-------------------------------------------------------------
_____________________________________________________________
*/
struct HashTable_S
{
    ht_item_string **items;
    int size;
    int count;
};

/* 
_________________________________________________________________________________
*   Hash Table Item (ht_item_string)
-------------------------------------------------------------
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
_________________________________________________________________________________
*   Creating Hash Table for String (create_table_string)
-------------------------------------------------------------
*   This function assigns memory for the hash table.
*   By default the count of this hashtable is 0 ie number
*   of element in the table.
-------------------------------------------------------------
_____________________________________________________________
*/

HashTable_S *create_table_string(int size)
{
    // Creates a new HashTable
    HashTable_S *table = (HashTable_S *)malloc(sizeof(HashTable_S));
    table->size = size;
    table->count = 0;
    table->items = (ht_item_string **)calloc(table->size, sizeof(ht_item_string *));
    for (int i = 0; i < table->size; i++)
        table->items[i] = NULL;

    return table;
}

/* 
_________________________________________________________________________________
*   Creating Hash Table Item for String (create_item_string)
-------------------------------------------------------------
*   Allocate memory using malloc function and assign
*   he pointer to ht_item_string. Same to the key
*   value. Assign the input values to allocated memory.
*   Return the newly created item.
-------------------------------------------------------------
_____________________________________________________________
*/

ht_item_string *create_item_string(char *key, char *value)
{
    // Creates a pointer to a new hash table item
    ht_item_string *item = (ht_item_string *)malloc(sizeof(ht_item_string));
    item->key = (char *)malloc(strlen(key) + 1);
    item->value = (char *)malloc(strlen(value) + 1);

    strcpy(item->key, key);
    strcpy(item->value, value);

    return item;
}

/* 
_________________________________________________________________________________
*   Function to release memory
-------------------------------------------------------------
*   Since we are using mallac and calloc, we must ensure that
*   we free the alloted memory once we are done with the item
*   or want to delete the item.
-------------------------------------------------------------
_____________________________________________________________
*/

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
        HashTable_S *item = table->items[i];
        if (item != NULL)
            free_item(item);
    }

    free(table->items);
}