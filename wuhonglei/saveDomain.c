/*************************************************************************
	> File Name: shutdownDomain.c
	> Author:wuhonglei 
	> Mail:1017368065@qq.com 
	> Created Time: 
    > Description:virDomainSave 将正在运行的虚拟机保存到文件中，保存成功，虚拟机关闭
 ************************************************************************/
#include<stdio.h>
#include<stdlib.h>
#include<libvirt/libvirt.h>

int main(int argc,char *argv[]){
    virConnectPtr conn;
    virDomainPtr dom;
    virDomainInfo info;
    const char *filename = "/var/lib/libvirt/save/centos.img";
    
    conn = virConnectOpen("xen:///");
    if(conn == NULL){
        fprintf(stderr,"Fail to open connection to xen:///\n");
        return 0;
    }
    
    dom = virDomainLookupByName(conn, "centos");
    if(!dom){
        fprintf(stderr,"Cannot find guest to be saved\n");
        return ;
    }
    
    if(virDomainGetInfo(dom,&info)<0){
        fprintf(stderr,"Cannot check guest state\n");
        return ;
    }
    
    if(info.state == VIR_DOMAIN_SHUTOFF){
        fprintf(stderr,"Not saving guest that isn't running\n");
        return ;
    }
    
    if(virDomainSave(dom, filename) < 0){
        fprintf(stderr,"Unable to save guest to %s\n",filename);
    }
    
    fprintf(stderr,"Guest state saved to %s\n",filename);
    
    virDomainFree(dom);
    virConnectClose(conn);
    return 1;
}
