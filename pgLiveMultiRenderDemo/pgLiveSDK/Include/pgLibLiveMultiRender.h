/*************************************************************************
  copyright   : Copyright (C) 2014-2017, Peergine, All rights reserved.
              : www.peergine.com, www.pptun.com
              :
  filename    : pgLibLiveMultiRender.h
  discription : 
  modify      : create, chenbichao, 2017/04/05

*************************************************************************/
#ifndef _PG_LIB_LIVE_MULTI_RENDER_H
#define _PG_LIB_LIVE_MULTI_RENDER_H

#import <UIKit/UIKit.h>


///
// Timer max
#define _PG_LIVE_MULTI_TIMER_MAX   8


///
// Live event class
@interface pgLibLiveMultiRenderEvent : NSObject
{
}

-(void)OnEvent:(NSString*)sAction data:(NSString*)sData capid:(NSString*)sCapID;

@end


///
// Live node event hook class
@interface pgLibLiveMultiRenderNodeEventHook : NSObject
{
}

-(int)OnExtRequest:(NSString*)sObj meth:(int)uMeth data:(NSString*)sData handle:(int)uHandle peer:(NSString*)sPeer;
-(int)OnReply:(NSString*)sObj err:(int)uErr data:(NSString*)sData param:(NSString*)sParam;

@end


///
// pgLibLiveMultiRender class
@interface pgLibLiveMultiRender : NSObject
{
    BOOL m_bInited;
	
	// PGNode and event interface.
	void* m_pNode;
	void* m_pNodeProc;
	pgLibLiveMultiRenderEvent* m_pEvent;
	pgLibLiveMultiRenderNodeEventHook* m_pHook;

	// Store init parameters
	NSString* m_sUser;
	NSString* m_sPass;
	NSString* m_sSvrAddr;
	NSString* m_sRelayAddr;
	int m_iP2PTryTime;

	// Server parameters
	NSString* m_sInitSvrName;
	NSString* m_sInitSvrAddr;

	// Status members.
	NSString* m_sObjSvr;
	NSString* m_sObjSelf;
	NSString* m_sLanScanRes;
	BOOL m_bStarted;
	BOOL m_bLogin;
	int m_iLanScanTimeout;
	BOOL m_bAloneRenID;
	BOOL m_bSingleMode;
	NSString*m_sSingleCapID;
	BOOL m_bReportPeerInfo;

	// API status parameters
	BOOL m_bApiLanScan;

	NSString* m_sListCapture;
	NSString* m_sListVideo;
	NSString* m_sListAudio;
	NSString* m_sListRecord;
	NSString* m_sListFile;

	void* m_dispItem;
    NSCondition* m_condDisp;

	NSThread* m_thread;
	BOOL m_bThreadExit;

	// Timer parameters.
	NSString* m_psTimerArray[_PG_LIVE_MULTI_TIMER_MAX];
}

// Override the init function.
-(pgLibLiveMultiRender*)init:(pgLibLiveMultiRenderEvent*)pEvent;

-(void)SetNodeEventHook:(pgLibLiveMultiRenderNodeEventHook*)pHook;

-(int)Initialize:(NSString*)sUser pass:(NSString*)sPass svrAddr:(NSString*)sSvrAddr
	relayAddr:(NSString*)sRelayAddr p2pTryTime:(int)iP2PTryTime initParam:(NSString*)sInitParam;
-(void)Clean;

// Get peergine node
-(void*)GetNode;

-(NSString*)GetSelfPeer;

-(int)LanScanStart;

-(int)Connect:(NSString*)sCapID;
-(void)Disconnect:(NSString*)sCapID;

-(int)MessageSend:(NSString*)sCapID data:(NSString*)sData;

-(int)VideoModeSize:(int)iMode width:(int)iWidth height:(int)iHeight;
-(int)VideoStart:(NSString*)sCapID videoID:(int)iVideoID param:(NSString*)sParam nodeView:(UIView*)nodeView;
-(void)VideoStop:(NSString*)sCapID videoID:(int)iVideoID;
-(int)VideoFramePull:(NSString*)sCapID videoID:(int)iVideoID;
-(int)VideoCamera:(NSString*)sCapID videoID:(int)iVideoID jpgPath:(NSString*)sJpgPath;
-(int)VideoParam:(NSString*)sCapID videoID:(int)iVideoID param:(NSString*)sParam;
-(int)VideoShowMode:(int)iMode;

-(int)AudioStart:(NSString*)sCapID audioID:(int)iAudioID param:(NSString*)sParam;
-(void)AudioStop:(NSString*)sCapID audioID:(int)iAudioID;
-(int)AudioSpeech:(NSString*)sCapID audioID:(int)iAudioID enable:(BOOL)bEnable;
-(int)AudioParam:(NSString*)sCapID audioID:(int)iAudioID param:(NSString*)sParam;
-(int)AudioMute:(NSString*)sCapID audioID:(int)iAudioID inPut:(BOOL)bInput outPut:(BOOL)bOutput;

-(int)RecordStart:(NSString*)sCapID aviPath:(NSString*)sAviPath videoID:(int)iVideoID audioID:(int)iAudioID;
-(void)RecordStop:(NSString*)sCapID;

-(int)SvrRequest:(NSString*)sData param:(NSString*)sParam;

-(int)FilePutRequest:(NSString*)sCapID path:(NSString*)sPath peerPath:(NSString*)sPeerPath;
-(int)FileGetRequest:(NSString*)sCapID path:(NSString*)sPath peerPath:(NSString*)sPeerPath;
-(int)FileAccept:(NSString*)sCapID path:(NSString*)sPath;
-(int)FileReject:(NSString*)sCapID errCode:(int)iErrCode;
-(int)FileCancel:(NSString*)sCapID;

-(NSString*)Version;

-(int)_NodeCallbackPost:(int)iType obj:(NSString*)sObj intParam0:(int)iParam0
    intParam1:(int)iParam1 strParam0:(NSString*)sParam0 strParam1:(NSString*)sParam1;

@end

#endif //_PG_LIB_LIVE_MULTI_RENDER_H
