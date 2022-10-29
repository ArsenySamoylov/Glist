#ifndef HOW_TO_SPEND_SCHOLARSHIP
#define HOW_TO_SPENF_SCHOLARSHIP

#include "ArsList.h"
#include <stdlib.h>

void CloseHtmlLog ();
FILE* SetHtmlLog   ();

extern FILE* HtmlLog;

const int MAX_GRAPH_NAME_LENGTH = 40;
const int SYSTEM_COMMAND_LENGTH = 30;
const int     IMAGE_NAME_LENGTH = 15;

const char* GetImage (ArsList* list);
void SetDot       (FILE* dot);
void SetNodesArr  (FILE* dot, ArsList* list);
void SetListStatus(FILE* dot, ArsList* list);
void SetEndDot    (FILE* dot);

#define hlog(...) fprintf(HtmlLog, __VA_ARGS__)


#define set_func_name   fprintf (dot, "########################################################### %s\n", __func__);
#define dot_print(...)  fprintf (dot, __VA_ARGS__)

#define node_print(node, node_num) {                                                                                                                          \
                                    dot_print("\t\tnode%d [shape = Mrecord label = \"node %d | {<next%d> next %d} | {data %d} | {<prev%d> prev %d}\"]\n",     \
                                                  node_num,                          node_num, node_num, (node)->next, (node)->data, node_num, (node)->prev); \
                                   }

#define connect_node(first, second) {                                                                          \
                                    dot_print("\t\tnode%d -- node%d     [weight = 301,  style = \"invis\"]\n", \
                                                     first,   second);                                         \
                                    }

#define connect_next(node, next) {                                            \
                                 dot_print("\t\tnode%d:<next%d> -- node%d\n", \
                                                    node, node,      next);   \
                                 }

#define connect_prev(node, prev) {                                              \
                                 dot_print("\t\tnode%d:<prev%d> -- node%d\n\n", \
                                                  node,   node,     prev);      \
                                 }

#define connect_next_with_zero(node) {                                                \
                                     dot_print("\t\tnode%d:<next%d> -- zero_node\n",\
                                                 node,    node);                      \
                                     }

#define connect_prev_with_zero(node) {                                                \
                                     dot_print("\t\tnode%d:<prev%d> -- zero_node\n\n",\
                                                      node,    node);                 \
                                     }

#endif