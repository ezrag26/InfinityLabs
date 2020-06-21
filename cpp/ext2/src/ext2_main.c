#include <stdio.h> /* NULL */
#include <assert.h> /* assert */

#include "ext2.h"

int main(int argc, char *argv[])
{
    char *device_path = NULL;
    char *filepath = NULL;
    
    assert(3 == argc);

    device_path = argv[1];
    filepath = argv[2];
    // device_path = "/dev/ram0";
    // filepath = "file.txt";

    EXT2PrintFile(device_path, filepath);

    return 0;
}
