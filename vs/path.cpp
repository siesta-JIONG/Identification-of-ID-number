#include "path.h"
#include<iostream>

/*
递归搜索指定路径下的所有文件，包括所有子目录中的文件，并将它们的路径存储在向量中。
*/
void getFileNames(string path, vector<string>& files)
{
	intptr_t   hFile = 0;//句柄，用于查找文件
	struct _finddata_t fileinfo;//结构体，存储文件信息
	string p;
	cout << "文件路径" << path << endl;
	//path路径下的所有文件，找到返回非负句柄
	if ((hFile = _findfirst(p.assign(path).append("\\*").c_str(), &fileinfo)) != -1)
	{
		do
		{
			if ((fileinfo.attrib & _A_SUBDIR))//如果当前文件是一个目录
			{
				if (strcmp(fileinfo.name, ".") != 0 && strcmp(fileinfo.name, "..") != 0)
					//cout << "当前文件是一个目录" << p.assign(path).append("\\").append(fileinfo.name) << endl;
					//getFileNames(p.assign(path).append("\\").append(fileinfo.name), files);//再往下一层寻找文件
					cout << "我就是一个条目\n";
			}
			else
			{
				//cout << "当前文件需要被记住：" << p.assign(path).append("\\").append(fileinfo.name) << endl;
				files.push_back(p.assign(path).append("/").append(fileinfo.name));//存储完整路径
			}
		} while (_findnext(hFile, &fileinfo) == 0);//直到全部找完
		_findclose(hFile);
	}
}


