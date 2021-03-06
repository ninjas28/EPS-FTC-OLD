#pragma config(Hubs,  S1, HTMotor,  HTServo,  none,     none)
#pragma config(Hubs,  S4, HTMotor,  none,     none,     none)
#pragma config(Sensor, S1,     ,               sensorI2CMuxController)
#pragma config(Sensor, S2,     HTIRS2,         sensorI2CCustom)
#pragma config(Sensor, S3,     touchSensor,    sensorTouch)
#pragma config(Sensor, S4,     ,               sensorI2CMuxController)
#pragma config(Motor,  motorA,           ,             tmotorNXT, openLoop)
#pragma config(Motor,  motorB,           ,             tmotorNXT, openLoop)
#pragma config(Motor,  motorC,           ,             tmotorNXT, openLoop)
#pragma config(Motor,  mtr_S1_C1_1,     motorD,        tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C1_2,     motorE,        tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S4_C1_1,     motorF,        tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S4_C1_2,     motorG,        tmotorTetrix, openLoop)
#pragma config(Servo,  srvo_S1_C2_1,    servo1,               tServoContinuousRotation)
#pragma config(Servo,  srvo_S1_C2_2,    servo2,               tServoContinuousRotation)
#pragma config(Servo,  srvo_S1_C2_3,    servo3,               tServoStandard)
#pragma config(Servo,  srvo_S1_C2_4,    servo4,               tServoNone)
#pragma config(Servo,  srvo_S1_C2_5,    servo5,               tServoNone)
#pragma config(Servo,  srvo_S1_C2_6,    servo6,               tServoNone)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

//
// Eastside Preparatory FTC Robot 1 main robot control code
//

#include "EPS_JoystickDriver.c"
#include "hitechnic-irseeker-v2.h"
#include "EPS_DECLARATIONS.h"
#include "EPS_MUSIC.h"
#include "EPS_REDRIVER.h"

void EPS_initialize () {
	// initialization after power up and before autonomous period
	// we may put servos into a certain position etc. here
	// if we do anything here, don't forget to put the "robot moves during init" label on the robot!!!

	EPS_WeAreTheChampions ();
}




void EPS_autonomous () {
	//EPS_autonomous_work();
	motor[motorE] = 50;
	motor[motorD] = -50;
	servo[servo4] = 0;
	wait10Msec(180);

	motor[motorE] = 0;
	motor[motorD] = 0;
	servo[servo4] = 18;
	return;
}

task main() {
	bool bAutoDone = false;
	EPS_initialize ();
	while (true) {
		waitForStart ();

		getJoystickSettings(joystick);
		if (joystick.UserMode || bAutoDone) {
			EPS_driver_control();
		}
		else {
			EPS_autonomous ();
			bAutoDone = true;
		}
	}
}
