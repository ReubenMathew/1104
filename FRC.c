package edu.wpi.first.wpilibj.templates;
import edu.wpi.first.wpilibj.Joystick;
import edu.wpi.first.wpilibj.RobotDrive;
import edu.wpi.first.wpilibj.Victor;
import edu.wpi.first.wpilibj.AnalogChannel;
import edu.wpi.first.wpilibj.Compressor;
import edu.wpi.first.wpilibj.Relay;
import edu.wpi.first.wpilibj.Gyro;
import edu.wpi.first.wpilibj.DoubleSolenoid;
import edu.wpi.first.wpilibj.AnalogPotentiometer;
import edu.wpi.first.wpilibj.smartdashboard.SmartDashboard;
import edu.wpi.first.wpilibj.Timer;
import com.sun.squawk.util.MathUtils;
//import java.lang.System;
import edu.wpi.first.wpilibj.IterativeRobot;

/**
 * The VM is configured to automatically run this class, and to call the
 * functions corresponding to each mode, as described in the IterativeRobot
 * documentation. If you change the name of this class or the package after
 * creating this project, you must also update the manifest file in the resource
 * directory.
 */
public class RobotTemplate extends IterativeRobot {
    //Declaration of all the variables needed to operate the robot
    RobotDrive myDrive;
    Joystick jtkDrive;
    Joystick jtkShooter;
    
    //Potentiometer is currently set in port 1
    //AnalogChannel potentiometer = new AnalogChannel(1);
    AnalogPotentiometer potentiomter = new AnalogPotentiometer(1);
    //Code needs to be added for compressor. I've currently placed it in port 4, which may be incorrect.
    AnalogChannel pTransducer = new AnalogChannel(3);    
    
    //Code needs to be added for compressor. I've currently placed it in port 4, which may be incorrect.
    
    Compressor compC = new Compressor(1,2);
    
    //Motors for driving
    Victor vicLeft = new Victor(1);
    Victor vicLeft2 = new Victor(2);
    Victor vicRight = new Victor(3);
    Victor vicRight2 = new Victor(4);
    //Motor for shooting
    Victor vicShoot = new Victor (5);    
    //Motor to allow tilting
    Victor vicTilt = new Victor (6);
    
    Timer ShootTimer = new Timer();
    int ShootStep;
    //Motor to intake balls
    Relay rIntake = new Relay(1);
    boolean Catch;
    boolean Load;
    boolean Release;
    boolean Compress = false;
    //Relay for compressor
    //Relay rComp = new Relay(2);

    
    //Pneumatic solenoids for fork arms.
    DoubleSolenoid solBottomLift;
    DoubleSolenoid solRightLift;
    DoubleSolenoid solLeftLift;
    
    //Pneumatic solenoids for shooting.
    DoubleSolenoid solShooting;
    DoubleSolenoid solPullBack;
    
    //Timer for various commands
    Timer clock = new Timer();
    
    //Gyroscope for autonomous use.
    //Gyro gyroDrive;
    //double kP = 0.03;
    double a = 0.25;
    double b = 0.35;
    double Y;
    double positionPot;
    double positionJoy;
    double PSI;
    
    public void robotInit() {
       
        //This may need to be fixed if forward/reverse is not correct.
        myDrive = new RobotDrive(vicLeft2,vicLeft,vicRight2,vicRight);
        jtkDrive = new Joystick(1);
        jtkShooter = new Joystick(2);
        solBottomLift = new DoubleSolenoid(1,1,2);
        solRightLift = new DoubleSolenoid(1,3,4);
        solLeftLift = new DoubleSolenoid(1,5,6);
        solShooting = new DoubleSolenoid(1,7,8);
        solPullBack = new DoubleSolenoid(2,1,2);
        compC.stop();
        
        myDrive.setSafetyEnabled(false);
        
        vicLeft.enableDeadbandElimination(true);
        vicLeft2.enableDeadbandElimination(true);
        vicRight.enableDeadbandElimination(true);
        vicRight2.enableDeadbandElimination(true);
        //vicTilt.enableDeadbandElimination(true);
       // vicShoot.enableDeadbandElimination(true);
        //gyroDrive;
        ShootTimer.start();
        ShootStep = 0;
    }
    
