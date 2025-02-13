/******************************************/
/* [AMDS]   변경된 Protocal      24.12.09 */
/******************************************/

//---------------------------------------------
// 콘솔형
//---------------------------------------------
//
typedef struct {

	//Prefix
	uint16_t Prefix;		//0xAABB

	//Header
	uint8_t Sender;			//0x0010
	uint8_t Receiver;		//0x0020
	uint16_t Command;		//0x0001
	uint32_t Count;
	uint16_t Size;

	//개별 항목
	float Temp1;			//Temp1 value
	float Temp2;			//Temp2 value
	uint8_t FANAssy1;		//Fan Ass'y1 bit-wise status
	uint8_t FANAssy2;		//Fan Ass'y2 bit-wise status
	uint8_t PSU1;			//PSU1 Status
	uint8_t PSU2;			//PSU2 Status

	//개별항목, LED항목
	uint8_t LED_DP1;		//DP1 Status(개별항목 겸용)
	uint8_t LED_DP2;		//DP2 Status (개별항목 겸용)

	//LED 항목
	uint8_t LED_PSU;		//PSU1 Status + PSU2 Status
	uint8_t LED_Temp;		//Temp1 Status + Temp2 Status
	uint8_t LED_FAN1;		//fan1 + fan2 + fan3 status
	uint8_t LED_FAN2;		//fan4 + fan5 + fan6 status

	//기타
	uint8_t MineDet_Num;	//Mine Detection Number

	//Sufix
	uint16_t Sufix;		//0xEDFF

} ConsoleStatusPacket_t;



//---------------------------------------------
// 이동형
//---------------------------------------------
//
typedef struct {

	//Prefix
	uint16_t Prefix;		//0xAABB

	//Header
	uint8_t Sender;
	uint8_t Receiver;
	uint16_t Command;
	uint32_t Count;
	uint16_t Size;

	//개별 항목
	float Temp1;			//Temp1 value
	float Temp2;			//Temp2 value
	uint8_t FAN1;			//Fan1 Status
	uint8_t FAN2;			//Fan2 Status

	//개별항목, LED항목
	uint8_t LED_DP1;		//DP1 Status(개별항목 겸용)
	uint8_t LED_DP2;		//DP2 Status(개별항목 겸용)
	uint8_t LED_DP3;		//DP3 Status(개별항목 겸용)

	//LED 항목
	uint8_t LED_Temp;		//Temp1 Status + Temp2 Status
	uint8_t LED_FAN;		//Fan1 Status + Fan2 Status

	//개별항목, LED항목
	uint8_t LED_Charger;	//Charger Status

	//-----------------
	//BATTERY Variables
	uint16_t Bat_SOC;		//Bat SOC(%) / 3-digit FND Display

	//개별항목(Non-Display)
	uint16_t Bat_Volt;
	uint16_t Bat_Current;
	uint16_t Bat_CycleCnt;
	uint16_t Bat_Temp;

	//기타
	uint8_t MineDet_Num;	//Mine Detection Number

	//Sufix
	uint16_t Sufix;		//0xEDFF

} PortableStatusPacket_t;
