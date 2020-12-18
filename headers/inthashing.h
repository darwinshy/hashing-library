/* 
_____________________________________________________________________________________
*   Hashing
-------------------------------------------------------------
*   Implemented for listed Data Structures 
*       Integer 
-------------------------------------------------------------
*   Hash Table
*       Implementation through array + linked list
*       a.  Closed Hashing using simple array
*       b.  Open Hasing using array and linked list
-------------------------------------------------------------
________________________________________________________________________________________
*/

/* 
_____________________________________________________________________________________
   (A) CLOSED HASHING USING A SIMPLE ARRAY
_____________________________________________________________________________________

*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#define SIZE 20

/* 
_________________________________________________________________________
*   Defining Structure and Functions of the hash table
_________________________________________________________________________
*/

/* 
_______________________________________________________
*   The hash Structure
_______________________________________________________
*/
struct DataItem
{
    int data;
};

struct DataItem *hashArray[SIZE];
struct DataItem *dummyItem;
struct DataItem *item;

/* 
_______________________________________________________
*   The hash key function
        the function will generate a key with respect
        to the value.
_______________________________________________________
*/
int hash_hashCode_int(int value)
{

    if (value < 0)
        return -1 * (value % SIZE);

    return (value % SIZE);
}

/* 
_______________________________________________________
*   The hash table hash_search_int function-
    *   this function will look for the value if it
        is present in the hash table.
_______________________________________________________
*/
int hash_search_int(int data)
{
    //get the hash
    int hashIndex = hash_hashCode_int(data);

    //move in array until an empty
    while (hashArray[hashIndex] != NULL)
    {

        if (hashArray[hashIndex]->data == data)
            return 1;

        //go to next cell
        ++hashIndex;

        //wrap around the table
        hashIndex %= SIZE;
    }

    return 0;
}

/* 
_______________________________________________________
*   The hash insert function-
        this function will hash_insert_int user inputed values
        in the hash table.
_______________________________________________________
*/
void hash_insert_int(int data)
{

    struct DataItem *item = (struct DataItem *)malloc(sizeof(struct DataItem));
    item->data = data;

    //get the hash
    int hashIndex = hash_hashCode_int(data);

    //move in array until an empty or deleted cell
    while (hashArray[hashIndex] != NULL && hashArray[hashIndex]->data != -1)
    {
        //go to next cell
        ++hashIndex;

        //wrap around the table
        hashIndex %= SIZE;
    }

    hashArray[hashIndex] = item;
}

/* 
_______________________________________________________
*   The hash delete function
        It will hash_delete_int the user inserted value 
        from the hash table if it is present.
            * return 1, successful delete
            * return 0, value not found
_______________________________________________________
*/
int hash_delete_int(int data)
{

    //get the hash
    int hashIndex = hash_hashCode_int(data);

    //move in array until an empty
    while (hashArray[hashIndex] != NULL)
    {

        if (hashArray[hashIndex]->data == data)
        {
            struct DataItem *temp = hashArray[hashIndex];

            //assign a dummy item at deleted position
            hashArray[hashIndex] = dummyItem;
            return 1;
        }

        //go to next cell
        ++hashIndex;

        //wrap around the table
        hashIndex %= SIZE;
    }

    return 0;
}

/* 
_______________________________________________________
*   The hash table display function
_______________________________________________________
*/
void hash_display_int()
{
    printf("\n________________________________________________\n");
    printf("Integer Hashtable ------------------------------\n\n");
    printf("[");
    for (int i = 0; i < SIZE; i++)
        if (hashArray[i] != NULL)
            printf("(%d) ", hashArray[i]->data);
        else
            printf("~ ");

    printf("]");
    printf("\n\n-----------------------------------------------");
    printf("\n________________________________________________\n");
}
/*
-------------------------------------------------------------------------------------
*/

/* 
_____________________________________________________________________________________
    (B) CLOSED HASHING USING A SIMPLE ARRAY
_____________________________________________________________________________________

*/

/* 
_______________________________________________________
*   Defined the size of the table 
_______________________________________________________
*/
#define size 7

/* 
_______________________________________________________
*   The hash Structure
_______________________________________________________
*/
struct node
{
    int data;
    struct node *next;
};

struct node *chain[size];

/* 
_______________________________________________________
*   The hash insert function-
        this function will insert user inputed values
        in the hash table.
_______________________________________________________
*/
void hash_INSERT_int(int value)
{
    //create a newnode with value
    struct node *newNode = (struct node *)malloc(sizeof(struct node));
    newNode->data = value;
    newNode->next = NULL;

    //calculate hash key
    int key = value % size;

    //check if chain[key] is empty
    if (chain[key] == NULL)
        chain[key] = newNode;
    //collision
    else
    {
        //add the node at the end of chain[key].
        struct node *temp = chain[key];
        while (temp->next)
        {
            temp = temp->next;
        }

        temp->next = newNode;
    }
}

/* 
_______________________________________________________
*   The hash delete function
        It will hash_delete_int the user inserted value 
        from the hash table if it is present.
            * return 1, successful delete
            * return 0, value not found
_______________________________________________________
*/

int hash_DELETE_int(int value)
{
    int key = value % size;
    struct node *temp = chain[key], *dealloc;
    if (temp != NULL)
    {
        if (temp->data == value)
        {
            dealloc = temp;
            temp = temp->next;
            free(dealloc);
            return 1;
        }
        else
        {
            while (temp->next)
            {
                if (temp->next->data == value)
                {
                    dealloc = temp->next;
                    temp->next = temp->next->next;
                    free(dealloc);
                    return 1;
                }
                temp = temp->next;
            }
        }
    }

    return 0;
}

/* 
_______________________________________________________
*   The hash table search function-
        this function will look for the value if it
        is present in the hash table.
            * return 1, if found
            * return 0, if not found
_______________________________________________________
*/
int hash_SEARCH_int(int value)
{
    int key = value % size;
    struct node *temp = chain[key];
    while (temp)
    {
        if (temp->data == value)
            return 1;
        temp = temp->next;
    }
    return 0;
}

/* 
_______________________________________________________
*   The hash table display function
_______________________________________________________
*/
void hash_DISPLAY_int()
{
    printf("\n________________________________________________\n");
    printf("Integer Hashtable ------------------------------\n\n");
    for (int i = 0; i < size; i++)
    {
        struct node *temp = chain[i];
        if (temp != NULL)
        {

            printf("(");
            printf("%d", temp->data);
            temp = temp->next;
            while (temp)
            {
                printf(" --> %d", temp->data);
                temp = temp->next;
            }
            printf(") ");
        }
    }
    printf("\n\n-----------------------------------------------");
    printf("\n________________________________________________\n");
}
