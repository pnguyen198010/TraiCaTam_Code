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
#define LOG_PORT            Serial
#define LOG_BAUD_RATE       115200


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

    private: uint8_t id;
    private: static bool flg_init;
};


/* ==================================================
** Extern function declaration
**
** =============================================== */


//


/* ==================================================
** Extern variables
**
** =============================================== */


//


#endif