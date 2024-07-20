#include <io.h>//文件操作
#include <string>
#include <vector>
using namespace std;

void getFileNames(string path, vector<string>& files);
/*
递归地获取给定路径下的所有文件名，并将这些文件名存储在一个 vector<string> 容器中

递归搜索指定路径下的所有文件，包括所有子目录中的文件，并将它们的路径存储在向量中。
*/