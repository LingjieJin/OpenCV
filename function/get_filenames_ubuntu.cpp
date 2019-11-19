/*
ref:https://blog.csdn.net/lsq2902101015/article/details/51373911


*/

//头文件
#include <iostream>
#include <sys/types.h>
#include <dirent.h>
#include <vector>
#include <string.h>

using namespace std;
 
 
void GetFileNames(string path,vector<string>& filenames)
{
    DIR *pDir;
    struct dirent* ptr;
    if(!(pDir = opendir(path.c_str())))
        return;
    while((ptr = readdir(pDir))!=0) {
        if (strcmp(ptr->d_name, ".") != 0 && strcmp(ptr->d_name, "..") != 0)
            filenames.push_back(path + "/" + ptr->d_name);
    }
    closedir(pDir);
}
 
int main() {
    vector<string> file_name;
    string path = "/home/image";
 
    GetFileNames(path, file_name);
 
    for(int i = 0; i <file_name.size(); i++)
    {
        cout<<file_name[i]<<endl;
    }
 
    return 0;
}