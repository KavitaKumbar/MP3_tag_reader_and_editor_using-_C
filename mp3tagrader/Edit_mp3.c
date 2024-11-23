#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "view.h"
#include "Tags.h"

Status read_and_validate_mp3_file(char *argv[], TagInfo *mp3Info)
{
	if (argv[3] == NULL)
	{
		printf("Error : Invalid Arguments\nTo edit please pass arguments like: ./a.out -e -t/-a/-A/-m/-y/-c  changing_text mp3filename\n");
		return r_failure;
	}
	mp3Info->mp3_fname = argv[4];
	mp3Info->fptr_mp3 = fopen(mp3Info->mp3_fname, "r");
	if (mp3Info->fptr_mp3 == NULL)
	{
		perror(mp3Info->mp3_fname);
		printf("INFO: To edit please pass arguments like: ./a.out -e -t/-a/-A/-m/-y/-c  changing_text mp3filename\n");
		return r_failure;
	}
	char tag[4] = {0};
	fread(tag, 1, 3, mp3Info->fptr_mp3);
	strcpy(mp3Info->frame_Id, tag);
	if (strcmp(tag, "ID3") == 0)
	{
		short *tag2 = &mp3Info->version;
		fread(tag2, 2, 1, mp3Info->fptr_mp3);
		mp3Info->version = *tag2;
	}
	fclose(mp3Info->fptr_mp3);
	return r_sucess;
}
Status Edit_mp3(TagInfo *mp3Info, char **argv)
{
	int i;
	char buffer[300];

	mp3Info->fptr_mp3 = fopen(argv[4], "r+");
	if (mp3Info->fptr_mp3 == NULL)
	{
		perror("fopen");
		exit(1);
	}
	if (strcmp(argv[2], "-t") == 0)
	{
		if (edit_title(mp3Info, argv) == r_failure)
		{
			printf("edit title failed\n");
			return r_failure;
		}
	}
	if (strcmp(argv[2], "-a") == 0)	
	{
		if (edit_artist(mp3Info, argv) == r_failure)
		{
			printf("edit artist failed\n");
			return r_failure;
		}
	}
	if (strcmp(argv[2], "-A") == 0)
	{
		if (edit_album(mp3Info, argv) == r_failure)
        {
            printf("edit album failed\n");
            return r_failure;
        }
	}

	if (strcmp(argv[2], "-y") == 0)
	{
		if (edit_year(mp3Info, argv) == r_failure)
		{
			printf("edit year failed\n");
			return r_failure;
		}
	}
	 if (strcmp(argv[2], "-m") == 0)
	 {
		if(edit_content_type(mp3Info, argv) == r_failure)
		{
			printf("edit content type failed\n");
            return r_failure;
		}
	 }
	 if (strcmp(argv[2], "-c") == 0)
	 {
		if (edit_comment(mp3Info, argv) == r_failure)
		{
			printf("edit comment failed\n");
            return r_failure;
		}
	 }
	return r_sucess;
}

Status edit_content_type(TagInfo *mp3Info, char **argv)
{
	fseek(mp3Info->fptr_mp3, +10, SEEK_SET);
	char buffer[100];
	char tag[5];
	uint flag;
	do
	{
		flag = 0;
		fread(tag, 4, 1, mp3Info->fptr_mp3);
		mp3Info -> size = get_size(mp3Info ->fptr_mp3);
		if(mp3Info->size > (unsigned)100)
		{
			printf("%u\n",mp3Info->size);
			return r_failure;
		}
		if (!strncmp(tag, "TCON", 4))
		{
			fseek(mp3Info->fptr_mp3, 3, SEEK_CUR);
			int x = ftell(mp3Info->fptr_mp3);
			fread(buffer,mp3Info->size-1, 1, mp3Info->fptr_mp3);
			printf("%s\n",buffer);
			int y = ftell(mp3Info ->fptr_mp3);
			int z = x - y;
			printf("Before Editing : %s\n", buffer);
			strcpy(buffer, argv[3]);
			fseek(mp3Info->fptr_mp3,z, SEEK_CUR);
			fwrite(buffer,mp3Info->size-1, 1, mp3Info->fptr_mp3);
			return r_sucess;
		}
		else
		{
			flag = 1;
			fseek(mp3Info->fptr_mp3,mp3Info->size, SEEK_CUR);
			fseek(mp3Info->fptr_mp3,2, SEEK_CUR);
		}

	} while (flag != 0);
	return r_failure;
}

