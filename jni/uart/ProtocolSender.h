/*
 * ProtocolSender.h
 *
 *  Created on: Sep 8, 2017
 *      Author: guoxs
 */

#ifndef _PROTOCOL_SENDER_H_
#define _PROTOCOL_SENDER_H_

#include "CommDef.h"

bool sendProtocol(UINT16 cmdID, BYTE deviceID, const BYTE *pData, UINT16 len);
bool setBeepOn();
#endif /* _PROTOCOL_SENDER_H_ */
