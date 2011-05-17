
#include "missiontasks.h"

//! declare object that are used in this file
extern HMC6352compass compass;
extern AF_DCMotor motor_l;
extern AF_DCMotor motor_r;
extern AF_Stepper motor_s;

//! Motor Duty Cycle constraints
const uint8_t STRAIGHT_DUTY_CYCLE = 125;
const uint8_t MIN_DUTY_CYCLE = 50;
const uint8_t MAX_DUTY_CYCLE = 200;

void goStraight(uint16_t heading, bool reverse)
{
  	//most recent PID update time in ms
	static unsigned long lastPIDTime; 
	float targetHeading;  //setpoint
	float motorPower; 	//0 - 255 PWM on
	int lm, rm;

	// update PID here//checks for rollover with millis()
	if(millis() < lastPIDTime){
		lastPIDTime = 0;
	}
	// can we make an adjustment??
	if((millis() - lastPIDTime) > 10){
		lastPIDTime += 10;
		motorPower = updatePID(heading, compass.getHeading());  //takes setpoint and process variable
		rm = constrain((STRAIGHT_DUTY_CYCLE) + motorPower, MIN_DUTY_CYCLE, MAX_DUTY_CYCLE);
		lm = constrain((STRAIGHT_DUTY_CYCLE) - motorPower, MIN_DUTY_CYCLE, MAX_DUTY_CYCLE);
		// update the motors
		// determine the direction of travel
		if (reverse == true){
			motor_l.setSpeed(rm);
			motor_r.setSpeed(lm);
			motor_l.run(BACKWARD);
 			motor_r.run(BACKWARD);
		}
		else{
			motor_l.setSpeed(lm);
			motor_r.setSpeed(rm);
			motor_l.run(FORWARD);
 			motor_r.run(FORWARD);
		}
	}
}

void stopRobot()
{
	motor_l.run(RELEASE);
	motor_r.run(RELEASE);
}

void scanEnvironment(uint8_t* map, uint8_t map_size)
{	
	// now we can move back and start storing sensor data
	for(uint8_t cnt=0; cnt<map_size; cnt++){
		// create the map element
		map[cnt] = irDistance_new(MEDIUM_RANGE_IR_PIN);
		// move the motor and do it again
		adjustScanPlatform((adjustScanPlatform(0)+1), 1);
		// allow the platform movement to settle
		delay(100);
	}
	
	// Return the scan platform to the home position
	adjustScanPlatform(0, 1);
}

uint8_t ROOM_CONSECUTIVE_CNT = 4;
uint8_t ROOM_DIFFERENCE_AMOUNT = 15;

void analyzeRoom(uint8_t* map1, uint8_t* map2, uint8_t* dist_map, uint16_t* heading_map)
{
	uint16_t result = 0;
	uint8_t consecutive_cnt = 0;
	uint16_t result_cnt = 0;
	// clear the result map
	for (uint8_t index = 0; index < MAX_PLAQUE_CNT; index++){
		heading_map[index] = 0;
		dist_map[index] = 0;
	}
	// look for the difference in the room
	for (uint8_t index = 0; index < 200; index++){
		result = map1[index] - map2[index];
		result = abs(result);
		// look for large differences
		if (result > ROOM_DIFFERENCE_AMOUNT){
			// the amount of consecutive large differences indicated a plaque
			consecutive_cnt++;
			if ((consecutive_cnt == ROOM_CONSECUTIVE_CNT) && (result_cnt < MAX_PLAQUE_CNT)){
				// store the heading to this plaque (degrees * 10)
				dist_map[result_cnt] = map2[index];
				heading_map[result_cnt] = index*18;
				// look for the max amount of plaques
				result_cnt++;
				// dont get the same object twice
				index += 36;
				consecutive_cnt = 0;
			}
		}
		else{
			consecutive_cnt = 0;
		}
	}
	// just hang here if all plaques arent found
	if (dist_map[(MAX_PLAQUE_CNT-1)] == 0){
		while(1);
	}
	// next time only look for n-1 consecutive differences
	//ROOM_CONSECUTIVE_CNT--;
	// nothing at all
	//if (ROOM_CONSECUTIVE_CNT == 1){
	//	ROOM_CONSECUTIVE_CNT = 4;
	//	ROOM_DIFFERENCE_AMOUNT -= 5;
	//	if (ROOM_DIFFERENCE_AMOUNT == 0){
	//		while(1);
	//	}
	//	
	//}
	//}	
	// convert angles referenced from 0 to angles referenced to angle[n-1]
	for (uint8_t loop=4; loop != 0; loop--){
		// convert to absolute angle from home to the angle between the last plaque can current
		if (heading_map[loop] != 0){
			heading_map[loop] = heading_map[loop] - heading_map[(loop-1)];
		}
	}				
}

