#pragma config(Sensor, S1,     sensorSound,    sensorSoundDB)
#pragma config(Sensor, S2,     sensorSonar,    sensorSONAR)
#pragma config(Motor,  motorA,          motorLeft,     tmotorNXT, PIDControl, encoder)
#pragma config(Motor,  motorB,          motorRight,    tmotorNXT, PIDControl, reversed, encoder)
#pragma config(Motor,  motorC,           ,             tmotorNXT, openLoop)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

//
// Eastside Preparatory MinionHunt Template
//

void PlayNote (float index, float beats, float pause)
{
 	PlayImmediateTone ((index), (beats - pause)*25);
  	writeDebugStreamLine ("Freq: %f", ((float)300*(pow(1.08333333,index))));
  	if (pause > 0)
	{
		wait10Msec ((beats - pause) * 25);
		ClearSounds();
		wait10Msec (pause * 25);
	}
  	else
	{
		wait10Msec (beats * 25);
	}
}

void EPS_BeeDoh (void)
{
	ClearSounds();
	PlayNote (350, 1.785, 0);
	PlayNote (300, 2, 0);
}


task EPS_BeeDohTask()
{
	ClearSounds();
	while (true)
	{
		EPS_BeeDoh();
		wait1Msec(1);
	}
}


#define DECISION_STRAIGHT	(1)
#define DECISION_LEFT		(2)
#define DECISION_RIGHT		(3)
#define DECISION_BACK		(4)
#define DECISION_STOP		(5)

int EPS_ProcessDataHunter(int sound, int sonar)
{
	static int prevSound = 0;
	int decision;

	//
	// Do something with values here, return "DECISION_xxx"
	//

	if (sound > prevSound && sound > 100)
	{
		decision = DECISION_STOP;
	}
	else
	{
		decision = DECISION_STRAIGHT;
	}

	//
	// Remember sound value as new "previous"
	//

	prevSound = sound;
	return (decision);
}

int EPS_ProcessDataMinion (int sonar)
{
	int decision;

	//
	// Do something with values here, return "DECISION_xxx"
	//

	if (sonar < 20)
	{
		decision = DECISION_STOP;
	}
	else
	{
		decision = DECISION_STRAIGHT;
	}

	return (decision);
}


bool EPS_SelectRole()
{
	int button;
	int counter;

	eraseDisplay ();
	nxtDisplayTextLine (4, "         Hunter >");
	nxtDisplayTextLine (5, "< Minion");

	// wait for button for a total of 10 seconds, not more
	counter = 100;
	while (counter--)
	{
		button = nNxtButtonPressed;
		switch(button)
		{
			case 2:
				// return false if this is a minion

				return false;
			case 1:
				// return true if this is a hunter
				return true;
		}
		wait10Msec (10);
	}
	// default is minion
	return (false);
}



task main()
{
	int currentSound;
	int currentSonar;
	int decision;

	if (EPS_SelectRole())
	{
		//hunter selected

		eraseDisplay ();
		nxtDisplayCenteredTextLine (4, "Hunting ...");
		while (true)
		{
			//
			// read sensors, process
			//

			currentSound = SensorValue [sensorSound];
			currentSonar = SensorValue [sensorSonar];

			decision = EPS_ProcessDataHunter (currentSound, currentSonar);
			switch(decision)
			{
				case DECISION_STRAIGHT:
				case DECISION_LEFT:
				case DECISION_RIGHT:
				case DECISION_BACK:
				case DECISION_STOP:
					motor[motorLeft] = 0;
					motor[motorRight] = 0;
					PlayNote (777, 6, 0);
					break;

				default:
					motor[motorLeft] = 100;
					motor[motorRight] = 100;
					break;
			}
		}
	}
	else
	{
		// minion selected

		StartTask (EPS_BeeDohTask);
		eraseDisplay ();
		nxtDisplayCenteredTextLine (4, "Beeee-Doooh ...");

		while (true)
		{
			//
			// read sensors, process
			//

			currentSonar = SensorValue [sensorSonar];

			decision = EPS_ProcessDataMinion (currentSonar);
			switch(decision)
			{
				case DECISION_STRAIGHT:
				case DECISION_LEFT:
				case DECISION_RIGHT:
				case DECISION_BACK:
				case DECISION_STOP:
					motor[motorLeft] = 0;
					motor[motorRight] = 0;
					break;

				default:
					motor[motorLeft] = 100;
					motor[motorRight] = 100;
					break;
			}
		}
	}



	//
	// Yield to other tasks
	//

	wait10Msec(1);
}

/*
** end of file
*/
