//
//  VideoViewController.m
//  pgLiveMultiRenderDemo
//
//  Created by ElvisCen on 2017/8/21.
//  Copyright © 2017年 ElvisCen. All rights reserved.
//

#import "VideoViewController.h"
#import <AudioToolbox/AudioToolbox.h>
#import <AVFoundation/AVAudioSession.h>
#import "pgLibLiveMultiView.h"

#define M_SCAPID @""  //需要传入采集端ID
@implementation DemoLiveEvent

-(id)init:(VideoViewController*) App
{
    if (self = [super init]) {
        m_App = App;
    }
    return self;
}

-(void)OnEvent:(NSString *)sAction data:(NSString *)sData capid:(NSString *)sCapID
{
    [m_App OnEventProc:sAction data:sData capID:sCapID];
}

@end
@interface VideoViewController ()

@end

@implementation VideoViewController
static void MyAudioSessionInterruptionListener(void * inClientData, UInt32 inInterruptionState)
{
}

- (instancetype)init
{
    self = [super init];
    if (self) {
        
        m_LiveEvent = [[DemoLiveEvent alloc]init:self];
        m_Live = [[pgLibLiveMultiRender alloc]init:m_LiveEvent];
        m_pView = 0;
        m_sCapID = @"";
    }
    return self;
}

-(void)dealloc{
    
}
-(NSString *)GetDocDir{
    //创建文件管理器
    NSFileManager *fileManeger = [NSFileManager defaultManager];
    //获取document 路径，括号中属性为当前应用程序独享
    NSArray *directoryPaths = NSSearchPathForDirectoriesInDomains(NSDocumentDirectory, NSUserDomainMask, YES);
    return [directoryPaths objectAtIndex:0];
}
//清除
-(void)viewDidDisappear:(BOOL)animated{
    [super viewDidDisappear:animated];
    if (m_pView != nil) {
        [pgLibLiveMultiView Release:m_pView];
        m_pView = nil;
    }
    [m_Live Clean];
}
- (void)viewDidLoad {
    [super viewDidLoad];
    // Do any additional setup after loading the view from its nib.
    //初始化
    m_sReplysPeer = @"";
    m_sReplysFile = @"";
    m_bNeedCallback = NO;
    m_bIsReplying = NO;
    m_iMethID = 32;
    
    
    [self createUI];
}
-(void)createUI{

    UIButton *startBtn = [UIButton buttonWithType:UIButtonTypeCustom];
    startBtn.layer.masksToBounds = YES;
    startBtn.layer.cornerRadius = 5.f;
    startBtn.titleLabel.font = [UIFont systemFontOfSize:14.f];
    startBtn.frame = CGRectMake(20, 70, 70, 40);
    startBtn.backgroundColor = [UIColor blackColor];
    [startBtn setTitle:@"开始" forState:UIControlStateNormal];

    [startBtn addTarget:self action:@selector(startConnect) forControlEvents:UIControlEventTouchUpInside];
    
    [self.view addSubview: startBtn];

    UIButton *stopBtn = [UIButton buttonWithType:UIButtonTypeCustom];
    stopBtn.layer.masksToBounds = YES;
    stopBtn.layer.cornerRadius = 5.f;
    stopBtn.titleLabel.font = [UIFont systemFontOfSize:14.f];
    stopBtn.frame = CGRectMake(120, 70, 70, 40);
    stopBtn.backgroundColor = [UIColor blackColor];
    [stopBtn setTitle:@"停止" forState:UIControlStateNormal];
    
    [stopBtn addTarget:self action:@selector(stopConnect) forControlEvents:UIControlEventTouchUpInside];
    
    [self.view addSubview: stopBtn];
    
    
    //Crerte live view。
    int iErr = [m_Live Initialize:@"ios_test" pass:@"" svrAddr:@"connect.peergine.com:7781" relayAddr:@"" p2pTryTime:1 initParam:@""];
    if (iErr != 0) {
        NSLog(@"pgLibLiveMulti:initialize failed ! iErr = %d",iErr);
        NSString *sInfo = [NSString stringWithFormat:@"Initialize failed! iErr=%d",iErr];
        [self showAlert:sInfo];
    }
    m_pView = [pgLibLiveMultiView Get:@"View0"];
    m_pView.frame = CGRectMake(0, 140, [UIScreen mainScreen].bounds.size.width, 350);
    [self.view addSubview:m_pView];
    
    NSError *error = nil;
    AVAudioSession *audioSession = [AVAudioSession sharedInstance];
    [audioSession setCategory:AVAudioSessionCategoryPlayAndRecord withOptions:AVAudioSessionCategoryOptionDefaultToSpeaker error:&error];
    [audioSession overrideOutputAudioPort:AVAudioSessionPortOverrideSpeaker error:&error];
    [audioSession setActive:YES error:&error];
    //定义记录文件全名以及路径的字符串filePath
    NSString *documentDirectory = [self GetDocDir];
    filePath = [documentDirectory stringByAppendingPathComponent:@"pgtest"];
    
    
    //查找文件 如果不存在，就创建一个文件
    NSFileManager *fileManager = [NSFileManager defaultManager];
    if (![fileManager fileExistsAtPath:filePath]) {
        NSLog(@"File no exsit, create new one");
        [fileManager createFileAtPath:filePath contents:nil attributes:nil];
    }
    
 
    
}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

//开始连接  video 和audio
-(void)startConnect{
    m_sCapID = @"chaws122903";
    [m_Live Connect:m_sCapID];
    [m_Live VideoStart:m_sCapID videoID:0 param:@"" nodeView:m_pView];
    [m_Live AudioStart:m_sCapID audioID:0 param:@""];
    
}
//取消连接
-(void)stopConnect{
    [m_Live AudioStop:m_sCapID audioID:0];
    [m_Live VideoStop:m_sCapID videoID:0];
    [m_Live Disconnect:m_sCapID];
}

