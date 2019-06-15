/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       Conner Harbaugh                                           */
/*    Created:      2018-2019                                                 */
/*    Description:  V5 competition code                                       */
/*                                                                            */
/*----------------------------------------------------------------------------*/

#include "vex.h"
#include "robot-config.h"

// declares all the functions for autonomous and other stuff
//declaring functions with variable types for future use in code
void driving_forward (int, vex::rotationUnits);
void driving_backward (int, vex::rotationUnits);
void driving_right_t (int, vex::rotationUnits);
void driving_left_t (int, vex::rotationUnits);
void sideways_Move_R (int, vex::rotationUnits);
void sideways_Move_L (int, vex::rotationUnits);

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*        Description: Competition template for VCS VEX V5                   */
/*                                                                           */
/*---------------------------------------------------------------------------*/

//Creates a competition object that allows access to Competition methods.
vex::competition    Competition;

/*---------------------------------------------------------------------------*/
/*                          Pre-Autonomous Functions                         */
/*                                                                           */
/*  You may want to perform some actions before the competition starts.      */
/*  Do them in the following function.  You must return from this function   */
/*  or the autonomous and usercontrol tasks will not be started.  This       */
/*  function is only called once after the cortex has been powered on and    */
/*  not every time that the robot is disabled.                               */
/*---------------------------------------------------------------------------*/

void pre_auton( void ) {
  // All activities that occur before the competition starts
  // Example: clearing encoders, setting servo positions, ...
  
}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              Autonomous Task                              */
/*                                                                           */
/*  This task is used to control your robot during the autonomous phase of   */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/

void autonomous( void ) {
  // ..........................................................................
  // Autonomous Code is here for the autonomous part of the compeition
  // ..........................................................................
  using namespace vex;
  driving_forward (-21, rotationUnits::rev);
  driving_forward (21, rotationUnits::rev);
    
}

/*----------------------------------------------------------------------------*/
/*                                                                            */
/*                              User Control Task                             */
/*                                                                            */
/*  This task is used to control your robot during the user control phase of  */
/*  a VEX Competition.                                                        */
/*                                                                            */
/*  You must modify the code to add your own robot specific commands here.    */
/*----------------------------------------------------------------------------*/

//saves typing
using namespace vex;

void usercontrol( void ) {
  //resets motor units to allow it to run right
  RotatorMotor.resetRotation();
  
  // User control code is here, inside the while loop
  while (1 == 1){
    // This is the main execution loop for the user control program.
    
    // Each time through the loop your program should update motor + servo 
    // values based on feedback from the joysticks.
    // Motor names corresponds to the location where they are. 
    
    // Commands for moving the bot  
    FrontRightMotor.spin(directionType::fwd, -(Controller1.Axis3.value()), vex::velocityUnits::pct);    
    BackRightMotor.spin(directionType::fwd, -(Controller1.Axis3.value()), vex::velocityUnits::pct);
    FrontLeftMotor.spin(directionType::fwd, -(Controller1.Axis2.value()), vex::velocityUnits::pct);    
    BackLeftMotor.spin(directionType::fwd, -(Controller1.Axis2.value()), vex::velocityUnits::pct);
    
    //checks to see if button press to lift the lift
    if ((Controller1.ButtonR1.pressing()) == true) {
        Lift2.spin(directionType::fwd, 77, velocityUnits::pct);
        Lift1.spin(directionType::fwd, -77, velocityUnits::pct);
    }

    // allows for the lift to go down at a coast speed after being lifted up and letting go of button
    if(((Controller1.ButtonR1.pressing()) == false) && ((Controller1.ButtonR2.pressing()) == false)) {
        Lift2.stop(vex::brakeType::brake);
        Lift1.stop(vex::brakeType::brake);
    }
    
    //rotates the motor one way
    if ((Controller1.ButtonL2.pressing()) == true) {
        RotatorMotor.rotateFor(180,rotationUnits::deg,77,velocityUnits::pct);
    }
    //rotates motor the other way
     else if((Controller1.ButtonL1.pressing()) == true) {
        RotatorMotor.rotateFor(-180,rotationUnits::deg,77,velocityUnits::pct);
    }
      else {
          RotatorMotor.stop(brakeType::hold);
      }
    //stops the rotation of the motor

    }
    //lifts the lift down
    if ((Controller1.ButtonR2.pressing()) == true) {
         Lift2.spin(directionType::fwd, -42, velocityUnits::pct);
         Lift1.spin(directionType::fwd, 42, velocityUnits::pct);
    }
    //strafing command number 1
    if ((Controller1.ButtonLeft.pressing()) == true) {
        FrontRightMotor.spin(directionType::rev, 100, vex::velocityUnits::pct);    
        BackRightMotor.spin(directionType::fwd, 100, vex::velocityUnits::pct);
        FrontLeftMotor.spin(directionType::fwd, 100, vex::velocityUnits::pct);    
        BackLeftMotor.spin(directionType::rev, 100, velocityUnits::pct);
    }
    //strafing command number 2
      if ((Controller1.ButtonRight.pressing()) == true) {
        FrontRightMotor.spin(directionType::fwd, 100, vex::velocityUnits::pct);    
        BackRightMotor.spin(directionType::rev, 100, vex::velocityUnits::pct);
        FrontLeftMotor.spin(directionType::rev, 100, vex::velocityUnits::pct);    
        BackLeftMotor.spin(directionType::fwd, 100, velocityUnits::pct);
    }
    vex::task::sleep(20); //Sleep the task for a short amount of time to prevent wasted resources. 
  }

