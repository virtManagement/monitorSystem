/*************************************************************************
	> File Name: Capabilities.c
	> Author:tiuhonglei 
	> Mail:1017368065@qq.com 
	> Created Time: Thu 29 Oct 2015 07:05:32 PM CST
    > Description: 
 ************************************************************************/
#include<stdio.h>
#include<stdlib.h>
#include<libvirt/libvirt.h>
#include<libvirt/virterror.h>
int main(int argvc, char *argv[]){
    static virConnectPtr conn = NULL;
    static virDomainPtr dom = NULL;
    char * Sysinfo;
    char* Capabilities;
    char* Hostname;
    int Vcpunum ;
    const  char* ConnectType;
    unsigned long * hvVer;
    int IsAlive;


    conn = virConnectOpen("xen:///");
    if(conn == NULL){
        fprintf(stderr,"Failed to open connection to xen");
        return -1;
    }
    dom = virDomainLookupByID(conn,1);
    if(dom == NULL){
        fprintf(stderr,"Failed to create a dom");
        return -1;
    }
    
  
    Capabilities = virConnectGetCapabilities(conn);//get capabilities
     if(Capabilities == NULL){
        fprintf(stdout,"failed to GetCapabilities");
        return -1;
     } 
    fprintf(stdout,"ConnectCapabilities %s\n",Capabilities);
    free(Capabilities);


    Sysinfo = virConnectGetSysinfo(conn,0);//Get Sysinfo
     if(Sysinfo ==NULL){
        fprintf(stdout,"failed to getinfo");
        return -1;
     }
    fprintf(stdout,"Sysinfo:%s\n",Sysinfo);
    free(Sysinfo);    


    Hostname = virConnectGetHostname(conn);//get hostname
    if(Hostname == NULL){
        fprintf(stderr,"failed to get hostname");
        return -1;
    }
    fprintf(stdout,"Hostname:%s\n",Hostname);
    free(Hostname);

  
    Vcpunum = virConnectGetMaxVcpus(conn,"xen");//Get Vcpunum
    if(Vcpunum <0){
        fprintf(stdout,"failed to GetCpunum");
        return -1;
    }
    fprintf(stdout,"Vcpunum: %d\n",Vcpunum);
   

    ConnectType = virConnectGetType(conn);//Connect Type
    if(ConnectType ==NULL){
        fprintf(stdout,"failed to GetConnectType");
        return -1;
    }    
    fprintf(stdout,"ConnectType is that :%s\n",ConnectType);    

    
    if(virConnectGetVersion(conn,hvVer)<0){
        fprintf(stderr,"Failed to Get Version");
        return -1;
    }
    fprintf(stdout,"ConnectVersion: %lu\n",*hvVer);

    
    IsAlive = virConnectIsAlive(conn);
    if(IsAlive == 1 ){
        fprintf(stdout,"alive\n");
    }
    else
        if(IsAlive == 0){
            fprintf(stdout,"dead\n");
        }
        else
            fprintf(stdout,"Failed to get Connect Status\n");


    free(dom);
    virConnectClose(conn);
    return 0;
}
