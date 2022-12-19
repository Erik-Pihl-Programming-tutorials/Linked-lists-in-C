/********************************************************************************
* int_list.c: Innehåller associerade funktioner för implementering av länkade
*             listor för lagring av heltal.
********************************************************************************/
#include "int_list.h"

/********************************************************************************
* int_list_clear: Tömmer angiven länkad lista och sätter listans attribut till
*                 startvärden.
*
*                 - self: Referens till listan som ska tömmas.
********************************************************************************/
void int_list_clear(struct int_list* self)
{
   for (struct int_node* i = self->first; i; )
   {
      struct int_node* next_node = i->next;
      int_node_delete(&i);
      i = next_node;
   }

   int_list_init(self);
   return;
}

/********************************************************************************
* int_list_push_front: Lägger ett nytt heltal längst fram i angiven länkad lista.
*                      Om talet lyckades läggas till returneras 0, annars
*                      returneras felkod 1.
*
*                      - self: Referens till listan som ska tilldelas heltalet.
*                      - data: Heltalet som ska läggas till.
********************************************************************************/
int int_list_push_front(struct int_list* self,
                        const int data)
{
   struct int_node* n1 = int_node_new(data);
   struct int_node* n2 = self->first;

   if (!n1) return 1;
   
   if (self->size == 0)
   {
      self->first = n1;
      self->last = n1;
   }
   else
   {
      n1->next = n2;
      n2->previous = n1;
      self->first = n1;
   }

   self->size++;
   return 0;
}

/********************************************************************************
* int_list_push_back: Lägger ett nytt heltal längst bak i angiven länkad lista.
*                     Om talet lyckades läggas till returneras 0, annars
*                     returneras felkod 1.
*
*                     - self: Referens till listan som ska tilldelas heltalet.
*                     - data: Heltalet som ska läggas till.
********************************************************************************/
int int_list_push_back(struct int_list* self,
                       const int data)
{
   struct int_node* n1 = self->last;
   struct int_node* n2 = int_node_new(data);

   if (!n2) return 1;

   if (self->size == 0)
   {
      self->first = n2;
      self->last = n2;
   }
   else
   {
      n1->next = n2;
      n2->previous = n1;
      self->last = n2;
   }

   self->size++;
   return 0;
}

/********************************************************************************
* int_list_insert: Lägger ett nytt heltal på angivet index i refererad länkad
*                  lista. Om angivet index är felaktigt eller om talet inte
*                  kunde läggas till returneras felkod 1, annars returneras 0.
*
*                  - self : Referens till listan som ska tilldelas heltalet.
*                  - index: Indexet som det nya talet ska läggas till på.
*                  - data : Heltalet som ska läggas till.
********************************************************************************/
int int_list_insert(struct int_list* self,
                    const size_t index,
                    const int data)
{
   if (index == 0)
   {
      return int_list_push_front(self, data);
   }
   else if (index == self->size)
   {
      return int_list_push_back(self, data);
   }
   else if (index > self->size)
   {
      return 1;
   }
   else
   {
      struct int_node* n3 = int_list_node_at(self, index);
      struct int_node* n1 = n3->previous;
      struct int_node* n2 = int_node_new(data);
      if (!n2) return 1;

      n2->next = n3;
      n3->previous = n2;
      n1->next = n2;
      n2->previous = n1;

      self->size++;
      return 0;
   }
}

/********************************************************************************
* int_list_pop_front: Tar bort ett heltal längst fram i angiven länkad lista.
*
*                     - self: Referens till listan.
********************************************************************************/
void int_list_pop_front(struct int_list* self)
{
   if (self->size <= 1)
   {
      int_list_clear(self);
   }
   else
   {
      struct int_node* n1 = self->first;
      struct int_node* n2 = n1->next;

      n2->previous = 0;
      self->first = n2;

      int_node_delete(&n1);
      self->size--;
   }
   return;
}

/********************************************************************************
* int_list_pop_back: Tar bort ett heltal längst bak i angiven länkad lista.
*
*                    - self: Referens till listan.
********************************************************************************/
void int_list_pop_back(struct int_list* self)
{
   if (self->size <= 1)
   {
      int_list_clear(self);
   }
   else
   {
      struct int_node* n2 = self->last;
      struct int_node* n1 = n2->previous;

      n1->next = 0;
      self->last = n1;

      int_node_delete(&n2);
      self->size--;
   }
   return;
}

/********************************************************************************
* int_list_remove: Tar bort ett heltal på angivet index i refererad länkad
*                  lista. Om angivet index är felaktigt returneras felkod 1,
*                  annars returneras 0.
*
*                  - self : Referens till listan.
*                  - index: Index för talet som ska tas bort.
********************************************************************************/
int int_list_remove(struct int_list* self,
                    const size_t index)
{
   if (index == 0)
   {
      int_list_pop_front(self);
   }
   else if (index == self->size - 1)
   {
      int_list_pop_back(self);
   }
   else if (index >= self->size)
   {
      return 1;
   }
   else
   {
      struct int_node* n2 = int_list_node_at(self, index);
      struct int_node* n1 = n2->previous;
      struct int_node* n3 = n2->next;

      n1->next = n3;
      n3->previous = n1;

      int_node_delete(&n2);
      self->size--;
   }
   return 0;
}

/********************************************************************************
* int_list_print: Skriver ut samtliga heltal lagrade i angiven länkad lista via
*                 godtycklig utström, där standardutenheten stdout används som
*                 default för utskrift i terminalen.
*
*                 - self   : Referens till listan vars innehåll ska skrivas ut.
*                 - ostream: Pekare till godtycklig utström.
********************************************************************************/
void int_list_print(const struct int_list* self,
                    FILE* ostream)
{
   if (self->size == 0) return;
   if (!ostream) ostream = stdout;
   fprintf(ostream, "--------------------------------------------------------------------------------\n");

   for (const struct int_node* i = self->first; i; i = i->next)
   {
      fprintf(ostream, "%d\n", i->data);
   }

   fprintf(ostream, "--------------------------------------------------------------------------------\n\n");
   return;
}