/*
 * ProtocolParser.cpp
 *
 *  Created on: Sep 7, 2017
 *      Author: guoxs
 */
#include <vector>
#include "CommDef.h"
#include "uart/ProtocolParser.h"
#include "utils/TimeHelper.h"
#include "utils/Log.h"

static std::vector<OnProtocolDataUpdateFun> sProtocolDataUpdateListenerList;

void registerProtocolDataUpdateListener(OnProtocolDataUpdateFun pListener) {
	LOGD("registerProtocolDataUpdateListener\n");
	if (pListener != NULL) {
		sProtocolDataUpdateListenerList.push_back(pListener);
	}
}

void unregisterProtocolDataUpdateListener(OnProtocolDataUpdateFun pListener) {
	LOGD("unregisterProtocolDataUpdateListener\n");
	if (pListener != NULL) {
		std::vector<OnProtocolDataUpdateFun>::iterator iter = sProtocolDataUpdateListenerList.begin();
		for (; iter != sProtocolDataUpdateListenerList.end(); iter++) {
			if ((*iter) == pListener) {
				sProtocolDataUpdateListenerList.erase(iter);
				return;
			}
		}
	}
}

static void notifyProtocolDataUpdate(const SProtocolData &data) {
	std::vector<OnProtocolDataUpdateFun>::const_iterator iter = sProtocolDataUpdateListenerList.begin();
	for (; iter != sProtocolDataUpdateListenerList.end(); iter++) {
		//(&iter)(data);
		(**iter)(data);
	}
}

static SProtocolData sProtocolData = { 0 };

SProtocolData& getProtocolData() {
	return sProtocolData;
}

/*
 * 协议解析
 */
