#include "VisualDump.h"

// vfrintf for some shit

void VisualDump (ArsList* list)
    {    
    if (!list) { hlog("Ebat, null ptr\n"); return;}

    const char* graph = GetImage(list);
    //AddGraphToHLog(graph);

    return;
    }

const char* GetImage (ArsList* list)
    {
    if (!list)  return NULL;

    static int num_of_img = 0;

    char      dot_file [MAX_GRAPH_NAME_LENGTH + 16] = {};
    snprintf (dot_file, MAX_GRAPH_NAME_LENGTH, "graphics/dot/list_num_%d.dot", ++num_of_img);
    printf   ("(%s)", dot_file);
    
    FILE* dot = fopen (dot_file, "wb"); // wb ? 
    if (!dot) return NULL;

    SetDot        (dot);
    SetNodesArr   (dot, list);
    SetListStatus (dot, list);
    SetEndDot     (dot);

    char*     image_name = NULL;
              image_name = (char*) calloc (IMAGE_NAME_LENGTH + 16, sizeof(image_name[0]));
         if (!image_name)  return NULL;
    snprintf (image_name,  IMAGE_NAME_LENGTH, "%d.png", num_of_img);

    char      system_command [SYSTEM_COMMAND_LENGTH + 16] = {};
    snprintf (system_command, SYSTEM_COMMAND_LENGTH, "dot -T png -o %s (%s)", image_name, dot_file);
    $s(system_command)
    $$
    system ("cd graphics/dot/");
    system (system_command);
    
    return image_name;
    }

void SetDot (FILE* dot)
    {
    if (!dot)   return;

    set_func_name;
    dot_print("graph \n{\n");

    return;
    }

void SetNodesArr (FILE* dot, ArsList* list)
    {
    if (!dot)   return;
    if (!list)  return;
    //VERIFICATE
    set_func_name;
    dot_print("\tsubgraph cluster_node_arr\n\t{\n\t\tbgcolor=lightgray\n");

    node* node_arr   = list->node_arr;
    int nodes_number = list->nodes_number;

    /////////////////////////////////////////////////////////////////node array
    //*********************** nodes initialization
    // zero node
    dot_print( "\t\tzero_node  [shape = Mrecord label = \"Zero node | {<head> head %d} | {data %0X} | {<tail> tail %d}\"]\n\n", \
                 node_arr->next, node_arr->data, node_arr->prev);

    for (index_t i = 1; i < nodes_number; i++)  
        node_print(node_arr + i, i);

    //*********************** connect nodes
    // zero node
    dot_print("\n\t\tzero_node -- node1     [weight = 301,  style = \"invis\"]\n");

    for (index_t i = 1; i < nodes_number; i++) 
        connect_node(i, i+1);

    dot_print("\n");
    //*********************** connect prev and next
    // zero node
    // what if tail is zero?
    dot_print("\t\tzero_node:<head> -- node%d\n", node_arr->next);

    if (node_arr->prev != 0)
        dot_print("\t\tzero_node:<tail> -- node%d\n\n", node_arr->prev);

    for (int i = 1; i <nodes_number; i++)
        {
        if ((node_arr + i)->next == 0)
             {connect_next_with_zero(i);}
        else 
            connect_next(i, (node_arr + i)->next);

        if ((node_arr + i)->prev == 0)
             {connect_prev_with_zero(i);}   
        else 
            connect_prev(i, (node_arr + i)->prev); 
        }

    dot_print("\t}\n");
    return;    
    }

void SetListStatus(FILE* dot, ArsList* list)
    {
    if (!dot)   return;
    if (!list)  return;

    set_func_name;

    dot_print("\tLIST [shape = Mrecord label = \"List status:  | \\\n" \
              "\t\t{Capacity %d} | {Active nodes %d} | {%s)}\"]",          \
                  list->capacity,  list->nodes_number, list->data_shuffle_status == SHUFFLED ? "SHUFFLED" : "LINEAR");  

    return;
    }

void SetEndDot (FILE* dot)
    {
    if (!dot)   return;

    set_func_name;

    dot_print("\n\n}"); 

    return;   
    }

#undef set_func_name
#undef dot_print
#undef node_print
#undef connect_node
#undef connect_next
#undef connect_prev
#undef connect_next_with_zero
#undef connect_prev_with_zero

FILE* SetHtmlLog()
    {
    FILE* HtmlLog_ = fopen ("HtmlMaster.html", "wb"); 
    setvbuf (HtmlLog_, NULL, _IONBF, 0);

    fprintf (HtmlLog_, "<pre>");
    fprintf (HtmlLog_, "<h1>My dear log</h1>\n");

    atexit (CloseHtmlLog);
    return HtmlLog_; 
    }

void CloseHtmlLog()
    {
    hlog("<h1> END OF LOG</h1>"); 
    //hlog("</pre>"); some closing tags
    fclose(HtmlLog);
    }

#undef hlog