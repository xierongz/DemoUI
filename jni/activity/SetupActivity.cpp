/***********************************************
/gen auto by zuitools
***********************************************/
#include "SetupActivity.h"

/*TAG:GlobalVariable全局变量*/
static ZKTextView* mTextVersionMCUPtr;
static ZKTextView* mTextVersionAppPtr;
static ZKTextView* mTextVersionOSPtr;
static ZKTextView* mText5Ptr;
static ZKTextView* mText4Ptr;
static ZKTextView* mText3Ptr;
static ZKTextView* mText2Ptr;
static ZKTextView* mText1Ptr;
static ZKWindow* mwindow_InfoPtr;
static ZKButton* mButtonDateSavePtr;
static ZKButton* mButtonMinUpPtr;
static ZKButton* mButtonHourUpPtr;
static ZKButton* mButtonDayUpPtr;
static ZKButton* mButtonMonthUpPtr;
static ZKButton* mButtonYearUpPtr;
static ZKButton* mButtonMinDownPtr;
static ZKButton* mButtonHourDownPtr;
static ZKButton* mButtonDaydownPtr;
static ZKButton* mButtonMonthDownPtr;
static ZKButton* mButtonYearDownPtr;
static ZKTextView* mText10Ptr;
static ZKTextView* mText9Ptr;
static ZKTextView* mText8Ptr;
static ZKTextView* mText7Ptr;
static ZKTextView* mText6Ptr;
static ZKTextView* mTextDateMinPtr;
static ZKTextView* mTextDateHourPtr;
static ZKTextView* mTextDateDayPtr;
static ZKTextView* mTextDateMonthPtr;
static ZKTextView* mTextDateYearPtr;
static ZKWindow* mwindow_settimePtr;
static ZKButton* mbtn_num_confirmPtr;
static ZKButton* mbtn_num_cancelPtr;
static ZKButton* mbtn_num_9Ptr;
static ZKButton* mbtn_num_8Ptr;
static ZKButton* mbtn_num_7Ptr;
static ZKButton* mbtn_num_0Ptr;
static ZKButton* mbtn_num_6Ptr;
static ZKButton* mbtn_num_5Ptr;
static ZKButton* mbtn_num_4Ptr;
static ZKButton* mbtn_num_clearPtr;
static ZKButton* mbtn_num_3Ptr;
static ZKButton* mbtn_num_2Ptr;
static ZKButton* mbtn_num_1Ptr;
static ZKTextView* mtext_passwordPtr;
static ZKWindow* mwindow_keyboardPtr;
static ZKListView* mlist_device_typePtr;
static ZKButton* mbtn_type_cancelPtr;
static ZKButton* mbtn_type_savePtr;
static ZKTextView* mtext_device_typePtr;
static ZKTextView* mLabel_14Ptr;
static ZKTextView* mLabel_13Ptr;
static ZKWindow* mwindow_childlock_typePtr;
static ZKTextView* mText12Ptr;
static ZKTextView* mText11Ptr;
static ZKButton* mButtonChildrenLockPtr;
static ZKButton* mbtn_show_keyboardPtr;
static ZKWindow* mwindow_childlockPtr;
static ZKTextView* mLabel_12Ptr;
static ZKTextView* mLabel_11Ptr;
static ZKSeekBar* mseekbar_brightnessPtr;
static ZKTextView* mLabel_10Ptr;
static ZKTextView* mLabel_8Ptr;
static ZKWindow* mwindow_screenPtr;
static ZKButton* mButtonWiFiPtr;
static ZKButton* mbtn_h_resetPtr;
static ZKTextView* mLabel_9Ptr;
static ZKTextView* mtext_h_remaining_timePtr;
static ZKTextView* mLabel_7Ptr;
static ZKButton* mbtn_f_resetPtr;
static ZKTextView* mtext_f_remaining_timePtr;
static ZKTextView* mLabel_6Ptr;
static ZKTextView* mLabel_5Ptr;
static ZKButton* mbtn_g_resetPtr;
static ZKTextView* mtext_g_remaining_timePtr;
static ZKTextView* mLabel_4Ptr;
static ZKTextView* mLabel_3Ptr;
static ZKWindow* mwindow_operationPtr;
static ZKTextView* mLabel_2Ptr;
static ZKButton* mbtn_disinfect_switchPtr;
static ZKTextView* mLabel_1Ptr;
static ZKWindow* mwindow_disinfectPtr;
static ZKButton* msys_backPtr;
static ZKButton* mbtn_systeminfoPtr;
static ZKButton* mbtn_screenPtr;
static ZKButton* mbtn_operationPtr;
static ZKButton* mbtn_disinfectPtr;
static ZKButton* mbtn_childlockPtr;
static ZKButton* mbtn_timePtr;
static ZKWindow* mView_1Ptr;

