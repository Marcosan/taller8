#include <stdio.h>    // Standard input/output definitions
#include <stdlib.h>
//#include <t_temping.h>   // t_temping function definitions
#include <unistd.h>   // para usleep()
#include <getopt.h>
#include <math.h>

#include "arduino-serial-lib.h"

float calculateSD(float data[]);

void error(char* msg)
{
    fprintf(stderr, "%s\n",msg);
    exit(EXIT_FAILURE);
}

int main(int argc, char *argv[])
{
	int fd = -1;
	int baudrate = 9600;  // default
    char t_temp = 't';
    char t_h = 'h';
    short buff;
    int reader;
    size_t nbytes; 

	fd = serialport_init("/dev/ttyACM0", baudrate);

	if( fd==-1 )
	{
		error("couldn't open port");
		return -1;
	}

    nbytes = sizeof(t_temp);
    
    
    while(1){
        write(fd, &t_temp, nbytes);
        usleep(50000);
        reader = read(fd, &buff, nbytes);
        printf("%u\n", buff);
        
        usleep(500000);

        write(fd, &t_h, nbytes);
        usleep(50000);
        reader = read(fd, &buff, nbytes); 
        
        printf("%u\n", buff);
	}
	close( fd );
	return 0;	
}

/* Ejemplo para calcular desviacion estandar y media */
float calculateSD(float data[])
{
    float sum = 0.0, mean, standardDeviation = 0.0;

    int i;

    for(i = 0; i < 10; ++i)
    {
        sum += data[i];
    }

    mean = sum/10;

    for(i = 0; i < 10; ++i)
        standardDeviation += pow(data[i] - mean, 2);

    return sqrt(standardDeviation / 10);
}

