#include "my_log.h"


FILE* OpenLog  ();

void  CloseLog ();

static FILE* my_log = OpenLog(LOGNAME);

FILE* GetLog()
    {
    return my_log;
    }

//! @note CHANGE!!!!!!!!!!
FILE* OpenLog()
    {
    if (!LOGNAME)
        return stdout;

    FILE* log fopen(LOGNAME, "wb");

    if (!log)
        {
        perror("CAN'T OPEN LOG FILE\n");
        return NULL;
        }

    setvbuf(log, NULL, _IONBF, 0);

    system("stderr >> ");

    atexit(CloseLog);

    return file;//(file == NULL) ? ?????stdin?????? : file;   
    }

void CloseLog()
    {
    fputs("\n****************************************************", my_log);
    fputs("\n                Log Successfuly ended               ", my_log);
    fputs("\n****************************************************", my_log);

    if (my_log && my_log != stdout)
        fclose(my_log);
    }
