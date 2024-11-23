#include<stdio.h>
#include<string.h>
#include "help.h"
#include"Tags.h"
#include "view.h"

OperationType check_operation_type(char *argv[]);
int main(int argc, char *argv[])
{
    if(argc<2)
    {
        printf ("ERROR: Incorrect format of Command Line Arguments.\n");
        printf ("INFO: Use \"./a.out --help\" for Help menu.\n");
        return 0;
    }
   OperationType type = check_operation_type(argv);
   TagInfo mp3Info;
    if(type == view)
    {
        if(read_and_validate_mp3_file_view(argv,&mp3Info) == r_sucess)
        {
            printf("-------------------------------------------------SELECTED VIEW DETAILS---------------------------------------------\n");
            printf("-------------------------------------------------------VIEW %s V2.%hd--------------------------------------------\n",mp3Info.frame_Id,mp3Info.version);
            if(view_tag(&mp3Info)==r_failure)
            {
                printf("VIEW FAILED\n");
            }
            printf("--------------------------------------------------------------------------------------------------------------------------------------------------\n");
        }

    }
    else if(type == edit)
    {
        printf("Edit is selected\n");
        if(read_and_validate_mp3_file(argv,&mp3Info) == r_sucess)
        {
            printf("Do_editing...\n");
            if(Edit_mp3(&mp3Info,argv) == r_failure)
            {
                printf("Editing failed\n");
            }
            else{
                printf("ediditing done successsflly\n");
            }
        }
    }
    else if(type == help)
    {
        Help_menu();
    }
    else
    {
        printf("Error : %s : INVALID ARGUMENTS\nUSAGE :\n",argv[0]);
        printf("To view please pass arguments like: ./a.out -v mp3filename\nTo edit please pass arguments like: ./a.out -e -t/-a/-A/-m/-y/-c  changing_text mp3filename\n");
        printf("To get help pass like : ./a.out --help.\n");
        
    }
}
OperationType check_operation_type(char *argv[])
{
    if(!strcmp(argv[1],"-v"))
    {
        return view;
    }
   else if(!strcmp(argv[1],"-e"))
    {
        return edit;
    }
    else if(!strcmp(argv[1],"--help"))
    {
        return help;
    }
    else
    {
        return invalid;
    }
}
