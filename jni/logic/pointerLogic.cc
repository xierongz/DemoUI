/*
*此文件由GUI工具生成
*文件功能：用于处理用户的逻辑相应代码
*功能说明：
*========================onButtonClick_XXXX
当页面中的按键按下后系统会调用对应的函数，XXX代表GUI工具里面的[ID值]名称，
如Button1,当返回值为false的时候系统将不再处理这个按键，返回true的时候系统将会继续处理此按键。比如SYS_BACK.
*========================onSlideWindowItemClick_XXXX(int index) 
当页面中存在滑动窗口并且用户点击了滑动窗口的图标后系统会调用此函数,XXX代表GUI工具里面的[ID值]名称，
如slideWindow1;index 代表按下图标的偏移值
*========================onSeekBarChange_XXXX(int progress) 
当页面中存在滑动条并且用户改变了进度后系统会调用此函数,XXX代表GUI工具里面的[ID值]名称，
如SeekBar1;progress 代表当前的进度值
*========================ogetListItemCount_XXXX() 
当页面中存在滑动列表的时候，更新的时候系统会调用此接口获取列表的总数目,XXX代表GUI工具里面的[ID值]名称，
如List1;返回值为当前列表的总条数
*========================oobtainListItemData_XXXX(ZKListView::ZKListItem *pListItem, int index)
 当页面中存在滑动列表的时候，更新的时候系统会调用此接口获取列表当前条目下的内容信息,XXX代表GUI工具里面的[ID值]名称，
如List1;pListItem 是贴图中的单条目对象，index是列表总目的偏移量。具体见函数说明
*========================常用接口===============
*LOGD(...)  打印调试信息的接口
*mTextXXX->setText("****") 在控件TextXXX上显示文字****
*mButton1->setSelected(true); 将控件mButton1设置为选中模式，图片会切换成选中图片，按钮文字会切换为选中后的颜色
*mSeekBar->setProgress(12) 在控件mSeekBar上将进度调整到12
*mListView1->refreshListView() 让mListView1 重新刷新，当列表数据变化后调用
*mDashbroadView1->setTargetAngle(120) 在控件mDashbroadView1上指针显示角度调整到120度
*
* 在Eclipse编辑器中  使用 “alt + /”  快捷键可以打开智能提示
*/

static int sCarTemp[] = { 28, 32, 27, 30, 29, 26, 32, 31 };
static int sWaterTemp[] = { 60, 50, 70, 80, 40, 30, 80, 50 };
static float totoalbase=1000;
static float curmil=0;
static float leaveMail = 500;

static int SpeedTemp[]={0,   3,    5,  10,  12, 18,  25,  36,49 ,60,   50,   65, 80  ,90,     110,120, 110,100,100,   90,95,95};
static int RPmTab[]={1500,1700,2000,2500,2600,2650,2400,2500,2500,2860,2560,2700,3200,3000,3000,3000,2800,2600,2000,2150,2000,2000};
static int oilTab[]={15,17,15,15,10,10,12,10,8,7.5,7.5,7.2,7.5,7.5,6.5,8,7.2,7.6,7.0,7.0,6.8,6.8};

int speedindex = 0;
bool binc = 1;

int tmpindex = 0;
int dirindex = 0;
bool btest = 0;
#define DIAGRAM_SIZE 30
static MPPOINT sPoints[DIAGRAM_SIZE];

static void movePoints(MPPOINT* p,int size){
	for(int i =0;i < size-1;i++){
		p[i].y = p[i+1].y;
	}
	p[size-1].y = 0;
}

static void updateGUI(){
	if(binc ){
		if(++speedindex >= sizeof(SpeedTemp)/sizeof(int)){
			binc = 0;
			speedindex -= 1;
		}
	}
	else{
		if(--speedindex < 0){
			speedindex = 0;
			binc = 1;
		}
	}

	int spe= SpeedTemp[speedindex];

	mDashbroadView_1Ptr->setTargetAngle(spe);

	char buff[50];

	totoalbase += ((float)spe/7200);
	sprintf(buff,"%.2f KM",totoalbase);
	mLabel_TotalMPtr->setText(buff);

	char buff1[50];
	curmil += ((float)spe/7200);
	sprintf(buff1,"%.2f KM",curmil);
	mLabel_CURMPtr->setText(buff1);

	char buff2[50];
	sprintf(buff2,"%d 转",RPmTab[speedindex]);
	mLabel_RPMPtr->setText(buff2);


	movePoints(sPoints,DIAGRAM_SIZE);
	if(mDiagram1Ptr != NULL){
		sPoints[DIAGRAM_SIZE-1].y =(RPmTab[speedindex])/50;
		mDiagram1Ptr->setData(0,sPoints,DIAGRAM_SIZE);
	}

	char buff3[50];
	leaveMail =500.0- curmil;
	if(leaveMail < 0) leaveMail = 0;
	sprintf(buff3,"%.2f KM",leaveMail);
	mLabel_OIL1Ptr->setText(buff3);

	char buff4[50];
	sprintf(buff4,"%d/100KM",oilTab[speedindex]);
	mLabel_OILPtr->setText(buff4);


}
void updateGUI_Tempture(){
	if(++tmpindex >= sizeof(sCarTemp)/sizeof(int)){
		tmpindex = 0;
	}
	char buff5[50];
	sprintf(buff5,"%d ℃",sCarTemp[tmpindex]);
	mLabel_TEMPPtr->setText(buff5);
}
static void onUI_init(){
    //Tips :添加 UI初始化的显示代码到这里,如:mText1->setText("123");
	for(int i =0;i < DIAGRAM_SIZE;i++){
		sPoints[i].x = (100*i)/DIAGRAM_SIZE;
		sPoints[i].y = 50;
	}
	updateGUI();
	updateGUI_Tempture();
}

static void onUI_quit() {

}

static bool onUI_Timer(int id){
    //Tips:添加定时器响应的代码到这里,但是需要先打开 activity/pointerActivity.cpp onCreate 函数里面的registerTmer
    //id 是定时器设置时候的标签,这里不要写耗时的操作，否则影响UI刷新,ruturn:[true] 继续运行定时器;[false] 停止运行当前定时器
    if(id == 0){
    	updateGUI();
    }else if(id == 1){
    	updateGUI_Tempture();
    }
	return true;
}

static bool onpointerActivityTouchEvent(const MotionEvent &ev) {
    // 返回false触摸事件将继续传递到控件上，返回true表示该触摸事件在此被拦截了，不再传递到控件上
    return false;
}
static bool onButtonClick_sys_back(ZKButton *pButton) {
    //LOGD(" ButtonClick sys_back !!!\n");
}

static void onProtocolDataUpdate(const SProtocolData &data) {
    // 串口数据回调接口
}


/**
 * 注册定时器
 * 在此数组中添加即可
 */
static S_ACTIVITY_TIMEER REGISTER_ACTIVITY_TIMER_TAB[] = {
    {0,  200}, //定时器id=0, 时间间隔6秒
    {1,  1000},
};
