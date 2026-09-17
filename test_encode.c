#include <stdio.h>
#include "encode.h"
#include "types.h"

int main(int argc,char *argv[])
{
    EncodeInfo encInfo;
    if(check_operation_type(argv[1][1])==e_encode)
    {
        if(read_and_validate_encode_args(argc,argv,&encInfo)==e_failur)//print error return e_failure
        do_encoding(&encInfo)
    }
    return 0;
}
OperationType check_operation_type(char opt)
{
    if(opt=='e')
    return e_encode;
    else if(opt=='d')
    return e_decode;
    else
    return e_unsupported;
}
