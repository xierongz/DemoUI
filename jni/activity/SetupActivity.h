/***********************************************
/gen auto by zuitools
***********************************************/
#ifndef __SETUPACTIVITY_H__
#define __SETUPACTIVITY_H__


#include "app/Activity.h"
#include "entry/EasyUIContext.h"

#include "uart/ProtocolData.h"
#include "uart/ProtocolParser.h"

#include "utils/Log.h"
#include "control/ZKDigitalClock.h"
#include "control/ZKButton.h"
#include "control/ZKCircleBar.h"
#include "control/ZKDiagram.h"
#include "control/ZKListView.h"
#include "control/ZKPointer.h"
#include "control/ZKQRCode.h"
#include "control/ZKTextView.h"
#include "control/ZKSeekBar.h"
#include "control/ZKEditText.h"
#include "control/ZKVideoView.h"
#include "control/ZKVideoView.h"
#include "window/ZKSlideWindow.h"

/*TAG:Macro宏ID*/
#define ID_SETUP_TextVersionMCU    50057
#define ID_SETUP_TextVersionApp    50056
#define ID_SETUP_TextVersionOS    50055
#define ID_SETUP_Text5    50054
#define ID_SETUP_Text4    50053
#define ID_SETUP_Text3    50052
#define ID_SETUP_Text2    50051
#define ID_SETUP_Text1    50050
#define ID_SETUP_window_Info    100014
#define ID_SETUP_ButtonDateSave    20081
#define ID_SETUP_ButtonMinUp    20080
#define ID_SETUP_ButtonHourUp    20079
#define ID_SETUP_ButtonDayUp    20078
#define ID_SETUP_ButtonMonthUp    20077
#define ID_SETUP_ButtonYearUp    20076
#define ID_SETUP_ButtonMinDown    20074
#define ID_SETUP_ButtonHourDown    20073
#define ID_SETUP_ButtonDaydown    20072
#define ID_SETUP_ButtonMonthDown    20071
#define ID_SETUP_ButtonYearDown    20070
#define ID_SETUP_Text10    50049
#define ID_SETUP_Text9    50048
#define ID_SETUP_Text8    50047
#define ID_SETUP_Text7    50046
#define ID_SETUP_Text6    50045
#define ID_SETUP_TextDateMin    50044
#define ID_SETUP_TextDateHour    50043
#define ID_SETUP_TextDateDay    50042
#define ID_SETUP_TextDateMonth    50041
#define ID_SETUP_TextDateYear    50040
#define ID_SETUP_window_settime    100013
#define ID_SETUP_btn_num_confirm    20068
#define ID_SETUP_btn_num_cancel    20064
#define ID_SETUP_btn_num_9    20063
#define ID_SETUP_btn_num_8    20062
#define ID_SETUP_btn_num_7    20061
#define ID_SETUP_btn_num_0    20060
#define ID_SETUP_btn_num_6    20059
#define ID_SETUP_btn_num_5    20058
#define ID_SETUP_btn_num_4    20057
#define ID_SETUP_btn_num_clear    20056
#define ID_SETUP_btn_num_3    20055
#define ID_SETUP_btn_num_2    20052
#define ID_SETUP_btn_num_1    20051
#define ID_SETUP_text_password    50037
#define ID_SETUP_window_keyboard    100012
#define ID_SETUP_list_subitem_type    70005
#define ID_SETUP_list_device_type    80002
#define ID_SETUP_btn_type_cancel    20047
#define ID_SETUP_btn_type_save    20046
#define ID_SETUP_text_device_type    50033
#define ID_SETUP_Label_14    50032
#define ID_SETUP_Label_13    50031
#define ID_SETUP_window_childlock_type    100009
#define ID_SETUP_Text12    50059
#define ID_SETUP_Text11    50058
#define ID_SETUP_ButtonChildrenLock    20083
#define ID_SETUP_btn_show_keyboard    20041
#define ID_SETUP_window_childlock    100007
#define ID_SETUP_Label_12    50026
#define ID_SETUP_Label_11    50025
#define ID_SETUP_seekbar_brightness    90002
#define ID_SETUP_Label_10    50022
#define ID_SETUP_Label_8    50021
#define ID_SETUP_window_screen    100005
#define ID_SETUP_ButtonWiFi    20084
#define ID_SETUP_btn_h_reset    20035
#define ID_SETUP_Label_9    50020
#define ID_SETUP_text_h_remaining_time    50019
#define ID_SETUP_Label_7    50018
#define ID_SETUP_btn_f_reset    20034
#define ID_SETUP_text_f_remaining_time    50017
#define ID_SETUP_Label_6    50016
#define ID_SETUP_Label_5    50015
#define ID_SETUP_btn_g_reset    20033
#define ID_SETUP_text_g_remaining_time    50014
#define ID_SETUP_Label_4    50011
#define ID_SETUP_Label_3    50010
#define ID_SETUP_window_operation    100004
#define ID_SETUP_Label_2    50005
#define ID_SETUP_btn_disinfect_switch    20029
#define ID_SETUP_Label_1    50002
#define ID_SETUP_window_disinfect    100003
#define ID_SETUP_sys_back   100
#define ID_SETUP_btn_systeminfo    20023
#define ID_SETUP_btn_screen    20019
#define ID_SETUP_btn_operation    20015
#define ID_SETUP_btn_disinfect    20011
#define ID_SETUP_btn_childlock    20007
#define ID_SETUP_btn_time    20003
#define ID_SETUP_View_1    100002
/*TAG:Macro宏ID END*/

class SetupActivity : public Activity, 
                     public ZKSeekBar::ISeekBarChangeListener, 
                     public ZKListView::IItemClickListener,
                     public ZKListView::AbsListAdapter,
                     public ZKSlideWindow::ISlideItemClickListener,
                     public EasyUIContext::ITouchListener,
                     public ZKEditText::ITextChangeListener,
                     public ZKVideoView::IVideoPlayerMessageListener
{
public:
    SetupActivity();
    virtual ~SetupActivity();

protected:
    /*TAG:PROTECTED_FUNCTION*/
    virtual const char* getAppName() const;
    virtual void onCreate();
    virtual void onClick(ZKBase *pBase);
    virtual void onResume();
    virtual void onPause();
    virtual void onIntent(const Intent *intentPtr);
    virtual bool onTimer(int id);

    virtual void onProgressChanged(ZKSeekBar *pSeekBar, int progress);

    virtual int getListItemCount(const ZKListView *pListView) const;
    virtual void obtainListItemData(ZKListView *pListView, ZKListView::ZKListItem *pListItem, int index);
    virtual void onItemClick(ZKListView *pListView, int index, int subItemIndex);

    virtual void onSlideItemClick(ZKSlideWindow *pSlideWindow, int index);

    virtual bool onTouchEvent(const MotionEvent &ev);

    virtual void onTextChanged(ZKTextView *pTextView, const string &text);

    void rigesterActivityTimer();

    virtual void onVideoPlayerMessage(ZKVideoView *pVideoView, int msg);
    void videoLoopPlayback(ZKVideoView *pVideoView, int msg, int callbackTabIndex);
    void startVideoLoopPlayback();
    void stopVideoLoopPlayback();
    bool parseVideoFileList(const char *pFileListPath, std::vector<string>& mediaFileList);
    int removeCharFromString(string& nString, char c);


private:
    /*TAG:PRIVATE_VARIABLE*/
    int mVideoLoopIndex;
    int mVideoLoopErrorCount;

};

#endif