    public void autonomousInit() {
        compC.start();
        solPullBack.set(DoubleSolenoid.Value.kForward);
        solShooting.set(DoubleSolenoid.Value.kReverse);        
        //vicLeft.set(0);
        //vicLeft2.set(0);
        //vicRight.set(0);
        //vicRight2.set(0);
        //vicTilt.set(0);
        //vicShoot.set(0);
        solLeftLift.set(DoubleSolenoid.Value.kOff);
        solRightLift.set(DoubleSolenoid.Value.kOff);        
        solBottomLift.set(DoubleSolenoid.Value.kOff); 
        //Timer.delay(5);
        vicLeft.set(0.5);
        vicLeft2.set(0.5);
        vicRight.set(-0.5);
        vicRight2.set(-0.5);
       // Timer.delay(1);
        Timer.delay(2);
        vicLeft.set(0);
        vicLeft2.set(0);
        vicRight.set(0);
        vicRight2.set(0);
        
        
        vicTilt.set(0.35);
        Timer.delay(0.6);
         vicTilt.set(0);
        solRightLift.set(DoubleSolenoid.Value.kForward);
        solLeftLift.set(DoubleSolenoid.Value.kForward);
        //Timer.delay(0.5);
        //solLeftLift.set(DoubleSolenoid.Value.kOff);
        //solRightLift.set(DoubleSolenoid.Value.kOff);
        //Timer.delay(0.5);
        //solShooting.set(DoubleSolenoid.Value.kReverse);
        //solPullBack.set(DoubleSolenoid.Value.kForward);
        //Timer.delay(1.5);
         vicShoot.set(-0.5);
         Timer.delay(0.5);
         vicShoot.set(0);
        Timer.delay(1);
        solShooting.set(DoubleSolenoid.Value.kForward);
        Timer.delay(1);
        solShooting.set(DoubleSolenoid.Value.kOff);
        Timer.delay(1);
        solPullBack.set(DoubleSolenoid.Value.kReverse);
        Timer.delay(1);
        solPullBack.set(DoubleSolenoid.Value.kOff);
        vicShoot.set(0.5);
        Timer.delay(1);
         vicShoot.set(0);            
        solRightLift.set(DoubleSolenoid.Value.kReverse);
         solLeftLift.set(DoubleSolenoid.Value.kReverse);
        Timer.delay(0.5);
         solLeftLift.set(DoubleSolenoid.Value.kOff);
        solRightLift.set(DoubleSolenoid.Value.kOff);       
       
        
        //if(potentiomter.get() > 3.5){
         //   vicTilt.set(0.25);
        //}
        //else{vicTilt.set(0);}
        
        //SmartDashboard.putString("Current Operation", "Setting Load Angle");
          /*  if (potentiomter.get() < 3.39 ) {
                vicTilt.set(-0.35);    
            }
            else if ((potentiomter.get() >= 3.39) && (potentiomter.get() < 3.49 )){
                vicTilt.set(-0.1);
            }    
            else if (potentiomter.get() > 3.61 ){
                vicTilt.set(0.35);
            }
            else if ((potentiomter.get() <= 3.51 ) && (potentiomter.get() > 3.61 )){
                vicTilt.set(0.1);
            }
            else{
                vicTilt.set(0);
            }
        
   */
        
        
        //myDrive.arcadeDrive(1, 1);
       // Timer.delay(2);
   /*     solRightLift.set(DoubleSolenoid.Value.kForward);
        solLeftLift.set(DoubleSolenoid.Value.kForward);
        Timer.delay(0.5);
        solLeftLift.set(DoubleSolenoid.Value.kOff);
        solRightLift.set(DoubleSolenoid.Value.kOff);
        Timer.delay(0.5);
        solShooting.set(DoubleSolenoid.Value.kReverse);
        solPullBack.set(DoubleSolenoid.Value.kForward);
        Timer.delay(1.5);
        vicShoot.set(-0.5);
        Timer.delay(0.5);
        vicShoot.set(0);
        Timer.delay(3);
        solShooting.set(DoubleSolenoid.Value.kForward);
        Timer.delay(1);
        solShooting.set(DoubleSolenoid.Value.kOff);
        Timer.delay(1);
        solPullBack.set(DoubleSolenoid.Value.kReverse);
        Timer.delay(1);
        solPullBack.set(DoubleSolenoid.Value.kOff);
        vicShoot.set(0.5);
        Timer.delay(1);
        vicShoot.set(0);            
        solRightLift.set(DoubleSolenoid.Value.kReverse);
        solLeftLift.set(DoubleSolenoid.Value.kReverse);
        Timer.delay(0.5);
        solLeftLift.set(DoubleSolenoid.Value.kOff);
        solRightLift.set(DoubleSolenoid.Value.kOff);        
        */
        
        
        
    }

