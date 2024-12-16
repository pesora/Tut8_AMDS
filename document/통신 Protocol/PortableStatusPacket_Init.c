typedef struct {

	//Header
	status.Sender = 0;
	status.Receiver = 0;
	status.Command = 0;
	status.Count = 0;
	status.Size = 0;

	//개별 항목
	status.Temp1 = 0;			//Temp1 value
	status.Temp2 = 0;			//Temp2 value
	status.FAN1 = 0;			//Fan1 Status
	status.FAN2 = 0;			//Fan2 Status

	//개별항목, LED항목
	status.LED_DP1 = 0;		//DP1 Status(개별항목 겸용)
	status.LED_DP2 = 0;		//DP2 Status(개별항목 겸용)
	status.LED_DP3 = 0;		//DP3 Status(개별항목 겸용)

	//LED 항목
	status.LED_Temp = 0.0f;		//Temp1 Status + Temp2 Status
	status.LED_FAN = 0.0f;		//Fan1 Status + Fan2 Status

	//개별항목, LED항목
	status.LED_Charger = 0;	//Charger Status

	//-----------------
	//BATTERY Variables
	status.Bat_SOC = 0;		//Bat SOC(%) / 3-digit FND Display

	//개별항목(Non-Display)
	status.Bat_Volt = 0;
	status.Bat_Current = 0;
	status.Bat_CycleCnt = 0;
	status.Bat_Temp = 0;

	//기타
	status.MineDet_Num = 0;	//Mine Detection Number

} PortableStatusPacket_t = 0;

