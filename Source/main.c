//Working Tutorial


//#include "asctecCommIntf.h"
//
//#include <unistd.h> // UNIX standard function definitions
//#include <fcntl.h>  // File control definitions
//#include <termios.h> // POSIX terminal control definitions
//#include <pthread.h>
////#include "C:\cygwin\usr\include\pthread.h"
//
//int fd;
//
//void transmit(void* byte, unsigned short cnt);
//void versions(struct ACI_INFO);
//void *aciThread(void* param);
//
//int main(int argc, char *argv[])
//{
//
// printf("Starting Program...\n");
// pthread_t p_acithread;
//
// fd = open("\\\\.\\COM40", O_RDWR | O_NOCTTY | O_NDELAY | O_NONBLOCK);
// printf("Port status: %i \n", fd);
// struct termios port_settings; // structure to store the port settings in
//
// cfsetispeed(&port_settings, B57600);    // set baud rates
// port_settings.c_cflag = B57600 | CS8 | CREAD | CLOCAL;
// port_settings.c_iflag = IGNPAR;
// port_settings.c_oflag = 0;
// port_settings.c_lflag = 0;
// tcsetattr(fd, TCSANOW, &port_settings); // apply the settings to the port
//
//
// aciInit();
// aciSetSendDataCallback(&transmit);
// aciInfoPacketReceivedCallback(&versions);
// aciSetEngineRate(100, 10);
//
// pthread_create(&p_acithread, NULL, &aciThread, NULL);
// aciCheckVerConf();
// pthread_join(p_acithread, NULL);
// printf("Threaded Joined.");
// //close(fd); //MDP
// return 0;
//}
//
//
//void transmit(void* byte, unsigned short cnt)
//{
//	printf("Transmitting: %d bytes\n", cnt);
// unsigned char *tbyte = (unsigned char *)byte;
//
// int i = 0;
// for (i = 0; i < cnt; i++)
// {
//	printf("Byte: %x\n",tbyte[i]);
//	int result = write(fd, &tbyte[i], 1);
//	//printf("Result = %d\n", result);
// }
// //printf("\nEND\n");
//}
//
//
//void *aciThread(void* param)
//{
// printf("Thread Function...\n");
// int result = 0;
// unsigned char data = 0;
// while(1)
// {
//  //printf("Thread about to read...\n");
//  result = read(fd, &data, 1);
//  //printf("%d\n", result);
//  while (result > 0)
//  {
//   aciReceiveHandler(data);
//   result = read(fd, &data, 1);
//  }
//  aciEngine();
//  usleep(10000);
// }
// return NULL;
//}
//
//void versions(struct ACI_INFO aciInfo)
//{
// printf("******************** Versions *******************\n");
// printf("* Type\t\t\tDevice\t\tRemote\t*\n");
// printf("* Major version\t\t%d\t=\t\%d\t*\n",aciInfo.verMajor,ACI_VER_MAJOR);
// printf("* Minor version\t\t%d\t=\t\%d\t*\n",aciInfo.verMinor,ACI_VER_MINOR);
// printf("* MAX_DESC_LENGTH\t%d\t=\t\%d\t*\n",aciInfo.maxDescLength,MAX_DESC_LENGTH);
// printf("* MAX_NAME_LENGTH\t%d\t=\t\%d\t*\n",aciInfo.maxNameLength,MAX_NAME_LENGTH);
// printf("* MAX_UNIT_LENGTH\t%d\t=\t\%d\t*\n",aciInfo.maxUnitLength,MAX_UNIT_LENGTH);
// printf("* MAX_VAR_PACKETS\t%d\t=\t\%d\t*\n",aciInfo.maxVarPackets,MAX_VAR_PACKETS);
// printf("*************************************************\n");
// fflush(stdout);
//}

//Tutorial #2 - Receive Commands

