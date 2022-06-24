/*
 * pivot_program.h
 *
 *  Created on: Jun 24, 2022
 *      Author: Ahmed
 */

#ifndef MAIN_PIVOT_PROGRAM_H_
#define MAIN_PIVOT_PROGRAM_H_
#define TOTAL_PULSES 2015
void initial_system_state(void);
void normal_state(uint8_t);
uint8_t manager_auth(void);
void direction(uint8_t); //O-to open;C- to close
void brake(uint8_t); //1- to brake;0- to release brake
void move_actuator(uint8_t); // L- to lock; U-to unlock;S-to stop
uint8_t actuator_state(void); // returns high when locked
uint8_t door_state(void); // returns high when closed
uint8_t select_system(void); //returns 1-normal operation;return 2-wind sensor master
uint8_t person_present(uint8_t); //input-F-to check front sensor;B-to check back sensor --> returns 1-person present;0-no person
uint8_t wind_sensor_state(void); //returns 1-wind speed high;returns 2-wind speed low
void emergency_close(void);
void remained_open(void);
//uint8_t countstates(uint8_t[]);
void move_motor(uint8_t, uint8_t);

#endif /* MAIN_PIVOT_PROGRAM_H_ */