void findPlaqueDistanceAngle(uint8_t* dist, uint16_t* angle, uint8_t plaque_num, uint8_t& plaque_dist, uint16_t& plaque_angle)
{
	if (plaque_num < 2){
		plaque_num = 2;
	}

	double dist1 = static_cast<double>(dist[(plaque_num-1)]);
	double dist2 = static_cast<double>(dist[(plaque_num-2)]);
	double angle1 = static_cast<double>(angle[(plaque_num-1)]);
	// find the distance to the next plaque 
	double tmp_plaque_dist = sqrt( ( pow(dist1,2) + 
						  			pow(dist2,2)) - (2 * dist2 * dist1 * (cos((angle1*PI)/180.0)) )
					  			 );
	plaque_dist = static_cast<uint8_t>(tmp_plaque_dist);
	// find the angle to the next plaque
	double tmp_plaque_angle = acos( ( pow(dist2,2) + pow(plaque_dist,2) - (dist1 * dist1) ) / 
						   			(2 * dist2 * plaque_dist)
					   			  );
	// convert back to degrees
	tmp_plaque_angle *= 180.00000 / PI; 
	plaque_angle = static_cast<uint16_t>(tmp_plaque_angle*10);
}
extern char* print;
void adjustHeading(uint16_t angle)
{
	// proportional error for speed management
	uint16_t p_err = 0;
	//exits only once the offset angle is reached
  	uint16_t target_offset = compass.getHeading();
	// make sure the heading is valid
	while (angle > 3599){
		angle -= 3600;
	}
	//sprintf(print, "looking for - %d \n", (angle/10));
	//Serial.write(print);
	//memset(print, 0, 64);
  	// keep looping until we are less than 5 degrees off
	// from desired setting 
	while(abs(angle - target_offset) > 50){
    	target_offset = compass.getHeading();
		p_err = abs(angle - target_offset);
		p_err = constrain(p_err, 75, 150);
		// set the motors to the same speed
		motor_r.setSpeed(p_err);
  		motor_l.setSpeed(p_err);
		if (target_offset > angle){
			// one should go forward and another backwards
  			motor_r.run(BACKWARD);
  			motor_l.run(FORWARD);  
		}
		else if (target_offset < angle){
			// one should go forward and another backwards
  			motor_r.run(FORWARD);
  			motor_l.run(BACKWARD);
		}
  	}
  	//once desired heading is found turn motors off
  	motor_l.run(RELEASE);
  	motor_r.run(RELEASE);
}

// ISSUES WITH SOME OF THE CODE HERE - commented out
int16_t readADC(uint16_t pin)
{
	const uint8_t sample_amout = 100;		// number of real ADC samples
	int16_t x_i = 0;      					// ADC input for sample i
	int16_t A_1 = 0;   						// current  i   running average
	int16_t A_0 = 0;       					// previous i-1 running average
	
	// deciminate the IR sensor to get a better idea of the distance
	for (uint8_t i=1; i<=sample_amout; i++){
    	// read from the ADC
		x_i = analogRead(pin);
		// rapid calculation method - http://en.wikipedia.org/wiki/Standard_deviation
		// accumulate the result
		A_1 = A_0 + (( x_i - A_0 ) / i);
		// stored for the next use
		A_0 = A_1;
	}
	// cast and return the result
	return A_1;
}