//#include "asctecCommIntf.h"
//
//#include <unistd.h> // UNIX standard function definitions
//#include <fcntl.h>  // File control definitions
//#include <termios.h> // POSIX terminal control definitionss
//#include <pthread.h>
//
//int fd;
//
//int32_t angle_pitch;
//int32_t angle_roll;
//int32_t angle_yaw;
//
//unsigned char var_getted;
//
//void transmit(void* byte, unsigned short cnt);
//void varListUpdateFinished(void);
//void *aciThread(void);
//
//int main(int argc, char *argv[]) {
//
// var_getted=0;
// angle_pitch = 0;
// angle_roll = 0;
// angle_yaw = 0;
// pthread_t p_acithread;
//
// fd = open("\\\\.\\COM40", O_RDWR | O_NOCTTY | O_NDELAY | O_NONBLOCK);
// struct termios port_settings; // structure to store the port settings in
//
// cfsetispeed(&port_settings, B57600);    // set baud rates
// port_settings.c_cflag = B57600 | CS8 | CREAD | CLOCAL;
// port_settings.c_iflag = IGNPAR;
// port_settings.c_oflag = 0;
// port_settings.c_lflag = 0;
// tcsetattr(fd, TCSANOW, &port_settings); // apply the settings to the port
//
//
// aciInit();
// aciSetSendDataCallback(&transmit);
// aciSetVarListUpdateFinishedCallback(&varListUpdateFinished);
// aciSetEngineRate(100, 10);
//
// pthread_create( &p_acithread, NULL, aciThread, NULL);
// aciGetDeviceVariablesList();
// pthread_join( p_acithread, NULL);
//}
//
//void transmit(void* byte, unsigned short cnt) {
//
// unsigned char *tbyte = (unsigned char *)byte;
// for (int i = 0; i < cnt; i++) {
//  write(fd, &tbyte[i], 1);
// }
//}
//
//void *aciThread(void)
//{
// int timecounter=0;
// int result = 0;
// unsigned char data = 0;
// while(1)
// {
//  timecounter++;
//  result = read(fd, &data, 1);
//  while (result > 0) {
//   aciReceiveHandler(data);
//   result = read(fd, &data, 1);
//  }
//  if(timecounter>100) {
//   if(var_getted) {
//    printf("Angles before Synchronizing: %f\t%f\t%f\n", (double)(angle_pitch)/1000, (double)(angle_roll)/1000 , (double)(angle_yaw)/1000);
//    aciSynchronizeVars();
//    printf("Angles after Synchronizing: %f\t%f\t%f\n---------\n", (double)(angle_pitch)/1000, (double)(angle_roll)/1000 , (double)(angle_yaw)/1000);
//    fflush(stdout);
//   }
//   timecounter=0;
//  }
//  aciEngine();
//  usleep(10000);
// }
// return NULL;
//}
//
//void varListUpdateFinished(void) {
// printf("variables updated\n");
// aciAddContentToVarPacket(0,0x0300,&angle_pitch);
// aciAddContentToVarPacket(0,0x0301,&angle_roll);
// aciAddContentToVarPacket(0,0x0302,&angle_yaw);
// aciSetVarPacketTransmissionRate(0,10);
// aciVarPacketUpdateTransmissionRates();
// aciSendVariablePacketConfiguration(0);
// var_getted=1;
//}



// Tutorial #3 - Send Commands

#include "asctecCommIntf.h"

#include <unistd.h> // UNIX standard function definitions
#include <fcntl.h>  // File control definitions
#include <termios.h> // POSIX terminal control definitions
#include <pthread.h>
#include <time.h>

int fd;

unsigned char ctrl_mode = 0;
unsigned char ctrl_enabled = 0;
unsigned char disable_motor_onoff_by_stick = 0;

unsigned char motor1=0;
unsigned char motor2=0;
unsigned char motor3=0;
unsigned char motor4=0;

unsigned char cmd_ready = 0;
unsigned char motor_start=1;

void transmit(void* byte, unsigned short cnt);
void varListUpdateFinished();
void cmdListUpdateFinished();
void paramListUpdateFinished();
void *aciThread(void*);
void startStopMotor(int);