void procParse(const BYTE *pData, UINT len) {
	switch (MAKEWORD(pData[1], pData[0])) {
	case CMDID_POWER:
		sProtocolData.power = pData[4];
		LOGD("power status:%d",sProtocolData.power);
		break;
	case CMDID_RUN_MODE:
		sProtocolData.eRunMode = (ERunMode) pData[4];
		break;
	case CMDID_WIND_SPEED_LEVEL:
		if (pData[2] == 0) {
			sProtocolData.internalWindSpeedLevel = pData[4];
		} else {
			sProtocolData.externalWindSpeedLevel = pData[4];
		}
		break;
	case CMDID_CYCLE_MODEM:
		if (pData[2] == 0) {
			sProtocolData.internalCycle = pData[4];
		} else {
			sProtocolData.externalCycle = pData[4];
		}
		break;
	case CMDID_CHILD_LOCK:
		sProtocolData.childLock = pData[4];
		break;
	case CMDID_UVLIGHT:
		if (pData[2] == 0) {
			sProtocolData.uvSJ = pData[4];
		} else {
			sProtocolData.uvXD = pData[4];
		}
		break;
	case CMDID_ANION:
		if (pData[2] == 0) {
			sProtocolData.anion = pData[4];
		} else {
			sProtocolData.ionCloud = pData[4];
		}
		break;
	case CMDID_FILTER_REPLACE_TIMER:
		switch (pData[2]) {
		case 0:
			sProtocolData.gTimer = MAKEWORD(pData[5], pData[4]);
			break;
		case 1:
			sProtocolData.fTimer = MAKEWORD(pData[5], pData[4]);
			break;
		case 2:
			sProtocolData.hTimer = MAKEWORD(pData[5], pData[4]);
			break;
		case 3:
			sProtocolData.iTimer = MAKEWORD(pData[5], pData[4]);
			break;
		}
		break;
	case CMDID_TIMMING_TIME_CLOSE:
		sProtocolData.closeTime = MAKEWORD(pData[5], pData[4]);
		break;
	case CMDID_TIMMING_TIME_OPEN:
		sProtocolData.openTime = MAKEWORD(pData[5], pData[4]);
		break;
	case CMDID_NOW_TIME:
		sProtocolData.nowTime[0] = pData[4];
		sProtocolData.nowTime[1] = pData[5];
		sProtocolData.nowTime[2] = pData[6];
		sProtocolData.nowTime[3] = pData[7];
		sProtocolData.nowTime[4] = pData[8];
		sProtocolData.nowTime[5] = pData[9];

	{
		struct tm t;
		t.tm_year = 2000 + pData[4] - 1900;
		t.tm_mon = pData[5] - 1;
		t.tm_mday = pData[6];
		t.tm_hour = pData[7];
		t.tm_min = pData[8];
		t.tm_sec = pData[9];

		TimeHelper::setDateTime(&t);
	}
		break;
	case CMDID_BEEP:
		sProtocolData.beep = pData[4];
		break;
	case CMDID_ZIGBEE_PAIR:
		sProtocolData.zigbeePair = pData[4];
		break;
	case CMDID_DEFROST:
		sProtocolData.defrost = pData[4];
		break;
	case CMDID_HEAT:
		sProtocolData.heat = pData[4];
		break;
	case CMDID_HUMIDITY_SET:
		sProtocolData.humidity = MAKEWORD(pData[5], pData[4]);
		break;
	case CMDID_PM2_5_SET:
		sProtocolData.pm2_5Set = MAKEWORD(pData[5], pData[4]);
		break;
	case CMDID_HUMIDIFICATION:
		sProtocolData.humidification = pData[4];
		break;
	case CMDID_FILTER_REPLACE_TIMER_RESET:
		switch (pData[2]) {
		case 0:
			sProtocolData.gFilterReset = pData[4];
			break;
		case 1:
			sProtocolData.fFilterReset = pData[4];
			break;
		case 2:
			sProtocolData.hFilterReset = pData[4];
			break;
		case 3:
			sProtocolData.iFilterReset = pData[4];
			break;
		}
		break;
	case CMDID_FRESH_AIR_SET:
		sProtocolData.freshAir = MAKEWORD(pData[5], pData[4]);
		break;
	case CMDID_EXHAUST_SET:
		sProtocolData.exhaust = MAKEWORD(pData[5], pData[4]);
		break;
	case CMDID_ERROR:
		switch (pData[2]) {
		case 0:
			sProtocolData.sError = pData[4];
			break;
		case 1:
			sProtocolData.iError = pData[4];
			break;
		case 2:
			sProtocolData.gError = pData[4];
			break;
		case 3:
			sProtocolData.hError = pData[4];
			break;
		case 4:
			sProtocolData.fError = pData[4];
			break;
		}
		break;
	case CMDID_ERROR_CLEAR:
		break;
	case CMDID_SYS_STATUS:
		break;
	case CMDID_UPDATE_MCU:
		break;
	case CMDID_SMART_LINK:
		sProtocolData.smartLink = pData[4];
		break;
	case CMDID_DEVICE_TYPE:
		sProtocolData.deviceType = MAKEWORD(pData[5], pData[4]);
		break;
	case CMDID_DISPLAY_CTRL:
		sProtocolData.displayCtrl = pData[4];
		break;
	case CMDID_DISPLAY_ON_TIME:
		sProtocolData.displayOnTime = MAKEWORD(pData[5], pData[4]);
		break;
	case CMDID_PM2_5:
		sProtocolData.pm2_5 = MAKEWORD(pData[5], pData[4]);
		break;
	case CMDID_CO2:
		sProtocolData.co2 = MAKEWORD(pData[5], pData[4]);
		break;
	case CMDID_TVOC:
		sProtocolData.tvoc = pData[4];
		break;
	case CMDID_TEMPERATURE:
		if (pData[2] == 0) {
			sProtocolData.internalTemperature = MAKEWORD(pData[5], pData[4])&0x7ff;
			// 符号位
			if (MAKEWORD(pData[5], pData[4]) & 0x8000) {
				sProtocolData.internalTemperature = -sProtocolData.internalTemperature;
			}
		} else {
			sProtocolData.externalTemperature = MAKEWORD(pData[5], pData[4])&0x7ff;
			if (MAKEWORD(pData[5], pData[4]) & 0x8000) {
				sProtocolData.externalTemperature = -sProtocolData.externalTemperature;
			}
		}
		break;
	case CMDID_HUMIDITY:
		if (pData[2] == 0) {
			sProtocolData.internalHumidity = MAKEWORD(pData[5], pData[4])&0x7ff;
			if (MAKEWORD(pData[5], pData[4]) & 0x8000) {
				sProtocolData.internalHumidity = -sProtocolData.internalHumidity;
			}
		} else {
			sProtocolData.externalHumidity = MAKEWORD(pData[5], pData[4])&0x7ff;
			if (MAKEWORD(pData[5], pData[4]) & 0x8000) {
				sProtocolData.externalHumidity = -sProtocolData.externalHumidity;
			}
		}
		break;
	case CMDID_O2:
		sProtocolData.o2 = MAKEWORD(pData[5], pData[4]);
		break;
	case CMDID_HCHO:
		sProtocolData.hcho = MAKEWORD(pData[5], pData[4]);
		break;
	case CMDID_ESP:
		sProtocolData.esp = pData[4];
		break;
	case CMDID_WATER_SHORTAGE:
		sProtocolData.waterShortage = pData[4];
		break;
	case CMDID_WIFI_STATE:
		sProtocolData.wifiState = pData[4];
		break;
	case CMDID_ERROR_CODE:
		sProtocolData.errorCode = pData[4];
		break;
	}

	notifyProtocolDataUpdate(sProtocolData);
}
