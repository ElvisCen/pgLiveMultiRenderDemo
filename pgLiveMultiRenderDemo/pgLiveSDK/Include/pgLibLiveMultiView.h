/*************************************************************************
  copyright   : Copyright (C) 2014-2017, Peergine, All rights reserved.
              : www.peergine.com, www.pptun.com
              :
  filename    : pgLibLiveMultiView.h
  discription : 
  modify      : create, chenbichao, 2017/05/10

*************************************************************************/
#ifndef _PG_LIB_LIVE_MULTI_VIEW_H
#define _PG_LIB_LIVE_MULTI_VIEW_H

#import <UIKit/UIKit.h>


///
// pgLibLiveMultiView class
@interface pgLibLiveMultiView : NSObject
{
}

+(UIView*)Get:(NSString*)sViewID;
+(void)Release:(UIView*)View;
+(void*)GetNodeByView:(UIView*)View;

@end


#endif
