#include "ArsList.h"
#include "VisualDump.h"


#include <errno.h>
FILE* HtmlLog = SetHtmlLog ();

int main()
    {
    ArsList test_list = {};
    CtorArsList(&test_list, 2);

    AddBack(&test_list, 13);
    AddBack(&test_list, 14);
    AddBack(&test_list, 15);
    AddBack(&test_list, 16);
    Insert(&test_list, 0, 6); 
    
    VisualDump(&test_list);

    SortAndRealloc(&test_list, 10);

    Delete(&test_list, 1);

    //ShowList(&test_list);
    VisualDump(&test_list);
    //ConsoleDump(&test_list);
    
    } 