#ifndef UTIL_IO_H
#define UTIL_IO_H

namespace util {

// 关闭文件描述符, 失败则打印错误信息, 以 EXIT_FAILURE 退出
void Close(int fd);

}


#endif
