#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <math.h>
#include "wav.h"

int write_wav(char *wavfile, wavdata_t *wav)
{
    int fd = open(wavfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd == -1) {
        printf("Could not open file %s\n", wavfile);
        return -1;
    }

    write(fd, "RIFF", 4);
    uint32_t filesize = wav->datasize + 36;
    uint8_t data[20];
    data[0] = filesize & 0xff;
    data[1] = (filesize>>8) & 0xff;
    data[2] = (filesize>>16) & 0xff;
    data[3] = (filesize>>24) & 0xff;
    write(fd, data, 4);
    write(fd, "WAVEfmt ", 8);

    data[0] = 16;
    data[1] = 0;
    data[2] = 0;
    data[3] = 0;
    data[4] = 1;
    data[5] = 0;
    data[6] = wav->nchannels & 0xff;
    data[7] = wav->nchannels >> 8;
    data[8] = wav->sample_rate & 0xff;
    data[9] = (wav->sample_rate>>8) & 0xff;
    data[10] = (wav->sample_rate>>16) & 0xff;
    data[11] = (wav->sample_rate>>24) & 0xff;
    uint32_t bytes_per_second =
        wav->sample_rate * wav->nchannels * wav->bits_per_sample/8;
    data[12] = bytes_per_second & 0xff;
    data[13] = (bytes_per_second>>8) & 0xff;
    data[14] = (bytes_per_second>>16) & 0xff;
    data[15] = (bytes_per_second>>24) & 0xff;
    uint16_t bytes_per_sample = wav->nchannels * wav->bits_per_sample/8;
    data[16] = bytes_per_sample & 0xff;
    data[17] = (bytes_per_sample>>8) & 0xff;
    data[18] = wav->bits_per_sample & 0xff;
    data[19] = wav->bits_per_sample >> 8;
    write(fd, data, 20);

    write(fd, "data", 4);
    data[0] = wav->datasize & 0xff;
    data[1] = (wav->datasize>>8) & 0xff;
    data[2] = (wav->datasize>>16) & 0xff;
    data[3] = (wav->datasize>>24) & 0xff;
    write(fd, data, 4);

    write(fd, wav->data, wav->datasize);

    close(fd);

    return 0;
}






    
