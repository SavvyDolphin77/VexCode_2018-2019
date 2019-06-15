vex::brain Brain;
vex::controller Controller1 = vex::controller();
vex::motor FrontLeftMotor = vex::motor(vex::PORT9, vex::gearSetting::ratio18_1, false);
vex::motor FrontRightMotor = vex::motor(vex::PORT2, vex::gearSetting::ratio18_1, true);
vex::motor BackLeftMotor = vex::motor(vex::PORT10, vex::gearSetting::ratio18_1, false);
vex::motor BackRightMotor = vex::motor(vex::PORT1, vex::gearSetting::ratio18_1, true);
vex::motor Lift1 = vex::motor(vex::PORT6, vex::gearSetting::ratio18_1, false);
vex::motor Lift2 = vex::motor(vex::PORT5, vex::gearSetting::ratio18_1, false);
vex::motor RotatorMotor = vex::motor(vex::PORT15, vex::gearSetting::ratio18_1, false);
