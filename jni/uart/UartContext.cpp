/*
 * UartContext.cpp
 *
 *  Created on: Sep 5, 2017
 *      Author: guoxs
 */
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <memory.h>
#include <termio.h>
#include <sys/ioctl.h>

#include "uart/UartContext.h"
#include "utils/Log.h"

#define UART_DATA_BUF_LEN			16384	// 16KB

/* SynchFrame SlaveAddr MasterAddr DataLen Data CheckSum */
/*     2Byte     2Byte      2Byte   2Byte  N Byte  1Byte */
// 最小长度: 2 + 2 + 2 + 2 + 1 = 9
#define DATA_PACKAGE_MIN_LEN		9

extern void procParse(const BYTE *pData, UINT len);

/**
 * 获取校验码
 */
BYTE getCheckSum(const BYTE *pData, int len) {
	int sum = 0;
	for (int i = 0; i < len; ++i) {
		sum += pData[i];
	}

	return (BYTE) (~sum + 1);
}

UartContext::UartContext() :
	mIsOpen(false),
	mUartID(0),
	mDataBufPtr(NULL),
	mDataBufLen(0) {

}

UartContext::~UartContext() {
	delete[] mDataBufPtr;
	closeUart();
}

bool UartContext::openUart(const char *pFileName, UINT baudRate) {
	LOGD("openUart pFileName = %s, baudRate = %d\n", pFileName, baudRate);
	mUartID = open(pFileName, O_RDWR|O_NOCTTY);

	if (mUartID <= 0) {
		mIsOpen = false;
	} else {
		struct termios oldtio = { 0 };
		struct termios newtio = { 0 };
		tcgetattr(mUartID, &oldtio);

		newtio.c_cflag = baudRate|CS8|CLOCAL|CREAD;
		newtio.c_iflag = 0;	// IGNPAR | ICRNL
		newtio.c_oflag = 0;
		newtio.c_lflag = 0;	// ICANON
		newtio.c_cc[VTIME] = 0; /* inter-character timer unused */
		newtio.c_cc[VMIN] = 1; /* blocking read until 1 character arrives */
		tcflush(mUartID, TCIOFLUSH);
		tcsetattr(mUartID, TCSANOW, &newtio);

		// 设置为非阻塞
		fcntl(mUartID, F_SETFL, O_NONBLOCK);

		mIsOpen = run("uart");
		if (!mIsOpen) {
			close(mUartID);
			mUartID = 0;
		}

		LOGD("openUart mIsOpen = %d\n", mIsOpen);
	}

	return mIsOpen;
}

void UartContext::closeUart() {
	LOGD("closeUart mIsOpen: %d...\n", mIsOpen);
	if (mIsOpen) {
		requestExit();

		close(mUartID);
		mUartID = 0;
		mIsOpen = false;
	}
}

bool UartContext::send(const BYTE *pData, UINT len) {
	if (!mIsOpen) {
		return false;
	}

	if (write(mUartID, pData, len) != len) {	// fail
		LOGD("send Fail\n");
		return false;
	}

	// success
//	LOGD("send Success\n");

	return true;
}

UartContext* UartContext::getInstance() {
	static UartContext sUC;
	return &sUC;
}

bool UartContext::readyToRun() {
	if (mDataBufPtr == NULL) {
		mDataBufPtr = new BYTE[UART_DATA_BUF_LEN];
	}

	if (mDataBufPtr == NULL) {
		closeUart();
	}

	return (mDataBufPtr != NULL);
}

bool UartContext::threadLoop() {
	if (mIsOpen) {
		// 可能上一次解析后有残留数据，需要拼接起来
		int readNum = read(mUartID, mDataBufPtr + mDataBufLen, UART_DATA_BUF_LEN - mDataBufLen);

		if (readNum > 0) {
			const BYTE *pData = mDataBufPtr;
			mDataBufLen += readNum;

			int dataLen;	// 数据包长度
			int frameLen;	// 帧长度
			while (mDataBufLen >= DATA_PACKAGE_MIN_LEN) {
				while ((mDataBufLen >= 2) && ((pData[0] != 0xF0) || (pData[1] != 0x5A))) {
					pData++;
					mDataBufLen--;
					continue;
				}

				if (mDataBufLen < DATA_PACKAGE_MIN_LEN) {
					break;
				}

				dataLen = MAKEWORD(pData[7], pData[6]);
				frameLen = dataLen + DATA_PACKAGE_MIN_LEN;
				if (frameLen > mDataBufLen) {
					// 数据内容不全
					break;
				}

				for (int i = 0; i < frameLen; ++i) {
					printf("%x ", pData[i]);
				}
				printf("\n");

				if (getCheckSum(pData, frameLen - 1) == pData[frameLen - 1]) {
					procParse(pData + DATA_PACKAGE_MIN_LEN - 1, dataLen);
				} else {
					LOGE("CheckSum error!!!!!!\n");
				}

				pData += frameLen;
				mDataBufLen -= frameLen;
			}

			// 数据未解析完
			if ((mDataBufLen > 0) && (mDataBufPtr != pData)) {
				LOGD("mDataBufLen: %d\n", mDataBufLen);

				// 将数据移到头部，方便下一包数据拼接
				memcpy(mDataBufPtr, pData, mDataBufLen);
			}
		} else {
			Thread::sleep(50);
		}

		return true;
	}

	return false;
}
