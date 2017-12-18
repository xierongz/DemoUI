/*
*此文件由GUI工具生成
*文件功能：用于处理用户的逻辑相应代码
*功能说明：
*========================onButtonClick_XXXX 
当页面中的按键按下后系统会调用对应的函数，XXX代表GUI工具里面的[标识]名称，
如ButtonChildrenLock,当返回值为false的时候系统将不再处理这个按键，返回true的时候系统将会继续处理此按键。比如SYS_BACK.
*========================onSlideWindowItemClick_XXXX(int index) 
当页面中存在滑动窗口并且用户点击了滑动窗口的图标后系统会调用此函数,XXX代表GUI工具里面的[标识]名称，
如slideWindow1;index 代表按下图标的偏移值
*========================onSeekBarChange_XXXX(int progress) 
当页面中存在滑动条并且用户改变了进度后系统会调用此函数,XXX代表GUI工具里面的[标识]名称，
如SeekBar1;progress 代表当前的进度值
*========================ogetListItemCount_XXXX() 
当页面中存在滑动列表的时候，更新的时候系统会调用此接口获取列表的总数目,XXX代表GUI工具里面的[标识]名称，
如List1;返回值为当前列表的总条数
*========================oobtainListItemData_XXXX(ZKListView::ZKListItem *pListItem, int index)
 当页面中存在滑动列表的时候，更新的时候系统会调用此接口获取列表当前条目下的内容信息,XXX代表GUI工具里面的[标识]名称，
如List1;pListItem 是贴图中的单条目对象，index是列表总目的偏移量。具体见函数说明
*========================常用接口===============
*LOGD(...)  打印调试信息的接口
*mTextXXX->setText("****") 在控件TextXXX上显示文字****
*mButtonChildrenLockPtr->setSelected(true); 将控件mButtonChildrenLock设置为选中模式，图片会切换成选中图片，按钮文字会切换为选中后的颜色
*mSeekBar->setProgress(12) 在控件mSeekBar上将进度调整到12
*mListView1->refreshListView() 让mListView1 重新刷新，当列表数据变化后调用
*mDashbroadView1->setTargetAngle(120) 在控件mDashbroadView1上指针显示角度调整到120度

*/
#include "uart/ProtocolData.h"
#include "uart/ProtocolParser.h"
#include "utils/TimeHelper.h"
#include "uart/ProtocolSender.h"
#include "utils/BrightnessHelper.h"

static SProtocolData mProtocolData;
int year,month,day,hour,minute;
#define PASSWORD_SIZE 6
std::string StrChildpasswd;
std::string StrChildpasswdTemp;
std::string StrChildPaddwdShow;

int passWordChangeStatus;
#define PASSWD_OLDPASS 	1
#define PASSWD_NEWPADSS 2
#define PASSWD_COMFIRMPASSWD	3

