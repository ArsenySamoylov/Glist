#include "ArsList.h"

int CtorArsList(ArsList* list, index_t capacity)
    {
    CHECK_PTR_RET(list, return FAILURE);

    if(list->status != UNITIALIZED)   return 0;
    if (capacity < MIN_LIST_CAPACITY) return 0; 

    node* node_arr = (node*) calloc (capacity + 1, sizeof(node_arr[0])); // + 1 for zero node
    CHECK_PTR_RET(node_arr, return FAILURE);

    // //setting zero node
    (*node_arr).next = 0;
    (*node_arr).prev = 0; 
    (*node_arr).data = CRINGE;   
    
    // first free index
    list->first_free_index = 1;

    // setting connections between nodes
    for (index_t i = 1; i < capacity + 1; i++)
        {
        (node_arr[i]).data = 0;

        (node_arr[i]).next = (i + 1) % (capacity + 1); // for last node to set next as 0
        (node_arr[i]).prev = -1; // how to set prev for zeronode capacity   
        }

    list->node_arr = node_arr;

    list->status         = ACTIVE;
    list->shuffle_status = LINEAR;

    list->capacity     = capacity;
    list->nodes_number = 0;

    return SUCCESS;
    }