/*register activity*/
REGISTER_ACTIVITY(SetupActivity);

typedef struct {
	int id; // 定时器ID ， 不能重复
	int time; // 定时器  时间间隔  单位 毫秒
}S_ACTIVITY_TIMEER;

#include "logic/SetupLogic.cc"

/***********/
typedef struct {
    int id;
    const char *pApp;
} SAppInfo;

/**
 *点击跳转window
 */
static SAppInfo sAppInfoTab[] = {
//  { ID_MAIN_TEXT, "TextViewActivity" },
};

/***************/
typedef bool (*ButtonCallback)(ZKButton *pButton);
/**
 * button onclick表
 */
typedef struct {
    int id;
    ButtonCallback callback;
}S_ButtonCallback;

/*TAG:ButtonCallbackTab按键映射表*/
static S_ButtonCallback sButtonCallbackTab[] = {
    ID_SETUP_ButtonDateSave, onButtonClick_ButtonDateSave,
    ID_SETUP_ButtonMinUp, onButtonClick_ButtonMinUp,
    ID_SETUP_ButtonHourUp, onButtonClick_ButtonHourUp,
    ID_SETUP_ButtonDayUp, onButtonClick_ButtonDayUp,
    ID_SETUP_ButtonMonthUp, onButtonClick_ButtonMonthUp,
    ID_SETUP_ButtonYearUp, onButtonClick_ButtonYearUp,
    ID_SETUP_ButtonMinDown, onButtonClick_ButtonMinDown,
    ID_SETUP_ButtonHourDown, onButtonClick_ButtonHourDown,
    ID_SETUP_ButtonDaydown, onButtonClick_ButtonDaydown,
    ID_SETUP_ButtonMonthDown, onButtonClick_ButtonMonthDown,
    ID_SETUP_ButtonYearDown, onButtonClick_ButtonYearDown,
    ID_SETUP_btn_num_confirm, onButtonClick_btn_num_confirm,
    ID_SETUP_btn_num_cancel, onButtonClick_btn_num_cancel,
    ID_SETUP_btn_num_9, onButtonClick_btn_num_9,
    ID_SETUP_btn_num_8, onButtonClick_btn_num_8,
    ID_SETUP_btn_num_7, onButtonClick_btn_num_7,
    ID_SETUP_btn_num_0, onButtonClick_btn_num_0,
    ID_SETUP_btn_num_6, onButtonClick_btn_num_6,
    ID_SETUP_btn_num_5, onButtonClick_btn_num_5,
    ID_SETUP_btn_num_4, onButtonClick_btn_num_4,
    ID_SETUP_btn_num_clear, onButtonClick_btn_num_clear,
    ID_SETUP_btn_num_3, onButtonClick_btn_num_3,
    ID_SETUP_btn_num_2, onButtonClick_btn_num_2,
    ID_SETUP_btn_num_1, onButtonClick_btn_num_1,
    ID_SETUP_btn_type_cancel, onButtonClick_btn_type_cancel,
    ID_SETUP_btn_type_save, onButtonClick_btn_type_save,
    ID_SETUP_ButtonChildrenLock, onButtonClick_ButtonChildrenLock,
    ID_SETUP_btn_show_keyboard, onButtonClick_btn_show_keyboard,
    ID_SETUP_ButtonWiFi, onButtonClick_ButtonWiFi,
    ID_SETUP_btn_h_reset, onButtonClick_btn_h_reset,
    ID_SETUP_btn_f_reset, onButtonClick_btn_f_reset,
    ID_SETUP_btn_g_reset, onButtonClick_btn_g_reset,
    ID_SETUP_btn_disinfect_switch, onButtonClick_btn_disinfect_switch,
    ID_SETUP_sys_back, onButtonClick_sys_back,
    ID_SETUP_btn_systeminfo, onButtonClick_btn_systeminfo,
    ID_SETUP_btn_screen, onButtonClick_btn_screen,
    ID_SETUP_btn_operation, onButtonClick_btn_operation,
    ID_SETUP_btn_disinfect, onButtonClick_btn_disinfect,
    ID_SETUP_btn_childlock, onButtonClick_btn_childlock,
    ID_SETUP_btn_time, onButtonClick_btn_time,
};
/***************/


