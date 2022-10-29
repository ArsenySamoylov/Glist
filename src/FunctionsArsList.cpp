#include "ArsList.h"

// CONST !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
inline index_t TailIndex (ArsList* list)
    {
    // $i((list->node_arr)->prev)
    return (list->node_arr)->prev;
    }

inline node* GetTail (ArsList* list)
    {
    return list->node_arr + TailIndex(list); // node_arr + zero_node->tail
    }

inline index_t FirstFreeIndex (ArsList* list)
    {
    return ((list->node_arr + (list->node_arr)->prev))->next; // tail->next
    }
// maybe make Actibvate First Free where also set new tail???
inline node* GetFirstFree (ArsList* list) 
    {
    return list->node_arr + FirstFreeIndex(list);
    }

// SortList
// 
index_t Swap   (); // just change data and check prev for -1


index_t AddBack (ArsList* list, element_t data)
    {
    CHECK_PTR_RET(list, return 0);
    //VERIFICATE
    node* node_arr = list->node_arr;

    node* zero_node = node_arr;
    node* tail = node_arr + zero_node->prev; // change to GetTail

    if (tail->next == 0)
        {
        if (list->capacity != list->nodes_number)
            {
            func_message("Error, tail points to zero node, but nodes number != capacity\n");
            return 0;
            }

        int status = AutoListResize(list);
        if (status != SUCCESS)
            {
            func_message("Ebat, oshibOCHKA, problem in resizing list\n");
            return 0;
            }
        
        node_arr = list->node_arr;
        tail = GetTail (list);
        }
    // afrer rezise tail is INVALID!!!
    index_t new_node_index = tail->next;
    // $i(new_node_index)
    // $$
    node* new_node = node_arr + new_node_index; // change to GetFirstFree()
    
    new_node->data = data;              // setting new_node
    new_node->prev = zero_node->prev;

    zero_node->prev = tail->next;      // setting new tail
    // there is no need to change prev or next cause they alredy all connected
    ++(list->nodes_number);

    return new_node_index;
    }

// //! @todo: 
// index_t AddBack (ArsList* list, element_t data)
//     {    
//     return Insert(list, TailIndex(list), data);
//     }

index_t AddFront (ArsList* list, element_t data)
    {
    return Insert(list, 0, data);    
    }

//! @note this function insert's elelement after given element and returns its index
//! don't forget about shuffled and unshuffled thing
index_t Insert (ArsList* list, index_t position, element_t data)
    {
    if(!list)   return 0;
    //VERIFICATE
    node* node_arr = list->node_arr;

    //checking position
    if (position < 0)
        {
        func_message("%d - is inccorrect index\n", position);
        return 0;
        }      

    if ((node_arr + position)->prev == -1) 
        {
        func_message("Element %d is free, so you can't add element after it\n");
        return 0;
        }

    if (position == TailIndex(list))
        return AddBack(list, data);

    if (list->capacity - 1 == list->nodes_number)
        {
        int status = AutoListResize(list);
        if (status != SUCCESS)
            {
            func_message("Ebat, oshibOCHKA, problem in resizing list\n");
            return 0;
            }
        
        node_arr = list->node_arr;
        }

    // inserttin new node
    node* tail = GetTail(list);

    node*   new_node            = node_arr + tail->next;
    index_t new_node_index      = tail->next;
    index_t new_free_node_index = new_node->next;

    node* current_node = node_arr + position;
    // // what if new_node is new tail ???
    // // test
    // node_arr->prev =                       // setting zero_node tail 
    // tail = GetTail(list);
    // //

    tail->next  = new_free_node_index;                  // setting tail
    
    new_node->prev = position;                          // setting new node
    new_node->next = current_node->next;
    new_node->data = data;

    current_node->next = new_node_index;                // settin previous node
   
    (node_arr + new_node->next)->prev = new_node_index; // setting next node

    ++(list->nodes_number);                             // setting list
    list->data_shuffle_status = SHUFFLED;
    
    return new_node_index; 
    }

