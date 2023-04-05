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


static bool flg_upd = false;


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


Log_t::Log_t(bool flg_disable)
{
    this->flg_disable = flg_disable;
}


/* ==================================================
** Log_t: Methods
**
** =============================================== */


void Log_t::raw(const char *format)
{
#ifdef LOG_PORT

    if(flg_disable) {return;}

    if(flg_upd) {
        raw("\n");
        flg_upd = false;
    }

    LOG_PORT.print(format);

#endif
}


void Log_t::fmt(const char *format, ...)
{
#ifdef LOG_PORT

    if(flg_disable) {return;}

    if(flg_upd) {
        raw("\n");
        flg_upd = false;
    }

    char buffer[128];
    va_list args;

    va_start(args, format);
    vsnprintf(buffer, sizeof(buffer), format, args);

    char loc_buf[64];
    char * temp = loc_buf;

    va_list arg;
    va_list copy;

    va_start(arg, format);
    va_copy(copy, arg);

    int len = vsnprintf(temp, sizeof(loc_buf), format, copy);
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

        len = vsnprintf(temp, len+1, format, arg);
    }

    va_end(arg);
    LOG_PORT.print(temp);

    if(temp != loc_buf) {free(temp);}

#endif
}


void Log_t::inf(const char *format, ...)
{
#ifdef LOG_PORT

    if(flg_disable) {return;}

    if(flg_upd) {
        raw("\n");
        flg_upd = false;
    }

    va_list args;
    va_start(args, format);

    fmt("I (%lu) ", millis());
    fmt(format, args);
    raw("\n");

#endif
}


void Log_t::err(const char *format, ...)
{
#ifdef LOG_PORT

    if(flg_disable) {return;}

    if(flg_upd) {
        raw("\n");
        flg_upd = false;
    }

    va_list args;
    va_start(args, fmt);

    fmt("E (%lu) ", millis());
    fmt(format, args);
    raw("\n");

#endif
}


void Log_t::upd(const char *format, ...)
{
#ifdef LOG_PORT

    if(flg_disable) {return;}
    flg_upd = true;

    va_list args;
    va_start(args, fmt);

    fmt("U (%lu) ", millis());
    fmt(format, args);
    raw("\r");

#endif
}


void Log_t::enable()
{
    flg_disable = false;
}


void Log_t::disable()
{
    flg_disable = true;
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

