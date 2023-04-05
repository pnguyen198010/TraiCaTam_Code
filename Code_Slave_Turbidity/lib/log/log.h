#ifndef log_h
#define log_h


/* ==================================================
** Libraries
**
** =============================================== */


#include <Arduino.h>


/* ==================================================
** Macro definition
**
** =============================================== */


#define LOG_ENABLE

#ifdef LOG_ENABLE
#define LOG_PORT            Serial
#define LOG_BAUD_RATE       115200
#define LOG_TIME_INIT       2000
#endif


/* ==================================================
** Type definition
**
** =============================================== */


class Log_t
{
    public: Log_t();

    public: void raw (const char *fmt);
    public: void fmt (const char *fmt, ...);
    public: void inf (const char *fmt, ...);
    public: void err (const char *fmt, ...);
    public: void upd (const char *fmt, ...);

    private: bool flg_disable;
};


/* ==================================================
** Extern function declaration
**
** =============================================== */


void Log_init();


/* ==================================================
** Extern variables
**
** =============================================== */


//


#endif