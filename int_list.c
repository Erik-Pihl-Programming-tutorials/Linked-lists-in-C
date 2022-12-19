/********************************************************************************
* int_list.c: Inneh�ller associerade funktioner f�r implementering av l�nkade
*             listor f�r lagring av heltal.
********************************************************************************/
#include "int_list.h"

/********************************************************************************
* int_list_clear: T�mmer angiven l�nkad lista och s�tter listans attribut till
*                 startv�rden.
*
*                 - self: Referens till listan som ska t�mmas.
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
* int_list_push_front: L�gger ett nytt heltal l�ngst fram i angiven l�nkad lista.
*                      Om talet lyckades l�ggas till returneras 0, annars
*                      returneras felkod 1.
*
*                      - self: Referens till listan som ska tilldelas heltalet.
*                      - data: Heltalet som ska l�ggas till.
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
* int_list_push_back: L�gger ett nytt heltal l�ngst bak i angiven l�nkad lista.
*                     Om talet lyckades l�ggas till returneras 0, annars
*                     returneras felkod 1.
*
*                     - self: Referens till listan som ska tilldelas heltalet.
*                     - data: Heltalet som ska l�ggas till.
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
* int_list_insert: L�gger ett nytt heltal p� angivet index i refererad l�nkad
*                  lista. Om angivet index �r felaktigt eller om talet inte
*                  kunde l�ggas till returneras felkod 1, annars returneras 0.
*
*                  - self : Referens till listan som ska tilldelas heltalet.
*                  - index: Indexet som det nya talet ska l�ggas till p�.
*                  - data : Heltalet som ska l�ggas till.
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
* int_list_pop_front: Tar bort ett heltal l�ngst fram i angiven l�nkad lista.
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
* int_list_pop_back: Tar bort ett heltal l�ngst bak i angiven l�nkad lista.
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
* int_list_remove: Tar bort ett heltal p� angivet index i refererad l�nkad
*                  lista. Om angivet index �r felaktigt returneras felkod 1,
*                  annars returneras 0.
*
*                  - self : Referens till listan.
*                  - index: Index f�r talet som ska tas bort.
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
* int_list_print: Skriver ut samtliga heltal lagrade i angiven l�nkad lista via
*                 godtycklig utstr�m, d�r standardutenheten stdout anv�nds som
*                 default f�r utskrift i terminalen.
*
*                 - self   : Referens till listan vars inneh�ll ska skrivas ut.
*                 - ostream: Pekare till godtycklig utstr�m.
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