给出一个长度为 n 的，仅包含字符 '(' 和 ')' 的字符串，计算最长的格式正确的括号子串的长度。

例1: 对于字符串 "(()" 来说，最长的格式正确的子串是 "()" ，长度为 2 .
例2：对于字符串 ")()())" , 来说, 最长的格式正确的子串是 "()()" ，长度为 4 .

```cpp
class Solution {
public:
    int longestValidParentheses(string str) {
        stack<int> s;
        s.push(-1); 
        int res = 0;

        for (int i = 0; i < str.length(); ++i) {
            if (str[i] == '(') {
                s.push(i);
            } else { //')'
                s.pop();
                if (s.empty()) { //新的开始, 不匹配的“)”
                    s.push(i);
                } else {
                    res = max(res, i - s.top());
                }
            }
        }

        return res;
    }
};
```