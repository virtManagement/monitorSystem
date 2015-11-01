/*************************************************************************
	> File Name: getLibVersion.c
	> Author:wuhonglei 
	> Mail:1017368065@qq.com 
	> Created Time: Sat 31 Oct 2015 11:23:15 AM CST
    > Description:virConnectGetLibVersion 获取主机上使用的libvirt软件版本
 ************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <libvirt/libvirt.h>
int main(int argc, char *argv[])
{
    virConnectPtr conn;
    unsigned long ver;
    conn = virConnectOpen("qemu:///system");
    if (conn == NULL) {
        fprintf(stderr, "Failed to open connection to qemu:///system\n");
        return 1;
    }
    virConnectGetLibVersion(conn, &ver);
    fprintf(stdout, "Libvirt Version: %lu\n", ver);
    virConnectClose(conn);
    return 0;
}
