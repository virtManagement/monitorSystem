/*************************************************************************
	> File Name: dq_libvirt.c
	> Author:wuhonglei 
	> Mail:1017368065@qq.com 
	> Created Time: Wed 28 Oct 2015 06:16:09 PM CST
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<libvirt/libvirt.h>
#include<libvirt/virterror.h>


static int set_start(char *guestname);
static int set_shutdown(char *guestname);
static int get_status(char *guestname);
static virConnectPtr conn = NULL;
static virDomainPtr dom = NULL;



int main(int argc,char *argv[])
{
    if(argc != 3){
        fprintf(stderr,"Usage:./virctl guest-name start/shutdown/status\n");
        return -1;
    }
    conn = virConnectOpen("xen:///");
    if(conn == NULL){
        fprintf(stderr,"Failed to open connection to qemu:///system\n");
        return -1;
    }
    dom = virDomainLookupByName(conn,argv[1]);
    if ( dom == NULL){
        fprintf(stderr,"virDomainLookupByName failed!\n");
        virConnectClose(conn);
        return -1;
    }
    if (strcmp(argv[2],"start")==0 || strcmp(argv[2],"START")==0){
        if(set_start(argv[1])!=0){
            fprintf(stderr,"start failed!\n");
            virDomainFree(dom);
            //virConnevtClose(vonn);
            return -1;
        }
    }
    if(strcmp(argv[2],"shutdown")==0 || strcmp(argv[2],"SHUTDOWN")==0){
        if(set_shutdown(argv[1])!=0){
            fprintf(stderr,"shutdown failed!\n");
            virConnectClose(conn);
            virDomainFree(dom);
            return -1;
        }        

    }
    if (strcmp(argv[2],"status")==0||strcmp(argv[2],"STATUS")==0){
	if(get_status(argv[1])!=0){
		fprintf(stderr,"get status failed!\n");
		virDomainFree(dom);
		virConnectClose(conn);
		return -1;	
	
	}
    }
    if (dom != NULL) virDomainFree(dom);
    if (conn != NULL) virConnectClose(conn);
    return 0;
}
int set_start(char *guestname){ 

   int flag = -1;
    flag = virDomainCreate(dom);
    if (flag !=0){
        virErrorPtr error = virGetLastError();
        fprintf(stderr,"virDomainCreate failed :%s!\n",error->message);
	virFreeError(error);
	return -1;
    }
    return 0;
}
int set_shutdown(char *guestname){	
    int flag = -1;
    flag = virDomainShutdown(dom);
    if(flag != 0){
	virErrorPtr error = virGetLastError();
	fprintf(stderr,"virDomainShutDown failed:%s!\n",error->message);
	virFreeError(error);
	return -1;
    
    }
    return 0;
}
int get_status(char *guestname){
    char *status = NULL;
    virErrorPtr error = NULL;
    int vcpus = 0;
    unsigned long long node_free_memory = 0;
    int id = 0;
    const char *name = NULL;
    virNodeInfo nodeinfo;
    virDomainInfo info;
    fprintf(stdout,"*********************************************************************\n");
    status = virConnectGetCapabilities(conn);
    if (status == NULL){
	error = virGetLastError();
    	fprintf(stderr,"virConnectGetCapabilities failed: %s\n",error->message);
	virFreeError(error);
	return -1;
    }
    //fprintf(stdout,"capabilities of connection:\n%s\n",status);
    free(status); status = NULL;
    
/*get the hostname reported from conn*/
    status = virConnectGetHostname(conn);
    if ( status ==NULL){
	error = virGetLastError();
	fprintf(stderr,"virConnectGetHostname failed:%s\n",error->message);
	virFreeError(error);
	return -1;
    }
    fprintf(stdout,"********************************************\n");
    fprintf(stdout,"Connection hostname:\t%s\n",status);
    free(status); status = NULL;

/*get the maximum number of vcpus supported */
    vcpus = virConnectGetMaxVcpus(conn,NULL);
    if(vcpus<0){
	error = virGetLastError();
	fprintf(stdout,"virConnectGetMaxVcpus failed:%s\n",error->message);
	virFreeError(error);
	return -1;
    }
    fprintf(stdout,"Maximum number of cpus supported on connection:\t%d\n",vcpus);

/*get the amount of free memory available on the node from conn4*/
    node_free_memory = virNodeGetFreeMemory(conn);
    if(node_free_memory ==0){
	error = virGetLastError();
    	fprintf(stdout,"virNodeGetFreeMemory failed: %s\n",error->message);
	virFreeError(error);
	return -1;
    }
    fprintf(stdout,"Node free Memory :\t%llu\n",node_free_memory);
/*get the node information form conn*/
    if(virNodeGetInfo(conn,&nodeinfo)<0){
	error = virGetLastError();
	fprintf(stderr,"virNodeGetInfo failed:%s\n",error->message);
	virFreeError(error);
	return -1;
    }
    fprintf(stdout,"***************************************************************\n");
    fprintf(stdout,"Node information from connection \n");
    fprintf(stdout,"Model:\t%s\n",nodeinfo.model);
    fprintf(stdout,"Memory size : \t%lukb \n",nodeinfo.memory);
    fprintf(stdout,"Number of cpus:\t%u\n",nodeinfo.cpus);
    fprintf(stdout,"MHz of CPUs:\t%u\n",nodeinfo.mhz);
    fprintf(stdout,"Number of NUMA nodes:\t%u\n",nodeinfo.nodes);
    fprintf(stdout,"Number of CPU sockets:\t%u\n",nodeinfo.sockets);
    fprintf(stdout,"Number of CPU cores per socket:\t%u\n",nodeinfo.cores);
    fprintf(stdout,"Number of CPU threads per core:\t%u\n",nodeinfo.threads);
    fprintf(stdout,"************************************************************** \n");
    fprintf(stdout,"id\tname\t\tstatus \n");
    fprintf(stdout,"--------------------------------------------------------------- \n");

    id = virDomainGetID(dom);
    name = virDomainGetName(dom);
    if(virDomainGetInfo(dom,&info)<0){
    	error = virGetLastError();
    	fprintf(stdout,"virDomainGetInfo failed:%s\n",error->message);
 	virFreeError(error);
    	return -1;
    }
    fprintf(stdout,"%d\t%s\t\t%d\n",id,name,info.state);
    fprintf(stdout,"******************************");
    return 0;
}
