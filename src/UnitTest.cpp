#include "ArsList.h"

int FirstTest(ArsList* lisr);
int SecondTest(ArsList* list);
int UnitTest(void);

int UnitTest(void)
    {
    ArsList list = {};
    CtorArsList(&list);

    int status = FirstTest(&list);

    return status;
    }

int FirstTest(ArsList* list)
    {
    AddBack(list, 10);


    return SUCCESS;
    }