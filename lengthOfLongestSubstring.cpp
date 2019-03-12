#include "pch.h"
#include <iostream>
#include <string>
#include <set>
#include <unordered_set>
#include <unordered_map>
#include <algorithm>

using namespace std;

int lengthOfLongestSubstring_string(string s) 
{
	string str;
	int longest = 0;
	for (int i = 0; i < s.length(); i++)
	{
		str.clear();
		int l = 0;
		for (int j = i; j >= 0; j--)
		{
			if (str.find(s[j]) != string::npos)
				break;
			str.push_back(s[j]);
			++l;
			if (longest < l)
				longest = l;
		}
	}
	return longest;
}

//  竟然比用string做缓存查慢
int lengthOfLongestSubstring_set(string s)
{
	unordered_set<char> sc;  // 网站上测试中unordered_set比set更快更省内存
	int longest = 0;
	for (int i = 0; i < s.length(); i++)
	{
		sc.clear();
		int l = 0;
		for (int j = i; j >= 0; j--)
		{
			// 更慢
			//pair<set<char>::iterator, bool> r = sc.emplace(s[j]);
			//if (!r.second)
			//	break;
			if (sc.find(s[j]) != sc.end())
				break;
			sc.emplace(s[j]);
			++l;
			if (longest < l)
				longest = l;
		}
	}
	return longest;
}

// 滑动窗口
int lengthOfLongestSubstring_slidewindow(string s)
{
	unordered_set<char> sc;
	size_t longest = 0;
	int i = 0, j = 0;
	while (j < s.length())
	{
		if (sc.find(s[j]) == sc.end())
		{
			sc.emplace(s[j++]);
			longest = max(longest, sc.size());
		}
		else
		{
			while (s[i] != s[j])
			{
				sc.erase(s[i]);
				++i;
			}
			++i;
			++j;
		}
	}
	return longest;
}

// 优化的滑动窗口,使用map
/*上述的方法最多需要执行 2n 个步骤。事实上，它可以被进一步优化为仅需要 n 个步骤。我们可以定义字符到索引的映射，而不是使用集合来判断一个字符是否存在。 当我们找到重复的字符时，我们可以立即跳过该窗口。
也就是说，如果 s[j]s[j] 在[i, j)[i, j) 范围内有与 j&#x27; j′重复的字符，我们不需要逐渐增加 ii 。 我们可以直接跳过[i，j&#x27; ][i，j′] 范围内的所有元素，并将 ii 变为 j&#x27; +1j′+ 1。*/
int lengthOfLongestSubstring_map(string s)
{
	unordered_map<char, int> mc;
	int longest = 0;
	int len = s.length();
	unordered_map<char, int>::iterator it;	// 使用iterator的我的版本比示例中的再稍微优化了一点
	for (int i = 0, j = 0; j < len; ++j)
	{
		it = mc.find(s[j]);
		if (it != mc.end())
		{
			// 最关键的是理解这一句，因为虽然有可能在map中找到该值，但该值可能在窗口之前，所以使用是否大于i来判断是否在窗口，
			// 如果是，则使用该值出现的索引+1，来定义新的窗口，而不用像上一个函数那样i不断+1来滑动窗口，这里一次就滑到位，所以效率更高一些
			i = max(it->second, i);		
			it->second = j + 1;
		}
		else
			mc[s[j]] = j + 1;	// 还有这一句，这里如果不+1也可以，在上面i的判断的地方+1
		longest = max(longest, j - i + 1);	// 窗口的大小使用j和i的差来确定，而非使用集合或者map的大小来确定
	}
	return longest;
}

int lengthOfLongestSubstring(string s)
{
	int index[128] = { 0 };
	int longest = 0;
	int len = s.length();
	for (int i = 0, j = 0; j < len; ++j)
	{
		i = max(index[s[j]], i);
		index[s[j]] = j + 1;	// 还有这一句，这里如果不+1也可以，在上面i的判断的地方+1
		longest = max(longest, j - i + 1);	// 窗口的大小使用j和i的差来确定，而非使用集合或者map的大小来确定
	}
	return longest;
}

int mainlong()
{
	//string s = "pwwkew";
	//string s = "abcabcbb";
	//string s = "abba";
	string s = "aabaab!bb";


	std::cout << lengthOfLongestSubstring(s) << endl;

	return 0;
}