Status edit_album(TagInfo *mp3Info, char **argv)
{
	fseek(mp3Info->fptr_mp3, +10, SEEK_SET);
	char buffer[100];
	char tag[5];
	uint flag;
	do
	{
		flag = 0;
		fread(tag, 4, 1, mp3Info->fptr_mp3);
		mp3Info -> size = get_size(mp3Info ->fptr_mp3);
		if(mp3Info->size > (unsigned)100)
		{
			printf("%u\n",mp3Info->size);
			return r_failure;
		}
		if (!strncmp(tag, "TALB", 4))
		{
			fseek(mp3Info->fptr_mp3, 3, SEEK_CUR);
			int x = ftell(mp3Info->fptr_mp3);
			fread(buffer,mp3Info->size-1, 1, mp3Info->fptr_mp3);
			printf("%s\n",buffer);
			int y = ftell(mp3Info ->fptr_mp3);
			int z = x - y;
			printf("Before Editing : %s\n", buffer);
			strcpy(buffer, argv[3]);
			fseek(mp3Info->fptr_mp3,z, SEEK_CUR);
			fwrite(buffer,mp3Info->size-1, 1, mp3Info->fptr_mp3);
			return r_sucess;
		}
		else
		{
			flag = 1;
			fseek(mp3Info->fptr_mp3,mp3Info->size, SEEK_CUR);
			fseek(mp3Info->fptr_mp3,2, SEEK_CUR);
		}

	} while (flag != 0);
	return r_failure;
}
Status edit_title(TagInfo *mp3Info, char **argv)
{
	fseek(mp3Info->fptr_mp3, +10, SEEK_SET);
	char buffer[100];
	char tag[5];
	uint flag;
	do
	{
		flag = 0;
		fread(tag, 4, 1, mp3Info->fptr_mp3);
		mp3Info -> size = get_size(mp3Info ->fptr_mp3);
		if(mp3Info->size > (unsigned)100)
		{
			printf("%u\n",mp3Info->size);
			return r_failure;
		}
		if (!strncmp(tag, "TIT2", 4))
		{
			fseek(mp3Info->fptr_mp3, 3, SEEK_CUR);
			int x = ftell(mp3Info->fptr_mp3);
			fread(buffer,mp3Info->size-1, 1, mp3Info->fptr_mp3);
			printf("%s\n",buffer);
			int y = ftell(mp3Info ->fptr_mp3);
			int z = x - y;
			printf("Before Editing : %s\n", buffer);
			strcpy(buffer, argv[3]);
			fseek(mp3Info->fptr_mp3,z, SEEK_CUR);
			fwrite(buffer,mp3Info->size-1, 1, mp3Info->fptr_mp3);
			return r_sucess;
		}
		else
		{
			flag = 1;
			fseek(mp3Info->fptr_mp3,mp3Info->size, SEEK_CUR);
			fseek(mp3Info->fptr_mp3,2, SEEK_CUR);
		}

	} while (flag != 0);
	return r_failure;
}
Status edit_artist(TagInfo *mp3Info, char **argv)
{
	fseek(mp3Info->fptr_mp3, +10, SEEK_SET);
	char buffer[100];
	char tag[5];
	uint flag;
	do
	{
		flag = 0;
		fread(tag, 4, 1, mp3Info->fptr_mp3);
		mp3Info -> size = get_size(mp3Info ->fptr_mp3);
		if(mp3Info->size > (unsigned)100)
		{
			printf("%u\n",mp3Info->size);
			return r_failure;
		}
		if (!strncmp(tag, "TPE1", 4))
		{
			fseek(mp3Info->fptr_mp3, 3, SEEK_CUR);
			int x = ftell(mp3Info->fptr_mp3);
			fread(buffer,mp3Info->size-1, 1, mp3Info->fptr_mp3);
			printf("%s\n",buffer);
			int y = ftell(mp3Info ->fptr_mp3);
			int z = x - y;
			printf("Before Editing : %s\n", buffer);
			strcpy(buffer, argv[3]);
			fseek(mp3Info->fptr_mp3,z, SEEK_CUR);
			fwrite(buffer,mp3Info->size-1, 1, mp3Info->fptr_mp3);
			return r_sucess;
		}
		else
		{
			flag = 1;
			fseek(mp3Info->fptr_mp3,mp3Info->size, SEEK_CUR);
			fseek(mp3Info->fptr_mp3,2, SEEK_CUR);
		}

	} while (flag != 0);
	return r_failure;
}
Status edit_year(TagInfo *mp3Info, char **argv)
{
	fseek(mp3Info->fptr_mp3, +10, SEEK_SET);
	char buffer[100];
	char tag[5];
	uint flag;
	do
	{
		flag = 0;
		fread(tag, 4, 1, mp3Info->fptr_mp3);
		mp3Info -> size = get_size(mp3Info ->fptr_mp3);
		if(mp3Info->size > (unsigned)100)
		{
			printf("%u\n",mp3Info->size);
			return r_failure;
		}
		if (!strncmp(tag, "TYER", 4))
		{
			fseek(mp3Info->fptr_mp3, 3, SEEK_CUR);
			int x = ftell(mp3Info->fptr_mp3);
			fread(buffer,mp3Info->size-1, 1, mp3Info->fptr_mp3);
			printf("%s\n",buffer);
			int y = ftell(mp3Info ->fptr_mp3);
			int z = x - y;
			printf("Before Editing : %s\n", buffer);
			strcpy(buffer, argv[3]);
			fseek(mp3Info->fptr_mp3,z, SEEK_CUR);
			fwrite(buffer,mp3Info->size-1, 1, mp3Info->fptr_mp3);
			return r_sucess;
		}
		else
		{
			flag = 1;
			fseek(mp3Info->fptr_mp3,mp3Info->size, SEEK_CUR);
			fseek(mp3Info->fptr_mp3,2, SEEK_CUR);
		}

	} while (flag != 0);
	return r_failure;
}
Status edit_comment(TagInfo *mp3Info, char **argv)
{
	fseek(mp3Info->fptr_mp3, +10, SEEK_SET);
	char buffer[100];
	char tag[5];
	uint flag;
	do
	{
		flag = 0;
		fread(tag, 4, 1, mp3Info->fptr_mp3);
		mp3Info -> size = get_size(mp3Info ->fptr_mp3);
		if(mp3Info->size > (unsigned)100)
		{
			printf("%u\n",mp3Info->size);
			return r_failure;
		}
		if (!strncmp(tag, "COMM", 4))
		{
			fseek(mp3Info->fptr_mp3, 3, SEEK_CUR);
			int x = ftell(mp3Info->fptr_mp3);
			fread(buffer,mp3Info->size-1, 1, mp3Info->fptr_mp3);
			printf("%s\n",buffer);
			int y = ftell(mp3Info ->fptr_mp3);
			int z = x - y;
			printf("Before Editing : %s\n", buffer);
			strcpy(buffer, argv[3]);
			fseek(mp3Info->fptr_mp3,z, SEEK_CUR);
			fwrite(buffer,mp3Info->size-1, 1, mp3Info->fptr_mp3);
			return r_sucess;
		}
		else
		{
			flag = 1;
			fseek(mp3Info->fptr_mp3,mp3Info->size, SEEK_CUR);
			fseek(mp3Info->fptr_mp3,2, SEEK_CUR);
		}

	} while (flag != 0);
	return r_failure;
}