typedef void (*SeekBarCallback)(ZKSeekBar *pSeekBar, int progress);
typedef struct {
    int id;
    SeekBarCallback callback;
}S_ZKSeekBarCallback;
/*TAG:SeekBarCallbackTab*/
static S_ZKSeekBarCallback SZKSeekBarCallbackTab[] = {
    ID_SETUP_seekbar_brightness, onProgressChanged_seekbar_brightness,
};


typedef int (*ListViewGetItemCountCallback)(const ZKListView *pListView);
typedef void (*ListViewobtainListItemDataCallback)(ZKListView *pListView,ZKListView::ZKListItem *pListItem, int index);
typedef void (*ListViewonItemClickCallback)(ZKListView *pListView, int index, int id);
typedef struct {
    int id;
    ListViewGetItemCountCallback getListItemCountCallback;
    ListViewobtainListItemDataCallback obtainListItemDataCallback;
    ListViewonItemClickCallback onItemClickCallback;
}S_ListViewFunctionsCallback;
/*TAG:ListViewFunctionsCallback*/
static S_ListViewFunctionsCallback SListViewFunctionsCallbackTab[] = {
    ID_SETUP_list_device_type, getListItemCount_list_device_type, obtainListItemData_list_device_type, onListItemClick_list_device_type,
};


typedef void (*SlideWindowItemClickCallback)(ZKSlideWindow *pSlideWindow, int index);
typedef struct {
    int id;
    SlideWindowItemClickCallback onSlideItemClickCallback;
}S_SlideWindowItemClickCallback;
/*TAG:SlideWindowFunctionsCallbackTab*/
static S_SlideWindowItemClickCallback SSlideWindowItemClickCallbackTab[] = {
};


typedef void (*EditTextInputCallback)(const std::string &text);
typedef struct {
    int id;
    EditTextInputCallback onEditTextChangedCallback;
}S_EditTextInputCallback;
/*TAG:EditTextInputCallback*/
static S_EditTextInputCallback SEditTextInputCallbackTab[] = {
};

typedef void (*VideoViewCallback)(ZKVideoView *pVideoView, int msg);
typedef struct {
    int id; //VideoView ID
    bool loop; // 是否是轮播类型
    int defaultvolume;//轮播类型时,默认视频音量
    VideoViewCallback onVideoViewCallback;
}S_VideoViewCallback;
/*TAG:VideoViewCallback*/
static S_VideoViewCallback SVideoViewCallbackTab[] = {
};


SetupActivity::SetupActivity() {
	//todo add init code here
	mVideoLoopIndex = 0;
	mVideoLoopErrorCount = 0;
}

SetupActivity::~SetupActivity() {
	//todo add init file here
    // 退出应用时需要反注册
    EASYUICONTEXT->unregisterGlobalTouchListener(this);
    onUI_quit();
    unregisterProtocolDataUpdateListener(onProtocolDataUpdate);
}

const char* SetupActivity::getAppName() const{
	return "Setup.ftu";
}

