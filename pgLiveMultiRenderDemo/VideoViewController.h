//
//  VideoViewController.h
//  pgLiveMultiRenderDemo
//
//  Created by ElvisCen on 2017/8/21.
//  Copyright © 2017年 ElvisCen. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "pgLibLiveMultiRender.h"


@class VideoViewController;
@interface DemoLiveEvent : pgLibLiveMultiRenderEvent
{
    VideoViewController *m_App;
}
-(id)init:(VideoViewController *)App;
-(void)OnEvent:(NSString *)sAction data:(NSString *)sData capid:(NSString *)sCapID;
@end

@interface VideoViewController : UIViewController
{
    DemoLiveEvent* m_LiveEvent;
    pgLibLiveMultiRender* m_Live;
    UIView* m_pView;
    NSString* m_sCapID;
    NSString* m_sReplysPeer;
    NSString* m_sReplysFile;
    BOOL m_bNeedCallback;
    BOOL m_bIsReplying;
    BOOL 	m_bTransfering ;
    int m_iMethID;
    NSString* filePath;
}
static void MyAudioSessionInterruptionListener(void * inClientData, UInt32 inInterruptionState);

-(void)OnEventProc:(NSString*)sAction data:(NSString*)sData capID:(NSString*)sCapID;
@end
