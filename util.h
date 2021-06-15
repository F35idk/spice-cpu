
#ifndef UTIL_H
#define UTIL_H

#include <stdio.h>
#include <string.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdbool.h>
#include <assert.h>
#include <stdarg.h>
#include <ngspice/sharedspice.h>
#include <stdlib.h>

#define INT_MAX_DIGITS 10

int ngspice_exit_callback(
    int exit_status,
    bool unload_immediately,
    bool exit_on_quit,
    int id,
    void *user_data
);

int ngspice_output_callback(
    char *output_str,
    int id,
    void *user_data
);

float get_ngspice_vector_voltage(const char *vector_name);

float get_ngspice_vector_voltage_fmt(const char *fmt_vector_name, int idx);

void send_ngspice_cmd(char *cmd);

// sets a breakpoint in the ngpsice simulation at t = 'time_us' microseconds
void set_ngspice_breakpoint_in_us(int time_us);

// sends a command to ngspice to alter 'device' with the given 'value'
void send_ngspice_alter_cmd(
    const char *device_name,
    const char value
);

#endif
