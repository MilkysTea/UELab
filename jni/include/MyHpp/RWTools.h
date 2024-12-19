//
// Created by Milky_Tea on 2024/12/19.
//

#ifndef RWTOOLS_H
#define RWTOOLS_H
#include <syscall.h>
#include "VectorStruct.h"
#include <cstdio>
#include <unistd.h>
#include <cstddef>
#include <fcntl.h>
#include <string>
uintptr_t libUE4,UWorld,Matrixaddr,Actor,APawn;
float px,py;
float Matrix[16];
int ActorCount;
int pid = -1;

//获取进程
int GetPid(const char *processName){
    FILE *fp;
    char command[0x100] = "pidof ";
    strcat(command, processName);
    fp = popen(command, "r");
    fscanf(fp, "%d", &pid);
    pclose(fp);
    return pid;
}

unsigned long get_module_base(int pid, const char *module_name) {
    FILE *fp;
    unsigned long addr = 0;
    char *pch;
    char filename[64];
    char line[1024];
    snprintf(filename, sizeof(filename), "/proc/%d/maps", pid);
    fp = fopen(filename, "r");
    if (fp != NULL) {
        while (fgets(line, sizeof(line), fp)) {
            if (strstr(line, module_name)) {
                pch = strtok(line, "-");
                addr = strtoul(pch, NULL, 16);
                if (addr == 0x8000)
                    addr = 0;
                break;
            }
        }
        fclose(fp);
    }
    return addr;
}

bool pvm(void *address, void *buffer, size_t size, bool iswrite) {
    struct iovec local[1];
    struct iovec remote[1];
    local[0].iov_base = buffer;
    local[0].iov_len = size;
    remote[0].iov_base = address;
    remote[0].iov_len = size;
    if (pid < 0) {
        return false;
    }
    ssize_t bytes = syscall(SYS_process_vm_readv, pid, local, 1, remote, 1, 0);
    // if (bytes == -1) {
    //     perror("Error in process_vm_writev");
    //     return false;
    // }

    return bytes == size;
}

bool vm_read(unsigned long address, void *buffer, size_t size) {
    return pvm(reinterpret_cast < void *>(address), buffer, size, false);
}

bool vm_write(unsigned long address, void *buffer, size_t size) {
    return pvm(reinterpret_cast < void *>(address), buffer, size, true);
}

template<typename T>
T Read(uintptr_t addr) {
    T buf;
    vm_read(addr, &buf, sizeof(buf));
    return buf;
}

template<typename T>
void Write(uintptr_t addr, const T &value) {
    vm_write(addr, &value, sizeof(T));
}

#endif //RWTOOLS_H
