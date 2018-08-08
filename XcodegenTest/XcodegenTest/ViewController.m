//
//  ViewController.m
//  XcodegenTest
//
//  Created by tiger on 2018/8/7.
//  Copyright © 2018年 tge. All rights reserved.
//

#import "ViewController.h"
#import <XcodegenAppFramework/Animal.h>
#import <Toast/Toast.h>

@interface ViewController ()
@property (weak, nonatomic) IBOutlet UILabel *messageLabel;

@end

@implementation ViewController

- (void)viewDidLoad {
  [super viewDidLoad];
  
  [Animal sayHellow];
  self.messageLabel.text = [Animal helloTipTrick];
  
  [self.view makeToast:@"Hello iOS Trick" duration:1 position:CSToastPositionCenter];
  
}

- (void)didReceiveMemoryWarning {
  [super didReceiveMemoryWarning];
  // Dispose of any resources that can be recreated.
}


@end
