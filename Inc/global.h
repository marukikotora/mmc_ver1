#ifndef __GLOBAL_H
#define __GLOBAL_H
#ifdef __cplusplus
 extern "C" {
#endif

/***Includes***********************************************************************/
#include "stdint.h"
#include <stdio.h>
#include <string.h>

/***define************************************************************************/

//0,1
#define true  1
#define false 0

#define ON 1
#define OFF 0


//motor 003SR
#define KT  1.98f//toluku[mNm/A]
#define KE  0.207f//return vatt[mV/min^-1]
#define Resistance 1.07f//[S^-1]
#define TORQUE 0.2


//encoder
#define ENC_CUL_ROT 1024.0f//512 * 2


//mouse
#define WEIGHT 100.0f //[g]
#define TIRE_RADIUS 12.5f  //[mm]
#define INERTIA     23.0f 
#define TREAD 73.0f  //[mm]
#define GEAR_RATE 5.25f

//calc
#define dt 0.001f

//straight
#define ACCEL 4000 //[mm/s^2]
#define MAX_VELOCITY 300 //[mm/s]

//yawrate
#define Y_ACCEL 2000 //[degree/s^2]
#define Y_MAX_VELOCITY 380//[degree/s]


/***typedef**************************************************************************/

//flag
typedef struct{
  uint8_t gyro_calc;
  uint8_t straight;
  uint8_t yawrate;
  uint8_t straight_zero;
  uint8_t yawrate_zero;
  uint8_t ir_led;
  uint8_t accel;
}flag_t;
extern volatile flag_t flag;


//gyro
typedef struct{
  short offset_cnt;
  int32_t offset;
  float befor;
  float degree;
  float velocity;
  float accel;
}gyro_t;
extern gyro_t gyro;


//encoder
typedef struct{
  int left;
  int right;
  float rpm_l;
  float rpm_r;
  float velocity_l;
  float velocity_r;
  float velocity_c;
  float distance_l;
  float distance_r;
  float old_l;
  float old_r;
}enc_t;
extern enc_t enc;


//sensor
typedef struct{
  uint16_t adc_on[4];
  uint16_t adc_off[4];
  uint16_t adc[4];
  uint8_t wall[4];
  uint16_t count[4];
}sensor_t;
extern sensor_t sensor;

typedef struct{
  float target_velocity[2000];
  float target_y_velocity[2000];
  float velocity_c[2000];
  float y_velocity[2000];
  float p[2000];
  float i[2000];
  float d[2000];
  int16_t pwm[2000];
}loger_t;
extern loger_t loger;

//batt
extern uint16_t batt_analog;
extern float batt_Vcc;

//motor parameters
typedef struct{
  int16_t pwm_l;
  int16_t pwm_r;
  int16_t accel_l;
  int16_t accel_r;
}motor_t;
extern motor_t motor;

//calc
typedef struct{
  float distance;
  int16_t velocity;
  int16_t accel;

  float yawrate_degree;
  int16_t yawrate_velocity;
  int16_t yawrate_accel;
}calc_t;
extern calc_t calc;

extern float s_accel;


//mouse position
typedef struct{
  uint8_t x;
  uint8_t y;
  uint8_t dir;
  float angle;
  float distance;
}position_t;
extern position_t position;


//count
extern uint16_t count_tim5;
extern uint16_t straight_cnt;
extern uint16_t yawrate_cnt;

//straight
extern uint16_t accel_T;
extern uint16_t constant_T;
extern uint16_t decrease_T;

//yawrate
extern uint16_t y_accel_T;
extern uint16_t y_constant_T;
extern uint16_t y_decrease_T;


#ifdef __cplusplus
}
#endif
#endif