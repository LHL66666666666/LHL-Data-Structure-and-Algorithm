//给定一个只包含大写字母的字符串
//S, 请你输出其中出现次数最多的字符。
//如果有多个字母均出现了最多次, 按字母表顺序依次输出所有这些字母。
#include <iostream>
#include <cstdio>
#include <string>
using namespace std;
int arr[30];
int main()
{
	string s;
	cin >> s;
	int n = s.size();
	for (int i = 0; i < n; i++)
	{
		int h = s[i] - 'A';
		arr[h]++;
	}
	int max = arr[0];
	for (int i = 0; i < 26; i++)
	{
		if (arr[i] > max)
		{
			max = arr[i];
		}
	}
	for (int i = 0; i < 26; i++)
	{
		if (arr[i] == max)
		{
			printf("%c",i+'A');
		}
	}
	return 0;
}