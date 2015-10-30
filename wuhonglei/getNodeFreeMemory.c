/*************************************************************************
	> File Name: ex12.c
	> Author:wuhonglei 
	> Mail:1017368065@qq.com 
	> Created Time: Wed 28 Oct 2015 10:35:05 PM CST
    > Description:virNodeGetInfo函数可以获取节点信息(cpu架构，内存大小，) 
 ************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <libvirt/libvirt.h>
int main(int argc, char *argv[])
{
    virConnectPtr conn;
    virNodeInfo nodeinfo;
    conn = virConnectOpen("qemu:///system");

    if (conn == NULL) {
        fprintf(stderr, "Failed to open connection to qemu:///system\n");
        return 1;
    }

    virNodeGetInfo(conn, &nodeinfo);
    
        fprintf(stdout,"Model: %s\n", nodeinfo.model);
    fprintf(stdout,"Memory size: %lukb\n", nodeinfo.memory);
    fprintf(stdout,"Number of CPUs: %u\n", nodeinfo.cpus);
    fprintf(stdout,"MHz of CPUs: %u\n", nodeinfo.mhz);
    fprintf(stdout,"Number of NUMA nodes: %u\n", nodeinfo.nodes);
    fprintf(stdout,"Number of CPU sockets: %u\n", nodeinfo.sockets);
    fprintf(stdout,"Number of CPU cores per socket: %u\n", nodeinfo.cores);
    fprintf(stdout,"Number of CPU threads per core: %u\n", nodeinfo.threads);

    virConnectClose(conn);
    return 0;
}

