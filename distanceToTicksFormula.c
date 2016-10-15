const int WHEEL_CIRCUMFERENCE = 10.21;

int numOfRevolutions;
void distanceAuto(int distance, int power){

distance = 10.21 * numOfRevolutions;
numOfRevolutions = distance/WHEEL_CIRCUMFERENCE;
int ticks = numOfRevolutions*90;

while((SensorValue[leftEncoder]<ticks)||(SensorValue[rightEncoder]<ticks))
{

motor[leftDrive] = power;
motor[rightDrive] = power;

}
}