//TAG:onCreate
void SetupActivity::onCreate() {
	Activity::onCreate();
    mTextVersionMCUPtr = (ZKTextView*)findControlByID(ID_SETUP_TextVersionMCU);
    mTextVersionAppPtr = (ZKTextView*)findControlByID(ID_SETUP_TextVersionApp);
    mTextVersionOSPtr = (ZKTextView*)findControlByID(ID_SETUP_TextVersionOS);
    mText5Ptr = (ZKTextView*)findControlByID(ID_SETUP_Text5);
    mText4Ptr = (ZKTextView*)findControlByID(ID_SETUP_Text4);
    mText3Ptr = (ZKTextView*)findControlByID(ID_SETUP_Text3);
    mText2Ptr = (ZKTextView*)findControlByID(ID_SETUP_Text2);
    mText1Ptr = (ZKTextView*)findControlByID(ID_SETUP_Text1);
    mwindow_InfoPtr = (ZKWindow*)findControlByID(ID_SETUP_window_Info);
    mButtonDateSavePtr = (ZKButton*)findControlByID(ID_SETUP_ButtonDateSave);
    mButtonMinUpPtr = (ZKButton*)findControlByID(ID_SETUP_ButtonMinUp);
    mButtonHourUpPtr = (ZKButton*)findControlByID(ID_SETUP_ButtonHourUp);
    mButtonDayUpPtr = (ZKButton*)findControlByID(ID_SETUP_ButtonDayUp);
    mButtonMonthUpPtr = (ZKButton*)findControlByID(ID_SETUP_ButtonMonthUp);
    mButtonYearUpPtr = (ZKButton*)findControlByID(ID_SETUP_ButtonYearUp);
    mButtonMinDownPtr = (ZKButton*)findControlByID(ID_SETUP_ButtonMinDown);
    mButtonHourDownPtr = (ZKButton*)findControlByID(ID_SETUP_ButtonHourDown);
    mButtonDaydownPtr = (ZKButton*)findControlByID(ID_SETUP_ButtonDaydown);
    mButtonMonthDownPtr = (ZKButton*)findControlByID(ID_SETUP_ButtonMonthDown);
    mButtonYearDownPtr = (ZKButton*)findControlByID(ID_SETUP_ButtonYearDown);
    mText10Ptr = (ZKTextView*)findControlByID(ID_SETUP_Text10);
    mText9Ptr = (ZKTextView*)findControlByID(ID_SETUP_Text9);
    mText8Ptr = (ZKTextView*)findControlByID(ID_SETUP_Text8);
    mText7Ptr = (ZKTextView*)findControlByID(ID_SETUP_Text7);
    mText6Ptr = (ZKTextView*)findControlByID(ID_SETUP_Text6);
    mTextDateMinPtr = (ZKTextView*)findControlByID(ID_SETUP_TextDateMin);
    mTextDateHourPtr = (ZKTextView*)findControlByID(ID_SETUP_TextDateHour);
    mTextDateDayPtr = (ZKTextView*)findControlByID(ID_SETUP_TextDateDay);
    mTextDateMonthPtr = (ZKTextView*)findControlByID(ID_SETUP_TextDateMonth);
    mTextDateYearPtr = (ZKTextView*)findControlByID(ID_SETUP_TextDateYear);
    mwindow_settimePtr = (ZKWindow*)findControlByID(ID_SETUP_window_settime);
    mbtn_num_confirmPtr = (ZKButton*)findControlByID(ID_SETUP_btn_num_confirm);
    mbtn_num_cancelPtr = (ZKButton*)findControlByID(ID_SETUP_btn_num_cancel);
    mbtn_num_9Ptr = (ZKButton*)findControlByID(ID_SETUP_btn_num_9);
    mbtn_num_8Ptr = (ZKButton*)findControlByID(ID_SETUP_btn_num_8);
    mbtn_num_7Ptr = (ZKButton*)findControlByID(ID_SETUP_btn_num_7);
    mbtn_num_0Ptr = (ZKButton*)findControlByID(ID_SETUP_btn_num_0);
    mbtn_num_6Ptr = (ZKButton*)findControlByID(ID_SETUP_btn_num_6);
    mbtn_num_5Ptr = (ZKButton*)findControlByID(ID_SETUP_btn_num_5);
    mbtn_num_4Ptr = (ZKButton*)findControlByID(ID_SETUP_btn_num_4);
    mbtn_num_clearPtr = (ZKButton*)findControlByID(ID_SETUP_btn_num_clear);
    mbtn_num_3Ptr = (ZKButton*)findControlByID(ID_SETUP_btn_num_3);
    mbtn_num_2Ptr = (ZKButton*)findControlByID(ID_SETUP_btn_num_2);
    mbtn_num_1Ptr = (ZKButton*)findControlByID(ID_SETUP_btn_num_1);
    mtext_passwordPtr = (ZKTextView*)findControlByID(ID_SETUP_text_password);
    mwindow_keyboardPtr = (ZKWindow*)findControlByID(ID_SETUP_window_keyboard);
    mlist_device_typePtr = (ZKListView*)findControlByID(ID_SETUP_list_device_type);if(mlist_device_typePtr!= NULL){mlist_device_typePtr->setListAdapter(this);mlist_device_typePtr->setItemClickListener(this);}
    mbtn_type_cancelPtr = (ZKButton*)findControlByID(ID_SETUP_btn_type_cancel);
    mbtn_type_savePtr = (ZKButton*)findControlByID(ID_SETUP_btn_type_save);
    mtext_device_typePtr = (ZKTextView*)findControlByID(ID_SETUP_text_device_type);
    mLabel_14Ptr = (ZKTextView*)findControlByID(ID_SETUP_Label_14);
    mLabel_13Ptr = (ZKTextView*)findControlByID(ID_SETUP_Label_13);
    mwindow_childlock_typePtr = (ZKWindow*)findControlByID(ID_SETUP_window_childlock_type);
    mText12Ptr = (ZKTextView*)findControlByID(ID_SETUP_Text12);
    mText11Ptr = (ZKTextView*)findControlByID(ID_SETUP_Text11);
    mButtonChildrenLockPtr = (ZKButton*)findControlByID(ID_SETUP_ButtonChildrenLock);
    mbtn_show_keyboardPtr = (ZKButton*)findControlByID(ID_SETUP_btn_show_keyboard);
    mwindow_childlockPtr = (ZKWindow*)findControlByID(ID_SETUP_window_childlock);
    mLabel_12Ptr = (ZKTextView*)findControlByID(ID_SETUP_Label_12);
    mLabel_11Ptr = (ZKTextView*)findControlByID(ID_SETUP_Label_11);
    mseekbar_brightnessPtr = (ZKSeekBar*)findControlByID(ID_SETUP_seekbar_brightness);if(mseekbar_brightnessPtr!= NULL){mseekbar_brightnessPtr->setSeekBarChangeListener(this);}
    mLabel_10Ptr = (ZKTextView*)findControlByID(ID_SETUP_Label_10);
    mLabel_8Ptr = (ZKTextView*)findControlByID(ID_SETUP_Label_8);
    mwindow_screenPtr = (ZKWindow*)findControlByID(ID_SETUP_window_screen);
    mButtonWiFiPtr = (ZKButton*)findControlByID(ID_SETUP_ButtonWiFi);
    mbtn_h_resetPtr = (ZKButton*)findControlByID(ID_SETUP_btn_h_reset);
    mLabel_9Ptr = (ZKTextView*)findControlByID(ID_SETUP_Label_9);
    mtext_h_remaining_timePtr = (ZKTextView*)findControlByID(ID_SETUP_text_h_remaining_time);
    mLabel_7Ptr = (ZKTextView*)findControlByID(ID_SETUP_Label_7);
    mbtn_f_resetPtr = (ZKButton*)findControlByID(ID_SETUP_btn_f_reset);
    mtext_f_remaining_timePtr = (ZKTextView*)findControlByID(ID_SETUP_text_f_remaining_time);
    mLabel_6Ptr = (ZKTextView*)findControlByID(ID_SETUP_Label_6);
    mLabel_5Ptr = (ZKTextView*)findControlByID(ID_SETUP_Label_5);
    mbtn_g_resetPtr = (ZKButton*)findControlByID(ID_SETUP_btn_g_reset);
    mtext_g_remaining_timePtr = (ZKTextView*)findControlByID(ID_SETUP_text_g_remaining_time);
    mLabel_4Ptr = (ZKTextView*)findControlByID(ID_SETUP_Label_4);
    mLabel_3Ptr = (ZKTextView*)findControlByID(ID_SETUP_Label_3);
    mwindow_operationPtr = (ZKWindow*)findControlByID(ID_SETUP_window_operation);
    mLabel_2Ptr = (ZKTextView*)findControlByID(ID_SETUP_Label_2);
    mbtn_disinfect_switchPtr = (ZKButton*)findControlByID(ID_SETUP_btn_disinfect_switch);
    mLabel_1Ptr = (ZKTextView*)findControlByID(ID_SETUP_Label_1);
    mwindow_disinfectPtr = (ZKWindow*)findControlByID(ID_SETUP_window_disinfect);
    msys_backPtr = (ZKButton*)findControlByID(ID_SETUP_sys_back);
    mbtn_systeminfoPtr = (ZKButton*)findControlByID(ID_SETUP_btn_systeminfo);
    mbtn_screenPtr = (ZKButton*)findControlByID(ID_SETUP_btn_screen);
    mbtn_operationPtr = (ZKButton*)findControlByID(ID_SETUP_btn_operation);
    mbtn_disinfectPtr = (ZKButton*)findControlByID(ID_SETUP_btn_disinfect);
    mbtn_childlockPtr = (ZKButton*)findControlByID(ID_SETUP_btn_childlock);
    mbtn_timePtr = (ZKButton*)findControlByID(ID_SETUP_btn_time);
    mView_1Ptr = (ZKWindow*)findControlByID(ID_SETUP_View_1);
	onUI_init();
        // 注册监听全局触摸
    EASYUICONTEXT->registerGlobalTouchListener(this);
    registerProtocolDataUpdateListener(onProtocolDataUpdate); 

    rigesterActivityTimer();
}

