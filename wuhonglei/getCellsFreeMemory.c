/*************************************************************************
	> File Name: ex13.c
	> Author:wuhonglei 
	> Mail:1017368065@qq.com 
	> Created Time: Thu 29 Oct 2015 11:17:35 AM CST
    > Description: virNodeGetCellsFreeMemory()获得处理器个数，并返回每个处理器的可用内存
 ************************************************************************/
#include<stdio.h>
#include<stdlib.h>
#include<libvirt/libvirt.h>

int main(int argc,char *argv[]){
    virConnectPtr conn;
    virNodeInfo nodeinfo;
    unsigned long long *freemem;
    int i;
    int numnodes;
    
    conn = virConnectOpen("xen:///");
    if(conn == NULL){
        fprintf(stderr,"Failed to open connection to xen:///");
        return 1;
    }
    
    virNodeGetInfo(conn,&nodeinfo);

    printf("number of nodes: %d\n",nodeinfo.nodes);
    
    freemem = malloc(nodeinfo.nodes*sizeof(unsigned long long));

    numnodes = virNodeGetCellsFreeMemory(conn,freemem,0,nodeinfo.nodes);
    
    for(i=0;i<numnodes;i++){
        fprintf(stdout,"Node %d: %llukb free memory\n",i,freemem[i]);
    }
    
    free(freemem);
    
    virConnectClose(conn);
    return 0;
}
