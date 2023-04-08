/* ==================================================
** Libraries
**
** =============================================== */


#include "bell.h"


/* ==================================================
** Macro definition
**
** =============================================== */


#define BELL_PIN        2


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


static uint8_t alert_id = ALERT_NONE;

static uint16_t ticker_alert_1[] = {2000, 2000};
static uint16_t ticker_alert_2[] = {6000, 3000};

static uint8_t ind_ticker = 0;


static const uint8_t SIZE_TICKER_ALERT_1 = sizeof(ticker_alert_1) / sizeof(ticker_alert_1[0]);
static const uint8_t SIZE_TICKER_ALERT_2 = sizeof(ticker_alert_2) / sizeof(ticker_alert_2[0]);


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
** Extern function definition
**
** =============================================== */


void Bell_init()
{
    pinMode(BELL_PIN, OUTPUT);
    digitalWrite(BELL_PIN, LOW);
}


void Bell_alert(Alert_id_t id)
{
    static uint32_t intv = millis();

    if(id != ALERT_CURR && alert_id != id)
    {
        alert_id = id;
        ind_ticker = 0;
        intv = millis();

        digitalWrite(BELL_PIN, alert_id==ALERT_NONE ? LOW : HIGH);
    }

    if(id == ALERT_1)
    {
        if(millis() - intv < ticker_alert_1[ind_ticker]) {return;}

        ind_ticker += 1;
        ind_ticker =  ind_ticker==SIZE_TICKER_ALERT_1 ? 0 : ind_ticker;
        digitalWrite(BELL_PIN, ind_ticker%2 == 0 ? HIGH : LOW);

        intv = millis();

        return;
    }

    if(id == ALERT_2)
    {
        if(millis() - intv < ticker_alert_2[ind_ticker]) {return;}

        ind_ticker += 1;
        ind_ticker =  ind_ticker==SIZE_TICKER_ALERT_2 ? 0 : ind_ticker;
        digitalWrite(BELL_PIN, ind_ticker%2 == 0 ? HIGH : LOW);

        intv = millis();

        return;
    }
}