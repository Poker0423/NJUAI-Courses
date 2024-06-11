#include <iostream>
#include <cstring>
using namespace std;
int main()
{
    int flag = 0;
    char arr[100] = { 0 };
    char str[100] = { 0 };
    cin.getline(arr, sizeof(arr));
    cin.getline(str, sizeof(str));//有空格必须这样操作 

    int leng_arr = strlen(arr);//strlen得到的长度是输入字符串的长度，不是数组原长度
    int leng_str = strlen(str);

    for (int i = 0; i < leng_arr; i++)
    {
        if (arr[i] == str[0])
        {
            flag = 1;
            for (int j = 1; j < leng_str; j++)
            {
                if (arr[i + j] != str[j])//判断后续字符串是否相同
                    flag = -1;
            }
            if (flag == 1)//已找到子串，开始父串中删除子串操作
            {
                for (int j = i; j < leng_arr; j++)
                {
                    arr[j] = arr[j + leng_str];//间隔一个子串的长度依次替换
                }
                leng_arr -= leng_str;//子串已删除，父串长度缩短，无需再遍历后续多余字符（这一步可以省略）
                i = -1;//循环完成后会i++，让i变为0，从头开始遍历，因为删除子串后可能会出现新的子串(精髓） 
            }
        }
    }
    cout << arr << endl;
    return 0;
}
