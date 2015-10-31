/*************************************************************************
	> File Name: listDomains.c
	> Author:wuhonglei 
	> Mail:1017368065@qq.com 
	> Created Time: Thu 29 Oct 2015 02:44:55 PM CST
    > Description: 
 ************************************************************************/
#include<stdio.h>
#include<stdlib.h>
#include<libvirt/libvirt.h>

int main(int argc,char *argv[]){
    virConnectPtr conn;
    int i;
    int numDomains;
    int *activeDomains;

    conn = virConnectOpen("xen:///");
    
    numDomains = virConnectNumOfDomains(conn);
    activeDomains = malloc(sizeof(int) * numDomains);
    numDomains = virConnectListDomains(conn, activeDomains, numDomains);
    
    printf("Active domain IDs:\n");
    for (i = 0 ; i < numDomains ; i++) {
        printf("  %d\n", activeDomains[i]);
    }
    
    free(activeDomains);
    virConnectClose(conn);
    return 0;
}