//
// Main will set up the competition functions and callbacks.
//
int main() {
    
    //Run the pre-autonomous function. 
    pre_auton();
    
    //Set up callbacks for autonomous and driver control periods.
    Competition.autonomous( autonomous );
    
    //begin free control of the bot for comepetition
    Competition.drivercontrol( usercontrol );

    //Prevent main from exiting with an infinite loop.                        
    while(1) {
      vex::task::sleep(100);//Sleep the task for a short amount of time to prevent wasted resources.
    }        
}

//below is all the functions that will be used in the int main section
//command for autonomous part driving forward
void driving_forward (int count, vex::rotationUnits rotations) {
    FrontLeftMotor.startRotateFor(count, rotations);
    BackLeftMotor.startRotateFor(count, rotations);
    FrontRightMotor.startRotateFor(count, rotations); 
    BackRightMotor.rotateFor(count, rotations);
}

//command for driving backwards for autonomous part
void driving_backward (int count, vex::rotationUnits rotations) {
    FrontLeftMotor.startRotateFor((-1 * count), rotations);
    BackLeftMotor.startRotateFor((-1 * count), rotations);
    FrontRightMotor.startRotateFor((-1 *  count), rotations); 
    BackRightMotor.rotateFor((-1 *  count), rotations);
}

//function for turning left
void driving_left_t (int count, vex::rotationUnits rotations) {
    FrontLeftMotor.startRotateFor((-1 * count), rotations);
    BackLeftMotor.startRotateFor((-1 * count), rotations);
    FrontRightMotor.startRotateFor(count, rotations); 
    BackRightMotor.rotateFor(count, rotations);
}

//function for turning right
void driving_right_t (int count, vex::rotationUnits rotations) {
    FrontLeftMotor.startRotateFor(count, rotations);
  //  BackLeftMotor.startRotateFor(count), rotations); 
    FrontRightMotor.startRotateFor((-1 *  count), rotations); 
    BackRightMotor.rotateFor((-1 *  count), rotations);
}

//function for Sideways movement right
void sideways_Move_R (int count, vex::rotationUnits rotations) {
    FrontLeftMotor.startRotateFor(count, rotations);
    BackLeftMotor.startRotateFor((-1 * count), rotations);
    FrontRightMotor.startRotateFor((-1 *  count), rotations); 
    BackRightMotor.rotateFor(count, rotations);
}

//function for sideways movement left
void sideways_Move_L (int count, vex::rotationUnits rotations) {
    FrontLeftMotor.startRotateFor((-1 * count), rotations);
    BackLeftMotor.startRotateFor(count, rotations);
    FrontRightMotor.startRotateFor(count, rotations); 
    BackRightMotor.rotateFor((-1 *  count), rotations);
}
