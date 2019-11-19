#include <iostream>
#include <sys/io.h>
#include <string>

using namespace std;

void dir(string path)
{
 long hFile = 0;
 struct _finddata_t fileInfo;
 string pathName, exdName;
 // \\* 代表要遍历所有的类型
 if ((hFile = _findfirst(pathName.assign(path).append("\\*").c_str(), &fileInfo)) == -1) {
  return;
 }
 do 
 {
  //判断文件的属性是文件夹还是文件
  cout << fileInfo.name << (fileInfo.attrib&_A_SUBDIR? "[folder]":"[file]") << endl;
 } while (_findnext(hFile, &fileInfo) == 0);
 _findclose(hFile);
 return;
}


int main()
{
 //要遍历的目录
 string path="E:\\work\\zhidao\\test4";
 dir(path);
 system("pause");
 return 0;
}