#include "ArsList.h"
#include "VisualDump.h"

FILE* HtmlLog = SetHtmlLog ();

int main()
    {

    ArsList test_list = {};
    CtorArsList(&test_list, 1);
   
   AddBack(&test_list, 14);
    AddBack(&test_list, 15);
    VisualDump (&test_list);
    $$
    AddBack(&test_list, 17);
    AddBack(&test_list, 19);
    
    Insert(&test_list, 0, 5); // error when position == tail
    //ShowList(&test_list);
    
    //int test = Delete(&test_list, 1); // delete head      +
   // $i(test)                    // delete tail       +
                           // delete empty node !!! error
                           // delete labs
                            // ret val
   // getchar();
    //AddBack(&test_list, 69);
    VisualDump(&test_list);
    $$

   // ShowList(&test_list); // problem with showing list when nodes number == capacity
    //ConsoleDump(&test_list);
    //printf("TEST: %d\n", -1 % 10); // 10 - (i)
    }