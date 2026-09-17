#include <stdio.h>
#include<string.h>
#include "encode.h"
#include "types.h"

/* Function Definitions */

/* Get image size
 * Input: Image file ptr
 * Output: width * height * bytes per pixel (3 in our case)
 * Description: In BMP Image, width is stored in offset 18,
 * and height after that. size is 4 bytes
 */
uint get_image_size_for_bmp(FILE *fptr_image)
{
    uint width, height;
    // Seek to 18th byte
    fseek(fptr_image, 18, SEEK_SET);

    // Read the width (an int)
    fread(&width, sizeof(int), 1, fptr_image);
    printf("width = %u\n", width);

    // Read the height (an int)
    fread(&height, sizeof(int), 1, fptr_image);
    printf("height = %u\n", height);

    // Return image capacity
    return width * height * 3;
}

/* 
 * Get File pointers for i/p and o/p files
 * Inputs: Src Image file, Secret file and
 * Stego Image file
 * Output: FILE pointer for above files
 * Return Value: e_success or e_failure, on file errors
 */
Status open_files(EncodeInfo *encInfo)
{
    // Src Image file
    encInfo->fptr_src_image = fopen(encInfo->src_image_fname, "r");
    // Do Error handling
    if (encInfo->fptr_src_image == NULL)
    {
    	perror("fopen");
    	fprintf(stderr, "ERROR: Unable to open file %s\n", encInfo->src_image_fname);

    	return e_failure;
    }

    // Secret file
    encInfo->fptr_secret = fopen(encInfo->secret_fname, "r");
    // Do Error handling
    if (encInfo->fptr_secret == NULL)
    {
    	perror("fopen");
    	fprintf(stderr, "ERROR: Unable to open file %s\n", encInfo->secret_fname);

    	return e_failure;
    }

    // Stego Image file
    encInfo->fptr_stego_image = fopen(encInfo->stego_image_fname, "w");
    // Do Error handling
    if (encInfo->fptr_stego_image == NULL)
    {
    	perror("fopen");
    	fprintf(stderr, "ERROR: Unable to open file %s\n", encInfo->stego_image_fname);

    	return e_failure;
    }

    // No failure return e_success
    return e_success;
}
Status read_and_validate_encode_args(int argc,char *argv[], EncodeInfo *encInfo)
{
    /*check valid number of arguments
    check if src file is .bmp or not if not print error and retrun e_failure if valid then store it in structure encinfo->src_image_fname=argv[2]
    store secerct file in structure encinfo->secert_fname=argv[3]
    check if argv[4] is null or not if it is null the you only give file name and store encinfo->stego_image_fname="output.bmp"
    if user given output first validate it if it is a .bmp or not and then store encinfo->stego_image_fname=argv[4] if not
    valid then print proper error and return e_failure*/
    if(argc<3 || argc>4)
    {
        printf("insufficient number of arguments.\n");
        return e_failure;
    }
    if((argv[2][strlen(argv[2])-4]!='.') || (argv[2][strlen(argv[2])-3]!='b') || (argv[2][strlen(argv[2])-2]!='m')|| (argv[2][strlen(argv[2])-1]!='p'))
    {
        printf("Source/input file must be .bmp file\n");
        return e_failure;
    }
    encinfo->src_image_fname=argv[2];
    encinfo->secert_fname=argv[3];
    if(argv[4]==NULL)
    encinfo->stego_image_fname="output.bmp";
    else
    {
        if((argv[4][strlen(argv[4])-4]!='.') || (argv[4][strlen(argv[4])-3]!='b') || (argv[4][strlen(argv[4])-2]!='m')|| (argv[4][strlen(argv[4])-1]!='p'))
    {
        printf("Output file must be .bmp file\n");
        return e_failure;
    }
    else
    encinfo->stego_image_fname=argv[4];
    }
    if(open_files(encInfo)==e_failure)return e_failure;
    return e_success;//at last return e_success
}
Status open_files(EncodeInfo *encInfo)
{
    /*open source file in read mode encInfo->src_image_fname then check if it is opened (returns NULL adrees)or not and if not 
    opened print error and return E_failure if it successs then store in encInfo->fptr_src_image=address
    open seceret file in read mode and do same as before
    open output file in write mode ans store it in respective structure file pointer if all sucess return e_success 
    */
}
Status do_encoding(EncodeInfo *encInfo)
{
    /*first check capacity check_capacity(encInfo)==e_fialure print error and retyurn e_failure if success*/
    if(check_capacity(encInfo)==e_fialure)return e_failure; 
    rewind(fptr_src_image);rewind(fptr_secret);
    if(copy_bmp_header(encInfo->fptr_src_image,encInfo->fptr_stego_image)==e_failure)return e_failure
    if(encode_magic_string(MAGIC_STRING,encInfo)==e_failure)return e_failure;
    if(encode_secret_file_extn_size(encInfo)==e_failure)return e_failure;
}
Status check_capacity(EncodeInfo *encInfo)
{
    encInfo->image_capacity=get_image_size_for_bmp(encInfo->fptr_src_image)
    if((14+get_file_size(encInfo->fptr_secret))*8>encInfo->image_capacity)return e_failure;
    else
    return e_success;
}
uint get_file_size(FILE *fptr)
{
   fseek(fptr,0,SEEK_END);
   encInfo->size_secret_file=ftell(fptr);
}
Status copy_bmp_header(FILE *fptr_src_image, FILE *fptr_dest_image)
{
   /*declare buff[54]
   read 54 bytes from src file
   write 54 bytes from dest file
   validate return return e_succcess*/
}
Status encode_magic_string(const char *magic_string, EncodeInfo *encInfo)
{
    /*declare buffer of 8 bytes
    1)read 8 bytes from source file into buffer
    2)encode_byte_to_lsb(magic_string[1],buffer)  
    3) write encoded buff to output_file do 1,2&3 2 times because magicstring is 2 bytes
    
    if everything ok then e_sucess*/
}
Status encode_byte_to_lsb(char data, char *image_buffer)
{
     /*get bits from data from msb to lsb and set or clear lsb of image buffer from 0 t0 7 according t0 bit got use loop run for 8 times
     for(int i=7;i>=0;i--)
     get ith bit of data
     if set set lsb of image_buffer[7-i]
     if 0 clr lsb of image_buffer[7-i]*/
}
Status encode_secret_file_extn_size(EncodeInfo *encInfo)
{
    /*char *dot=strchr(seceret_file_name,'.')
    strcpy(extn_secret_file,dot);
    declare buffer[32] read 32 bytes from srcfile
    encode_size_to_lsb(strlen(extn_secret_file),buffer)*/
}
Status encode_size_to_lsb(int size,  char *image_buffer)
{
    /*get bits from data from msb to lsb and set or clear lsb of image buffer from 0 t0 7 according t0 bit got use loop run for 8 times
     for(int i=31;i>=0;i--)
     get ith bit of data
     if set set lsb of image_buffer[31-i]
     if 0 clr lsb of image_buffer[31-i]*/
}