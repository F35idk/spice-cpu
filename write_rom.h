
#include <stdio.h>
#include <string.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <unistd.h>

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
