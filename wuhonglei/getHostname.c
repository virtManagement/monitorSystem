/*************************************************************************
	> File Name: getHostname.c
	> Author:wuhonglei 
	> Mail:1017368065@qq.com 
	> Created Time: Sat 31 Oct 2015 10:35:33 AM CST
    > Description:virConnectGetHostname 获得主机(Dom0)的名字
 ************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <libvirt/libvirt.h>
int main(int argc, char *argv[])
{
    virConnectPtr conn;
    char *host;
    conn = virConnectOpen("xen:///");
    if (conn == NULL) {
        fprintf(stderr, "Failed to open connection to xen:///\n");
        return 1;
    }
    host = virConnectGetHostname(conn);
    fprintf(stdout, "Hostname:%s\n", host);
    free(host);
    virConnectClose(conn);
    return 0;
}
