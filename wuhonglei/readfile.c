/*************************************************************************
	> File Name: readfile.c
	> Author:wuhonglei 
	> Mail:1017368065@qq.com 
	> Created Time: Fri 30 Oct 2015 04:46:51 PM CST
    > Description: 
 ************************************************************************/
#include "stdio.h"
#include "stdlib.h"
 
int main( void )
{
    FILE *fp;
    fp = fopen("xenwin7.hvm" , "r");
    fseek( fp , 0 , SEEK_END );
    int file_size;
    file_size = ftell( fp );
    printf( "%d" , file_size );
    char *tmp;
    fseek( fp , 0 , SEEK_SET);
    tmp =  (char *)malloc( file_size * sizeof( char ) );
    fread( tmp , file_size , sizeof(char) , fp);
    printf("%s" , tmp );
    return 0;
}
