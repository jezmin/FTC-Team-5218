#pragma config(Hubs,  S1, HTServo,  HTMotor,  HTMotor,  HTMotor)
#pragma config(Hubs,  S2, HTServo,  none,     none,     none)
#pragma config(Sensor, S1,     ,               sensorI2CMuxController)
#pragma config(Sensor, S2,     ,               sensorI2CMuxController)
#pragma config(Sensor, S3,     carrot,         sensorSONAR)
#pragma config(Sensor, S4,     HTSMUX,         sensorI2CCustom)
#pragma config(Motor,  mtr_S1_C2_1,     driveRearRight, tmotorTetrix, PIDControl, encoder)
#pragma config(Motor,  mtr_S1_C2_2,     driveFrontRight, tmotorTetrix, PIDControl, encoder)
#pragma config(Motor,  mtr_S1_C3_1,     shoulder,      tmotorTetrix, PIDControl, encoder)
#pragma config(Motor,  mtr_S1_C3_2,     motorG,        tmotorTetrix, PIDControl, encoder)
#pragma config(Motor,  mtr_S1_C4_1,     driveFrontLeft, tmotorTetrix, PIDControl, reversed, encoder)
#pragma config(Motor,  mtr_S1_C4_2,     driveRearLeft, tmotorTetrix, PIDControl, reversed, encoder)
#pragma config(Servo,  srvo_S1_C1_1,    servo1,               tServoNone)
#pragma config(Servo,  srvo_S1_C1_2,    brush,                tServoContinuousRotation)
#pragma config(Servo,  srvo_S1_C1_3,    arm,                  tServoStandard)
#pragma config(Servo,  srvo_S1_C1_4,    dockarm,              tServoContinuousRotation)
#pragma config(Servo,  srvo_S1_C1_5,    servo5,               tServoNone)
#pragma config(Servo,  srvo_S1_C1_6,    servo6,               tServoNone)
#pragma config(Servo,  srvo_S2_C1_1,    rightEye,             tServoStandard)
#pragma config(Servo,  srvo_S2_C1_2,    leftEye,              tServoStandard)
#pragma config(Servo,  srvo_S2_C1_3,    finger,               tServoStandard)
#pragma config(Servo,  srvo_S2_C1_4,    servo10,              tServoNone)
#pragma config(Servo,  srvo_S2_C1_5,    servo11,              tServoNone)
#pragma config(Servo,  srvo_S2_C1_6,    door,                 tServoStandard)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#define FOUR_WHEEL_DRIVE

#define LSERVO_CENTER 134
#define RSERVO_CENTER 113
#define RSERVO_PERP   235

#define US_DIST_POS_1 80
#define US_DIST_POS_3 55

#include "../../lib/sensors/drivers/hitechnic-sensormux.h"
#include "../../lib/sensors/drivers/hitechnic-irseeker-v2.h"
#include "../../lib/baemax_drivetrain_defs.h"
#include "../../lib/drivetrain_square.h"
#include "../../lib/dead_reckon.h"
#include "../../lib/data_log.h"
#include "../../lib/ir_utils.h"
#include "../../lib/us_cascade_utils.c"

const tMUXSensor irr_left = msensor_S4_1;
const tMUXSensor irr_right = msensor_S4_2;

ir_direction_t dir;

void move_to_pole(int count)
{
    init_path();

    switch (count) {
    case 1:
        add_segment(-22, 0, 50);
        add_segment(-20, 180, 100);
        break;
    case 2:
        add_segment(-10, 0, 50);
        add_segment(0, 30, 50);
        add_segment(-50, 0, 100);
        break;
    case 3:
        add_segment(-10, 90, 50);
        add_segment(-45, -90, 50);
        break;
    }
    stop_path();
  	dead_reckon();
}

task main()
{
    int i;
    int center_position;

    initialize_receiver(irr_left, irr_right);

    servo[leftEye] = LSERVO_CENTER;
    servo[rightEye] = RSERVO_CENTER;

    center_position = ultrasound(carrot, -24, US_DIST_POS_1, US_DIST_POS_3);

    for (i = 0; i < center_position; i++) {
        playImmediateTone(251, 50);
        wait1Msec(1000);
    }

    move_to_pole(center_position);

    while(true) {
        nxtDisplayTextLine(1, "Sensor value: %d", SensorValue[carrot]);
    }
}
