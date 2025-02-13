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

////////////////////////////
//main함수에서 디폴트 설정값을 디스플레이한 후 다음 함수의 
//맨 처음에 "Enter new server IP: " 프롬프트가 뜨는데, 
//이때 아무것도 입력안하고 엔터를 치면 이전의 값을 그대로 사용하고 
//그 다음 프롬프트로 넘어가도록 해줘

void EditConfig(std::string& serverIp, int& serverPort, int& localPort) {
    std::cout << "Enter new server IP: ";
    std::cin >> serverIp;
    std::cout << "Enter new server port: ";
    std::cin >> serverPort;
    std::cout << "Enter new local port: ";
    std::cin >> localPort;

    // Validate inputs
    if (serverPort <= 0 || serverPort > 65535) {
        std::cerr << "Invalid server port. Please enter a number between 1 and 65535." << std::endl;
        return;
    }
    if (localPort <= 0 || localPort > 65535) {
        std::cerr << "Invalid local port. Please enter a number between 1 and 65535." << std::endl;
        return;
    }
}
//++++++++++++++++++
// ANSWER
void EditConfig(std::string& serverIp, int& serverPort, int& localPort) {
    std::string input;

    std::cout << "Enter new server IP (" << serverIp << "): ";
    std::getline(std::cin, input);
    if (!input.empty()) {
        serverIp = input;
    }

    std::cout << "Enter new server port (" << serverPort << "): ";
    std::getline(std::cin, input);
    if (!input.empty()) {
        int port = std::stoi(input);
        if (port > 0 && port <= 65535) {
            serverPort = port;
        } else {
            std::cerr << "Invalid server port. Please enter a number between 1 and 65535." << std::endl;
            return;
        }
    }

    std::cout << "Enter new local port (" << localPort << "): ";
    std::getline(std::cin, input);
    if (!input.empty()) {
        int port = std::stoi(input);
        if (port > 0 && port <= 65535) {
            localPort = port;
        } else {
            std::cerr << "Invalid local port. Please enter a number between 1 and 65535." << std::endl;
            return;
        }
    }
}
