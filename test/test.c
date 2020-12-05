#include "../headers/hashing.h"

int main()
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
    return 0;
}
