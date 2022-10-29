#ifndef BEGITE_YEBKI
#define BEGITE_YEBKI

#include <stdlib.h>
#include <stdio.h>

#include "EasyDebug.h"
#include "CommonErrors.h"

typedef int element_t;
typedef int index_t;

const int MIN_LIST_CAPACITY = 1;
const int INITIAL_LIST_SIZE = 10; 
const int LIST_GROWTH_RATE  = 2;

const element_t CRINGE = 0xDED;

enum ArsListStatus
    {
    UNITIALIZED,
    ACTIVE, 
    DEAD,

    SHUFFLED,
    UNSHUFFFLED,
    };

struct node
    {
    index_t   prev;
    element_t data;
    index_t   next;
    };

struct ArsList
    {
    node* node_arr;

    int   data_shuffle_status;
    int status = UNITIALIZED; 

    unsigned capacity;
    unsigned nodes_number;  
    };

int CtorArsList(ArsList* list, unsigned capacity  = INITIAL_LIST_SIZE);
int DtorList (ArsList* list);

// NODISCARDD!!!!!!!!! (makefile std17)
//insert
index_t AddBack  (ArsList* list, element_t data);
index_t AddFront (ArsList* list, element_t data);
index_t Insert   (ArsList* list, index_t position, element_t data);
//delete
//! @todo when last element deleted -> sort 
index_t DeleLast(ArsList* list);
element_t Delete(ArsList* list, index_t index);

void ShowList (ArsList* list);

int AutoListResize (ArsList* list);

void ConsoleDump (ArsList* list);
void VisualDump  (ArsList* list);
#endif