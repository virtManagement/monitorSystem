/*************************************************************************
	> File Name: ex10.c
	> Author:wuhonglei 
	> Mail:1017368065@qq.com 
	> Created Time: Wed 28 Oct 2015 08:50:00 PM CST
    > description:virConnectGetVcpus()Maxium number of CPUs support for virtualization
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<libvirt/libvirt.h>

int main(int argc,char *argv[]){
    virConnectPtr conn;
    int vcpus;
    
    conn = virConnectOpen("xen:///");
    if(conn==NULL){
        fprintf(stderr,"Failed to open connection to qeme:///system\n");
        return 1;
    }

    vcpus = virConnectGetMaxVcpus(conn,NULL);
    fprintf(stdout,"Maxium support virtual CPUs:%d\n",vcpus);

    virConnectClose(conn);
    return 0;
}
