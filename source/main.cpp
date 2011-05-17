
// Mission implementation file

#include "missiontasks.h"

// objects that are used throught the program
// compass for heading
HMC6352compass compass;
// motor control
AF_DCMotor motor_l(3, MOTOR12_64KHZ);
AF_DCMotor motor_r(4, MOTOR12_64KHZ);
AF_Stepper motor_s(200, 1);

int main (void)
{
	//! This must be called first to configure
	//! routines that the core code relies on
	init();

	//! This is can be any standard setup function
	//! from a previous Arduino.cc project
	setup();

	while(1){
	
		//! This is the same loop from a previous 
		//! Arduino.cc project
		loop();
		
	}

	//! This will never get called but must be present
	//! in any main function that returns a value.
	return 0;
}

uint16_t heading = 0;
uint16_t go_time = 0;
bool dir = 0;
char* print;
void setup (void)
{
	//! sets the led pin as a digital output
	pinMode(ONBOARD_LED_PIN, OUTPUT);
	//! make sure the analog pins are inputs and select the A_REF for reference
	pinMode(LONG_RANGE_IR_PIN, INPUT);
	pinMode(MEDIUM_RANGE_IR_PIN, INPUT);
	analogReference(EXTERNAL);
	// activate the stepper motors to lock the position of the scan platform
	adjustScanPlatform(1,1);
	adjustScanPlatform(0,1);
	// get the powered up heading
	print = (char*)calloc(64, 0);
	Serial.begin(57600);
}
uint8_t room_map1[200];
uint8_t room_map2[200];
uint8_t dist_map[5];
uint16_t angle_map[5];
uint8_t new_dist = 0;
uint16_t new_angle = 0;

void loop (void)
{
	// make the no object map
	scanEnvironment(room_map1, 200);
	// put up the obsticles
	delay(5000);
	// make the object map
	scanEnvironment(room_map2, 200);
	// create a game plan
	analyzeRoom(room_map1, room_map2, dist_map, angle_map);
	// get the current heading
	heading = compass.getHeading();
	// turn to the first object
/* OBJECT #1 */
	fineTuneMJ(dist_map[0], (heading+angle_map[0]));
	// get our current heading
	heading = compass.getHeading();
	// go to it
	while (irDistance_new(MEDIUM_RANGE_IR_PIN) > 23){
		goStraight(heading);
	}
	stopRobot();
	// calculate the second angle and distance
	findPlaqueDistanceAngle(dist_map, angle_map, 2, new_dist, new_angle);
	// get our current heading
	heading = compass.getHeading();
	// turn to the second plaque
/* OBJECT #2 */
	fineTuneMJ(constrain(new_dist, 60, 100), (new_angle+heading));
	// get the heading to the next object
	heading = compass.getHeading();
	// go to the next object
	while(irDistance_new(MEDIUM_RANGE_IR_PIN) > 23){
		goStraight(heading);
	}
	// wait there
	stopRobot();
	// find the third plaque angle and distance
	findPlaqueDistanceAngle(dist_map, angle_map, 3, new_dist, new_angle);
	// get the current heading
	heading = compass.getHeading();
	// turn to the plaque
/* OBJECT #3 */
	fineTuneMJ(constrain(new_dist, 60, 100), (new_angle+heading));
	// get the current heading
	heading = compass.getHeading();
	while(irDistance_new(MEDIUM_RANGE_IR_PIN) > 30){
		goStraight(heading);
	}
	// wait here
	stopRobot();
	// find the fourth plaque angle and distance
	findPlaqueDistanceAngle(dist_map, angle_map, 4, new_dist, new_angle);
	// get the current heading
	heading = compass.getHeading();
	// turn to the plaque
/* OBJECT #4 */	
	fineTuneMJ(constrain(new_dist, 60, 100), (new_angle+heading));
	// get the current heading
	heading = compass.getHeading();
	while(irDistance_new(MEDIUM_RANGE_IR_PIN) > 30){
		goStraight(heading);
	}
	stopRobot();
	heading = compass.getHeading();
	// victory dance
	while(1){
		goStraight(heading);
		delay(2000);
		goStraight(heading, 1);
		delay(2000);
	}
}

