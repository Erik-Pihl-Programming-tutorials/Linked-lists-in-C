/********************************************************************************
* main.c: Demonstration av länkade listor i C.
********************************************************************************/
#include "int_list.h"

/********************************************************************************
* main: Fyller två länkade listor med heltal och skriver ut i terminalen.
********************************************************************************/
int main(void)
{
   struct int_list l1, *l2;

   int_list_init(&l1);
   l2 = int_list_new();

   if (!l2) return 1;

   for (int i = 0; i < 10; ++i)
   {
      int_list_push_front(&l1, i);
   }

   for (int i = 0; i < 50; ++i)
   {
      int_list_push_back(l2, i + 25);
   }

   int_list_insert(&l1, 5, 500);
   int_list_remove(l2, 10);

   int_list_print(&l1, 0);
   int_list_print(l2, 0);

   int_list_clear(&l1);
   int_list_delete(&l2);
   return 0;
}