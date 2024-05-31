#include <stdint.h>

typedef struct {
    uint16_t nchannels;
    uint16_t bits_per_sample;
    uint32_t sample_rate;
    uint32_t datasize;
    int16_t* data;
} wavdata_t;
    
int read_wav(char *wavfile, wavdata_t *);
int write_wav(char *wavfile, wavdata_t *);

typedef struct {
    double r;
    double i;
} complex_t;
    
void dft(int16_t *x, complex_t *X, int N);
