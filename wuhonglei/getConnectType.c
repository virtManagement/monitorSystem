/*************************************************************************
	> File Name: getConnectType.c
	> Author:wuhonglei 
	> Mail:1017368065@qq.com 
	> Created Time: Sat 31 Oct 2015 11:00:36 AM CST
    > Description: virConnectGetType 获得本机所采用的虚拟化类型(例如xen) 
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <libvirt/libvirt.h>

int main(int argc, char *argv[])
{
    virConnectPtr conn;
    conn = virConnectOpen("xen:///");
    if (conn == NULL) {
        fprintf(stderr, "Failed to open connection to qemu:///system\n");
        return 1;
    }
    fprintf(stdout, "Virtualization type: %s\n", virConnectGetType(conn));
    virConnectClose(conn);
    return 0;
}
