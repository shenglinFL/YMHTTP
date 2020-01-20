//
//  YMMultiHandle.h
//  YMHTTP
//
//  Created by zymxxxs on 2020/1/3.
//

#import <Foundation/Foundation.h>
#include "curl.h"

typedef void * YMURLSessionMultiHandle;

NS_ASSUME_NONNULL_BEGIN

@interface YMMultiHandle : NSObject

@property (nonatomic, assign) YMURLSessionMultiHandle rawHandle;
@property (nonatomic, strong) dispatch_queue_t queue;
@property (nonatomic, strong) dispatch_group_t group;

@end


typedef NS_ENUM(NSUInteger, YMSocketRegisterActionType) {
    YMSocketRegisterActionTypeNone = 0,
    YMSocketRegisterActionTypeRegisterRead,
    YMSocketRegisterActionTypeRegisterWrite,
    YMSocketRegisterActionTypeRegisterReadAndWrite,
    YMSocketRegisterActionTypeUnregister
    
};

@interface YMSocketRegisterAction : NSObject

-(instancetype)initWithRawValue:(int)rawValue;

@property (readonly, nonatomic, assign) YMSocketRegisterActionType type;
@property (readonly, nonatomic, assign) BOOL needsReadSource;
@property (readonly, nonatomic, assign) BOOL needsWriteSource;
@property (readonly, nonatomic, assign) BOOL needsSource;

@end


@interface YMSocketSources : NSObject

@property (nonatomic, strong, nullable) dispatch_source_t readSource;
@property (nonatomic, strong, nullable) dispatch_source_t writeSource;

- (void)createSourcesWithAction:(YMSocketRegisterAction *)action socket:(curl_socket_t)socket queue:(dispatch_queue_t)queue handler:(dispatch_block_t)handler;
- (void)createReadSourceWithSocket:(curl_socket_t)socket queue:(dispatch_queue_t)queue handler:(dispatch_block_t)handler;
- (void)createWriteSourceWithSocket:(curl_socket_t)socket queue:(dispatch_queue_t)queue handler:(dispatch_block_t)handler;

+ (instancetype)from:(void *)socketSourcePtr;

@end

NS_ASSUME_NONNULL_END
