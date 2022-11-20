#include "Header.h"
#include "Compress.h"
#include "Uncompress.h"

int main(int argc, char **argv) {
    char *Action = argv[1];
    //Compress
    if (strcmp(Action,"-e") == 0)
        compressed(argc, argv);
    else if (strcmp(Action,"-d") == 0)
        uncompressed(argc, argv);
    else 
        cout << "Wrong command!";
    return 0;
}