/*
 * bq34z100.h
 *
 *  Created on: Jun 4, 2024
 *      Author: machi
 */

#ifndef BQ34Z100_H_
#define BQ34Z100_H_

#include <stdint.h>
#include <stdbool.h>

typedef struct {
  uint16_t SOC_Val;
  uint16_t Voltage;
  int16_t AvgCurrent;
  uint16_t CycleCount;
  float InternalTemp;
} BatData_t;

#define I2C_BQ34Z100_ADDR   0xAA

// bq34z100 Command Table
//---------------------------+------------+-------+----------+--------------------------------------------------------------
//     NAME                  | COMMAND    | UNIT  |DATA TYPE |  DESCRIPTION
//                           | CODE       |       |          |
//---------+-------------- --+------------+-------+----------+--------------------------------------------------------------
// SOC     | StateOfCharge() | 0x02       | %     | uint16_t | the  predicted  remaining  battery  capacity
//         |                 |            |       |          | with a range of 0 to 100%
// VOLT    | Voltage()       | 0x08/0x09  | mV    | uint16_t | the measured battery voltage in mV
//         |                 |            |       |          | with a range of 0 V to 65535 mV
// AI      | AverageCurrent()| 0x0A/0x0B  | mA    | int16_t  | the average current flowing through the senese resister
//         |                 |            |       |          |
// INTTEMP | InteranlTemp()  | 0x2A/0x2B  | 0.1K  | uint16_t | the measured internal temperature of the device,
//         |                 |            |       |          | in units of 0.1 K
// CC      | CycleCount()    |0 x2C/0x2D  | Counts| uint16_t | the number of cycles the battery has experienced
//         |                 |            |       |          | with a range of 0 to 65535
//---------+-----------------+------------+-------+----------+--------------------------------------------------------------

//Standard Data Command
#define CNTL            0x00    //Control
#define SOC             0x02    //State Of Charge
#define RM              0x04    //Remaining Capacity
#define FCC             0x06    //Full Charge Capaciy
#define VOLT            0x08    //Voltage
#define AI              0x0A    //Average Current

//Control Subcommand
#define CONTROL_STATUS  0x0000  //Control Status
#define DEVICE_TYPE     0x0001  //Device Type
#define FW_VERSION      0x0002  //Firmware Version
#define HW_VERSION      0x0003  //Hardware Verison
#define RESETX          0x0041  //Reset

//Extended Data Command
#define INTTEMP         0x2A    //Internal Temp
#define CC              0x2C    //Cycle Count

#define KELVIN          ((float)273.15f)


extern BatData_t Bat;
extern uint16_t BatData16[];

//extern uint16_t SOC_Val;
//extern uint16_t Voltage;
//extern int16_t AvgCurrent;
//extern float  InternalTemp;
//extern uint16_t CycleCount;

void ReadBq34z100(void);
void PrintBq34z100Data(void);
uint8_t i2c_scan(void);


#endif /* BQ34Z100_H_ */
