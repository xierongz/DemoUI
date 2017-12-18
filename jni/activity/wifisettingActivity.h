/***********************************************
/gen auto by zuitools
***********************************************/
#ifndef __WIFISETTINGACTIVITY_H__
#define __WIFISETTINGACTIVITY_H__


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
#define ID_WIFISETTING_EditTextPass    51000
#define ID_WIFISETTING_Buttonconnect    20009
#define ID_WIFISETTING_TextSecType    50025
#define ID_WIFISETTING_TextSSID    50024
#define ID_WIFISETTING_Text3    50023
#define ID_WIFISETTING_Text2    50022
#define ID_WIFISETTING_Text1    50021
#define ID_WIFISETTING_window_set    100010
#define ID_WIFISETTING_Text_onoff    50020
#define ID_WIFISETTING_Label_1    50019
#define ID_WIFISETTING_SYS_BACK   100
#define ID_WIFISETTING_Button_sw    20005
#define ID_WIFISETTING_View_2    100006
#define ID_WIFISETTING_ListSubItem_subtext    70002
#define ID_WIFISETTING_ListSubItem_NAME    70001
#define ID_WIFISETTING_ListSubItem_icon    70000
#define ID_WIFISETTING_ListView_1    80000
#define ID_WIFISETTING_View_1    100004
/*TAG:Macro宏ID END*/

class wifisettingActivity : public Activity, 
                     public ZKSeekBar::ISeekBarChangeListener, 
                     public ZKListView::IItemClickListener,
                     public ZKListView::AbsListAdapter,
                     public ZKSlideWindow::ISlideItemClickListener,
                     public EasyUIContext::ITouchListener,
                     public ZKEditText::ITextChangeListener,
                     public ZKVideoView::IVideoPlayerMessageListener
{
public:
    wifisettingActivity();
    virtual ~wifisettingActivity();

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
