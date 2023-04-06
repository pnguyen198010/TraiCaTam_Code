/* ==================================================
** Libraries
**
** =============================================== */


#include "lora_service.h"

#include <LoRa_E32.h>
#include <SoftwareSerial.h>


/* ==================================================
** Macro definition
**
** =============================================== */


#define LORA_RX         5
#define LORA_TX         6
#define LORA_AUX        4
#define LORA_M0         7
#define LORA_M1         8

#define LORA_BAUD_RATE  UART_BPS_RATE_9600

#define LORA_ADDL       0x0
#define LORA_ADDH       0x2
#define LORA_CHAN       0x19


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


// static const byte LORA_RX        = 3;
// static const byte LORA_TX        = 4;
// static const byte LORA_AUX       = 5;
// static const byte LORA_M0        = 5;
// static const byte LORA_M1        = 6;

// static const byte LORA_ADDL      = 0x0;
// static const byte LORA_ADDH      = 0x2;
// static const byte LORA_CHAN      = 0x19;

static SoftwareSerial mySerial(LORA_TX, LORA_RX);
static LoRa_E32 e32ttl100(&mySerial, LORA_AUX, LORA_M0, LORA_M1, LORA_BAUD_RATE);


/* ==================================================
** Static function declaration
**
** =============================================== */


static void printParameters(struct Configuration configuration);
static 
void printModuleInformation(struct ModuleInformation moduleInformation);


/* ==================================================
** Static function definition
**
** =============================================== */


void printParameters(struct Configuration configuration) 
{
	// Serial.println("----------------------------------------");

	// Serial.print(F("HEAD : "));  Serial.print(configuration.HEAD, BIN);Serial.print(" ");Serial.print(configuration.HEAD, DEC);Serial.print(" ");Serial.println(configuration.HEAD, HEX);
	// Serial.println(F(" "));
	// Serial.print(F("AddH : "));  Serial.println(configuration.ADDH, BIN);
	// Serial.print(F("AddL : "));  Serial.println(configuration.ADDL, BIN);
	// Serial.print(F("Chan : "));  Serial.print(configuration.CHAN, DEC); Serial.print(" -> "); Serial.println(configuration.getChannelDescription());
	// Serial.println(F(" "));
	// Serial.print(F("SpeedParityBit     : "));  Serial.print(configuration.SPED.uartParity, BIN);Serial.print(" -> "); Serial.println(configuration.SPED.getUARTParityDescription());
	// Serial.print(F("SpeedUARTDatte  : "));  Serial.print(configuration.SPED.uartBaudRate, BIN);Serial.print(" -> "); Serial.println(configuration.SPED.getUARTBaudRate());
	// Serial.print(F("SpeedAirDataRate   : "));  Serial.print(configuration.SPED.airDataRate, BIN);Serial.print(" -> "); Serial.println(configuration.SPED.getAirDataRate());

	// Serial.print(F("OptionTrans        : "));  Serial.print(configuration.OPTION.fixedTransmission, BIN);Serial.print(" -> "); Serial.println(configuration.OPTION.getFixedTransmissionDescription());
	// Serial.print(F("OptionPullup       : "));  Serial.print(configuration.OPTION.ioDriveMode, BIN);Serial.print(" -> "); Serial.println(configuration.OPTION.getIODroveModeDescription());
	// Serial.print(F("OptionWakeup       : "));  Serial.print(configuration.OPTION.wirelessWakeupTime, BIN);Serial.print(" -> "); Serial.println(configuration.OPTION.getWirelessWakeUPTimeDescription());
	// Serial.print(F("OptionFEC          : "));  Serial.print(configuration.OPTION.fec, BIN);Serial.print(" -> "); Serial.println(configuration.OPTION.getFECDescription());
	// Serial.print(F("OptionPower        : "));  Serial.print(configuration.OPTION.transmissionPower, BIN);Serial.print(" -> "); Serial.println(configuration.OPTION.getTransmissionPowerDescription());

	// Serial.println("----------------------------------------");

}


void printModuleInformation(struct ModuleInformation moduleInformation) 
{
	// Serial.println("----------------------------------------");
	// Serial.print(F("HEAD BIN: "));  Serial.print(moduleInformation.HEAD, BIN);Serial.print(" ");Serial.print(moduleInformation.HEAD, DEC);Serial.print(" ");Serial.println(moduleInformation.HEAD, HEX);

	// Serial.print(F("Freq.: "));  Serial.println(moduleInformation.frequency, HEX);
	// Serial.print(F("Version  : "));  Serial.println(moduleInformation.version, HEX);
	// Serial.print(F("Features : "));  Serial.println(moduleInformation.features, HEX);
	// Serial.println("----------------------------------------");

}

/* ==================================================
** Extern function definition
**
** =============================================== */


void Lora_init()
{
	e32ttl100.begin();

	ResponseStructContainer c   = e32ttl100.getConfiguration();
	Configuration configuration = *(Configuration*) c.data;

	// Serial.println(c.status.getResponseDescription());
	// Serial.println(c.status.code);
	// printParameters(configuration);

	configuration.ADDL = LORA_ADDL;
	configuration.ADDH = LORA_ADDH;
	configuration.CHAN = LORA_CHAN;

	configuration.OPTION.fec                = FEC_0_OFF;
	configuration.OPTION.fixedTransmission  = FT_FIXED_TRANSMISSION;
	configuration.OPTION.ioDriveMode        = IO_D_MODE_PUSH_PULLS_PULL_UPS;
	configuration.OPTION.transmissionPower  = POWER_17;
	configuration.OPTION.wirelessWakeupTime = WAKE_UP_1250;

	configuration.SPED.airDataRate  = AIR_DATA_RATE_010_24;
	configuration.SPED.uartBaudRate = UART_BPS_9600;
	configuration.SPED.uartParity   = MODE_00_8N1;

	ResponseStatus rs = e32ttl100.setConfiguration(configuration, WRITE_CFG_PWR_DWN_LOSE);

	// Serial.println(rs.getResponseDescription());
	// Serial.println(rs.code);
	// printParameters(configuration);

	c.close();
}


ResponseStatus Lora_sendFixedMessage(byte ADDH, byte ADDL, byte CHAN, String message)
{
    ResponseStatus rs = e32ttl100.sendFixedMessage(ADDH, ADDL, CHAN, message);

    // Serial.println("Send message to 00 03 04");
    // Serial.println(rs.getResponseDescription());

    return rs;
}