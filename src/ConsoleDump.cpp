#include "ArsList.h"

void ConsoleDump(ArsList* list) 
    {
    CHECK_PTR_MSG_RET(list, return ,"Ebaniko, use dump right (null pointer)\n");

    int number_of_nodes = list->nodes_number;
    int capacity        = list->capacity;
    node* node_arr = list->node_arr;
    
    CHECK_PTR_RET(node_arr, return);
    ////////////////list status
    printf("List status: nodes number: %d, capacity %d, shuffle status: %s \n", 
                            list->nodes_number, list->capacity, list->shuffle_status == SHUFFLED ? "shuffled":"linear");
    printf("???????????????????????????????????\n");
    ////////////////zero node
    printf("ZERO NODE: \n");
    printf("TAIL (prev) index: %d, HEAD (next) index %d. (data %0X)\n\n", node_arr->prev, node_arr->next, node_arr->data);
    /////////////////
    for(index_t i = 1; i < capacity + 1; i++)
        {
        node temp = node_arr[i];

        printf("ELement %d\n", i);
        printf("prev index: %d, next index %d. (data %d)\n\n", temp.prev, temp.next, temp.data);
        }
    }