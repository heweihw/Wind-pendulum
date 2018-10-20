#include "JY901.h"
#include "string.h"

//***************************iic part********************************

struct STime		stcTime;
struct SAcc 		stcAcc;
struct SGyro 		stcGyro;
struct SAngle 	stcAngle;
struct SMag 		stcMag;
struct SDStatus stcDStatus;
struct SPress 	stcPress;
struct SLonLat 	stcLonLat;
struct SGPSV 		stcGPSV;

extern unsigned char rxBuffer[250];
void SerialEnventListener(unsigned char data) {
	
static unsigned char rxCnt = 0;
	
	rxBuffer[rxCnt++] = data;
	if (rxBuffer[0] != 0x55) {
		rxCnt = 0;
		return;
	}
	if (rxCnt < 11) {
		return;
	} else {
		switch (rxBuffer[1]) {
			case 0x50:	memcpy(&stcTime, &rxBuffer[2],8); break;
			case 0x51:	memcpy(&stcAcc, &rxBuffer[2],8); break;
			case 0x52:	memcpy(&stcGyro, &rxBuffer[2],8); break;
			case 0x53:	memcpy(&stcAngle, &rxBuffer[2],8); break;
			case 0x54:	memcpy(&stcMag, &rxBuffer[2],8); break;
			case 0x55:	memcpy(&stcDStatus, &rxBuffer[2],8); break;
			case 0x56:	memcpy(&stcPress, &rxBuffer[2],8); break;
			case 0x57:	memcpy(&stcLonLat, &rxBuffer[2],8); break;
			case 0x58:	memcpy(&stcGPSV, &rxBuffer[2],8); break;
		} 
		rxCnt = 0;
	}
		
}
extern u16 p_r,i_r,d_r;
void receive(unsigned char data)
{
	static unsigned char rxCnt = 0;
	rxBuffer[rxCnt++]=data;
	if(rxBuffer[rxCnt-1]==0x6b)
	{
		if(rxBuffer[rxCnt-2]==0x6f)
		{
			p_r=rxBuffer[rxCnt-8];
			p_r=p_r<<8;
			p_r=p_r&rxBuffer[rxCnt-7];
			i_r=rxBuffer[rxCnt-6];
			i_r=i_r<<8;
			i_r=i_r&rxBuffer[rxCnt-5];
			d_r=rxBuffer[rxCnt-4];
			d_r=d_r<<8;
			d_r=d_r&rxBuffer[rxCnt-3];
			rxCnt=0;
		}
	}
}