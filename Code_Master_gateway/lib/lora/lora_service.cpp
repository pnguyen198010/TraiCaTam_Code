/* ==================================================
** Libraries
**
** =============================================== */


#include "lora_service.h"

#include "turbidity.h"


/* ==================================================
** Macro definition
**
** =============================================== */


#define LORA_RX         5
#define LORA_TX         6
#define LORA_AUX        21
#define LORA_M0         25
#define LORA_M1         26

#define LORA_BAUD_RATE  UART_BPS_RATE_9600

#define LORA_ADDL       0x0
#define LORA_ADDH       0x1
#define LORA_CHAN       0x18

#define LORA_CHAN_TURBIDITY	0x19
#define LORA_CHAN_BELL		0x20

#define STR_TURBIDITY_1_FALSE	"0-0"
#define STR_TURBIDITY_1_TRUE	"0-1"
#define STR_TURBIDITY_2_FALSE	"1-0"
#define STR_TURBIDITY_2_TRUE	"1-1"
#define STR_TURBIDITY_3_FALSE	"2-0"
#define STR_TURBIDITY_3_TRUE	"3-1"

#define STR_BELL_ALERT_NONE		"0"
#define STR_BELL_ALERT_1		"1"
#define STR_BELL_ALERT_2		"2"


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

// static const uint32_t TIME_UPD_TURBIDITY = 1 * 60 * 1000;

static LoRa_E32 e32ttl100(&Serial2, LORA_AUX, LORA_M0, LORA_M1, LORA_BAUD_RATE);


/* ==================================================
** Static function declaration
**
** =============================================== */


// static void printParameters(struct Configuration configuration);
// static void printModuleInformation(struct ModuleInformation moduleInformation);


/* ==================================================
** Static function definition
**
** =============================================== */


// void printParameters(struct Configuration configuration) 
// {
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

// }


// void printModuleInformation(struct ModuleInformation moduleInformation) 
// {
	// Serial.println("----------------------------------------");
	// Serial.print(F("HEAD BIN: "));  Serial.print(moduleInformation.HEAD, BIN);Serial.print(" ");Serial.print(moduleInformation.HEAD, DEC);Serial.print(" ");Serial.println(moduleInformation.HEAD, HEX);

	// Serial.print(F("Freq.: "));  Serial.println(moduleInformation.frequency, HEX);
	// Serial.print(F("Version  : "));  Serial.println(moduleInformation.version, HEX);
	// Serial.print(F("Features : "));  Serial.println(moduleInformation.features, HEX);
	// Serial.println("----------------------------------------");

// }

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

	configuration.OPTION.fec                = FEC_1_ON;
	configuration.OPTION.fixedTransmission  = FT_TRANSPARENT_TRANSMISSION;
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


// ResponseStatus Lora_send_fixedMessage(byte ADDH, byte ADDL, byte CHAN, String message)
// {
//     ResponseStatus rs = e32ttl100.sendFixedMessage(ADDH, ADDL, CHAN, message);

    // Serial.println("Send message to 00 03 04");
    // Serial.println(rs.getResponseDescription());

//     return rs;
// }


// void Lora_receive_fixedMessage()
// {
//     if (e32ttl100.available() > 1)
//     {
//         ResponseContainer rs = e32ttl100.receiveMessage();
//         // First of all get the data
//         String message = rs.data;

//         Serial.println(rs.status.getResponseDescription());
//         Serial.println(message);
//     }
// }


// void Lora_upd_turbidity()
// {
// 	static uint32_t intv = millis();

// 	if(millis() - intv < TIME_UPD_TURBIDITY) {return;}

// 	uint8_t turbidity = Turbidity_is_true();
// 	String  message   = String(turbidity);
// 	ResponseStatus rs = e32ttl100.sendFixedMessage(LORA_ADDH_GATEWAY, LORA_ADDL_GATEWAY, LORA_CHAN_GATEWAY, message);
	
//     // Serial.println("Send message to 00 03 04");
//     // Serial.println(rs.getResponseDescription());

// 	intv = millis();
// }




void Lora_receive_turbidity()
{
    if (e32ttl100.available() > 1)
    {
        ResponseContainer rs = e32ttl100.receiveMessage();
        String message = rs.data;

        // Serial.println(rs.status.getResponseDescription());
        // Serial.println(message);

		if(message.equals(STR_TURBIDITY_3_TRUE)
		or message.equals(STR_TURBIDITY_3_TRUE))
		{
			e32ttl100.sendBroadcastFixedMessage(LORA_CHAN_BELL, STR_BELL_ALERT_2);
			return;
		}

		if(message.equals(STR_TURBIDITY_1_TRUE))
		{
			e32ttl100.sendBroadcastFixedMessage(LORA_CHAN_BELL, STR_BELL_ALERT_1);
			return;
		}

		e32ttl100.sendBroadcastFixedMessage(LORA_CHAN_BELL, STR_BELL_ALERT_NONE);
    }
}
