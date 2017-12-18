/*
 * ZKVideoView.h
 *
 *  Created on: Nov 13, 2017
 *      Author: guoxs
 */

#ifndef _CONTROL_ZKVIDEOVIEW_H_
#define _CONTROL_ZKVIDEOVIEW_H_

#include "ZKBase.h"
#include "media/ZKMediaPlayer.h"

class ZKVideoView : public ZKBase {
public:
	ZKVideoView(HWND hParentWnd);
	virtual ~ZKVideoView();

	void play(const char *pFilePath, int msec = 0);
	void pause();
	void resume();
	void seekTo(int msec);
	void stop();

	bool isPlaying();

	void setVolume(float volume);
	void setPosition(const LayoutPosition &position);

	int getDuration();
	int getCurrentPosition();

public:
	typedef enum {
		E_MSGTYPE_VIDEO_PLAY_STARTED,
		E_MSGTYPE_VIDEO_PLAY_COMPLETED,
		E_MSGTYPE_VIDEO_PLAY_ERROR
	} EMessageType;

	class IVideoPlayerMessageListener {
	public:
		virtual ~IVideoPlayerMessageListener() { }
		virtual void onVideoPlayerMessage(ZKVideoView *pVideoView, int msg) = 0;
	};

	void setVideoPlayerMessageListener(IVideoPlayerMessageListener *pListener) {
		mVideoPlayerMessageListenerPtr = pListener;
	}

protected:
	virtual void onBeforeCreateWindow(const Json::Value &json);
	virtual void onAfterCreateWindow(const Json::Value &json);
	virtual const char* getClassName() const { return ZK_VIDEOVIEW; }

	virtual void onDraw(HDC hdc);

private:
	void parseVideoViewAttributeFromJson(const Json::Value &json);

	class PlayerMessageListener : public ZKMediaPlayer::IPlayerMessageListener {
	public:
		PlayerMessageListener(ZKVideoView *pVideoView) : mVideoViewPtr(pVideoView) { }
		virtual void onPlayerMessage(ZKMediaPlayer *pMediaPlayer, int msg, void *pMsgData);

	private:
		ZKVideoView * const mVideoViewPtr;
	};

private:
	ZKMediaPlayer *mMediaPlayerPtr;
	IVideoPlayerMessageListener *mVideoPlayerMessageListenerPtr;

	PlayerMessageListener mPlayerMessageListener;
};

#endif /* _CONTROL_ZKVIDEOVIEW_H_ */
