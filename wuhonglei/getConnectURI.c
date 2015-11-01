/*************************************************************************
	> File Name: getConnectURI.c
	> Author:wuhonglei 
	> Mail:1017368065@qq.com 
	> Created Time: Sat 31 Oct 2015 11:39:49 AM CST
    > Description:virConnectGetURI 获得当前连接的URI  
 ************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <libvirt/libvirt.h>
int main(int argc, char *argv[])
{
    virConnectPtr conn;
    char *uri;
    conn = virConnectOpen("xen:///");
    if (conn == NULL) {
        fprintf(stderr, "Failed to open connection to qemu:///system\n");
        return 1;
    }
    uri = virConnectGetURI(conn);
    fprintf(stdout, "Canonical URI: %s\n", uri);
    free(uri);
    virConnectClose(conn);
    return 0;
}
