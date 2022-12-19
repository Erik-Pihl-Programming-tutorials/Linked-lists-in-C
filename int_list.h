/********************************************************************************
* int_list.h: Innehåller funktionalitet för länkade listor innehållande heltal
*             via struktar int_node samt int_list samt associerade funktioner.
********************************************************************************/
#ifndef INT_LIST_H_
#define INT_LIST_H_

/* Inkluderingsdirektiv: */
#include <stdio.h>  /* Innehåller funktionalitet för utskrift och inmatning. */
#include <stdlib.h> /* Innehåller funktionalitet för dynamisk minnesallokering. */

/********************************************************************************
* int_node: Strukt för implementering av noder innehållande heltal.
********************************************************************************/
struct int_node
{
   struct int_node* previous; /* Pekare till föregående nod. */
   struct int_node* next;     /* Pekare till nästa nod. */
   int data;                  /* Datan som lagras (ett heltal). */
};

/********************************************************************************
* int_list: Strukt för implementering av länkad lista innehållande heltal.
********************************************************************************/
struct int_list
{
   struct int_node* first; /* Pekare till första noden i listan. */
   struct int_node* last;  /* Pekare till sista noden i listan. */
   size_t size;            /* Listans storlek, dvs. antalet noder i listan. */
};

/********************************************************************************
* int_node_new: Returnerar en pekare till en ny nod som lagrar angiven data.
*               Om minnesallokeringen misslyckas returneras en nullpekare.
*               Annars initieras noden, där angiven heltal lagras och pekare
*               till föregående samt nästa element sätts till null.
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
* int_node_delete: Raderar angiven nod och sätter motsvarande pekare till null.
*                  För att möjliggöra detta skickas adressen till nodpekaren,
*                  annars kommer det fram en kopia av nodpekaren, vilket gör
*                  att vi inte kan sätta ordinarie nodpekare till null. 
*                  Vi kommer åt nodpekaren via dereferensen av adressen.
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
* int_list_init: Initierar tom länkad lista för lagring av heltal.
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
* int_list_clear: Tömmer angiven länkad lista och sätter listans attribut till 
*                 startvärden.
*
*                 - self: Referens till listan som ska tömmas.
********************************************************************************/
void int_list_clear(struct int_list* self);

/********************************************************************************
* int_list_new: Returnerar en pekare till en ny tom heapallokerad länkad lista 
*               för lagring av heltal. Om minnesallokeringen misslyckas
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
* int_list_delete: Raderar angiven heapallokerad länkad lista och sätter 
*                  motsvarande pekare till null. För att möjliggöra detta skickas 
*                  adressen till listpekaren, annars kommer det fram en kopia av 
*                  denna, vilket gör att vi inte kan sätta ordinarie listpekare 
*                  till null. Listpekaren kan nås via dereferensen av adressen.
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
* int_list_node_at: Returnerar en pekare till nod på angivet index i refererad
*                   länkad lista. Om index är felaktigt returneras null.
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
* int_list_push_front: Lägger ett nytt heltal längst fram i angiven länkad lista.
*                      Om talet lyckades läggas till returneras 0, annars 
*                      returneras felkod 1.
*
*                      - self: Referens till listan som ska tilldelas heltalet.
*                      - data: Heltalet som ska läggas till.
********************************************************************************/
int int_list_push_front(struct int_list* self,
                        const int data);

/********************************************************************************
* int_list_push_back: Lägger ett nytt heltal längst bak i angiven länkad lista.
*                     Om talet lyckades läggas till returneras 0, annars
*                     returneras felkod 1.
*
*                     - self: Referens till listan som ska tilldelas heltalet.
*                     - data: Heltalet som ska läggas till.
********************************************************************************/
int int_list_push_back(struct int_list* self,
                       const int data);

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
                    const int data);

/********************************************************************************
* int_list_pop_front: Tar bort ett heltal längst fram i angiven länkad lista.
*
*                     - self: Referens till listan.
********************************************************************************/
void int_list_pop_front(struct int_list* self);

/********************************************************************************
* int_list_pop_back: Tar bort ett heltal längst bak i angiven länkad lista.
*
*                    - self: Referens till listan.
********************************************************************************/
void int_list_pop_back(struct int_list* self);

/********************************************************************************
* int_list_remove: Tar bort ett heltal på angivet index i refererad länkad
*                  lista. Om angivet index är felaktigt returneras felkod 1, 
*                  annars returneras 0.
*
*                  - self : Referens till listan.
*                  - index: Index för talet som ska tas bort.
********************************************************************************/
int int_list_remove(struct int_list* self,
                    const size_t index);

/********************************************************************************
* int_list_print: Skriver ut samtliga heltal lagrade i angiven länkad lista via
*                 godtycklig utström, där standardutenheten stdout används som
*                 default för utskrift i terminalen.
*
*                 - self   : Referens till listan vars innehåll ska skrivas ut.
*                 - ostream: Pekare till godtycklig utström.
********************************************************************************/
void int_list_print(const struct int_list* self, 
                    FILE* ostream);

#endif /* INT_LIST_H_ */