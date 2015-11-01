/*************************************************************************
	> File Name: shutdownDomain.c
	> Author:wuhonglei 
	> Mail:1017368065@qq.com 
	> Created Time: 
    > Description:virDomainShutdown 关闭虚拟机(永久性的虚拟机关闭后会变成Defined，临时性的虚拟机会直接关闭)
 ************************************************************************/
#include<stdio.h>
#include<stdlib.h>
#include<libvirt/libvirt.h>

int main(int argc,char *argv[]){
    virConnectPtr conn;
    virDomainPtr dom;
    
    conn = virConnectOpen("xen:///");
    if(conn == NULL){
        fprintf(stderr,"Failed to open connection to xen:///\n");
        return 0;   
    }
    
    printf("connect success\n");
 
    dom = virDomainLookupByName(conn,"centos");
    if(!dom){
        fprintf(stderr,"Cannot find guest centos\n")    ;
        return 0;
    }

    if(virDomainShutdown(dom)<0){
       fprintf(stderr,"Fail to shutdown this domain\n") ;
        return 0;
    }
    printf("the centos ha been shutdown");

    virDomainFree(dom);
    virConnectClose(conn);
    return 1;

}