    public void autonomousPeriodic() {
        SmartDashboard.putString("Mode:", "Autonomous");
        
        
        /* if (potentiomter.get() < 3.39 ) {
                vicTilt.set(-0.35);    
            }
            else if ((potentiomter.get() >= 3.39) && (potentiomter.get() < 3.49 )){
                vicTilt.set(-0.1);
            }    
            else if (potentiomter.get() > 3.61 ){
                vicTilt.set(0.35);
            }
            else if ((potentiomter.get() <= 3.51 ) && (potentiomter.get() > 3.61 )){
                vicTilt.set(0.1);
            }
            else{
                vicTilt.set(0);
            }
        
        
        vicTilt.set(0);
        
        
        vicTilt.set(0.35);
        Timer.delay(0.6);
        vicTilt.set(0);
        solRightLift.set(DoubleSolenoid.Value.kForward);
        solLeftLift.set(DoubleSolenoid.Value.kForward);
        Timer.delay(0.5);
        solLeftLift.set(DoubleSolenoid.Value.kOff);
        solRightLift.set(DoubleSolenoid.Value.kOff);
        Timer.delay(0.5);
        solShooting.set(DoubleSolenoid.Value.kReverse);
        solPullBack.set(DoubleSolenoid.Value.kForward);
        Timer.delay(1.5);
        vicShoot.set(-0.5);
        Timer.delay(0.5);
        vicShoot.set(0);
        Timer.delay(3);
        solShooting.set(DoubleSolenoid.Value.kForward);
        Timer.delay(1);
        solShooting.set(DoubleSolenoid.Value.kOff);
        Timer.delay(1);
        solPullBack.set(DoubleSolenoid.Value.kReverse);
        Timer.delay(1);
        solPullBack.set(DoubleSolenoid.Value.kOff);
        vicShoot.set(0.5);
        Timer.delay(1);
        vicShoot.set(0);            
        solRightLift.set(DoubleSolenoid.Value.kReverse);
        solLeftLift.set(DoubleSolenoid.Value.kReverse);
        Timer.delay(0.5);
        solLeftLift.set(DoubleSolenoid.Value.kOff);
        solRightLift.set(DoubleSolenoid.Value.kOff);       
       
          
        //if(potentiomter.get() > 3.5){
         //   vicTilt.set(0.25);
        //}
        //else{vicTilt.set(0);}
        
        //myDrive.arcadeDrive(1, 1);
        //Timer.delay(2);
        //solRightLift.set(DoubleSolenoid.Value.kForward);
        //solLeftLift.set(DoubleSolenoid.Value.kForward);
        //Timer.delay(0.5);
        //solLeftLift.set(DoubleSolenoid.Value.kOff);
        //solRightLift.set(DoubleSolenoid.Value.kOff);
        //Timer.delay(0.5);
        //solShooting.set(DoubleSolenoid.Value.kReverse);
        //solPullBack.set(DoubleSolenoid.Value.kForward);
        //Timer.delay(1.5);
        //vicShoot.set(-0.5);
        //Timer.delay(0.5);
        //vicShoot.set(0);
        //Timer.delay(3);
        //solShooting.set(DoubleSolenoid.Value.kForward);
        //Timer.delay(1);
        //solShooting.set(DoubleSolenoid.Value.kOff);
        //Timer.delay(1);
        //solPullBack.set(DoubleSolenoid.Value.kReverse);
        //Timer.delay(1);
        //solPullBack.set(DoubleSolenoid.Value.kOff);
        ///vicShoot.set(0.5);
        //Timer.delay(1);
        //vicShoot.set(0);            
        //solRightLift.set(DoubleSolenoid.Value.kReverse);
        ///solLeftLift.set(DoubleSolenoid.Value.kReverse);
        //Timer.delay(0.5);
        //solLeftLift.set(DoubleSolenoid.Value.kOff);
        //solRightLift.set(DoubleSolenoid.Value.kOff);        
        
        compC.start();
        */
    }