void SetupActivity::onClick(ZKBase *pBase) {
	//TODO: add widget onClik code 
    int buttonTablen = sizeof(sButtonCallbackTab) / sizeof(S_ButtonCallback);
    for (int i = 0; i < buttonTablen; ++i) {
        if (sButtonCallbackTab[i].id == pBase->getID()) {
            sButtonCallbackTab[i].callback((ZKButton*)pBase);
            break;
        }
    }


    int len = sizeof(sAppInfoTab) / sizeof(sAppInfoTab[0]);
    for (int i = 0; i < len; ++i) {
        if (sAppInfoTab[i].id == pBase->getID()) {
            EASYUICONTEXT->openActivity(sAppInfoTab[i].pApp);
            return;
        }
    }

	Activity::onClick(pBase);
}

void SetupActivity::onResume() {
	Activity::onResume();
	startVideoLoopPlayback();
}

void SetupActivity::onPause() {
	Activity::onPause();
	stopVideoLoopPlayback();
}

void SetupActivity::onIntent(const Intent *intentPtr) {
	//TODO:  
	
	Activity::onIntent(intentPtr);
}

bool SetupActivity::onTimer(int id) {
	return onUI_Timer(id);
}

void SetupActivity::onProgressChanged(ZKSeekBar *pSeekBar, int progress){

    int seekBarTablen = sizeof(SZKSeekBarCallbackTab) / sizeof(S_ZKSeekBarCallback);
    for (int i = 0; i < seekBarTablen; ++i) {
        if (SZKSeekBarCallbackTab[i].id == pSeekBar->getID()) {
            SZKSeekBarCallbackTab[i].callback(pSeekBar, progress);
            break;
        }
    }
}

