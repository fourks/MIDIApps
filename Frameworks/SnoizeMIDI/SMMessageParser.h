//
// Copyright 2001-2003 Kurt Revis. All rights reserved.
//

#import <CoreMIDI/CoreMIDI.h>
#import <Foundation/Foundation.h>

@class SMEndpoint;
@class SMSystemExclusiveMessage;


@interface SMMessageParser : NSObject
{
    SMEndpoint *nonretainedOriginatingEndpoint;
    id nonretainedDelegate;

    NSMutableData *readingSysExData;
    NSLock *readingSysExLock;
    MIDITimeStamp startSysExTimeStamp;
    NSTimer *sysExTimeOutTimer;
    NSTimeInterval sysExTimeOut;

    BOOL ignoreInvalidData;
}

- (id)delegate;
- (void)setDelegate:(id)value;

- (SMEndpoint *)originatingEndpoint;
- (void)setOriginatingEndpoint:(SMEndpoint *)value;

- (NSTimeInterval)sysExTimeOut;
- (void)setSysExTimeOut:(NSTimeInterval)value;

- (BOOL)ignoresInvalidData;
- (void)setIgnoresInvalidData:(BOOL)value;

- (void)takePacketList:(const MIDIPacketList *)packetList;

- (BOOL)cancelReceivingSysExMessage;
    // Returns YES if it successfully cancels a sysex message which is being received, and NO otherwise.

@end


@interface NSObject (SMMessageParserDelegate)

- (void)parser:(SMMessageParser *)parser didReadMessages:(NSArray *)messages;
- (void)parser:(SMMessageParser *)parser isReadingSysExWithLength:(unsigned int)length;
- (void)parser:(SMMessageParser *)parser finishedReadingSysExMessage:(SMSystemExclusiveMessage *)message;

@end
