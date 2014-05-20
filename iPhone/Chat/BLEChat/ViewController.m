//
//  ViewController.m
//  BLEChat
//
//  Created by Cheong on 15/8/12.
//  Copyright (c) 2012 RedBear Lab., All rights reserved.
//

#import "ViewController.h"

@interface ViewController ()

@end

@implementation ViewController

- (void)viewDidLoad
{
    [super viewDidLoad];
	// Do any additional setup after loading the view, typically from a nib.
    
    bleShield = [[BLE alloc] init];
    [bleShield controlSetup];
    bleShield.delegate = self;
    
    //UIAccelerometer *accel = [UIAccelerometer sharedAccelerometer];
    //accel.delegate = self;
    //accel.updateInterval = 1.0f/60.0f;
    
    //[self startGetDeviceAngle];

}

- (void)viewDidUnload
{
    [super viewDidUnload];
    // Release any retained subviews of the main view.
}

- (BOOL)shouldAutorotateToInterfaceOrientation:(UIInterfaceOrientation)interfaceOrientation
{
    return (interfaceOrientation != UIInterfaceOrientationPortraitUpsideDown);
}

// Called when scan period is over to connect to the first found peripheral
-(void) connectionTimer:(NSTimer *)timer
{
    if(bleShield.peripherals.count > 0)
    {
        [bleShield connectPeripheral:[bleShield.peripherals objectAtIndex:0]];
    }
    else
    {
        [self.spinner stopAnimating];
    }
}

-(void) bleDidReceiveData:(unsigned char *)data length:(int)length
{
    NSData *d = [NSData dataWithBytes:data length:length];
    NSString *s = [[NSString alloc] initWithData:d encoding:NSUTF8StringEncoding];
    self.label.text = s;
}

NSTimer *rssiTimer;

-(void) readRSSITimer:(NSTimer *)timer
{
    [bleShield readRSSI];
}

- (void) bleDidDisconnect
{
    [self.buttonConnect setTitle:@"Connect" forState:UIControlStateNormal];
    
    [rssiTimer invalidate];
}

-(void) bleDidConnect
{
    [self.spinner stopAnimating];
    [self.buttonConnect setTitle:@"Disconnect" forState:UIControlStateNormal];
    
    // Schedule to read RSSI every 1 sec.
    rssiTimer = [NSTimer scheduledTimerWithTimeInterval:(float)1.0 target:self selector:@selector(readRSSITimer:) userInfo:nil repeats:YES];
    [self startGetDeviceAngle];
}

-(void) bleDidUpdateRSSI:(NSNumber *)rssi
{
    self.labelRSSI.text = rssi.stringValue;
}

- (IBAction)BLEShieldSend:(id)sender
{
    NSString *s;
    NSData *d;
    
    if (self.textField.text.length > 16)
        s = [self.textField.text substringToIndex:16];
    else
        s = self.textField.text;

    s = [NSString stringWithFormat:@"%@\r\n", s];
    d = [s dataUsingEncoding:NSUTF8StringEncoding];
    
    [bleShield write:d];
}

- (IBAction)BLEShieldScan:(id)sender
{
    if (bleShield.activePeripheral)
        if(bleShield.activePeripheral.isConnected)
        {
            [[bleShield CM] cancelPeripheralConnection:[bleShield activePeripheral]];
            return;
        }
    
    if (bleShield.peripherals)
        bleShield.peripherals = nil;
    
    [bleShield findBLEPeripherals:3];
    
    [NSTimer scheduledTimerWithTimeInterval:(float)3.0 target:self selector:@selector(connectionTimer:) userInfo:nil repeats:NO];
    
    [self.spinner startAnimating];
}

- (void)startGetDeviceAngle{
    _motionManager = [[CMMotionManager alloc] init];
    
    // 加速度センサが使用可能かどうか確認
    if (_motionManager.accelerometerAvailable) {
        // 更新の間隔を設定する
        _motionManager.gyroUpdateInterval = 1.0f / 30.0f;
        
        // ハンドラを設定する
        CMGyroHandler   gyroHandler;
        gyroHandler = ^ (CMGyroData *data, NSError* error) {
            // デバイスの向きを表示する
            //double timestamp = data.timestamp;  // 更新時刻
            double x = data.rotationRate.x;  // X軸: 加速度G
            //double y = data.rotationRate.y;  // X軸: 加速度G
            //double z = data.rotationRate.z;  // X軸: 加速度G
            NSString *s;
            NSData *d;
            //NSLog(@"{%lf %lf %lf}",x,y,z);
            NSLog(@"{%lf}",x);
            //s = [NSString stringWithFormat:@"90\r"];
            s = [NSString stringWithFormat:@"%lf=", x];
            //s = [NSString stringWithFormat:@"%d=", (int)(motion.attitude.yaw*180/M_PI)];
            d = [s dataUsingEncoding:NSUTF8StringEncoding];
            
            [bleShield write:d];
        };
        
        // 向きの更新通知を開始する
        //[_motionManager startDeviceMotionUpdatesToQueue:[NSOperationQueue currentQueue]
                                            //withHandler:deviceMotionHandler];
        [_motionManager startGyroUpdatesToQueue:[NSOperationQueue currentQueue] withHandler:gyroHandler];

        if (_motionManager.gyroActive) {
            [_motionManager stopAccelerometerUpdates];
        }
    }
    }

@end
