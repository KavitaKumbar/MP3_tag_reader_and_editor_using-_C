#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "view.h"

Status read_and_validate_mp3_file_view(char *argv[], TagInfo *mp3Info)
{
    if (argv[2] == NULL)
    {
        printf("Error : Invalid Arguments\nTo view please pass arguments like: ./a.out -v mp3filename\n");
        return r_failure;
    }
    if (strstr(argv[2], ".mpeg") == NULL /*strstr(argv[2], ".mp3") == NULL*/)
    {
        perror(argv[2]);
        printf("INFO: For Viewing the Tags -> ./a.out -v <file_name.mp3>\n");
        return r_failure;
    }
    mp3Info->mp3_fname = argv[2];
    mp3Info->fptr_mp3 = fopen(mp3Info->mp3_fname, "r");
    if (mp3Info->fptr_mp3 == NULL)
    {
        perror(mp3Info->mp3_fname);
        printf("INFO: For Viewing the Tags -> ./a.out -v <file_name.mp3>\n");
        return r_failure;
    }
    char tag[4] = {0};
    fread(tag, 1, 3, mp3Info->fptr_mp3);
    strcpy(mp3Info->frame_Id, tag);
    if (strcmp(tag, "ID3") == 0)
    {
        char tag2[3];
        fread(tag2, 1, 2, mp3Info->fptr_mp3);
        mp3Info->version = string_short(tag2);
    }
    fclose(mp3Info->fptr_mp3);
    return r_sucess;
}
Status view_tag(TagInfo *mp3Info)
{
    mp3Info->fptr_mp3 = fopen(mp3Info->mp3_fname, "r");

    if (mp3Info->fptr_mp3 == NULL)
    {
        perror(mp3Info->mp3_fname);
        printf("INFO: For Viewing the Tags -> ./a.out -v <file_name.mp3>\n");
        return r_failure;
    }
    fseek(mp3Info->fptr_mp3, 10, SEEK_SET);
    uint flag;
    do
    {
        flag = 0;
        fread(mp3Info->tag, 4, 1, mp3Info->fptr_mp3);
        if (!strncmp(mp3Info->tag, "TIT2", 4))
        {
            char *ret = get_tag_info(mp3Info);
            mp3Info->title_size = mp3Info->size;
            flag = 1;
            printf("TITLE       :     %s\n", ret);
            free(ret);
        }
        if (!strncmp(mp3Info->tag, "TPE1", 4))
        {
            flag = 1;
            char *ret = get_tag_info(mp3Info);
            printf("ARTIST      :     %s\n", ret);
            free(ret);
        }
        if (!strncmp(mp3Info->tag, "TALB", 4))
        {
            flag = 1;
            char *ret = get_tag_info(mp3Info);
            printf("ALBUM       :     %s\n", ret);
            free(ret);
        }
        if (!strncmp(mp3Info->tag, "TYER", 4))
        {
            flag = 1;
            char *ret = get_tag_info(mp3Info);
            printf("YEAR        :     %s\n", ret);
            free(ret);
        }
        if (!strncmp(mp3Info->tag, "TCON", 4))
        {
            flag = 1;
            char *ret = get_tag_info(mp3Info);
            printf("MUSIC       :     %s\n", ret);
            free(ret);
        }
        if (!strncmp(mp3Info->tag, "COMM", 4))
        {
            flag = 1;
            char *ret = get_tag_info(mp3Info);
            printf("COMMENT     :     %s\n", ret);
            free(ret);
        }
    } while (flag != 0);
    return r_sucess;
}
char *get_tag_info(TagInfo *mp3Info)
{
    mp3Info->size = get_size(mp3Info->fptr_mp3);
    char *str = malloc(mp3Info->size);
    get_data(str, mp3Info->size, mp3Info->fptr_mp3);
    return str;
}
uint get_size(FILE *fptr)
{
    char buffer[4];
    fread(buffer, 4, 1, fptr);
    uint data = 0;
    for (int i = 0; i < 4; i++)
    {
        data = data | (unsigned)buffer[i];
    }
    return data;
}
Status get_data(char *data, uint size, FILE *fptr)
{
    char buffer[size - 1];
    fseek(fptr, 3, SEEK_CUR);
    fread(buffer, size - 1, 1, fptr);
    int i;
    for (i = 0; i < size - 1; i++)
    {
        data[i] = buffer[i];
        /*if (data[i] == 0)
        {
            data[i] = '.';
        }*/
    }
    data[i] = '\0';
    return r_sucess;
}
sint string_short(char *data)
{
    unsigned char v = 0;
    for (int i = 0; i < 2; i++)
    {
        v = v | (unsigned)data[i];
    }
    return v;
}