//连接
-(NSString *)getcontent:(NSString *)sData Key:(NSString *)key{
    NSString *result = @"";
    NSArray *values = [sData componentsSeparatedByString:@"&"];
    for (int i = 0; i< values.count; i ++) {
        NSArray *entry = [[values objectAtIndex:i] componentsSeparatedByString:@"="];
        if ([[entry objectAtIndex:0] isEqualToString:key]) {
            result = [entry objectAtIndex:1];
            break;
        }
    }
    return result;
}

-(void)timerFireMethod:(NSTimer  *)theTimer{
    UIAlertView *prompAlert = (UIAlertView *)[theTimer userInfo];
    [prompAlert dismissWithClickedButtonIndex:0 animated:NO];
    prompAlert = NULL;
}
-(void)showAlert:(NSString *)_message{
    UIAlertView *promptAlert = [[UIAlertView alloc]initWithTitle:@"" message:_message delegate:nil cancelButtonTitle:nil otherButtonTitles:nil, nil];
    [NSTimer scheduledTimerWithTimeInterval:1.0f target:self selector:@selector(timerFireMethod:) userInfo:promptAlert repeats:YES];
    [promptAlert show];
}
-(void)OnEventProc:(NSString *)sAction data:(NSString *)sData capID:(NSString *)sCapID{
    NSLog(@"Action:%@, Data:%@, sCapID:%@", sAction, sData, sCapID);
    if ([sAction isEqualToString:@"VideoStatus"]) {
        // Video status report
        NSLog(@"Video status report ：Action:%@, Data:%@, sCapID:%@", sAction, sData, sCapID);
    }
    else if ([sAction isEqualToString:@"Notify"]) {
        // Receive the notify from capture side
        NSString* sInfo = [NSString stringWithFormat:@"Receive notify, data=%@", sData];
        [self showAlert:sInfo];
    }
    else if ([sAction isEqualToString:@"Message"]) {
        // Receive the message from render or capture
        NSString* sInfo = [NSString stringWithFormat:@"Receive msg, data=%@, capID=%@", sData, sCapID];
        [self showAlert:sInfo];
    }
    else if ([sAction isEqualToString:@"Login"]) {
        // Login reply
        if ([sData isEqualToString:@"0"]) {
            NSString* sInfo = @"Login success";
            [self showAlert:sInfo];
        }
        else {
            NSString* sInfo = [NSString stringWithFormat:@"Login failed, error=%@", sData];
            [self showAlert:sInfo];
        }
    }
    else if ([sAction isEqualToString:@"Logout"] ) {
        // Logout
        NSString* sInfo = @"Logout";
        [self showAlert:sInfo];
    }
    else if ([sAction isEqualToString:@"Connect"] ) {
        // Connect to capture
        NSString* sInfo = @"Connect to capture";
        [self showAlert:sInfo];
    }
    else if ([sAction isEqualToString:@"Disconnect"] ) {
        // Disconnect from capture
        NSString* sInfo = @"Disconnect from capture";
        [self showAlert:sInfo];
    }
    else if ([sAction isEqualToString:@"Offline"]) {
        // The capture is offline.
        NSString* sInfo = @"The capture is offline";
        [self showAlert:sInfo];
    }
    else if ([sAction isEqualToString:@"LanScanResult"] ) {
        // Lan scan result.
        NSString* sInfo = [NSString stringWithFormat:@"Lan scan result: %@", sData];
        [self showAlert:sInfo];
    }
    else if ([sAction isEqualToString:@"ForwardAllocReply"] ) {
       //
        NSString* sInfo = [NSString stringWithFormat:@"Forward alloc reply, error=%@", sData];
        [self showAlert:sInfo];
    }
    else if ([sAction isEqualToString:@"ForwardFreeReply"] ) {
       //
        NSString* sInfo = [NSString stringWithFormat:@"Forward free reply, error=%@", sData];
        [self showAlert:sInfo];
    }
    else if ([sAction isEqualToString:@"FilePutRequest"] ) {
       //
    }
    else if ([sAction isEqualToString:@"FileGetRequest"] ) {
        NSString* sInfo = [NSString stringWithFormat:@"File accept: %@", sData];
        [self showAlert:sInfo];
    }
    else if ([sAction isEqualToString:@"FileAccept"] ) {
        NSString* sInfo = [NSString stringWithFormat:@"File accept: %@", sData];
        [self showAlert:sInfo];
    }
    else if ([sAction isEqualToString:@"FileReject"] ) {
        NSString* sInfo = [NSString stringWithFormat:@"File Reject: %@", sData];
        [self showAlert:sInfo];
    }
    else if ([sAction isEqualToString:@"FileAbort"] ) {
        NSString* sInfo = [NSString stringWithFormat:@"File Abort: %@", sData];
        [self showAlert:sInfo];
    }
    else if ([sAction isEqualToString:@"FileFinish"] ) {// 文件传输完毕
        NSString* sInfo = [NSString stringWithFormat:@"File Finish: %@", sData];
        [self showAlert:sInfo];
    }
    else if ([sAction isEqualToString:@"FileProgress"]) {
        NSString* sInfo = [NSString stringWithFormat:@"File Progress: %@", sData];
        [self showAlert:sInfo];
    }
    else if ([sAction isEqualToString:@"outString"]) {
        NSString* sInfo = [NSString stringWithFormat:@"outString: %@", sData];
        [self showAlert:sInfo];
    }
    else if ([sAction isEqualToString:@"SvrNotify"]) {
        NSString* sInfo = [NSString stringWithFormat:@"Receive server notify, data=%@", sData];
        [self showAlert:sInfo];
    }
}


@end
