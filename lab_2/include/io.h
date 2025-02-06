#ifndef IO_H
#define IO_H

int read_csv(const char *filename, float *data, char timestamps[MAX_SAMPLES][20], int *num_samples);
int write_csv(const char *filename, float *data, char timestamps[MAX_SAMPLES][20], int num_samples, FilterType filter_type);

#endif