#ifndef BEGITE_YEBKI
#define BEGITE_YEBKI

#include <stdlib.h>
#include <stdio.h>

#include "EasyDebug.h"
#include "CommonErrors.h"
#include "Utils.h"

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
    LINEAR,
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
    
    index_t first_free_index;

    unsigned capacity;
    unsigned nodes_number;

    int shuffle_status;
    int status = UNITIALIZED;   
    };

int CtorArsList (ArsList* list, index_t capacity  = INITIAL_LIST_SIZE);
int DtorList    (ArsList* list);

// NODISCARDD!!!!!!!!! (makefile std17)
//insert
index_t AddBack  (ArsList* list, element_t data);
index_t AddFront (ArsList* list, element_t data);
index_t Insert   (ArsList* list, index_t position, element_t data);

element_t Delete(ArsList* list, index_t index);

ArsList* SortAndRealloc (ArsList* list, index_t new_size);

// delete
//! @todo when last element deleted -> sort 

void ShowList (ArsList* list);

int AutoListResize (ArsList* list);

void ConsoleDump (ArsList* list);
void VisualDump  (ArsList* list);
#endif