uint16_t irDistance_new(uint8_t pin)
{
	uint16_t dist = readADC(pin);
	//dist = pgm_read_word(&medium_range_data[dist]);
	//return dist;
	// Get the medium range result
	if (dist > (MEDIUM_RANGE_OFFSET+MEDIUM_RANGE_TABLE_SIZE)){
		return MIN_MEDIUM_RANGE_IR_DISTANCE;
	}
	else if (dist < MEDIUM_RANGE_OFFSET){
		return MAX_MEDIUM_RANGE_IR_DISTANCE;
	}
	else{
		// get the value from flash (offset from all the same values)
		dist = pgm_read_byte(&medium_range_data[(dist-MEDIUM_RANGE_OFFSET)]);
		dist *= 2;
		return dist;
	}
}

uint16_t irDistance(uint8_t pin)
{
	// store the value from the ADC converter
	uint16_t tmp_adc_result1 = readADC(LONG_RANGE_IR_PIN);
	uint16_t tmp_adc_result2 = readADC(MEDIUM_RANGE_IR_PIN);
	uint16_t dist_from_flash1;
	uint16_t dist_from_flash2;

	// Get the medium range result
	//if (tmp_adc_result2 > (MEDIUM_RANGE_OFFSET+MEDIUM_RANGE_TABLE_SIZE)){
	//	dist_from_flash2 = MIN_MEDIUM_RANGE_IR_DISTANCE;
	//}
	//else if (tmp_adc_result2 < MEDIUM_RANGE_OFFSET){
	//	dist_from_flash2 = MAX_MEDIUM_RANGE_IR_DISTANCE;
	//}
	//else{
		// get the value from flash (offset from all the same values)
	//	dist_from_flash2 = pgm_read_byte(&medium_range_data[tmp_adc_result2-MEDIUM_RANGE_OFFSET]);
	//	dist_from_flash2 *= 2;
	//}	
	
	// get the long range result
	// reduce the size of the lookup table
	//if (tmp_adc_result1 > (LONG_RANGE_OFFSET+LONG_RANGE_TABLE_SIZE)){
	//	dist_from_flash1 = MIN_LONG_RANGE_IR_DISTANCE;
	//}
	//else if (tmp_adc_result1 < LONG_RANGE_OFFSET){
	//	dist_from_flash1 = MAX_LONG_RANGE_IR_DISTANCE;
	//}
	//else{
		// get the value from flash (offset from all the same values)
	//	dist_from_flash1 = pgm_read_byte(&long_range_data[tmp_adc_result1-LONG_RANGE_OFFSET]);
	//	dist_from_flash1 *= 2;
	//}
	
	// find what value is closer to the look up mid value.  This will be the most reliable value
	//float long_result = dist_from_flash1 / (MAX_LONG_RANGE_IR_DISTANCE + MIN_LONG_RANGE_IR_DISTANCE);
	//float medium_result = dist_from_flash2 / (MAX_MEDIUM_RANGE_IR_DISTANCE + MIN_MEDIUM_RANGE_IR_DISTANCE);
	// convet from decimal to percentage
	//long_result *= 100;
	// weight the long range result since it has less values in the table
	//long_result *= static_cast<float>(MEDIUM_RANGE_TABLE_SIZE) / LONG_RANGE_TABLE_SIZE;
	//medium_result *= 100;
	// center the result at 50 which is mid-way.  Now the lowest value will be the best choice
	///long_result = abs((long_result-50));
	//medium_result = abs((medium_result-50));
	// use the long result - closer to center of a valid range
	//if (long_result < medium_result){
		// make suse the medium range and long arent pinned on extreme edges
	//	if (dist_from_flash1 == MIN_LONG_RANGE_IR_DISTANCE && 
	//		dist_from_flash2 == MIN_MEDIUM_RANGE_IR_DISTANCE){
			// return a defined value
	//		return MIN_MEDIUM_RANGE_IR_DISTANCE;
	//	}
	//	else if (dist_from_flash1 == MIN_LONG_RANGE_IR_DISTANCE && 
	//		dist_from_flash2 == MAX_MEDIUM_RANGE_IR_DISTANCE){
			// return midway between the two
	//		return (MAX_MEDIUM_RANGE_IR_DISTANCE + MIN_LONG_RANGE_IR_DISTANCE) / 2;
	//	}
	//	else if (dist_from_flash1 == MAX_LONG_RANGE_IR_DISTANCE && 
	//		dist_from_flash2 == MIN_MEDIUM_RANGE_IR_DISTANCE){
			// return midway between the two
	//		return MIN_MEDIUM_RANGE_IR_DISTANCE;
	//	}
	//	return dist_from_flash1;
	//}
	//else{
		// make suse the medium range isnt pinned on an extreme edge
	//	if (dist_from_flash2 == MAX_MEDIUM_RANGE_IR_DISTANCE){
			// use the long range value
	//		return dist_from_flash1;
	//	}
	//	return dist_from_flash2;
	//}
	
	return 0;
}

