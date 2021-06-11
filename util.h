
#include <stdio.h>
#include <string.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdbool.h>
#include <assert.h>
#include <ngspice/sharedspice.h>
#include <stdlib.h>

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

// alters a rom netlist file (see rom/rom.inc) to contain the data in 'rom'
void
write_rom(
    const char (*rom)[16],
    const char *rom_path
)
{
    int rom_fd;
    int rom_file_len;
    char *rom_file;

    // open the rom netlist file
    rom_fd = open(rom_path, O_RDWR);
    rom_file_len = lseek(rom_fd, 0, SEEK_END);
    rom_file = mmap(NULL, rom_file_len + 1, PROT_READ | PROT_WRITE, MAP_SHARED, rom_fd, 0);
    rom_file[rom_file_len] = 0; // add NULL-terminator
    close(rom_fd);

    // NOTE to self: this code does not make the assumption that the byte-subcircuits
    // in rom are located in addressing order (from byte 0 to 15) in the netlist file.
    // hence why the entire file is searched repeatedly (with strstr), instead of iteratively

    // the name of the current byte-subcircuit in ROM being written to
    char byte_circuit_name[9] = {0};
    for (int i = 0; i < 16; i++) {
        snprintf(byte_circuit_name, 9, "xxbyte%i", i);
        char *rom_file_pos = strstr(rom_file, byte_circuit_name);

        // skip past the next two spaces
        for (int j = 0; j < 2; j++)
            while (*(rom_file_pos++) != ' ') { continue; }

        // loop over each bit (each pin in the byte-subcircuit)
        for (int j = 0; j < 8; j++) {
            // connect to vdd or vss depending on the state of the current bit
            if ((*rom)[i] & (1 << j))
                memcpy(rom_file_pos, "vdd", 3);
            else
                memcpy(rom_file_pos, "vss", 3);

            // skip past the next space
            while (*(rom_file_pos++) != ' ') { continue; }
        }
    }

    msync(rom_file, rom_file_len, MS_SYNC);
    munmap(rom_file, rom_file_len + 1);
}
