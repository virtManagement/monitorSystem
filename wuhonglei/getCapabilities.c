/*************************************************************************
	> File Name: ex8.c
	> Author:tangjie 
	> Mail:824647349@qq.com 
	> Created Time: Tue 27 Oct 2015 08:50:26 PM CST
    > compile with: gcc ex8.c -o ex8 -lvirt
    >Description:viriConnectGetCapabilities,获得关于主机和虚拟机性能相关的性能参数并以xml形式呈现出来
 ************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <libvirt/libvirt.h>
int main(int argc, char *argv[])
{
    virConnectPtr conn;
    char *caps;

    conn = virConnectOpen("xen:///");
    if (conn == NULL) {
        fprintf(stderr, "Failed to open connection to qemu:///system\n");
        return 1;
    }
    caps = virConnectGetCapabilities(conn);
    fprintf(stdout, "Capabilities:\n%s\n", caps);
    free(caps);

    virConnectClose(conn);
    return 0;
}



