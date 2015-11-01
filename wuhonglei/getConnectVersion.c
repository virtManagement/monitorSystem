/*************************************************************************
	> File Name: getConnectVersion.c
	> Author:wuhonglei 
	> Mail:1017368065@qq.com 
	> Created Time: Sat 31 Oct 2015 11:17:37 AM CST
    > Description:virConnectGetVersion 获取主机虚拟化软件所采用的版本
 ************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <libvirt/libvirt.h>
int main(int argc, char *argv[])
{
    virConnectPtr conn;
    unsigned long ver;
    conn = virConnectOpen("xen:///");
    if (conn == NULL) {
        fprintf(stderr, "Failed to open connection to qemu:///system\n");
        return 1;
    }
    virConnectGetVersion(conn, &ver);
    fprintf(stdout, "Version: %lu\n", ver);
    virConnectClose(conn);
    return 0;
}