    public void teleopPeriodic() {
        //This may need to be fixed if forward/reverse is not correct.
        double rot;// = -jtkDrive.getX();
        double speed;// = -jtkDrive.getY(); 
        double xSpeed = 11;
        
        speed = (-1) * (( a * MathUtils.pow(jtkDrive.getY(),3.0) ) + (1-a)* jtkDrive.getY());
        rot = (-1) * (( b * MathUtils.pow(jtkDrive.getX(),3.0) ) + (1-b)* jtkDrive.getX());
        SmartDashboard.putString("Mode:", "Teleop"); 
        SmartDashboard.putString("Current Operation", "Driving");
        SmartDashboard.putNumber("Speed:", Math.abs(speed) * 19 );
        SmartDashboard.putNumber("Speed Dial:", Math.abs(speed) * 19);
        //SmartDashboard.putNumber("Pot Angle (degrees):" , potentiometer.getAverageVoltage()*54);
        //SmartDashboard.putNumber("Pot Value (V):" , potentiometer.getAverageVoltage());
        SmartDashboard.putNumber("Pot Angle (degrees):" , potentiomter.get()*54);
        SmartDashboard.putNumber("Pot Value (V):" , potentiomter.get());
        SmartDashboard.putBoolean("Compressor Switch Value :", compC.getPressureSwitchValue());
        SmartDashboard.putNumber("Pressure Value (psi):", pTransducer.getVoltage()*40);
        SmartDashboard.putNumber("Pressure Value Dial:", pTransducer.getVoltage()*40);
        //SmartDashboard.putNumber("Bottom Solenoid:", DoubleSolenoid.getDefaultSolenoidModule());
        //SmartDashboard.putNumber("Bottom Lift",solBottomLift.);
        
        myDrive.arcadeDrive(speed,rot);
        
        SmartDashboard.putString("Current Operation", "Driving");
        
        if (Math.abs(speed)*19 <= xSpeed){
            //myDrive.arcadeDrive(speed,rot);
            if (pTransducer.getAverageVoltage()*40 <= 110){
                compC.start();
            }
            else{
                compC.stop();
            }
        }
        else{
            //myDrive.arcadeDrive(speed,rot);
            compC.stop();
        }
        
        //Manually set the compressor on. You can read gauge from the 
        PSI = pTransducer.getAverageVoltage()*40;
		//if(!jtkDrive.getRawButton(1)){
            if (!Compress && PSI <= 85){
            //compC.start();
                Compress = true;
            }
            else if (Compress && PSI > 92) {
                Compress = false;
            }
            else {
                
            }
       // }
       // else{
           // compC.stop();
       // }
if (!jtkDrive.getRawButton(1) ){
    if(Compress){
        compC.start();
    }
    else{
        compC.stop();
    }  
}
 else{
            compC.stop();
            }
        //For catching balls. Opens all forks to an appropriate amount
        if (jtkDrive.getRawButton(3)){
            Catch = true;
            //myDrive.arcadeDrive(speed,rot);
            SmartDashboard.putString("Current Operation", "Catching balls!");
            solRightLift.set(DoubleSolenoid.Value.kForward);
            solLeftLift.set(DoubleSolenoid.Value.kForward);
            solBottomLift.set(DoubleSolenoid.Value.kReverse); 
           /* Timer.delay(0.5);
            solRightLift.set(DoubleSolenoid.Value.kOff);
            solLeftLift.set(DoubleSolenoid.Value.kOff);
            solBottomLift.set(DoubleSolenoid.Value.kOff);
            Timer.delay(2);
            solRightLift.set(DoubleSolenoid.Value.kForward);
            solLeftLift.set(DoubleSolenoid.Value.kForward);
            solBottomLift.set(DoubleSolenoid.Value.kForward);
            Timer.delay(0.5);
            solRightLift.set(DoubleSolenoid.Value.kOff);
            solLeftLift.set(DoubleSolenoid.Value.kOff);
            solBottomLift.set(DoubleSolenoid.Value.kOff);  
            */
        }
        else{
            if( Catch ){
                Catch = false;
            solRightLift.set(DoubleSolenoid.Value.kReverse);
            solLeftLift.set(DoubleSolenoid.Value.kReverse);
            solBottomLift.set(DoubleSolenoid.Value.kForward);
            }
            //myDrive.arcadeDrive(speed,rot);
                    
        }
        
        //For releasing balls. Open left and bottom forks to an appropriate mount and have the ball fall out
        if (jtkDrive.getRawButton(4)){
            Release = true;
           solBottomLift.set(DoubleSolenoid.Value.kReverse);
           solLeftLift.set(DoubleSolenoid.Value.kForward);
            //Timer.delay(0.5);
           // solLeftLift.set(DoubleSolenoid.Value.kOff);
            //solBottomLift.set(DoubleSolenoid.Value.kOff);
            rIntake.set(Relay.Value.kReverse);
            //Timer.delay(2);

            //rIntake.set(Relay.Value.kOff);

            //Timer.delay(0.5);

            //solLeftLift.set(DoubleSolenoid.Value.kForward);
            //solBottomLift.set(DoubleSolenoid.Value.kForward);
            //Timer.delay(0.5);
            //solLeftLift.set(DoubleSolenoid.Value.kOff);
            //solBottomLift.set(DoubleSolenoid.Value.kOff);            
        }
        else{
            if(Release){
                Release = false;
                rIntake.set(Relay.Value.kOff);          
                solBottomLift.set(DoubleSolenoid.Value.kForward);
                solLeftLift.set(DoubleSolenoid.Value.kReverse);
            }
                
           // myDrive.arcadeDrive(speed,rot);
            //rIntake.set(Relay.Value.kOff);
            //solLeftLift.set(DoubleSolenoid.Value.kOff);
            //solBottomLift.set(DoubleSolenoid.Value.kOff);    
            //Timer.delay(1);
            //solLeftLift.set(DoubleSolenoid.Value.kForward);
            //solBottomLift.set(DoubleSolenoid.Value.kForward);
            //Timer.delay(0.5);
            //solLeftLift.set(DoubleSolenoid.Value.kOff);
            //solBottomLift.set(DoubleSolenoid.Value.kOff);
		}
 
        
       // vicTilt.set(jtkShooter.getRawAxis(2)*0.15);
       //Manual tilting of the shooter. This should be used when aiming for goal, or trying to catch a ball.
       //Max and mins will be added to not go over 90 degrees and below 20 degrees
       // if(jtkShooter.getRawButton(5)){
          //  myDrive.arcadeDrive(speed,rot);

          //  if(potentiomter.get() > 2.7 && potentiomter.get() < 4.00){
                vicTilt.set(jtkShooter.getRawAxis(2)*0.2);
           // }
           // else{
               // vicTilt.set(0);
       //     }
      //  }
      //  else{
         //   myDrive.arcadeDrive(speed,rot);
          //  vicTilt.set(0);
      //  }
        //For Loading. Check position of potentiometer on button press
        //Tilt Shooter to requested loading position, open claws and turn on intake  
        //The values of the voltage will need to be calibrated to our lowest point.
     
        if (jtkShooter.getRawButton(1)){
            myDrive.arcadeDrive(speed,rot);
            SmartDashboard.putString("Current Operation", "Setting Load Angle");
            if (potentiomter.get() < 3.39 ) {
                vicTilt.set(-0.35);    
            }
            else if ((potentiomter.get() >= 3.39) && (potentiomter.get() < 3.49 )){
                vicTilt.set(-0.1);
            }    
            else if (potentiomter.get() > 3.61 ){
                vicTilt.set(0.35);
            }
            else if ((potentiomter.get() <= 3.51 ) && (potentiomter.get() > 3.61 )){
                vicTilt.set(0.1);
            }
            else{
                vicTilt.set(0);
            }
        }
        else{
            //myDrive.arcadeDrive(speed,rot);
            positionPot = potentiomter.get();
            positionJoy = jtkShooter.getRawAxis(2);
            if(positionPot >= 4.05 && positionJoy < 0){
                vicTilt.set(0);
            }
            else if(positionPot <= 2.2 && positionJoy > 0) {
                vicTilt.set(0);
             }
            else if(positionPot >= 3.75 && positionJoy < 0){
                vicTilt.set(positionJoy*0.5);
            }
            else if(positionPot <= 2.5 && positionJoy > 0){
                vicTilt.set(positionJoy*0.5);                
            }
            else{
                vicTilt.set(positionJoy);
            }
            
 /*vicTilt.set((jtkShooter.getRawAxis(2)));
                if (potentiomter.get() <= 2.0){
                    //pwmTilt.set(0);
                    //ds.println(DriverStationLCD.Line.kUser2, 1, "STOP!!");
                    //ds.println(DriverStationLCD.Line.kUser3, 1, "Motor Moving Up. ");
                    //ds.updateLCD();
                    vicTilt.set(-0.5);
                }
                else if (potentiomter.get() >= 4.2){
                    //pwmTilt.set(0);
                    //ds.println(DriverStationLCD.Line.kUser2, 1, "STOP!!");
                    //ds.println(DriverStationLCD.Line.kUser3, 1, "Motor Moving Down.");
                    //ds.updateLCD();
                    vicTilt.set(0.5);
                }
            */
           // else{
                   // pwmTilt.set(0);
           // vicTilt.set(jtkShooter.getRawAxis(2)*0.5);
        }
        
        
        //For loading balls. Must have shooter set first into loading position.
        if (jtkShooter.getRawButton(2)){
            myDrive.arcadeDrive(speed,rot);
            SmartDashboard.putString("Current Operation", "Loading Ball");
            Load = true;
            //solLeftLift.set(DoubleSolenoid.Value.kReverse);
            //Timer.delay(0.5);
            //solLeftLift.set(DoubleSolenoid.Value.kOff);
            //Timer.delay(1);
            solLeftLift.set(DoubleSolenoid.Value.kForward);
            rIntake.set(Relay.Value.kForward);
            //Timer.delay(1.5);
            //rIntake.set(Relay.Value.kOff);
            //timer.delay(1);
            //solLeftLift.set(DoubleSolend.Value.kForward);
            //Timer.delay(0.5);
            //solLeftLift.set(DoubleSolenoid.Value.kOff);
        } 
        else{
            //myDrive.arcadeDrive(speed,rot);
            if (Load) {
            rIntake.set(Relay.Value.kOff);  
            
            solLeftLift.set(DoubleSolenoid.Value.kReverse);
            Load=false;
            }
        }
        
        /*This will be used for shooting. Need to fix this:
        Essentially open the Left and right forks a bit
        Unlock the shooting victor
        Run the Shooting Solenoid
        Pull back using the Catching Solenoid
        Locking the shooting victor
        Close the forks
        */
        if (ShootStep == 0){
                  
            if (jtkShooter.getRawButton(5)) {
                ShootStep ++;
                ShootTimer.reset();
                SmartDashboard.putString("Current Operation", "Shoot!");
                solRightLift.set(DoubleSolenoid.Value.kForward);
                solLeftLift.set(DoubleSolenoid.Value.kForward);
            }
            else{
                vicShoot.set(0);
                //solPullBack.set(DoubleSolenoid.Value.kOff);
                //solShooting.set(DoubleSolenoid.Value.kOff);
               // solRightLift.set(DoubleSolenoid.Value.kOff);
               // solLeftLift.set(DoubleSolenoid.Value.kOff);    
            }
        }
        else if(ShootStep == 1 && ShootTimer.get()> 0.5 ){
            ShootStep ++;
            ShootTimer.reset();
            solLeftLift.set(DoubleSolenoid.Value.kOff);
            solRightLift.set(DoubleSolenoid.Value.kOff);
            
        }
        else if(ShootStep == 2 && ShootTimer.get()> 0.5){
            ShootStep ++;
            ShootTimer.reset();
            solShooting.set(DoubleSolenoid.Value.kReverse);
            solPullBack.set(DoubleSolenoid.Value.kForward);
        }
        else if(ShootStep == 3 && ShootTimer.get()> 1.5 && jtkShooter.getRawButton(6) ){
            ShootStep ++;
            ShootTimer.reset();
            vicShoot.set(-0.5);
        }
        else if(ShootStep == 4 && ShootTimer.get()> 0.5){
            ShootStep ++;
            ShootTimer.reset();
            vicShoot.set(0);
            solShooting.set(DoubleSolenoid.Value.kForward);
        }
        else if(ShootStep == 5 && ShootTimer.get()> 0.5){
            ShootStep ++;
            ShootTimer.reset();
            solShooting.set(DoubleSolenoid.Value.kOff);
            //solShooting.set(DoubleSolenoid.Value.kForward);
        }
        else if(ShootStep == 6 && ShootTimer.get()> 0.5){
            ShootStep ++;
            ShootTimer.reset();
            //solShooting.set(DoubleSolenoid.Value.kOff);
            solPullBack.set(DoubleSolenoid.Value.kReverse);
        }
        else if(ShootStep == 7 && ShootTimer.get()> 2){
            ShootStep ++;
            ShootTimer.reset();
            solPullBack.set(DoubleSolenoid.Value.kOff);
            vicShoot.set(0.5);
            solRightLift.set(DoubleSolenoid.Value.kReverse);
            solLeftLift.set(DoubleSolenoid.Value.kReverse);
        }
        else if(ShootStep == 8 && ShootTimer.get()> 1){
            ShootStep ++;
            ShootTimer.reset();
            vicShoot.set(0);         
            
        }
        else if(ShootStep == 9 && ShootTimer.get()>0.5){
            ShootStep = 0;
            //ShootTimer.reset();
            solLeftLift.set(DoubleSolenoid.Value.kOff);
            solRightLift.set(DoubleSolenoid.Value.kOff);
        }
        
            
 //           myDrive.arcadeDrive(speed,rot);
           // SmartDashboard.putString("Current Operation", "Shoot!");
          /*  solRightLift.set(DoubleSolenoid.Value.kForward);
            solLeftLift.set(DoubleSolenoid.Value.kForward);
            Timer.delay(0.5);
            
            solLeftLift.set(DoubleSolenoid.Value.kOff);
            solRightLift.set(DoubleSolenoid.Value.kOff);
            Timer.delay(0.5);
            solShooting.set(DoubleSolenoid.Value.kReverse);
            solPullBack.set(DoubleSolenoid.Value.kForward);
            Timer.delay(1.5);
            vicShoot.set(-0.5);
            Timer.delay(0.5);
            vicShoot.set(0);
            //Timer.delay(3);
            solShooting.set(DoubleSolenoid.Value.kForward);
            Timer.delay(1);
            solShooting.set(DoubleSolenoid.Value.kOff);
            //Timer.delay(1);
            solPullBack.set(DoubleSolenoid.Value.kReverse);
            Timer.delay(1);
            solPullBack.set(DoubleSolenoid.Value.kOff);
            vicShoot.set(0.5);
            Timer.delay(1);
            vicShoot.set(0);            
            solRightLift.set(DoubleSolenoid.Value.kReverse);
            solLeftLift.set(DoubleSolenoid.Value.kReverse);
            Timer.delay(0.5);
            solLeftLift.set(DoubleSolenoid.Value.kOff);
            solRightLift.set(DoubleSolenoid.Value.kOff);
        }
        else{
//            myDrive.arcadeDrive(speed,rot);
            vicShoot.set(0);
            solPullBack.set(DoubleSolenoid.Value.kOff);
            solShooting.set(DoubleSolenoid.Value.kOff);
            solRightLift.set(DoubleSolenoid.Value.kOff);
            solLeftLift.set(DoubleSolenoid.Value.kOff);            
        }
            */
            
/*        if(jtkShooter.getRawButton(8)){
            shootCommand.trigger();
        }
        else{
            vicShoot.set(0);
            solPullBack.set(DoubleSolenoid.Value.kOff);
            solShooting.set(DoubleSolenoid.Value.kOff);
            solRightLift.set(DoubleSolenoid.Value.kOff);
            solLeftLift.set(DoubleSolenoid.Value.kOff);                  
        }*/
    }
    
