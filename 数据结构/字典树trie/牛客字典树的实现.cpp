/*
描述
字典树又称为前缀树或者Trie树，是处理字符串常用的数据结构。
假设组成所有单词的字符仅是‘a’～‘z’，
请实现字典树的结构，并包含以下四个主要的功能。
void insert(String word)：添加word，可重复添加；
void delete(String word)：删除word，如果word添加过多次，仅删除一次；
boolean search(String word)：查询word是否在字典树中出现过(完整的出现过，前缀式不算)；
int prefixNumber(String pre)：返回以字符串pre作为前缀的单词数量。
现在给定一个m，表示有m次操作，每次操作都为以上四种操作之一。
每次操作会给定一个整数op和一个字符串word，op代表一个操作码，
如果op为1，则代表添加word，op为2则代表删除word，
op为3则代表查询word是否在字典树中，op为4代表返回以word为前缀的单词数量
（数据保证不会删除不存在的word）。
*/
#include <string>
#include <iostream>
//using namespace std;
//使用静态数组实现
const int N = 3e5 + 5;
int tree[N][26];
int end[N];
int pass[N];
//cnt记录申请节点的编号
int cnt;
//初始化
void build() {
	cnt = 1;
}

//增
void insert(std::string s) {
	//从头节点开始，首先在头节点+1表示经过了头节点
	//cur表示当前的节点是哪个
	int cur = 1;
	pass[cur]++;
	for (int i = 0; i < s.size(); i++) {
		//path表示下一步的路径
		int path = s[i] - 'a';
		if (tree[cur][path] == 0) {
			//分配新的内存编号
			tree[cur][path] = ++cnt;
		}
		//更新当前的节点
		cur = tree[cur][path];
		//经过下一个位置
		pass[cur]++;
	}
	//遍历完之后，将现在在的节点end值+1
	end[cur]++;
}

//查
int search(std::string s) {
	int cur = 1;
	for (int i = 0; i < s.size(); i++) {
		int path = s[i] - 'a';
		if (tree[cur][path] == 0) {
			return 0;
		}
		cur = tree[cur][path];
	}
	return end[cur];
}

//查询前缀
int prefix(std::string s) {
	int cur = 1;
	for (int i = 0; i < s.size(); i++) {
		int path = s[i] - 'a';
		if (tree[cur][path] == 0) {
			return 0;
		}
		cur = tree[cur][path];
	}
	return pass[cur];
}
//删
void delete1(std::string s)
{
	if (search(s) > 0)
	{
		//记得将头节点-1
		pass[1]--;
		int cur = 1;
		for (int i = 0; i < s.size(); i++)
		{
			int path = s[i] - 'a';
			if (pass[tree[cur][path]] - 1 == 0)
			{
				pass[tree[cur][path]]--;
				tree[cur][path] = 0;
				return;
			}
			pass[tree[cur][path]]--;
			cur = tree[cur][path];
		}
		end[cur]--;
	}
}

//清空数组，避免数据污染
void clear() {
	for (int i = 1; i <= cnt; i++) {
		//因为我们最多用了cnt行
		memset(tree[i], 0, 26);
		end[i] = 0;
		pass[i] = 0;
	}
}
int main() {
	int m;
	std::cin >> m;
	build();
	while (m--) {
		int op;
		std::cin >> op;
		std::string s;
		std::cin >> s;
		if (op == 1) {
			insert(s);
		}
		else if (op == 2) {
			delete1(s);
		}
		else if (op == 3) {
			if (search(s) > 0) {
				std::cout << "YES" << '\n';
			}
			else std::cout << "NO" << '\n';
		}
		else {
			std::cout << prefix(s) << '\n';
		}
	}
	return 0;
}