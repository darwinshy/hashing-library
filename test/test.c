#include "../headers/stringhashing.h"
#include "../headers/inthashing.h"
void intHashing()
{

    hash_insert_int(20);
    hash_insert_int(70);
    hash_insert_int(80);
    hash_insert_int(25);
    hash_insert_int(44);
    hash_insert_int(32);
    hash_insert_int(11);
    hash_insert_int(78);
    hash_insert_int(97);

    hash_display_int();

    printf("Searching element 70: ");

    if (hash_search_int(70))
        printf("Found\n");
    else
        printf("Not Found\n");

    if (hash_delete_int(70))
    {
        printf("After Deletion of 70\n");
        hash_display_int();
    }
    else
        printf("Value Not Present\n");

    printf("_________________________________________");
    //Open Hashing using link list

    hash_INSERT_int(7);
    hash_INSERT_int(0);
    hash_INSERT_int(3);
    hash_INSERT_int(10);
    hash_INSERT_int(4);
    hash_INSERT_int(5);

    hash_DISPLAY_int();

    printf("Searching element 10: ");

    if (hash_SEARCH_int(10))
        printf("Found\n");
    else
        printf("Not Found\n");

    if (hash_DELETE_int(10))
    {
        printf("After Deletion of 10\n");
        hash_DISPLAY_int();
    }
    else
        printf("Value Not Present\n");

    printf("Searching element 10: ");

    if (hash_SEARCH_int(10))
        printf("Found\n");
    else
        printf("Not Found\n");
}

void stringHashing()
{
    char a[5] = {'F', 'i', 'r', 's', 't'};
    char b[5] = {'S', 'e', 'c', 'o', 'n'};
    char c[5] = {'T', 'h', 'i', 'r', 'd'};
    char d[5] = {'F', 'o', 'u', 'r', 't'};

    HashTable_S *ht = create_HT_string(100);
    insertTo_HT_string(ht, (char *)"1", a);
    insertTo_HT_string(ht, (char *)"2", b);
    insertTo_HT_string(ht, (char *)"H", c);
    insertTo_HT_string(ht, (char *)"C", d);
    print_search(ht, (char *)"1");
    print_search(ht, (char *)"2");
    print_search(ht, (char *)(char *)"3");
    print_search(ht, (char *)"Hel");
    print_search(ht, (char *)"Cau");
    print_table(ht);
    delete_HT_item_string(ht, (char *)"1");
    delete_HT_item_string(ht, (char *)"Cau");
    print_table(ht);
    free_table(ht);
}

int main()
{
    intHashing();
    stringHashing();
    return 0;
}
