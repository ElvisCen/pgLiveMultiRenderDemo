//
//  ViewController.m
//  pgLiveMultiRenderDemo
//
//  Created by ElvisCen on 2017/8/21.
//  Copyright © 2017年 ElvisCen. All rights reserved.
//

#import "ViewController.h"
#import "VideoViewController.h"
@interface ViewController ()

@end

@implementation ViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    // Do any additional setup after loading the view, typically from a nib.
    self.title = @"Demo";
    UIButton *btn = [UIButton buttonWithType:UIButtonTypeCustom];
    btn.frame = CGRectMake(100, 100, 100, 100);
    btn.backgroundColor = [UIColor blueColor];
    [btn setTitle:@"跳转" forState:UIControlStateNormal];
    [btn addTarget:self action:@selector(nextVC ) forControlEvents:UIControlEventTouchUpInside];
    [self.view addSubview:btn];
}

-(void)nextVC{
    VideoViewController *videoVC = [[VideoViewController alloc]init];
    [self.navigationController pushViewController:videoVC animated:YES];
}
- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}


@end
