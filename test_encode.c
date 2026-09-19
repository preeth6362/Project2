#include <stdio.h>
#include "encode.h"
#include "types.h"

int main(int argc,char *argv[])
{
    EncodeInfo encInfo;
    if(check_operation_type(argv[1][1])==e_encode)
    {
        if(read_and_validate_encode_args(argc,argv,&encInfo)==e_success)
            printf("validation completed\n");
        else
        return 1;
        if(do_encoding(&encInfo)==e_success)
        printf("encoding completed\n");
    }
    return 0;
}
OperationType check_operation_type(char opt)
{
    if(opt=='e')
    {
        printf("Encoding selected\n");
    return e_encode;
    }
    else if(opt=='d')
    {
        printf("Decoding selected\n");
    return e_decode;
    }
    else
    {
        printf("unsupported operation type\n");
    return e_unsupported;
    }
}
