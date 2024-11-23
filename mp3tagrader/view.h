#ifndef VIEW_H
#define VIEW_H


#include "Tags.h"      //Contains User-defined Data Types.
#define MAXIMUM_TAG_SIZE 4
#define MAXIMUM_TEXT_SIZE 1000

/*
 * Structure to store information required for storing the various MP3 Tag details
 * Information about Output data is also stored
 */

typedef struct _TagInfo
{

    char tag[4];
    uint size;
    /* Source MP3 file Info */
    char *mp3_fname;
    FILE* fptr_mp3;
    char frame_Id[4];
    sint version;

    /* Title Info */
    char title_tag[MAXIMUM_TAG_SIZE];
    uint title_size;

    /* Artist Info */
    char artist_tag[MAXIMUM_TAG_SIZE];
    uint artist_size;

    /* Album Info */
    char album_tag[MAXIMUM_TAG_SIZE];
    uint album_size;

    /* Year of Release Info */
    char year_tag[MAXIMUM_TAG_SIZE];
    uint year_size;

    /* Content Type Info */
    char content_tag[MAXIMUM_TAG_SIZE];
    uint content_type_size;

    /* Comments Info */
    char comment_tag[MAXIMUM_TAG_SIZE];
    uint comment_size;

} TagInfo;

/* Printing MP3 Tag details Function Prototype */

/* Perform Validation of the Arguments passed and store in the Structure */
Status read_and_validate_mp3_file_view(char* argv[], TagInfo* mp3Info);

/* Perform the Viewing Tag details Operation */
Status view_tag (TagInfo* mp3Info);

/* functions to display the various Frame contents of the MP3 file */

Status get_title(TagInfo *mp3Info);
Status get_artist(TagInfo *mp3Info);
Status get_album(TagInfo *mp3Info);
Status get_year(TagInfo *mp3Info);
Status get_content(TagInfo *mp3Info);
Status get_comment(TagInfo *mp3Info);
Status display_info(TagInfo *mp3Info);
Status get_data(char *data,uint size,FILE *fptr);
uint get_size(FILE *fptr);
sint string_short(char *data);
char * get_tag_info(TagInfo *mp3Info);


/* Functions to edit various frame contents of the mp3 file */

Status read_and_validate_mp3_file(char* argv[], TagInfo* mp3Info);

Status Edit_mp3(TagInfo *mp3Info,char **argv);

Status edit_content_type(TagInfo *mp3Info,char **argv);
Status edit_album(TagInfo *mp3Info,char **argv);
Status edit_title(TagInfo *mp3Info,char **argv);
Status edit_artist(TagInfo *mp3Info,char **argv);
Status edit_year(TagInfo *mp3Info,char **argv);
Status edit_comment(TagInfo *mp3Info,char **argv);

#endif