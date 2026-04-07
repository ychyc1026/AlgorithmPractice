#include <iostream>
#include <string>
#include <vector>
using namespace std;

// 第一步：求next数组（核心：计算模式串每个位置的最长相等前后缀长度）
void getNext(string pat, vector<int>& next) {
    int n = pat.size();
    next.resize(n, 0);  // next数组初始化，默认值为0
    int j = 0;  // j指向前缀的末尾（同时表示当前最长相等前后缀长度）
    
    // i指向后缀的末尾，从1开始（i=0时，前后缀长度为0）
    for (int i = 1; i < n; i++) {
        // 前后缀不相等，j回退（利用已算好的next数组，避免重复计算）
        while (j > 0 && pat[i] != pat[j]) {
            j = next[j - 1];
        }
        // 前后缀相等，j++，更新当前最长相等前后缀长度
        if (pat[i] == pat[j]) {
            j++;
        }
        // 赋值next[i]，即前i+1个字符的最长相等前后缀长度
        next[i] = j;
    }
}

// 第二步：KMP匹配（主串指针永不回退）
int kmpMatch(string txt, string pat) {
    int m = txt.size();
    int n = pat.size();
    if (n == 0) return 0;
    
    vector<int> next;
    getNext(pat, next);
    
    int i = 0;  // 主串指针，只增不减
    int j = 0;  // 模式串指针
    while (i < m) {
        // 字符匹配，双指针同时后移
        if (txt[i] == pat[j]) {
            i++;
            j++;
        }
        // 匹配成功：j遍历完模式串，返回起始位置
        if (j == n) {
            return i - j;  // 起始位置 = 主串当前位置 - 模式串长度
        }
        // 失配：j根据next数组回退，i不回退
        else if (i < m && txt[i] != pat[j]) {
            // j != 0，回退到上一个最长相等前后缀的位置
            if (j != 0) {
                j = next[j - 1];
            }
            // j == 0，无法回退，主串后移
            else {
                i++;
            }
        }
    }
    // 未匹配成功
    return -1;
}

// 测试函数
int main() {
    // 测试用例1：模式串有最长相等前后缀（abcabc）
    string txt1 = "abcabcdefg";
    string pat1 = "abcabc";
    // 测试用例2：模式串无明显前后缀（abcabxabcaby）
    string txt2 = "abcabxabcaby123";
    string pat2 = "abcabxabcaby";
    // 测试用例3：极端情况（主串全为a，模式串全为aa）
    string txt3 = "aaaaaaa";
    string pat3 = "aaa";
    
    int res1 = kmpMatch(txt1, pat1);
    int res2 = kmpMatch(txt2, pat2);
    int res3 = kmpMatch(txt3, pat3);
    
    cout << "测试用例1:" << (res1 != -1 ? "匹配成功，起始位置：" + to_string(res1) : "匹配失败") << endl;
    cout << "测试用例2:" << (res2 != -1 ? "匹配成功，起始位置：" + to_string(res2) : "匹配失败") << endl;
    cout << "测试用例3:" << (res3 != -1 ? "匹配成功，起始位置：" + to_string(res3) : "匹配失败") << endl;
    
    return 0;
}