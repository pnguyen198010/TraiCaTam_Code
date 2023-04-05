/* ==================================================
** Libraries
**
** =============================================== */


#include "log.h"


/* ==================================================
** Macro definition
**
** =============================================== */


//


/* ==================================================
** Type definition
**
** =============================================== */


//


/* ==================================================
** Extern variables
**
** =============================================== */


//


/* ==================================================
** Static variables
**
** =============================================== */


//


/* ==================================================
** Static function declaration
**
** =============================================== */


//


/* ==================================================
** Static function definition
**
** =============================================== */


//


/* ==================================================
** Log_t: Constructors
**
** =============================================== */


Log_t::Log_t()
{
}


/* ==================================================
** Log_t: Methods
**
** =============================================== */


void Log_t::raw(const char *fmt)
{
#ifdef LOG_PORT

    if(flg_disable) {return;}
    LOG_PORT.print(fmt);

#endif
}


void Log_t::fmt(const char *fmt, ...)
{
    char buffer[128];
    va_list args;

    va_start(args, fmt);
    vsnprintf(buffer, sizeof(buffer), fmt, args);

    char loc_buf[64];
    char * temp = loc_buf;

    va_list arg;
    va_list copy;

    va_start(arg, fmt);
    va_copy(copy, arg);

    int len = vsnprintf(temp, sizeof(loc_buf), fmt, copy);
    va_end(copy);

    if(len < 0) {
        va_end(arg);
        return;
    };

    if((unsigned long)len >= sizeof(loc_buf))
    {
        temp = (char*) malloc(len+1);

        if(temp == NULL) {
            va_end(arg);
            return;
        }

        len = vsnprintf(temp, len+1, fmt, arg);
    }

    va_end(arg);
    LOG_PORT.print(temp);

    if(temp != loc_buf) {free(temp);}
}


/* ==================================================
** Extern function definition
**
** =============================================== */


void Log_init()
{
#ifdef LOG_PORT

    LOG_PORT.begin(LOG_BAUD_RATE);
    delay(LOG_TIME_INIT);

    LOG_PORT.print(F("\n\n"));

#endif
}

