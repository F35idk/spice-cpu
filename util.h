
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

int
ngspice_exit_callback(
    int exit_status,
    bool unload_immediately,
    bool exit_on_quit,
    int id,
    void *user_data
)
{
    return 0;
}

int
ngspice_output_callback(
    char *output_str,
    int id,
    void *user_data
)
{
    if (strstr(output_str, "stderr")) {
        #ifdef DEBUG
        fprintf(stderr, "ngspice error: '%s'\n", &output_str[7]);
        fflush(stderr);
        #endif

        if (strstr(output_str, "Simulation interrupted due to error!")
            || strstr(output_str, "simulation aborted")) {
            #ifndef DEBUG
            fprintf(stderr, "ngspice error: '%s'\n", &output_str[7]);
            fflush(stderr);
            exit(1);
            #endif
        }
    }

    return 0;
}

float
get_ngspice_vector_voltage(const char *vector_name)
{
    vector_info *info;
    float voltage;

    info = ngGet_Vec_Info(vector_name);
    assert(info);

    if (!info->v_length) {
        printf("error: output vector '%s' has length zero - check stderr\n",
               info->v_name);
        exit(1);
    }

    voltage = info->v_realdata[info->v_length - 1];
    return voltage;
}

float
get_ngspice_vector_voltage_fmt(const char *fmt_vector_name, int idx)
{
    int name_len;
    char *vector_name;
    float voltage;

    name_len = snprintf(NULL, 0, fmt_vector_name, idx) + 1;
    vector_name = calloc(1, name_len);
    snprintf(vector_name, name_len, fmt_vector_name, idx);

    voltage = get_ngspice_vector_voltage(vector_name);
    free(vector_name);

    return voltage;
}

void
send_ngspice_cmd(char *cmd)
{
    int error = ngSpice_Command(cmd);
    if (error) {
        printf("error when sending command: '%s' - check stderr\n", cmd);
        // NOTE: this path 'leaks' cmd if cmd was heap-allocated
        exit(1);
    }
}

// sets a breakpoint in the ngpsice simulation at t = 'time_us' microseconds
void
set_ngspice_breakpoint_in_us(int time_us)
{
    // calculate maximum length of command at compile-time
    #define CMD_LEN sizeof("stop when time = us") - 1 + INT_MAX_DIGITS + 1
    char break_cmd[CMD_LEN];

    snprintf(break_cmd, CMD_LEN, "stop when time = %ius", time_us);
    send_ngspice_cmd(break_cmd);
    #undef CMD_LEN
}

// sends a command to ngspice to alter 'device' with the given 'value'
void
send_ngspice_alter_cmd(
    const char *device_name,
    const char value
)
{
    int cmd_len = 10 + strlen(device_name) + 1;
    char *alter_cmd = calloc(1, cmd_len);

    // format the 'alter' command to set the right device parameter and value
    snprintf(alter_cmd, cmd_len, "alter %s = %c", device_name, value);

    // send the alter command to ngspice
    #ifdef DEBUG
    printf("setting %s = %cV\n", device_name, value);
    #endif
    send_ngspice_cmd(alter_cmd);
    free(alter_cmd);
}