int main(int argc, char *argv[])
{

 pthread_t p_acithread;

 fd = open("\\\\.\\COM40", O_RDWR | O_NOCTTY | O_NDELAY | O_NONBLOCK);
 struct termios port_settings; // structure to store the port settings in

 cfsetispeed(&port_settings, B57600); // set baud rates
 port_settings.c_cflag = B57600 | CS8 | CREAD | CLOCAL;
 port_settings.c_iflag = IGNPAR;
 port_settings.c_oflag = 0;
 port_settings.c_lflag = 0;
 tcsetattr(fd, TCSANOW, &port_settings); // apply the settings to the port

 aciInit();
 aciSetSendDataCallback(&transmit);
 aciSetVarListUpdateFinishedCallback(&varListUpdateFinished);
 aciSetCmdListUpdateFinishedCallback(&cmdListUpdateFinished);
 aciSetParamListUpdateFinishedCallback(&paramListUpdateFinished);
 aciSetEngineRate(100, 10);

 pthread_create(&p_acithread, NULL, aciThread, NULL);
 aciGetDeviceCommandsList();
 printf("Waiting for command list...\n");
 while(!cmd_ready) usleep(1000);
 while(motor_start) {

  printf("Start Motor number (0 for quit): ");
  scanf("%i", &motor_start);
  startStopMotor(motor_start);

 }
 //pthread_join(p_acithread, NULL);

}

void startStopMotor(int motor)
{
printf("Motor %d selected\n", motor); //MDP
 switch(motor)
 {
 case 1:
  motor1 = (motor1>0)? 0 : 10;
  printf("Motor value: %d\n", motor1); //MDP
  break;
 case 2:
  motor2 = (motor2>0)? 0 : 10;
  printf("Motor value: %d\n", motor2); //MDP
  break;
 case 3:
  motor3 = (motor3>0)? 0 : 10;
  printf("Motor value: %d\n", motor3); //MDP
  break;
 case 4:
  motor4 = (motor4>0)? 0 : 10;
  printf("Motor value: %d\n", motor4); //MDP
  break;
 }
 aciUpdateCmdPacket(0);
}

void transmit(void* byte, unsigned short cnt) {

 unsigned char *tbyte = (unsigned char *) byte;
 int i = 0;
 for (i = 0; i < cnt; i++)
 {
  //printf("Byte: %x\n",tbyte[i]); //MDP
  write(fd, &tbyte[i], 1);
 }
}

void *aciThread(void*p) {
 int result = 0;
 int timecounter = 0;
 unsigned char data = 0;

 while (1) {
  result = read(fd, &data, 1);
  while (result > 0) {
   aciReceiveHandler(data);
   result = read(fd, &data, 1);
  }
  aciEngine();
  usleep(10000);
 }
 return NULL;
}

void varListUpdateFinished() {

}

void cmdListUpdateFinished() {
 printf("command list getted!\n");
 aciAddContentToCmdPacket(0, 0x0500, &motor1);
 aciAddContentToCmdPacket(0, 0x0501, &motor2);
 aciAddContentToCmdPacket(0, 0x0502, &motor3);
 aciAddContentToCmdPacket(0, 0x0503, &motor4);
 aciAddContentToCmdPacket(1, 0x0600, &ctrl_mode);
 aciAddContentToCmdPacket(1, 0x0601, &ctrl_enabled);
 aciAddContentToCmdPacket(1, 0x0602, &disable_motor_onoff_by_stick);
 aciSendCommandPacketConfiguration(0, 0);
 aciSendCommandPacketConfiguration(1, 1);
 motor1 = 0;
 motor2 = 0;
 motor3 = 0;
 motor4 = 0;
 ctrl_mode=0;
 ctrl_enabled=1;
 disable_motor_onoff_by_stick=1;
 aciUpdateCmdPacket(0);
 aciUpdateCmdPacket(1);
 cmd_ready=1;
}

void paramListUpdateFinished()
{

}
