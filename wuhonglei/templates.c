/*************************************************************************
	> File Name: shutdownDomain.c
	> Author:wuhonglei 
	> Mail:1017368065@qq.com 
	> Created Time: 
    > Description: 
 ************************************************************************/
#include<stdio.h>
#include<stdlib>
#include<libvirt/libvirt.h>

int main(int argc,char *argv[]){
    virConnectPtr conn;
    virDomainPtr dom;
    
    conn = virConnectOpen("xen:///");
    if(conn == NULL){
        fprintf(stderr,"Fail to open connection to xen:///");
        return 0;
    }
}
