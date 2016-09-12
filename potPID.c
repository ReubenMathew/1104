int Target;
int Error;
int Gain = 0.5;
int Drive;
 

if ( vexRT[Btn5D] == 1 )
{
Target = 600 ;
}
else if ( vexRT[Btn5D] == 1 )
{
Target = 1000 ;
}
else if ( vexRT[Btn5D] == 1 )
{
Target = 1600 ;
}
liftSensor = SensorValue[pot]; 
Error = (liftSensor - Target); 
Drive = ((Gain * Error)+127); 
