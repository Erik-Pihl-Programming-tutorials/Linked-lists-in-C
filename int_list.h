/********************************************************************************
* int_list.h: Inneh�ller funktionalitet f�r l�nkade listor inneh�llande heltal
*             via struktar int_node samt int_list samt associerade funktioner.
********************************************************************************/
#ifndef INT_LIST_H_
#define INT_LIST_H_

/* Inkluderingsdirektiv: */
#include <stdio.h>  /* Inneh�ller funktionalitet f�r utskrift och inmatning. */
#include <stdlib.h> /* Inneh�ller funktionalitet f�r dynamisk minnesallokering. */

/********************************************************************************
* int_node: Strukt f�r implementering av noder inneh�llande heltal.
********************************************************************************/
struct int_node
{
   struct int_node* previous; /* Pekare till f�reg�ende nod. */
   struct int_node* next;     /* Pekare till n�sta nod. */
   int data;                  /* Datan som lagras (ett heltal). */
};

/********************************************************************************
* int_list: Strukt f�r implementering av l�nkad lista inneh�llande heltal.
********************************************************************************/
struct int_list
{
   struct int_node* first; /* Pekare till f�rsta noden i listan. */
   struct int_node* last;  /* Pekare till sista noden i listan. */
   size_t size;            /* Listans storlek, dvs. antalet noder i listan. */
};

/********************************************************************************
* int_node_new: Returnerar en pekare till en ny nod som lagrar angiven data.
*               Om minnesallokeringen misslyckas returneras en nullpekare.
*               Annars initieras noden, d�r angiven heltal lagras och pekare
*               till f�reg�ende samt n�sta element s�tts till null.
* 
*               - data: Datan (heltalet) som ska lagras.
********************************************************************************/
static inline struct int_node* int_node_new(const int data)
{
   struct int_node* self = (struct int_node*)malloc(sizeof(struct int_node));
   if (!self) return 0;

   self->previous = 0;
   self->next = 0;
   self->data = data;
   return self;
}

/********************************************************************************
* int_node_delete: Raderar angiven nod och s�tter motsvarande pekare till null.
*                  F�r att m�jligg�ra detta skickas adressen till nodpekaren,
*                  annars kommer det fram en kopia av nodpekaren, vilket g�r
*                  att vi inte kan s�tta ordinarie nodpekare till null. 
*                  Vi kommer �t nodpekaren via dereferensen av adressen.
*
*                  - self: Adressen till nodpekaren.
********************************************************************************/
static inline void int_node_delete(struct int_node** self)
{
   free(*self);
   *self = 0;
   return;
}

/********************************************************************************
* int_list_init: Initierar tom l�nkad lista f�r lagring av heltal.
* 
*                - self: Referens till listan som ska initieras.
********************************************************************************/
static inline void int_list_init(struct int_list* self)
{
   self->first = 0;
   self->last = 0;
   self->size = 0;
   return;
}

/********************************************************************************
* int_list_clear: T�mmer angiven l�nkad lista och s�tter listans attribut till 
*                 startv�rden.
*
*                 - self: Referens till listan som ska t�mmas.
********************************************************************************/
void int_list_clear(struct int_list* self);

/********************************************************************************
* int_list_new: Returnerar en pekare till en ny tom heapallokerad l�nkad lista 
*               f�r lagring av heltal. Om minnesallokeringen misslyckas
*               returneras felkod 1, annars returneras 0.
********************************************************************************/
static inline struct int_list* int_list_new(void)
{
   struct int_list* self = (struct int_list*)malloc(sizeof(struct int_list));
   if (!self) return 0;
   int_list_init(self);
   return self;
}

/********************************************************************************
* int_list_delete: Raderar angiven heapallokerad l�nkad lista och s�tter 
*                  motsvarande pekare till null. F�r att m�jligg�ra detta skickas 
*                  adressen till listpekaren, annars kommer det fram en kopia av 
*                  denna, vilket g�r att vi inte kan s�tta ordinarie listpekare 
*                  till null. Listpekaren kan n�s via dereferensen av adressen.
*
*                  - self: Adressen till listpekaren.
********************************************************************************/
static inline void int_list_delete(struct int_list** self)
{
   int_list_clear(*self);
   free(*self);
   *self = 0;
   return;
}

/********************************************************************************
* int_list_node_at: Returnerar en pekare till nod p� angivet index i refererad
*                   l�nkad lista. Om index �r felaktigt returneras null.
*
*                   - self : Referens till listan som ska tilldelas heltalet.
*                   - index: Nodens index.
********************************************************************************/
static inline struct int_node* int_list_node_at(struct int_list* self,
                                                const size_t index)
{
   struct int_node* node = self->first;
   if (index >= self->size) return 0;
   for (size_t i = 0; i < index; ++i) node = node->next;
   return node;
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
                        const int data);

/********************************************************************************
* int_list_push_back: L�gger ett nytt heltal l�ngst bak i angiven l�nkad lista.
*                     Om talet lyckades l�ggas till returneras 0, annars
*                     returneras felkod 1.
*
*                     - self: Referens till listan som ska tilldelas heltalet.
*                     - data: Heltalet som ska l�ggas till.
********************************************************************************/
int int_list_push_back(struct int_list* self,
                       const int data);

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
                    const int data);

/********************************************************************************
* int_list_pop_front: Tar bort ett heltal l�ngst fram i angiven l�nkad lista.
*
*                     - self: Referens till listan.
********************************************************************************/
void int_list_pop_front(struct int_list* self);

/********************************************************************************
* int_list_pop_back: Tar bort ett heltal l�ngst bak i angiven l�nkad lista.
*
*                    - self: Referens till listan.
********************************************************************************/
void int_list_pop_back(struct int_list* self);

/********************************************************************************
* int_list_remove: Tar bort ett heltal p� angivet index i refererad l�nkad
*                  lista. Om angivet index �r felaktigt returneras felkod 1, 
*                  annars returneras 0.
*
*                  - self : Referens till listan.
*                  - index: Index f�r talet som ska tas bort.
********************************************************************************/
int int_list_remove(struct int_list* self,
                    const size_t index);

/********************************************************************************
* int_list_print: Skriver ut samtliga heltal lagrade i angiven l�nkad lista via
*                 godtycklig utstr�m, d�r standardutenheten stdout anv�nds som
*                 default f�r utskrift i terminalen.
*
*                 - self   : Referens till listan vars inneh�ll ska skrivas ut.
*                 - ostream: Pekare till godtycklig utstr�m.
********************************************************************************/
void int_list_print(const struct int_list* self, 
                    FILE* ostream);

#endif /* INT_LIST_H_ */