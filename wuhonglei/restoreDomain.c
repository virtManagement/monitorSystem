/*************************************************************************
	> File Name: shutdownDomain.c
	> Author:wuhonglei 
	> Mail:1017368065@qq.com 
	> Created Time: 
    > Description:virDomainRestore 将虚拟机从文件中恢复 
 ************************************************************************/
#include<stdio.h>
#include<stdlib.h>
#include<libvirt/libvirt.h>

int main(int argc,char *argv[]){
    virConnectPtr conn;
    virDomainPtr dom;
    int id;
    char *filename = "/var/lib/libvirt/save/centos.img" ;
    
    conn = virConnectOpen("xen:///");
    if(conn == NULL){
        fprintf(stderr,"Fail to open connection to xen:///");
        return 0;
    }
        
    if((id = virDomainRestore(conn,filename)) < 0){
        fprintf(stderr,"Unable to restore guest from %s\n",filename);
        return ;
    }
    
   /* printf("Domain ID: %d\n",id);
    dom = virDomainLookupByID(conn,id);
    if(!dom){
        fprintf(stderr,"Cannnot find Guest that was restored\n");
        return ;
    }*/
    
    fprintf(stderr,"Guest state retored from %s\n",filename);
    
   // virDomainFree(dom);
    virConnectClose(conn);
    return 1;
}   