int SetupActivity::getListItemCount(const ZKListView *pListView) const{
    int tablen = sizeof(SListViewFunctionsCallbackTab) / sizeof(S_ListViewFunctionsCallback);
    for (int i = 0; i < tablen; ++i) {
        if (SListViewFunctionsCallbackTab[i].id == pListView->getID()) {
            return SListViewFunctionsCallbackTab[i].getListItemCountCallback(pListView);
            break;
        }
    }
    return 0;
}

void SetupActivity::obtainListItemData(ZKListView *pListView,ZKListView::ZKListItem *pListItem, int index){
    int tablen = sizeof(SListViewFunctionsCallbackTab) / sizeof(S_ListViewFunctionsCallback);
    for (int i = 0; i < tablen; ++i) {
        if (SListViewFunctionsCallbackTab[i].id == pListView->getID()) {
            SListViewFunctionsCallbackTab[i].obtainListItemDataCallback(pListView, pListItem, index);
            break;
        }
    }
}

void SetupActivity::onItemClick(ZKListView *pListView, int index, int id){
    int tablen = sizeof(SListViewFunctionsCallbackTab) / sizeof(S_ListViewFunctionsCallback);
    for (int i = 0; i < tablen; ++i) {
        if (SListViewFunctionsCallbackTab[i].id == pListView->getID()) {
            SListViewFunctionsCallbackTab[i].onItemClickCallback(pListView, index, id);
            break;
        }
    }
}

