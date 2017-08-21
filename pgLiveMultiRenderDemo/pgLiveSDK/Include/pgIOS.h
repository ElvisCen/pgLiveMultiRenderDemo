/****************************************************************
  copyright   : Copyright (C) 2014, chenbichao, All rights reserved.
                www.peergine.com, www.pptun.com
                
  filename    : pgIOS.h
  discription : 
  modify      : create, chenbichao, 2014/7/27

*****************************************************************/
#ifndef _PG_IOS_H
#define _PG_IOS_H

///
// The node callback intetface class.
class IPGIOSNodeProc {
public:
	virtual unsigned int OnReply(NSString* lpszObj, unsigned int uErrCode,
		NSString* lpszData, NSString* lpszParam) = 0;

	virtual int OnExtRequest(NSString* lpszObj, unsigned int uMethod,
		NSString* lpszData, unsigned int uHandle, NSString* lpszPeer) = 0;
};


///
// The node interface class.
class IPGIOSNode
{
public:
	// The node property
	NSString* Control;
	NSString* Class;
	NSString* Server;
	NSString* Local;
	NSString* Relay;
	NSString* Node;

public:
	// The node callback interface.
	IPGIOSNodeProc* NodeProc;

public:
	// The OML Parser methods.
	virtual NSString* omlEncode(NSString* lpszEle) = 0;
	virtual NSString* omlDecode(NSString* lpszEle) = 0;
	virtual NSString* omlSetName(NSString* lpszEle, NSString* lpszPath, NSString* lpszName) = 0;
	virtual NSString* omlSetClass(NSString* lpszEle, NSString* lpszPath, NSString* lpszClass) = 0;
	virtual NSString* omlSetContent(NSString* lpszEle, NSString* lpszPath, NSString* lpszContent) = 0;
	virtual NSString* omlNewEle(NSString* lpszName, NSString* lpszClass, NSString* lpszContent) = 0;
	virtual NSString* omlGetEle(NSString* lpszEle, NSString* lpszPath, int uSize, int uPos) = 0;
	virtual NSString* omlDeleteEle(NSString* lpszEle, NSString* lpszPath, int uSize, int uPos) = 0;
	virtual NSString* omlGetName(NSString* lpszEle, NSString* lpszPath) = 0;
	virtual NSString* omlGetClass(NSString* lpszEle, NSString* lpszPath) = 0;
	virtual NSString* omlGetContent(NSString* lpszEle, NSString* lpszPath) = 0;
	virtual NSString* omlInsertEle(NSString* lpszEle, NSString* lpszPath, int uPos,
		NSString* lpszName, NSString* lpszClass, NSString* lpszContent) = 0;

	// Object handle methods.
	virtual int ObjectAdd(NSString* lpszName, NSString* lpszClass, NSString* lpszGroup, int uFlag) = 0;
	virtual void ObjectDelete(NSString* lpszObj) = 0;
	virtual NSString* ObjectEnum(NSString* lpszObject, NSString* lpszClass) = 0;
	virtual NSString* ObjectGetClass(NSString* lpszObj) = 0;
	virtual int ObjectSetGroup(NSString* lpszObj, NSString* lpszGroup) = 0;
	virtual NSString* ObjectGetGroup(NSString* lpszObj) = 0;
	virtual int ObjectSync(NSString* lpszObj, NSString* lpszPeer, int uAction) = 0;
	virtual int ObjectRequest(NSString* lpszObj, int uMethod, NSString* lpszIn, NSString* lpszParam) = 0;
	virtual int ObjectExtReply(NSString* lpszObj, int uErrCode, NSString* lpszOut, int uHandle) = 0;

	// Utilize methods.
	virtual NSString* utilCmd(NSString* lpszCmd, NSString* lpszParam) = 0;
	virtual NSString* utilGetWndRect() = 0;

	// Node window methods.
	virtual UIView* WndNew(int iLeft, int iTop, int iWidth, int iHeight) = 0;
	virtual void WndDelete() = 0;
	virtual int WndSetSize(int iLeft, int iTop, int iWidth, int iHeight) = 0;

	// Node contel methods.
	virtual int Start(int uOption) = 0;
	virtual void Stop() = 0;
	virtual int PostMessage(NSString* lpszMsg) = 0;
	virtual int PumpMessage() = 0;
	virtual void Quit() = 0;

	// Delete this node object.
	virtual void Delete() = 0;
};


///
// New a node object.
IPGIOSNode* pgNewIOSNode();


///
// Node lib initialize
unsigned int pgIOSInitialize();

// Node lib clean
void pgIOSClean();

#endif

