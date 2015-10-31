/*************************************************************************
	> File Name: 4.3.1.1.1.c
	> Author:wuhonglei 
	> Mail:1017368065@qq.com 
	> Created Time: Fri 30 Oct 2015 04:27:17 PM CST
    > Description: 
 ************************************************************************/
#include<stdio.h>
#include<stdlib.h>
#include<libvirt/libvirt.h>

char *getXMLconfig(char *filename);

int main(int argc,char *argv[]){
    virConnectPtr conn;
    virDomainPtr dom;
    //const char *xmlconfig = getXMLconfig("xenwin7.hvm");
    const char *xmlconfig = "test";
    
    conn = virConnectOpen("xen:///");
    dom = virConnectCreateXML(conn,xmlconfig,0);

    if(!dom){
        fprintf(stderr,"Domain creation failed");
        return 1;
    }
    
    fprintf(stdout,"Guest %s has booted",virDomainName(dom));
    virDomainFree(dom);
    virConnectClose(conn);
    return 0;
}

char *getXMLconfig(char *filename){
    FILE *fp;
    fp = fopen(filename , "r");
    fseek( fp , 0 , SEEK_END );
    int file_size;
    file_size = ftell( fp );
    printf( "%d" , file_size );
    char *tmp;
    fseek( fp , 0 , SEEK_SET);
    tmp =  (char *)malloc( file_size * sizeof(char));
    fread( tmp , file_size , sizeof(char) , fp);
    return tmp;
}

