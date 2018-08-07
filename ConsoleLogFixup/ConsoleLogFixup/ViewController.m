//
//  ViewController.m
//  ConsoleLogFixup
//
//  Created by Damon on 2018/8/7.
//  Copyright © 2018 BigCuteFish. All rights reserved.
//

#import "ViewController.h"

@interface ViewController ()

@end

@implementation ViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    NSData *strData = [@"string -> iOS 开发技术栈" dataUsingEncoding:NSUTF8StringEncoding];
    
    NSData *jsonData = [NSJSONSerialization dataWithJSONObject:@{@"key": @"dic -> iOS 开发技术栈",}
                                                      options:NSJSONWritingPrettyPrinted
                                                        error:nil];
    
    NSMutableSet *set = [NSMutableSet setWithArray:@[@"set0",
                                                     strData,
                                                     jsonData]];
    NSDictionary *dic = @{
                          @"name"  : @"iOS 开发技术栈",
                          @"emoji" : @"😝🙋🍎",
                          @"contact" : @[@"iOS_trick"],
                          @"set" :set
                          };
    NSLog(@"%@", dic);}


@end
