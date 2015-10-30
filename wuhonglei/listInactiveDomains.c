/*************************************************************************
	> File Name: listInactiveDomains.c
	> Author:wuhonglei 
	> Mail:1017368065@qq.com 
	> Created Time: Thu 29 Oct 2015 05:36:32 PM CST
    > Description: 
 ************************************************************************/
#include<stdio.h>
#include<stdlib.h>
#include<libvirt/libvirt.h>

int main(int argc,char *argv[]){
    virConnectPtr conn;
    int i;
    int numDomains;
    char **inactiveDomains;

    conn == virConnectOpen("xen:///");
    numDomains = virConnectNumOfDefinedDomains(conn);
    inactiveDomains = malloc(sizeof(char *) * numDomains);
    numDomains = virConnectListDefinedDomains(conn, inactiveDomains, numDomains);
    
    printf("Inactive domain names:\n");
    for (i = 0 ; i < numDomains ; i++) {
        printf("  %s\n", inactiveDomains[i]);
        free(inactiveDomains[i]);
    }
    free(inactiveDomains);
    
    virConnectClose(conn);
    return 0;
}


