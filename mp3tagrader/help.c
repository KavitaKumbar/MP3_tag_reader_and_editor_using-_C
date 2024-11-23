#include <stdio.h>
#include "Tags.h"
#include "help.h"

Status Help_menu()
{
    printf("\n-------------------------HELP MENU------------------------------\n\n");

    printf("1. -v -> to view mp3 file contents\n2. -e -> to edit mp3 file contents\n");
    printf("\t2.1  -t  ->  to edit song title\n");
    printf("\t2.2  -a  ->  to edit artist name\n");
    printf("\t2.3  -A  ->  to edit album name\n");
    printf("\t2.4  -y  ->  to edit year\n");
    printf("\t2.5  -m  ->  to edit content\n");
    printf("\t2.6  -c  ->  to edit comment\n");

    printf("\n----------------------------------------------------------------\n\n");
}