#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

#include "wav.h"
#define MAXSAMPLES 1000000
int main(int argc, char **argv)
{
    if (argc != 4) {
        printf("%s datafile wavfile scale\n", argv[0]);
        exit(-1);
    }

    char* datafile = argv[1];
    char* wavfile = argv[2];
    double scale = atof(argv[3]);
    
    // allocate space for 1000000 int16_t's
	int16_t sounddata[MAXSAMPLES];

    // read the data from the datafile into sounddata 
	int fd = open(datafile, O_RDONLY);
	if (fd < 0) {
        perror("error opening file");
        exit(-1);
    }
	
	int bytes_read = read(fd, sounddata, MAXSAMPLES*sizeof(int16_t));
	if (bytes_read < 0) {
        perror("error reading file");
        exit(-1);
	}
	
	int numsamples = bytes_read / 2;
	
	
    // iterate through the array and scale the values
	for (int i=0;i<numsamples;i++) {
		float scaled_value = sounddata[i] * scale;
		if (scaled_value > 32767) { sounddata[i] = 32767; }
		else if (scaled_value < -32768) { sounddata[i] = -32768; }
		else { sounddata[i] = (int16_t)scaled_value; }
	}
	
    wavdata_t wav;
    // fill in the wav struct
    wav.nchannels = 1;
    wav.bits_per_sample = 16;
    wav.sample_rate = 22050;
    wav.datasize = bytes_read;
    wav.data = sounddata;
    
    write_wav(argv[2], &wav);
}
