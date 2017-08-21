/*************************************************************************
  copyright   : Copyright (C) 2012-2014, chenbichao, All rights reserved.
  filename    : pgLibLive.h
  discription : 
  modify      : create, chenbichao, 2014/08/06

*************************************************************************/
#ifndef _PG_LIB_LIVE_H
#define _PG_LIB_LIVE_H

#import <UIKit/UIKit.h>


///
// Live mode
enum pgLibLiveMode {
	pgLibLiveModeRender = 0,
	pgLibLiveModeCapture = 1
};


///
// Live event class
@interface pgLibLiveEvent : NSObject
{
}

-(void)OnEvent:(NSString*)sAction data:(NSString*)sData render:(NSString*)sRender;

@end


///
// Live node event hook class
@interface pgLibLiveNodeEventHook : NSObject
{
}

-(int)OnExtRequest:(NSString*)sObj meth:(int)uMeth data:(NSString*)sData handle:(int)uHandle peer:(NSString*)sPeer;
-(int)OnReply:(NSString*)sObj err:(int)uErr data:(NSString*)sData param:(NSString*)sParam;

@end


///
// pgLibLive class
@interface pgLibLive : NSObject
{
	pgLibLiveEvent* m_pEvent;
	pgLibLiveNodeEventHook* m_pHook;
	UIView* m_pView;

	// Store init parameters
	int m_iMode;
	NSString* m_sVideoParam;
	NSString* m_sAudioParam;
	NSString* m_sCapID;

	NSObject* m_LiveCapture;
	NSObject* m_LiveRender;
}

// Override the init function.
-(pgLibLive*)init:(pgLibLiveEvent*)pEvent;

-(void)SetNodeEventHook:(pgLibLiveNodeEventHook*)pHook;

// Initialize and cleanup.
-(BOOL)Initialize:(int)iMode user:(NSString*)sUser pass:(NSString*)sPass
	svrAddr:(NSString*)sSvrAddr relayAddr:(NSString*)sRelayAddr p2pTryTime:(int)iP2PTryTime videoParam:(NSString*)sVideoParam;

-(BOOL)InitializeEx:(int)iMode user:(NSString*)sUser pass:(NSString*)sPass
	svrAddr:(NSString*)sSvrAddr relayAddr:(NSString*)sRelayAddr p2pTryTime:(int)iP2PTryTime
	initParam:(NSString*)sInitParam videoParam:(NSString*)sVideoParam audioParam:(NSString*)sAudioParam;

-(void)Cleanup;

-(void)EventEnable:(BOOL)bEnable;

// Get peergine node
-(void*)GetNode;
-(NSString*)GetSelfPeer;

// Create and destroy the NSView of node.
-(UIView*)WndCreate:(int)iX y:(int)iY w:(int)iW h:(int)iH;
-(void)WndDestroy;

// Start and stop the live.
-(BOOL)Start:(NSString*)sCapID;
-(void)Stop;

// Start and stop video.
-(BOOL)VideoStart;
-(void)VideoStop;

// Start and stop audio.
-(BOOL)AudioStart;
-(void)AudioStop;

// Mutilcast notify to all render.
-(BOOL)NotifySend:(NSString*)sMsg;

// Send message to one render.
-(BOOL)MessageSend:(NSString*)sData render:(NSString*)sRender;

// Pull one MJPEG frame.
-(BOOL)FramePull;

// Scan the captures in the same lan.
-(BOOL)LanScanStart;

// Video control
-(BOOL)VideoSource:(int)iCameraNo;
-(BOOL)VideoCamera:(NSString*)sJpgPath;
-(BOOL)VideoModeSize:(int)iMode width:(int)iWidth height:(int)iHeight;
-(BOOL)VideoShowMode:(int)iMode;
-(BOOL)VideoParam:(NSString*)sVideoParam;
-(BOOL)VideoRecordStart:(NSString*)sAviPath;
-(void)VideoRecordStop;

// Audio control
-(BOOL)AudioSpeech:(BOOL)bEnable;
-(BOOL)AudioParam:(NSString*)sParam;
-(BOOL)AudioSpeakerVolume:(int)iVolume render:(NSString*)sRender;
-(BOOL)AudioMute:(BOOL)bInput output:(BOOL)bOutput;

// Record video and audio.
-(BOOL)RecordStart:(NSString*)sAviPath video:(BOOL)bVideo audio:(BOOL)bAudio;
-(void)RecordStop;

// Live forward alloc and free
-(int)ForwardAlloc;
-(int)ForwardFree;

// File transfer functions
-(int)FileGetRequest:(NSString*)sPeer Path:(NSString*)sPath PeerPath:(NSString*)sPeerPath;
-(int)FilePutRequest:(NSString*)sPeer Path:(NSString*)sPath PeerPath:(NSString*)sPeerPath;
-(int)FileAccept:(NSString*)sPeer Path:(NSString*)sPath;
-(int)FileReject:(NSString*)sPeer;
-(int)FileCancel:(NSString*)sPeer;

// Server request.
-(BOOL)SvrRequest:(NSString*)sData;

@end


#endif //_PG_LIB_LIVE_H
