输入一棵二叉树前序遍历和中序遍历的结果，请重建该二叉树。

注意:

二叉树中每个节点的值都互不相同；
输入的前序遍历和中序遍历一定合法；
样例
给定：
前序遍历是：[3, 9, 20, 15, 7]
中序遍历是：[9, 3, 15, 20, 7]

返回：[3, 9, 20, null, null, 15, 7, null, null, null, null]
返回的二叉树如下所示：
3
/ \
9  20
/  \
15   7

```cpp
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
public:
    map<int, int> hash;
    vector<int> preorder;
    vector<int> inorder;
    
    TreeNode* dfs(int pl, int pr, int il, int ir)
     {
         if (pl > pr) return NULL;
         
         auto root = new TreeNode(preorder[pl]);
         //借助hash，避免扫描
         int k = hash[root->val];
         
         auto left = dfs(pl + 1, pl + k - il, il, k - 1);
         auto right = dfs(pl + k - il + 1, pr, k + 1, ir);
         
         root->left = left; 
         root->right = right;
         return root;
     }
     
    
    TreeNode* buildTree(vector<int>& _preorder, vector<int>& _inorder) {
        preorder = _preorder;
        inorder = _inorder;
        
        for (int i = 0; i < inorder.size(); ++i) hash[inorder[i]] = i;
        
        return dfs(0, preorder.size() - 1, 0, inorder.size() - 1);
    }
};
```