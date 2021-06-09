
#include <stdio.h>
#include "util.h"

int
main(void)
{
    const char rom[16] = {
        0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00,
    };

    write_rom(&rom, "rom/rom.inc");

    return 0;
}