    public void testPeriodic() {
    solLeftLift.set(DoubleSolenoid.Value.kForward);
    }
   /* private final ThreadedTriggerCommand shootCommand = new ThreadedTriggerCommand() {
        public void doCommand() {
            SmartDashboard.putString("Current Operation", "Shoot!");
            solRightLift.set(DoubleSolenoid.Value.kForward);
            solLeftLift.set(DoubleSolenoid.Value.kForward);
            Timer.delay(0.5);
            solLeftLift.set(DoubleSolenoid.Value.kOff);
            solRightLift.set(DoubleSolenoid.Value.kOff);
            Timer.delay(0.5);
            solShooting.set(DoubleSolenoid.Value.kReverse);
            solPullBack.set(DoubleSolenoid.Value.kForward);
            Timer.delay(1.5);
            vicShoot.set(-0.5);
            Timer.delay(0.5);
            vicShoot.set(0);
            //Timer.delay(3);
            solShooting.set(DoubleSolenoid.Value.kForward);
            Timer.delay(1);
            solShooting.set(DoubleSolenoid.Value.kOff);
            //Timer.delay(1);
            solPullBack.set(DoubleSolenoid.Value.kReverse);
            Timer.delay(1);
            solPullBack.set(DoubleSolenoid.Value.kOff);
            vicShoot.set(0.5);
            Timer.delay(1);
            vicShoot.set(0);            
            solRightLift.set(DoubleSolenoid.Value.kReverse);
            solLeftLift.set(DoubleSolenoid.Value.kReverse);
            Timer.delay(0.5);
            solLeftLift.set(DoubleSolenoid.Value.kOff);
            solRightLift.set(DoubleSolenoid.Value.kOff);
        }
    */
    

    
}