//! @note returns Last index after deleting
index_t DeleLast(ArsList* list)
    {
    CHECK_PTR_RET(list, return 0);
    //VERIFICATE
    node* zero_node = list->node_arr;

    index_t last = zero_node->prev; // zero_node->tail
    if (!last)
        {
        func_message("List allready empty!\n");
        return 0;
        }

    node* ready_to_die = list->node_arr + last;

    zero_node->prev = ready_to_die->prev; // know tail is previous from ready_to_die
    
    ready_to_die->prev = -1;
    ready_to_die->data = 0;

    --(list->nodes_number);

    return zero_node->prev;
    }

element_t Delete(ArsList* list, index_t index)
    {
    CHECK_PTR_RET(list, return 0);
    //VERIFICATE
    //$i(list->nodes_number)
    if (index < 1)
        {
        func_message("Wrong index (%d)\n", index);
        return 0;
        }
    node* node_arr = list->node_arr;

    node* ready_to_die =  node_arr + index;
    
    if (ready_to_die->prev == -1)
        {
        func_message("You are trying to delete not existing node\n");
        //$i(list->nodes_number)

        return 0;
        }

    node* prev_node = node_arr + (ready_to_die->prev);
    node* next_node = node_arr + (ready_to_die->next);

    if (next_node->prev == -1)   // set new tail
        {
        node_arr->prev = ready_to_die->prev; // setting new tail
        }
    else
        {
        list->data_shuffle_status = SHUFFLED;  
        func_message("From now on list is SHUFFLED\n");

        next_node->prev = ready_to_die->prev; 
        prev_node->next = ready_to_die->next;

        node* tail = node_arr + node_arr->prev;

        ready_to_die->next = tail->next;
        tail->next = index;
        }
    

    // deleting data from node
    element_t temp = ready_to_die->data;

    ready_to_die->data = 0;
    ready_to_die->prev = -1;

    --(list->nodes_number);

    return temp; 
    }

void ShowList (ArsList* list)
    {
    CHECK_PTR_RET(list, return);
    //VERIFICATE

    node* xuy = list->node_arr + (list->node_arr)->next; // node_arr + head;
    
    printf("Elements (in logical order)\n");
    #pragma GCC diagnostic ignored "-Wsign-compare"
    for(index_t i = 1; i <= list->nodes_number; i++)
        {
        printf(" [%02d] ", i);
        }
    printf("\n");

    int i = 0;
    while (xuy->prev != -1)
        {
        if (i > list->nodes_number)
            {
            func_message("Ebat, something wrong with either number of nodes (%d) or list\n", 
                                                                            list->nodes_number);
            break;
            }

        printf(" %3d  ", xuy->data);

         if (xuy->next == 0)
            break;

        xuy = list->node_arr + xuy->next;

        i++;
        }
    printf("\n");
    return;
    }

int AutoListResize(ArsList* list)
    {
    CHECK_PTR_RET(list, return FAILURE);
    //VERIFICATE

    // checking that list has no free nodes
    index_t tail_index = (list->node_arr)->prev; // (zero_node)->tail
    if ((list->node_arr + tail_index)->next)   // if it's not 0, then list has free nodes
        {
        func_message("List isn't full, to realoc\n");
        return FAILURE;
        }

    unsigned old_capacity = list->capacity;
    unsigned new_capacity = old_capacity * LIST_GROWTH_RATE; 

    // realloc
    node* temp_arr = (node*) realloc (list->node_arr, (new_capacity + 1) * sizeof(temp_arr[0]));
    CHECK_PTR_RET(temp_arr, return FAILURE);
    
    // setting new conections between nodes
    (temp_arr + tail_index)->next = old_capacity + 1; // add new free node_arr to tail
    for(index_t i = old_capacity + 1; i < new_capacity + 1; i++) 
        {
        (temp_arr + i)->next = (i + 1) % (new_capacity + 1);
        (temp_arr + i)->data = 0;
        (temp_arr + i)->prev = -1;
        }

    // setting list
    list->node_arr = temp_arr;
    list->capacity = new_capacity;

    return SUCCESS;
    }