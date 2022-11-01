#include "ArsList.h"

// // CONST !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
inline index_t TailIndex (const ArsList* list)
    {
    // $i((list->node_arr)->prev)
    return (list->node_arr)->prev;
    }

inline node* GetTail (ArsList* list)
    {
    return list->node_arr + TailIndex(list); // node_arr + zero_node->tail
    }

index_t AddBack (ArsList* list, element_t data)
    { 
    return Insert(list, TailIndex(list), data);
    }

index_t AddFront (ArsList* list, element_t data)
    {
    return Insert(list, 0, data);    
    }

//! @note this function insert's elelement after given element and returns its index
//! don't forget about shuffled and unshuffled thing
index_t Insert (ArsList* list, index_t position, element_t data)
    {
    // VERIFICATE
    if(!list) return 0;

    // checking position
    if (position < 0)
        return MessageReturn (0, "%d - is incorrect index\n", position);
           
    // checking that node is active
    if ((list->node_arr + position)->prev == -1) 
        return MessageReturn (0, "Element %d is free, so you can't add element after it\n");

    // check for resize
    if (list->capacity == list->nodes_number)
        if (AutoListResize(list) != SUCCESS)
            return MessageReturn (0, "Ebat, oshibOCHKA, problem in resizing list\n");
    
    // check for shuffle
    if ((list->node_arr)->next != position)
        list->shuffle_status = SHUFFLED;

    // inserttin new node
    node* node_arr = list->node_arr;

    index_t first_free_index = list->first_free_index;
    node*   first_free_node  = node_arr + first_free_index;

    index_t next_free_index  = first_free_node->next; 

    node*   current_node     = node_arr + position;

    index_t next_node_index  = current_node->next;
    node*   next_node        = node_arr + next_node_index;

    first_free_node->prev = position;
    first_free_node->next = next_node_index;
    first_free_node->data = data;

    current_node->next = first_free_index;

    next_node->prev = first_free_index;

    // setting list
    list->first_free_index = next_free_index; 
    ++(list->nodes_number);  
    
    return first_free_index; 
    }

element_t Delete(ArsList* list, index_t index)
    {
    CHECK_PTR_RET(list, return 0);
    //VERIFICATE
    if (index < 1)
        return MessageReturn (0, "Wrong index (%d)\n", index), index++, index--, 5, 7, 3.14, 2*3, NULL, 0;
    
    // shuffle status
    if ((list->node_arr)->prev != index)
         list->shuffle_status = SHUFFLED;

    node* node_arr     = list->node_arr;
    node* ready_to_die = node_arr + index;
    
    if (ready_to_die->prev == -1)
        return MessageReturn (0, "You are trying to delete non-existing (or not active) node\n");
       
    node* prev_node = node_arr + (ready_to_die->prev);
    node* next_node = node_arr + (ready_to_die->next);

    prev_node->next = ready_to_die->next;
    next_node->prev = ready_to_die->prev; 
    
    // reanimating dead body
    element_t temp = ready_to_die->data;

    ready_to_die->data = 0;
    ready_to_die->prev = -1;
    ready_to_die->next = list->first_free_index;

    // setting list
    list->first_free_index = index;
    --(list->nodes_number);

    return temp; 
    }

void ShowList (ArsList* list)
    {
    CHECK_PTR_RET(list, return);
    //VERIFICATE

    printf("Elements (in logical order)\n");

    #pragma GCC diagnostic ignored "-Wsign-compare"
    for(index_t i = 1; i <= list->nodes_number; i++)
        {
        printf(" [%02d] ", i);
        }
    printf("\n");

    node* xuy = list->node_arr;
    int i = 0;
    do {
        xuy = list->node_arr + xuy->next;

        if (i > list->nodes_number)
            {
            func_message("__EBAT__, something wrong with either number of nodes (%d) or list\n", 
                                                                            list->nodes_number);
            break;
            }

        printf(" %3d  ", xuy->data);  // Machine learning failed.

        i++;
        } while (xuy->next != 0);

    printf("\n");
    return;
    }

int AutoListResize(ArsList* list)
    {
    CHECK_PTR(list, /* or */ return FAILURE);  // define OR 
    //VERIFICATE

    // checkig that list has no free nodes
    if (list->first_free_index)   
        return MessageReturn (FAILURE, "List isn't full, to realoc (list->first_free_index != 0)\n");
   
    if (list->capacity != list->nodes_number)
        return MessageReturn (FAILURE, "List isn't full, to realoc (list->capacity != list->nodes_number)\n");

    unsigned old_capacity = list->capacity;
    unsigned new_capacity = old_capacity * LIST_GROWTH_RATE; 

    // realloc
    node* temp_arr = (node*) realloc (list->node_arr, (new_capacity + 1) * sizeof(temp_arr[0]));
    CHECK_PTR_RET(temp_arr, return FAILURE);
    
    // setting new free nodes
    for (index_t i = old_capacity + 1; i < new_capacity + 1; i++) 
        {
        (temp_arr + i)->next = (i + 1) % (new_capacity + 1);
        (temp_arr + i)->data = 0;
        (temp_arr + i)->prev = -1;
        }

    // setting list
    list->node_arr         = temp_arr;
    list->capacity         = new_capacity;
    list->first_free_index = old_capacity + 1; // check!!!

    return SUCCESS;
    }

ArsList* SortAndRealloc (ArsList* list, index_t new_size)
    {
    CHECK_PTR_RET(list, return NULL);
    // VERIFICATE
    
    if (new_size < MIN_LIST_CAPACITY)   return NULL;

    // setting new nodes array
    node* temp_arr = (node*) calloc (new_size + 1, sizeof(temp_arr[0]));
    CHECK_PTR_RET(temp_arr, return NULL);

    for (index_t i = 1; i < new_size + 1; i++)
        {
        (temp_arr[i]).data = 0;

        (temp_arr[i]).next = (i + 1) % (new_size + 1); 
        (temp_arr[i]).prev = -1;   
        }

    // setting zero node
    temp_arr->data = CRINGE;
    temp_arr->next = 1;
    temp_arr->prev = (list->capacity > new_size) ? new_size:list->nodes_number;

    // setting new nodes array
    node* node_arr = list->node_arr;
    node* old_node = node_arr + node_arr->next;
    int nodes_number = list->nodes_number;
    for (index_t i = 1; i < new_size + 1 && nodes_number; i++, nodes_number--)
        {
        node* new_node = temp_arr + i;

        new_node->data = old_node->data;
        new_node->prev = i - 1;   // i ain't sure about this line

        if (!old_node->next)      // if it is last active node
            new_node->next = 0; 

        old_node = node_arr + old_node->next;       
        }

    // setting list
    list->nodes_number     = (new_size < list->capacity) ? new_size : list->nodes_number;
    list->first_free_index = (new_size < list->capacity) ? 0        : list->nodes_number + 1; // I am't sure about this
    list->capacity         =  new_size;
    list->shuffle_status   = LINEAR;
    list->node_arr         = temp_arr;
    
    return list;    
    }