// 获取某月的天数
static int getDaysInMonth(int y, int m) {
	int d;
	int day[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
	if (2 == m) {
		d = ((((0 == y % 4) && (0 != y % 100)) || (0 == y % 400)) ? 29 : 28);
	} else {
		d = day[m - 1];
	}

	return d;
}

static void onProtocolDataUpdate(const SProtocolData &data) {
	if (mProtocolData.uvXD != data.uvXD) {
		mProtocolData.uvXD = data.uvXD;
		mbtn_disinfect_switchPtr->setSelected(mProtocolData.uvXD);
	}
	if (mProtocolData.gTimer != data.gTimer) {
		mProtocolData.gTimer = data.gTimer;
		char str[20];
		sprintf(str, "%d小时", mProtocolData.gTimer);
		mtext_g_remaining_timePtr->setText(str);
	}
	if (mProtocolData.fTimer != data.fTimer) {
		mProtocolData.fTimer = data.fTimer;
		char str[20];
		sprintf(str, "%d小时", mProtocolData.fTimer);
		mtext_f_remaining_timePtr->setText(str);
	}
	if (mProtocolData.hTimer != data.hTimer) {
		mProtocolData.hTimer = data.hTimer;
		char str[20];
		sprintf(str, "%d小时", mProtocolData.hTimer);
		mtext_h_remaining_timePtr->setText(str);
	}
	if (mProtocolData.deviceType != data.deviceType) {
		mProtocolData.deviceType = data.deviceType;
		char str[10];
		sprintf(str, "机型%d", mProtocolData.deviceType);

		mtext_device_typePtr->setText(str);
	}
	return;
}
static void updateUI_TimeSet(){
	char timeStr[20];
	//static bool bflash = false;
	struct tm *t = TimeHelper::getDateTime();
	year = t->tm_year+1900;
	month = t->tm_mon+1;
	day = t->tm_mday;
	hour = t->tm_hour;
	minute = t->tm_min;

	char buff[3];
	mTextDateYearPtr->setText(year);
	sprintf(buff,"%02d",month);
	mTextDateMonthPtr->setText(buff);
	sprintf(buff,"%02d",day);
	mTextDateDayPtr->setText(buff);
	sprintf(buff,"%02d",hour);
	mTextDateHourPtr->setText(buff);
	sprintf(buff,"%02d",minute);
	mTextDateMinPtr->setText(buff);
}
static void onUI_init(){
	//Tips :添加 UI初始化的显示代码到这里,如:mText1->setText("123");

	mProtocolData = getProtocolData();
	mbtn_timePtr->setSelected(true);
	mbtn_childlockPtr->setSelected(false);
	mbtn_disinfectPtr->setSelected(false);
	mbtn_operationPtr->setSelected(false);
	mbtn_screenPtr->setSelected(false);
	mbtn_systeminfoPtr->setSelected(false);
	mwindow_settimePtr->showWnd();
	mwindow_InfoPtr->hideWnd();
	mwindow_childlockPtr->hideWnd();
	mwindow_disinfectPtr->hideWnd();
	mwindow_keyboardPtr->hideWnd();
	//mwindow_resetfilterPtr->hideWnd();
	mwindow_screenPtr->hideWnd();
	//mButton_TimerPtr->setSelected(false);
	//mWindowsetTimerPtr->hideWnd();
	updateUI_TimeSet();

	mseekbar_brightnessPtr->setProgress(BRIGHTNESSHELPER->getBrightness());
}
static bool onUI_Timer(int id){
	//Tips:添加定时器响应的代码到这里,但是需要先打开 activity/SetupActivityActivity.cpp onCreate 函数里面的registerTmer
	//id 是定时器设置时候的标签,这里不要写耗时的操作，否则影响UI刷新,ruturn:[true] 继续运行定时器;[false] 停止运行当前定时器
	/*
	if(StrChildPaddwdShow.length()>0){
		int len = StrChildPaddwdShow.length();
		if(!StrChildPaddwdShow.substr(len-2,1).compare("*")){
			StrChildPaddwdShow = StrChildPaddwdShow.substr(0,len - 1);
			StrChildPaddwdShow.push_back('*');
		}
	}
	*/
	return true;
}
static bool onButtonClick_btn_time(ZKButton* pButton){
//LOGD(" ButtonClick btn_time !!!\n");
	setBeepOn();
	mbtn_timePtr->setSelected(true);
	mbtn_childlockPtr->setSelected(false);
	mbtn_disinfectPtr->setSelected(false);
	mbtn_operationPtr->setSelected(false);
	mbtn_screenPtr->setSelected(false);
	mbtn_systeminfoPtr->setSelected(false);
	mwindow_settimePtr->showWnd();
	mwindow_InfoPtr->hideWnd();
	mwindow_childlockPtr->hideWnd();
	mwindow_disinfectPtr->hideWnd();
	mwindow_keyboardPtr->hideWnd();
	//mwindow_resetfilterPtr->hideWnd();
	mwindow_screenPtr->hideWnd();
	//mButton_TimerPtr->setSelected(false);
//	mWindowsetTimerPtr->hideWnd();
	updateUI_TimeSet();
	 return true;
}
static bool onButtonClick_btn_childlock(ZKButton* pButton){
//LOGD(" ButtonClick btn_childlock !!!\n");
	setBeepOn();
	mbtn_timePtr->setSelected(false);
	mbtn_childlockPtr->setSelected(true);
	mbtn_disinfectPtr->setSelected(false);
	mbtn_operationPtr->setSelected(false);
	mbtn_screenPtr->setSelected(false);
	mbtn_systeminfoPtr->setSelected(false);
	mwindow_settimePtr->hideWnd();
	mwindow_InfoPtr->hideWnd();
	mwindow_childlockPtr->showWnd();
	mwindow_disinfectPtr->hideWnd();
	mwindow_keyboardPtr->hideWnd();
	//mwindow_resetfilterPtr->hideWnd();
	mwindow_screenPtr->hideWnd();
	//mButton_TimerPtr->setSelected(false);
	//mWindowsetTimerPtr->hideWnd();
	 return true;
}
static bool onButtonClick_btn_disinfect(ZKButton* pButton){
//LOGD(" ButtonClick btn_disinfect !!!\n");
	setBeepOn();
	mbtn_timePtr->setSelected(false);
	mbtn_childlockPtr->setSelected(false);
	mbtn_disinfectPtr->setSelected(true);
	mbtn_operationPtr->setSelected(false);
	mbtn_screenPtr->setSelected(false);
	mbtn_systeminfoPtr->setSelected(false);
	mwindow_settimePtr->hideWnd();
	mwindow_InfoPtr->hideWnd();
	mwindow_childlockPtr->hideWnd();
	mwindow_disinfectPtr->showWnd();
	mwindow_keyboardPtr->hideWnd();
	//mwindow_resetfilterPtr->hideWnd();
	mwindow_screenPtr->hideWnd();
	//mButton_TimerPtr->setSelected(false);
	//mWindowsetTimerPtr->hideWnd();
	 return true;
}
static bool onButtonClick_btn_operation(ZKButton* pButton){
//LOGD(" ButtonClick btn_operation !!!\n");
	setBeepOn();
	mbtn_timePtr->setSelected(false);
	mbtn_childlockPtr->setSelected(false);
	mbtn_disinfectPtr->setSelected(false);
	mbtn_operationPtr->setSelected(true);
	mbtn_screenPtr->setSelected(false);
	mbtn_systeminfoPtr->setSelected(false);
	mwindow_settimePtr->hideWnd();
	mwindow_InfoPtr->hideWnd();
	mwindow_childlockPtr->hideWnd();
	mwindow_disinfectPtr->hideWnd();
	mwindow_keyboardPtr->hideWnd();
	//mwindow_resetfilterPtr->showWnd();
	mwindow_screenPtr->hideWnd();
	//mButton_TimerPtr->setSelected(false);
	//mWindowsetTimerPtr->hideWnd();
	 return true;
}
static bool onButtonClick_btn_screen(ZKButton* pButton){
//LOGD(" ButtonClick btn_screen !!!\n");
	setBeepOn();
	mbtn_timePtr->setSelected(false);
	mbtn_childlockPtr->setSelected(false);
	mbtn_disinfectPtr->setSelected(false);
	mbtn_operationPtr->setSelected(false);
	mbtn_screenPtr->setSelected(true);
	mbtn_systeminfoPtr->setSelected(false);
	mwindow_settimePtr->hideWnd();
	mwindow_InfoPtr->hideWnd();
	mwindow_childlockPtr->hideWnd();
	mwindow_disinfectPtr->hideWnd();
	mwindow_keyboardPtr->hideWnd();
	//mwindow_resetfilterPtr->hideWnd();
	mwindow_screenPtr->showWnd();
	//mButton_TimerPtr->setSelected(false);
	//mWindowsetTimerPtr->hideWnd();
	return true;
}
static bool onButtonClick_btn_systeminfo(ZKButton* pButton){
//LOGD(" ButtonClick btn_systeminfo !!!\n");
	setBeepOn();
	mTextVersionAppPtr->setText("SkyWalker UI6 20171023");
	mTextVersionMCUPtr->setText("SkyWalker MCU 20171023");
	mTextVersionOSPtr->setText("SkyWalker OS 20171023");
	mbtn_timePtr->setSelected(false);
	mbtn_childlockPtr->setSelected(false);
	mbtn_disinfectPtr->setSelected(false);
	mbtn_operationPtr->setSelected(false);
	mbtn_screenPtr->setSelected(false);
	mbtn_systeminfoPtr->setSelected(true);
	mwindow_settimePtr->hideWnd();
	mwindow_InfoPtr->showWnd();
	mwindow_childlockPtr->hideWnd();
	mwindow_disinfectPtr->hideWnd();
	mwindow_keyboardPtr->hideWnd();
	//mwindow_resetfilterPtr->hideWnd();
	mwindow_screenPtr->hideWnd();
	//mButton_TimerPtr->setSelected(false);
	//mWindowsetTimerPtr->hideWnd();
	return true;
}
static bool onButtonClick_sys_back(ZKButton* pButton){
//LOGD(" ButtonClick sys_back !!!\n");
	setBeepOn();
	 return true;
}
static bool onButtonClick_btn_disinfect_switch(ZKButton* pButton){
//LOGD(" ButtonClick btn_disinfect_switch !!!\n");
	setBeepOn();
	BYTE disinfect = mbtn_disinfect_switchPtr->isSelected() ? 0 : 1;
	sendProtocol(CMDID_UVLIGHT, 1, &disinfect, 1);
	mbtn_disinfect_switchPtr->setSelected(!mbtn_disinfect_switchPtr->isSelected());
	return true;
}
static bool onButtonClick_btn_g_reset(ZKButton* pButton){
//LOGD(" ButtonClick btn_g_reset !!!\n");
	setBeepOn();
	BYTE reset = 1;
	sendProtocol(CMDID_FILTER_REPLACE_TIMER_RESET, 0, &reset, 1);
	 return true;
}
static bool onButtonClick_btn_f_reset(ZKButton* pButton){
//LOGD(" ButtonClick btn_f_reset !!!\n");
	setBeepOn();
	BYTE reset = 1;
	sendProtocol(CMDID_FILTER_REPLACE_TIMER_RESET, 1, &reset, 1);
	 return true;
}
static bool onButtonClick_btn_h_reset(ZKButton* pButton){
//LOGD(" ButtonClick btn_h_reset !!!\n");
	setBeepOn();
	BYTE reset = 1;
	sendProtocol(CMDID_FILTER_REPLACE_TIMER_RESET, 2, &reset, 1);
	 return true;
}
static bool onButtonClick_btn_show_keyboard(ZKButton* pButton){
//LOGD(" ButtonClick btn_show_keyboard !!!\n");
	setBeepOn();
	StrChildpasswd.clear();
	StrChildPaddwdShow.clear();
	mwindow_keyboardPtr->showWnd();
	mtext_passwordPtr->setText("请输入当前密码");
	passWordChangeStatus = PASSWD_OLDPASS;
	return true;
}
static bool onButtonClick_btn_type_save(ZKButton* pButton){
//LOGD(" ButtonClick btn_type_save !!!\n");
	 return true;
}
static bool onButtonClick_btn_type_cancel(ZKButton* pButton){
//LOGD(" ButtonClick btn_type_cancel !!!\n");

	 return true;
}
static bool onButtonClick_btn_num_1(ZKButton* pButton){
//LOGD(" ButtonClick btn_num_1 !!!\n");
	setBeepOn();
	if(StrChildPaddwdShow.size() >= 6) return true;
	StrChildPaddwdShow.push_back('*');
	StrChildpasswd.push_back('1');

	mtext_passwordPtr->setText(StrChildPaddwdShow.c_str());
	return true;
}
static bool onButtonClick_btn_num_2(ZKButton* pButton){
//LOGD(" ButtonClick btn_num_2 !!!\n");
	setBeepOn();
	if(StrChildPaddwdShow.size() >= 6) return true;
	StrChildPaddwdShow.push_back('*');
	StrChildpasswd.push_back('2');

	mtext_passwordPtr->setText(StrChildPaddwdShow.c_str());
	 return true;
}
static bool onButtonClick_btn_num_3(ZKButton* pButton){
//LOGD(" ButtonClick btn_num_3 !!!\n");
	setBeepOn();
	if(StrChildPaddwdShow.size() >= 6) return true;
	StrChildPaddwdShow.push_back('*');
	StrChildpasswd.push_back('3');
	mtext_passwordPtr->setText(StrChildPaddwdShow.c_str());
	 return true;
}
static bool onButtonClick_btn_num_clear(ZKButton* pButton){
//LOGD(" ButtonClick btn_num_clear !!!\n");
	setBeepOn();
	//if(StrChildPaddwdShow.size() >= 6) return true;

	StrChildPaddwdShow.clear();
	StrChildpasswd.clear();
	mtext_passwordPtr->setText(StrChildPaddwdShow.c_str());
	 return true;
}
static bool onButtonClick_btn_num_4(ZKButton* pButton){
//LOGD(" ButtonClick btn_num_4 !!!\n");
	setBeepOn();
	if(StrChildPaddwdShow.size() >= 6) return true;

	StrChildPaddwdShow.push_back('*');
	StrChildpasswd.push_back('4');
	mtext_passwordPtr->setText(StrChildPaddwdShow.c_str());
	 return true;
}
static bool onButtonClick_btn_num_5(ZKButton* pButton){
//LOGD(" ButtonClick btn_num_5 !!!\n");
	setBeepOn();
	if(StrChildPaddwdShow.size() >= 6) return true;

	StrChildPaddwdShow.push_back('*');
	StrChildpasswd.push_back('5');
	mtext_passwordPtr->setText(StrChildPaddwdShow.c_str());
	 return true;
}
static bool onButtonClick_btn_num_6(ZKButton* pButton){
//LOGD(" ButtonClick btn_num_6 !!!\n");
	setBeepOn();
	if(StrChildPaddwdShow.size() >= 6) return true;
	StrChildPaddwdShow.push_back('*');
	StrChildpasswd.push_back('6');
	mtext_passwordPtr->setText(StrChildPaddwdShow.c_str());
	 return true;
}
static bool onButtonClick_btn_num_0(ZKButton* pButton){
//LOGD(" ButtonClick btn_num_0 !!!\n");
	setBeepOn();
	if(StrChildPaddwdShow.size() >= 6) return true;

	StrChildPaddwdShow.push_back('*');
	StrChildpasswd.push_back('0');
	mtext_passwordPtr->setText(StrChildPaddwdShow.c_str());
	 return true;
}
static bool onButtonClick_btn_num_7(ZKButton* pButton){
//LOGD(" ButtonClick btn_num_7 !!!\n");
	setBeepOn();
	if(StrChildPaddwdShow.size() >= 6) return true;
	StrChildPaddwdShow.push_back('*');
	StrChildpasswd.push_back('7');
	mtext_passwordPtr->setText(StrChildPaddwdShow.c_str());
	 return true;
}
static bool onButtonClick_btn_num_8(ZKButton* pButton){
//LOGD(" ButtonClick btn_num_8 !!!\n");
	setBeepOn();
	if(StrChildPaddwdShow.size() >= 6) return true;
	StrChildPaddwdShow.push_back('*');
	StrChildpasswd.push_back('8');
	mtext_passwordPtr->setText(StrChildPaddwdShow.c_str());
	 return true;
}
static bool onButtonClick_btn_num_9(ZKButton* pButton){
//LOGD(" ButtonClick btn_num_9 !!!\n");
	setBeepOn();
	if(StrChildPaddwdShow.size() >= 6) return true;
	StrChildPaddwdShow.push_back('*');
	StrChildpasswd.push_back('9');
	mtext_passwordPtr->setText(StrChildPaddwdShow.c_str());
	 return true;
}
static bool onButtonClick_btn_num_cancel(ZKButton* pButton){
//LOGD(" ButtonClick btn_num_cancel !!!\n");
	setBeepOn();
	StrChildpasswd.clear();
	StrChildPaddwdShow.clear();
	mwindow_keyboardPtr->hideWnd();
	return true;
}
static bool onButtonClick_btn_num_confirm(ZKButton* pButton){
//LOGD(" ButtonClick btn_num_confirm !!!\n");
	setBeepOn();
	if(StrChildpasswd.size() != 6){
		passWordChangeStatus = PASSWD_OLDPASS;
		mtext_passwordPtr->setText("请重新输入6位当前密码");
		StrChildpasswd.clear();
		StrChildPaddwdShow.clear();
		return true;
	}
	if(passWordChangeStatus == PASSWD_OLDPASS){

		if(mProtocolData.password.size() != 6){
			mProtocolData.password = "123456";
		}
		if(mProtocolData.password ==  StrChildpasswd){
			passWordChangeStatus = PASSWD_NEWPADSS;
			mtext_passwordPtr->setText("请输入新的密码");
			StrChildpasswd.clear();
			StrChildPaddwdShow.clear();
		}else{
			passWordChangeStatus = PASSWD_OLDPASS;
			mtext_passwordPtr->setText("请重新输入当前密码");
			StrChildpasswd.clear();
			StrChildPaddwdShow.clear();
		}
	}else if(passWordChangeStatus == PASSWD_NEWPADSS){
		StrChildpasswdTemp = StrChildpasswd;
		passWordChangeStatus = PASSWD_COMFIRMPASSWD;
		mtext_passwordPtr->setText("请再次输入密码确认更改");
		StrChildpasswd.clear();
		StrChildPaddwdShow.clear();
	}else if(passWordChangeStatus == PASSWD_COMFIRMPASSWD){
		if(StrChildpasswdTemp != StrChildpasswd){
			passWordChangeStatus = PASSWD_OLDPASS;
			mtext_passwordPtr->setText("两次输入密码不匹配错误，请重新输入当前密码");
			StrChildpasswd.clear();
			StrChildPaddwdShow.clear();
		}else{
			mProtocolData.password = StrChildpasswd;
			getProtocolData().password = StrChildpasswd;
			mtext_passwordPtr->setText("密码更改成功");
			StrChildpasswd.clear();
			StrChildPaddwdShow.clear();
			mwindow_keyboardPtr->hideWnd();
		}
	}

	return true;
}
static bool onButtonClick_ButtonYearDown(ZKButton* pButton){
//LOGD(" ButtonClick ButtonYearDown !!!\n");
	setBeepOn();
	year--;
	if(year < 2000){
		year = 2099;
	}
	mTextDateYearPtr->setText(year);
	return true;
}
static bool onButtonClick_ButtonMonthDown(ZKButton* pButton){
//LOGD(" ButtonClick ButtonMonthDown !!!\n");
	setBeepOn();
	month--;
	if(month < 1){
		month = 12;
	}
	char buff[3];
	sprintf(buff,"%02d",month);
	mTextDateMonthPtr->setText(buff);
	return true;
}
static bool onButtonClick_ButtonDaydown(ZKButton* pButton){
//LOGD(" ButtonClick ButtonDaydown !!!\n");
	setBeepOn();
	day--;
	if(day < 1){
		day = getDaysInMonth(year,month);
	}
	char buff[3];
	sprintf(buff,"%02d",day);
	mTextDateDayPtr->setText(buff);
	return true;
}
static bool onButtonClick_ButtonHourDown(ZKButton* pButton){
//LOGD(" ButtonClick ButtonHourDown !!!\n");
	setBeepOn();
	hour--;
	if(hour < 0){
		hour = 23;
	}
	char buff[3];
	sprintf(buff,"%02d",hour);
	mTextDateHourPtr->setText(buff);
	 return true;
}
static bool onButtonClick_ButtonMinDown(ZKButton* pButton){
//LOGD(" ButtonClick ButtonMinDown !!!\n");
	setBeepOn();
	minute--;
	if(minute < 0){
		minute = 59;
	}

	char buff[3];
	sprintf(buff,"%02d",minute);
	mTextDateMinPtr->setText(buff);
	 return true;
}
static bool onButtonClick_ButtonYearUp(ZKButton* pButton){
//LOGD(" ButtonClick ButtonYearUp !!!\n");
	setBeepOn();
	year++;
	if(year > 2099){
		year = 2000;
	}
	mTextDateYearPtr->setText(year);
	 return true;
}
static bool onButtonClick_ButtonMonthUp(ZKButton* pButton){
//LOGD(" ButtonClick ButtonMonthUp !!!\n");
	setBeepOn();
	month++;
	if(month > 12){
		month = 1;
	}
	char buff[3];
	sprintf(buff,"%02d",month);
	mTextDateMonthPtr->setText(buff);
	 return true;
}
static bool onButtonClick_ButtonDayUp(ZKButton* pButton){
//LOGD(" ButtonClick ButtonDayUp !!!\n");
	setBeepOn();
	day++;
	if(day > getDaysInMonth(year,month)){
		day = 1;
	}
	char buff[3];
	sprintf(buff,"%02d",day);
	mTextDateDayPtr->setText(buff);
	 return true;
}
static void onUI_quit() {

}

static bool onSetupActivityTouchEvent(const MotionEvent &ev) {
    // 返回false触摸事件将继续传递到控件上，返回true表示该触摸事件在此被拦截了，不再传递到控件上
    return false;
}
static bool onButtonClick_ButtonHourUp(ZKButton* pButton){
//LOGD(" ButtonClick ButtonHourUp !!!\n");
	setBeepOn();
	hour++;
	if(hour > 23){
		hour = 0;
	}
	char buff[3];
	sprintf(buff,"%02d",hour);
	mTextDateHourPtr->setText(buff);
	return true;
}
static bool onButtonClick_ButtonMinUp(ZKButton* pButton){
//LOGD(" ButtonClick ButtonMinUp !!!\n");
	setBeepOn();
	minute++;
	if(minute > 59){
		minute = 0;
	}
	char buff[3];
	sprintf(buff,"%02d",minute);
	mTextDateMinPtr->setText(buff);
	 return true;
}
static bool onButtonClick_ButtonChildrenLock(ZKButton* pButton){
	setBeepOn();
	getProtocolData().childLock = !getProtocolData().childLock;
	sendProtocol(CMDID_CHILD_LOCK, 0, &getProtocolData().childLock,1);
	mButtonChildrenLockPtr->setSelected(getProtocolData().childLock);
	return true;
}
static bool onButtonClick_ButtonDateSave(ZKButton* pButton){
	LOGD(" ButtonClick ButtonDateSave !!!\n");
	setBeepOn();
	BYTE buff[6];
	buff[0]=year-2000;
	buff[1]=month;
	buff[2]=day;
	buff[3] = hour;
	buff[4] = minute;
	buff[5] = 0;
	sendProtocol(CMDID_NOW_TIME, 0, buff, 6);

	struct tm t;
	t.tm_year = year-1900;
	t.tm_mon = month - 1;
	t.tm_mday = day;
	t.tm_hour = hour;
	t.tm_min = minute;
	t.tm_sec = 1;
	LOGD("tm_year:%d",t.tm_year);
	LOGD("t.tm_mon:%d",t.tm_mon);
	LOGD("t.tm_mday:%d",t.tm_mday);
	LOGD("t.tm_hour:%d",t.tm_hour);
	LOGD("t.tm_min:%d",t.tm_min);
	LOGD("t.tm_sec:%d",t.tm_sec);

	TimeHelper::setDateTime(&t);

	return true;
}

static int getListItemCount_list_device_type(const ZKListView *pListView){
	// return 100; // 样例代码, 100个列表成员的演示样例 
	return 0;
}
static void obtainListItemData_list_device_type(ZKListView *pListView,ZKListView::ZKListItem *pListItem, int index){
#if 0 // 样例代码
//ID_LIST_LISTSUBITEM_MAINTEXT 是贴图中列表单元内的元素ID，ID在对应的Activity.h文件（如：winodwActivity.h）中定义。
	ZKListView::ZKListSubItem* mainText = pListItem->findSubItemByID(ID_LIST_LISTSUBITEM_MAINTEXT); 
//ID_LIST_LISTSUBITEM_MAINTEXT 字段显示[测试字段]，如果需要显示不同的字样可以通过index判断偏移值
	mainText->setText("测试字段");
#endif
}
static void onListItemClick_list_device_type(ZKListView *pListView, int index, int id){
/*
*当用户点击了 列表单元后，会返回当前点击的列表单元是在列表整体中的偏移数值index,触控到列表单元中的子控件的id,
*当没有点击到子控件的时候返回的id是ListItem本身的ID
*/
}

int powerOnHour = 8;
int powerOnMin= 0;
int powerOffHour= 12;
int powerOffMin= 0;

static bool onButtonClick_Button_Timer(ZKButton *pButton) {
    //LOGD(" ButtonClick Button_Timer !!!\n");
	setBeepOn();
	mbtn_timePtr->setSelected(false);
	mbtn_childlockPtr->setSelected(false);
	mbtn_disinfectPtr->setSelected(false);
	mbtn_operationPtr->setSelected(false);
	mbtn_screenPtr->setSelected(false);
	mbtn_systeminfoPtr->setSelected(false);
	mwindow_settimePtr->hideWnd();
	mwindow_InfoPtr->hideWnd();
	mwindow_childlockPtr->hideWnd();
	mwindow_disinfectPtr->hideWnd();
	mwindow_keyboardPtr->hideWnd();
	//mwindow_resetfilterPtr->hideWnd();
	mwindow_screenPtr->hideWnd();
	//mButton_TimerPtr->setSelected(true);
	//mWindowsetTimerPtr->showWnd();


    return true;
}

static void onProgressChanged_seekbar_brightness(ZKSeekBar *pSeekBar, int progress) {
    //LOGD(" ProgressChanged seekbar_brightness %d !!!\n", progress);
	BRIGHTNESSHELPER->setBrightness(progress);
}
static bool onButtonClick_Button1(ZKButton *pButton) {
    //LOGD(" ButtonClick Button1 !!!\n");
    return true;
}

static bool onButtonClick_ButtonOpenHourUp(ZKButton *pButton) {
    //LOGD(" ButtonClick ButtonOpenHourUp !!!\n");
	setBeepOn();
	if(++powerOnHour > 23){
		powerOnHour = 0;
	}
	//mTextOpenHourPtr->setText(powerOnHour);
    return true;
}

static bool onButtonClick_ButtonOpenMinUp(ZKButton *pButton) {
    //LOGD(" ButtonClick ButtonOpenMinUp !!!\n");
	setBeepOn();
	if(++powerOnMin > 59){
		powerOnMin = 0;
	}
	//mTextOpenMinPtr->setText(powerOnMin);
    return true;
}

static bool onButtonClick_ButtonOpenHourDn(ZKButton *pButton) {
    //LOGD(" ButtonClick ButtonOpenHourDn !!!\n");
	setBeepOn();
	if(--powerOnHour < 0){
		powerOnHour = 23;
	}
	//mTextOpenHourPtr->setText(powerOnHour);
    return true;
}

static bool onButtonClick_ButtonOpenMinDn(ZKButton *pButton) {
    //LOGD(" ButtonClick ButtonOpenMinDn !!!\n");
	setBeepOn();
	if(--powerOnMin < 0){
		powerOnMin = 59;
	}
	//mTextOpenMinPtr->setText(powerOnMin);
    return true;
}

static bool onButtonClick_ButtonCloseHourUp(ZKButton *pButton) {
    //LOGD(" ButtonClick ButtonCloseHourUp !!!\n");
	setBeepOn();
	if(++powerOffHour > 23){
		powerOffHour = 0;
	}
	//mTextCloseHourPtr->setText(powerOffHour);
    return true;
}

static bool onButtonClick_ButtonCloseMinUp(ZKButton *pButton) {
    //LOGD(" ButtonClick ButtonCloseMinUp !!!\n");
	setBeepOn();
	if(++powerOffMin > 59){
		powerOffMin = 0;
	}
	//mTextCloseMinPtr->setText(powerOffMin);
    return true;
}

static bool onButtonClick_ButtonCloseHourDn(ZKButton *pButton) {
    //LOGD(" ButtonClick ButtonCloseHourDn !!!\n");
	setBeepOn();
	if(--powerOffHour < 0){
		powerOffHour = 23;
	}
	//mTextCloseHourPtr->setText(powerOffHour);
    return true;
}

static bool onButtonClick_ButtonCloseMinDn(ZKButton *pButton) {
    //LOGD(" ButtonClick ButtonCloseMinDn !!!\n");
	setBeepOn();
	if(--powerOffMin < 0){
		powerOffMin = 59;
	}
	//mTextCloseMinPtr->setText(powerOffMin);
    return true;
}
static bool onButtonClick_ButtonOpenConfirm(ZKButton *pButton) {
    //LOGD(" ButtonClick ButtonOpenConfirm !!!\n");
	setBeepOn();
	BYTE buff[2];
	buff[0] = powerOnHour&0xFF;
	buff[1] = powerOnMin&0xFF;
	sendProtocol(CMDID_TIMMING_TIME_OPEN, 0,buff,2);

	mProtocolData.openTime = MAKEWORD(powerOnMin,powerOnHour);
	getProtocolData().openTime = mProtocolData.openTime;

    return true;
}

static bool onButtonClick_ButtonCloseConfirm(ZKButton *pButton) {
    //LOGD(" ButtonClick ButtonCloseConfirm !!!\n");
	setBeepOn();
	BYTE buff[2];
	buff[0] = powerOffHour&0xFF;
	buff[1] = powerOffMin&0xFF;
	sendProtocol(CMDID_TIMMING_TIME_CLOSE, 0,buff,2);
	mProtocolData.closeTime = MAKEWORD(powerOffMin,powerOffHour);
	getProtocolData().closeTime = mProtocolData.closeTime;
    return true;
}


static bool onButtonClick_ButtonResetFilter(ZKButton *pButton) {
    //LOGD(" ButtonClick ButtonResetFilter !!!\n");
	//sendProtocol(CMDID_CHILD_LOCK, 0,buff,2);
    setBeepOn();
   //sendProtocol(CMDID_CHILD_LOCK, 0,buff,2);
	return true;
}


/**
 * 注册定时器
 * 在此数组中添加即可
 */
static S_ACTIVITY_TIMEER REGISTER_ACTIVITY_TIMER_TAB[] = {
//    {0,  6000}, //定时器id=0, 时间间隔6秒
//    {1,  1000},
};
static bool onButtonClick_ButtonWiFi(ZKButton *pButton) {
    //LOGD(" ButtonClick ButtonWiFi !!!\n");
    return true;
}

