/*************************************************************************
	> File Name: demo01.c
	> Author:tangjie 
	> Mail:824647349@qq.com 
	> Created Time: Tue 27 Oct 2015 08:25:58 PM CST
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
#include<libvirt/libvirt.h>
#include<libvirt/virterror.h>


static int create_kvm();
static int get_status();
static int open_file(char *file_name);


static virConnectPtr conn = NULL;
static virDomainPtr dom = NULL;
char *buff = NULL;

int main (int argc, char *argv[])
{
    if(argc!=2){
        fprintf(stderr,"parametes are wrong ,please checkout!\n");
        return -1;
    }
    if(open_file(argv[1])!=0){
        fprintf(stderr,"openfile failed!\n");
        return -1;
    }
    conn = virConnectOpen("xen:///");
    if(conn == NULL){
        fprintf(stderr,"Failed to open connection to qemu:///system\n");
        return -1;
    }
    if(create_kvm()!=0){
        fprintf(stderr,"create_kvm failed!\n");
        virConnectClose(conn);
        return -1;
    }
    if(get_status()!=0){
    	fprintf(stderr,"create_kvm failed!\n");
	virDomainFree(dom);
	virConnectClose(conn);
	return -1;
    }
    if(dom != NULL){
   	virDomainFree(dom);
    } 
    if(conn != NULL) virConnectClose(conn);		
    return 0;
}

int open_file(char *file_name){
    FILE *fp = fopen(file_name,"r+");
    assert(fp);
    int flag = fseek(fp,0,SEEK_END);
    assert(flag == 0);
    int len = ftell(fp);
    buff = (char*)malloc(sizeof(char)*(len+1));
    flag = fseek(fp,0,SEEK_SET);
    assert(flag == 0);
    int num = fread(buff,1,len + 1,fp); 
    assert(num == len);
    return 0;
}
int create_kvm(){
    dom = virDomainDefineXML(conn,buff);
    if(!dom){
        virErrorPtr error = virGetLastError();
        fprintf(stderr,"virDomainDefineXML failed:%s!\n",error->message);
        virFreeError(error);
	return -1;
    }
    if(virDomainCreate(dom)<0){
    	virErrorPtr error = virGetLastError();
	fprintf(stderr,"virDomainCreate failed:%s!\n",error->message);
	virDomainUndefine(dom);
	virFreeError(error);
	//virDomainFree(dom);
	return -1;	
    }
    return 0;
}
int get_status(){
    char *status = NULL;
    virErrorPtr error = NULL;
    int vcpus = 0;
    unsigned long long node_free_memory = 0;
    int id = 0;
    const char *name = NULL;
    virNodeInfo nodeinfo;
    virDomainInfo info;
    fprintf(stdout,"******************************************\n");

    /* get the capabilities of conn*/
    status = virConnectGetCapabilities(conn);
    if(status == NULL){
    	error = virGetLastError();
    	fprintf(stderr,"virConnectGetCapabilities failed:%s\n",error->message);
    	virFreeError(error);
    	return -1;
    }
    fprintf(stdout,"Caabilities of connection:\t%s\n",status);
    free(status);
    status = NULL;
    

    /*get the hostname reported from conn*/	
    status = virConnectGetHostname(conn);
    if(status == NULL){
    	error = virGetLastError();
    	fprintf(stderr,"virConnectGetHostname failed:%s\n",error->message);
    	virFreeError(error);
    	return -1;	
    }    	
    fprintf(stdout,"Connection hostname :\t%s\n",status);
    free(status); status = NULL;


    /* get the maximum number of vcpus  supported bt conn3*/
    vcpus = virConnectGetMaxVcpus(conn,NULL);
    if(vcpus<0){
    	error = virGetLastError();
    	fprintf(stderr,"virConnectGetMaxVcpus failed:%s\n",error->message);
    	virFreeError(error);
	return -1;
    }
    fprintf(stdout,"Maximum number of cpus supported on  connecion:\t%d\n",vcpus);


   /*get the amount of free memory acailable on the node from conn4*/
    node_free_memory = virNodeGetFreeMemory(conn);
    if(node_free_memory == 0){
     	error = virGetLastError();
    	fprintf(stderr,"virNodeGetFreeMemory failed:%s\n",error->message);
    	virFreeError(error);
    	return -1;
    }
    fprintf(stdout,"Node free memory:\t%llu\n",node_free_memory);

    /*get the node information from conn*/
    if (virNodeGetInfo(conn,&nodeinfo)<0){
     	error = virGetLastError();
    	fprintf(stderr,"virNodeGetInfo failed:%s\n",error->message);
    	virFreeError(error);
    	return -1;
    }
    fprintf(stdout,"Node information from connection\n");
    fprintf(stdout,"Model:\t%s\n",nodeinfo.model);
    fprintf(stdout,"Memory size:\t%lukb\n",nodeinfo.memory);
    fprintf(stdout,"Number of CPUd:\t%u\n",nodeinfo.cpus);
    fprintf(stdout,"MHz of CPUs:\t%u\n",nodeinfo.mhz);
    fprintf(stdout,"Number of NUMA nodes:\t%u\n",nodeinfo.nodes);
    fprintf(stdout,"Number of CPU sockets:\t%u\n",nodeinfo.sockets);
    fprintf(stdout,"Number of CPU cores per socket:\t%u\n",nodeinfo.cores);
    fprintf(stdout,"Number of CPU threads per core :\t%u\n",nodeinfo.threads);
    fprintf(stdout,"**********************************************************\n");
    fprintf(stdout,"id\t\t\n");
    fprintf(stdout,"******************************************************\n");
    id = virDomainGetID(dom);
    name = virDomainGetName(dom);
    if(virDomainGetInfo(dom,&info)<0){
	error = virGetLastError();
	fprintf(stderr,"virDomainGetInfo failed:%s\n",error->message);
	virFreeError(error);
	return -1;
   }
    fprintf(stdout,"%d\t%s\t\t%d\n",id,name,info.state);
    fprintf(stdout,"***************************************");
    return 0;

}