uint8_t adjustScanPlatform(uint8_t steps, uint8_t update)
{
	//debug.enable();
	static uint16_t current_step_cnt = 0;
	// Only accepts steps from 0 -> 200
	if ( (steps >= 200) && (update == 1) ){
		return current_step_cnt;
	}
	
	// update = 1 means adjust the position
	if (update > 0){
		// move the stepper to the angle requested
		if (current_step_cnt < steps){
			while(current_step_cnt != steps){
				motor_s.onestep(FORWARD, SINGLE);
				current_step_cnt++;
				//debug.mediumRangeIR(current_step_cnt);
				delay(10);
			}
		}
		else if (current_step_cnt > steps){
			while(current_step_cnt != steps){
				motor_s.onestep(BACKWARD, SINGLE);
				current_step_cnt--;
				delay(10);
				//debug.mediumRangeIR(current_step_cnt);
			}
		}
	}
	// just return the angle
	return current_step_cnt;
}

void fineTuneMJ(uint8_t dist, uint16_t angle)
{
	// only move half of the desired angle at a time
	uint16_t offset_angle = 0;
	uint8_t consec_hits = 0;
	int16_t err = 0;
	uint16_t next_step = 0;
	uint16_t ang = angle/2;
	// shimmy shake
	adjustHeading(ang);
	offset_angle = compass.getHeading();
	// look for the appropriate distance
	delay(100);
	err = irDistance_new(MEDIUM_RANGE_IR_PIN);
	err -= dist;
	err = abs(err);
	// find the plaque
	while(err > ROOM_DIFFERENCE_AMOUNT){
		while((err > ROOM_DIFFERENCE_AMOUNT) && (consec_hits > 3)){
			// lock onto the target
			next_step = adjustScanPlatform(0) + 1;
			adjustScanPlatform(next_step, 1);
			// find the new error
			err = irDistance_new(MEDIUM_RANGE_IR_PIN);
			err -= dist;
			err = abs(err);
			delay(100);
			// look for a solid object - not noise
			if (err > ROOM_DIFFERENCE_AMOUNT){
				consec_hits++;
			}
			else{
				consec_hits = 0;
			}
		}
		// prepare for the next shimmy shake
		ang = adjustScanPlatform(0)*18;
		adjustScanPlatform(0,1);
		ang = ang/2;
		ang = ang+offset_angle;
		// shimmy shake
		adjustHeading(ang);
		offset_angle = compass.getHeading();
		delay(100);
		err = irDistance_new(MEDIUM_RANGE_IR_PIN);
		err -= dist;
		err = abs(err);
	}
	// miss the target to the right
	adjustHeading((offset_angle+50));
}