void SetupActivity::onSlideItemClick(ZKSlideWindow *pSlideWindow, int index) {
    int tablen = sizeof(SSlideWindowItemClickCallbackTab) / sizeof(S_SlideWindowItemClickCallback);
    for (int i = 0; i < tablen; ++i) {
        if (SSlideWindowItemClickCallbackTab[i].id == pSlideWindow->getID()) {
            SSlideWindowItemClickCallbackTab[i].onSlideItemClickCallback(pSlideWindow, index);
            break;
        }
    }
}

bool SetupActivity::onTouchEvent(const MotionEvent &ev) {
    return onSetupActivityTouchEvent(ev);
}

void SetupActivity::onTextChanged(ZKTextView *pTextView, const std::string &text) {
    int tablen = sizeof(SEditTextInputCallbackTab) / sizeof(S_EditTextInputCallback);
    for (int i = 0; i < tablen; ++i) {
        if (SEditTextInputCallbackTab[i].id == pTextView->getID()) {
            SEditTextInputCallbackTab[i].onEditTextChangedCallback(text);
            break;
        }
    }
}

void SetupActivity::rigesterActivityTimer() {
    int tablen = sizeof(REGISTER_ACTIVITY_TIMER_TAB) / sizeof(S_ACTIVITY_TIMEER);
    for (int i = 0; i < tablen; ++i) {
        S_ACTIVITY_TIMEER temp = REGISTER_ACTIVITY_TIMER_TAB[i];
        registerTimer(temp.id, temp.time);
    }
}


void SetupActivity::onVideoPlayerMessage(ZKVideoView *pVideoView, int msg) {
    int tablen = sizeof(SVideoViewCallbackTab) / sizeof(S_VideoViewCallback);
    for (int i = 0; i < tablen; ++i) {
        if (SVideoViewCallbackTab[i].id == pVideoView->getID()) {
        	if (SVideoViewCallbackTab[i].loop) {
                //循环播放
        		videoLoopPlayback(pVideoView, msg, i);
        	} else if (SVideoViewCallbackTab[i].onVideoViewCallback != NULL){
        	    SVideoViewCallbackTab[i].onVideoViewCallback(pVideoView, msg);
        	}
            break;
        }
    }
}

