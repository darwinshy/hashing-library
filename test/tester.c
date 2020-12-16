#include<D:\My Stuffs\my codes\College_Works\integerHashing.h>

int main()
{
    //Closed Hashing /simple hashing
   {
        insert( 20);
        insert( 70);
        insert( 80);
        insert( 25);
        insert( 44);
        insert( 32);
        insert( 11);
        insert( 78);
        insert( 97);

        display();
        
        printf("Searching element 70: ");

            if (search(70))
                printf("Found\n");
            else
                printf("Not Found\n");

        if(delete(70))
        {
            printf("After Deletion of 70\n");
            display();
        }
        else
            printf("Value Not Present\n");
   }
    printf("_________________________________________________________________________________________________");
   //Open Hashing using link list 
   {
        INSERT(7);
        INSERT(0);
        INSERT(3);
        INSERT(10);
        INSERT(4);
        INSERT(5);

        DISPLAY();

        printf("Searching element 10: ");

        if (SEARCH(10))
            printf("Found\n");
        else
            printf("Not Found\n");

        if (DELETE(10))
        {
            printf("After Deletion of 10\n");
            DISPLAY();
        }
        else
            printf("Value Not Present\n");
        

        printf("Searching element 10: ");

        if (SEARCH(10))
            printf("Found\n");
        else
            printf("Not Found\n");
   }

}