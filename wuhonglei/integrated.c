/*************************************************************************
	> File Name: integrated.c
	> Author:wuhonglei 
	> Mail:1017368065@qq.com 
	> Created Time: Thu 29 Oct 2015 12:23:24 PM CST
    > Description: 
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<libvirt/libvirt.h>

int main(int argc,char *argv[]){
    virConnectPtr conn;
    unsigned long hvVer;
    
    conn = virConnectOpen("xen:///");
    if(conn == NULL){
        fprintf(stderr,"Failed to open to the xen:///");
        return 1;
    }
    if(virConnectGetVersion(conn,&hvVer) == 0)
        fprintf(stdout,"the version of Xen is: %u\n",hvVer);
    
    virConnectClose(conn);
    return 0;
}
