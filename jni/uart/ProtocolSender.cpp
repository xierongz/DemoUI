/*
 * ProtocolSender.cpp
 *
 *  Created on: Sep 8, 2017
 *      Author: guoxs
 */

#include "uart/ProtocolSender.h"
#include "uart/UartContext.h"
#include "utils/Log.h"
#include <stdio.h>

extern BYTE getCheckSum(const BYTE *pData, int len);
bool setBeepOn(){

}
bool sendProtocol(UINT16 cmdID, BYTE deviceID, const BYTE *pData, UINT16 len) {
	BYTE dataBuf[256];

	dataBuf[0] = 0xF0;
	dataBuf[1] = 0x5A;	// 同步帧头

	dataBuf[2] = 0x00;
	dataBuf[3] = 0x01;	// 从机地址

	dataBuf[4] = 0x80;
	dataBuf[5] = 0x01;	// 主机地址

	dataBuf[6] = HIBYTE(len+4);
	dataBuf[7] = LOBYTE(len+4);		// 数据域长度

	dataBuf[8] = HIBYTE(cmdID);
	dataBuf[9] = LOBYTE(cmdID);		// cmdID

	dataBuf[10] = deviceID;			// deviceID

	dataBuf[11] = len;	// dataLen

	UINT frameLen = 12;

	// 数据

	LOGD("send UART len[%d] cmd[%04x] devicesid[%02x] data[",len,cmdID,deviceID);
	for (int i = 0; i < len; ++i) {
		dataBuf[frameLen++] = pData[i];
		LOGD("%02X,",pData[i]);
	}
	LOGD("]\n");

	// 校验码
	dataBuf[frameLen] = getCheckSum(dataBuf, frameLen);
	frameLen++;

	return UARTCONTEXT->send(dataBuf, frameLen);
}