void SetupActivity::videoLoopPlayback(ZKVideoView *pVideoView, int msg, int callbackTabIndex) {

	switch (msg) {
	case ZKVideoView::E_MSGTYPE_VIDEO_PLAY_STARTED:
		LOGD("ZKVideoView::E_MSGTYPE_VIDEO_PLAY_STARTED\n");
		pVideoView->setVolume(SVideoViewCallbackTab[callbackTabIndex].defaultvolume / 10.0);
		mVideoLoopErrorCount = 0;
		break;
	case ZKVideoView::E_MSGTYPE_VIDEO_PLAY_ERROR:
		/**错误处理 */
		++mVideoLoopErrorCount;
		if (mVideoLoopErrorCount > 100) {
			LOGD("video loop error counts > 100, quit loop playback !");
            break;
		} //不用break, 继续尝试播放下一个
	case ZKVideoView::E_MSGTYPE_VIDEO_PLAY_COMPLETED:
		LOGD("ZKVideoView::E_MSGTYPE_VIDEO_PLAY_COMPLETED\n");
        std:vector<std::string> videolist;
        std::string fileName(getAppName());
        if (fileName.size() < 4) {
             LOGD("getAppName size < 4, ignore!");
             break;
        }
        fileName = fileName.substr(0, fileName.length() - 4) + "_video_list.txt";
        fileName = "/mnt/extsd/" + fileName;
        if (!parseVideoFileList(fileName.c_str(), videolist)) {
            LOGD("parseVideoFileList failed !");
		    break;
        }
		if (pVideoView && !videolist.empty()) {
			mVideoLoopIndex = (mVideoLoopIndex + 1) % videolist.size();
			pVideoView->play(videolist[mVideoLoopIndex].c_str());
		}
		break;
	}
}

void SetupActivity::startVideoLoopPlayback() {
    int tablen = sizeof(SVideoViewCallbackTab) / sizeof(S_VideoViewCallback);
    for (int i = 0; i < tablen; ++i) {
    	if (SVideoViewCallbackTab[i].loop) {
    		ZKVideoView* videoView = (ZKVideoView*)findControlByID(SVideoViewCallbackTab[i].id);
    		if (!videoView) {
    			return;
    		}
    		//循环播放
    		videoLoopPlayback(videoView, ZKVideoView::E_MSGTYPE_VIDEO_PLAY_COMPLETED, i);
    		return;
    	}
    }
}

void SetupActivity::stopVideoLoopPlayback() {
    int tablen = sizeof(SVideoViewCallbackTab) / sizeof(S_VideoViewCallback);
    for (int i = 0; i < tablen; ++i) {
    	if (SVideoViewCallbackTab[i].loop) {
    		ZKVideoView* videoView = (ZKVideoView*)findControlByID(SVideoViewCallbackTab[i].id);
    		if (!videoView) {
    			return;
    		}
    		if (videoView->isPlaying()) {
    		    videoView->stop();
    		}
    		return;
    	}
    }
}

bool SetupActivity::parseVideoFileList(const char *pFileListPath, std::vector<string>& mediaFileList) {
	mediaFileList.clear();
	if (NULL == pFileListPath || 0 == strlen(pFileListPath)) {
        LOGD("video file list is null!");
		return false;
	}

	string tmp;
	ifstream is(pFileListPath, ios_base::in);
	if (!is.is_open()) {
		LOGD("cann't open file %s \n", pFileListPath);
		return false;
	}
	while (getline(is, tmp)) {
		removeCharFromString(tmp, '\"');
		removeCharFromString(tmp, '\r');
		removeCharFromString(tmp, '\n');
		if (tmp.size() > 1) {
     		mediaFileList.push_back(string(tmp.c_str()));
		}
	}
	LOGD("(f:%s, l:%d) parse fileList[%s], get [%d]files\n", __FUNCTION__,
			__LINE__, pFileListPath, mediaFileList.size());
	for (size_t i = 0; i < mediaFileList.size(); i++) {
		LOGD("file[%d]:[%s]\n", i, mediaFileList[i].c_str());
	}
	is.close();

	return true;
}

int SetupActivity::removeCharFromString(string& nString, char c) {
    string::size_type   pos;
    while(1)
    {
        pos = nString.find(c);
        if(pos != string::npos)
        {
            nString.erase(pos, 1);
        }
        else
        {
            break;
        }
    }
    return (int)nString.size();
}
