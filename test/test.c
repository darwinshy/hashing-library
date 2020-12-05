#include "../headers/hashing.h"

int main()
{
    HashTable_S *ht = create_HT_string(100);
    insertTo_HT_string(ht, "1", "First address");
    insertTo_HT_string(ht, "2", "Second address");
    insertTo_HT_string(ht, "Hel", "Third address");
    insertTo_HT_string(ht, "Cau", "Fourth address");
    print_search(ht, "1");
    print_search(ht, "2");
    print_search(ht, "3");
    print_search(ht, "Hel");
    print_search(ht, "Cau");
    print_table(ht);
    delete_HT_item_string(ht, "1");
    delete_HT_item_string(ht, "Cau");
    print_table(ht);
    free_table(ht);
    return 0;
}
