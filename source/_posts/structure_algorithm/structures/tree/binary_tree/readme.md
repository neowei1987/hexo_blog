---
title: 二叉树系列-二叉树常用套路汇总&必知必会
date: 2021-1-13 13:47:03
mathjax: true
categories:
tags: 
---

## 关于二叉树，你一定要知道的

* Q：二叉树遍历

A: 作为图的一种简单形式，树也有两种遍历方式：广度优先、深度优先；广度优先的话，即对应二叉树的按层次遍历；深度优先的话，我们可以按照中间节点的访问顺序， 进一步分为先序遍历（中、左、右）、中序遍历（左、中、右）、后序遍历（左、右、中）。

* Q：二叉树的层次遍历（BFS遍历）

A: 通常我们借助队列（queue)来辅助完成分层遍历。 还有某些情况，我们需要了解到每一个节点的深度（也就是位于第几层）。对于这种要求，我在下面的代码模版中给出了一种解决方案，供参考。

<!-- more -->

* Q：二叉树的常规遍历（DFS遍历）

A: 如前面所讲，常规遍历分为前中后序三种；实现的话，又分为递归版本和迭代版本。具体可以参考下面的代码。

* Q: 二叉树的遍历（前中后序遍历、层次遍历）与图的遍历（DFS、BFS）的联系与区别

A: 联系在于二叉树遍历是图遍历的一种简化形式；区别在于，tree的遍历不需要st来保存访问状态，不需要通过遍历的方式来访问相邻节点，直接通过left、right即可。

* Q: 回溯是什么？回溯一般用递归来实现，那如果有递归，一定会回溯吗？

A: 关于回溯是什么，这里不展开讨论，后续会有专门文章来细讲。

我们尝试着来回答第二个问题：有递归是否一定会有回溯。首先**递归是一种算法结构**，**回溯是一种思想**，一种通过枚举解空间来找到最优解的问题解决套路，两者本质是不同的，自然也就**没有有递归一定有回溯**的说法。

例如，我通过递归来解决斐波那契数列数列的计算问题，$f(n)=f(n-1) + f(n-2)$ ，这里是有递归发生的，但完全不涉及回溯算法中保存现场、还原现场这些概念。

* Q: 为什么二叉树的遍历过程中我感觉不到回溯？

A: 这里我给出的答案是，“感觉不到有两方面原因：第一，感觉不到是由于实际上就没有发生回溯；第二，感觉不到是由于在回溯前后使用的是局部变量，系统自动帮我们进行了现场的保存与还原”。

在遍历二叉树时是否发生回溯，取决于我们解决问题的视角。如果我们是从子问题视角去解决问题，那么我们大概是看不到回溯的影子的。

但如果我们是从遍历整个树的视角去解决问题，那么我们就会看到回溯。

* Q: 二叉树的遍历过程与回溯的联系与区别又是什么？

A: 我们平常在利用回溯求解问题时，会把问题的解空间想像成一个二叉树或者多叉树，整个回溯的过程就是在进行这个树的遍历。

所以要说两者的联系的话，我们可以把二叉树遍历当作是回溯的一种实现形式。回溯的代码写出来，都特别类似于我们在遍历一颗多叉树。

## 二叉树相关的代码模版

图的DFS一般形式

```cpp
    bool st[N]; //表示某一个节点是否访问过
    void dfs(int u) {
        //访问节点u
        st[u] = true;
        for (与节点u相邻的所有节点 x ) {
             if (!st[x]) {
                 dfs(x);
             }
        }
    }
```

多叉树的DFS一般形式（以B树的先序遍历为例）

与上面图的DFS很像，只是没有用st来记录某个节点是否被访问过。这是为什么呢？因为对于树的访问都是从父亲到孩子，从上到下，所以从来不会重复访问到之前访问过的节点，也就没有必要用st来保存访问状态了。

```cpp
    struct TreeNode {
        int val;
        TreeNode* children[N];
    };

    void dfs(TreeNode* root) {
        //访问节点root
        cout << root->val << endl;
        for (child in root->children ) {
            dfs(child);
        }
    }
```

树的DFS一般形式(以先序遍历为例)

```cpp
    struct TreeNode {
        int val;
        TreeNode* left;
        TreeNode* right;
    };
    void dfs(TreeNode* root) {
        //访问节点root
        cout << root->val << endl;
        //对于最常见的二叉树来说，与root相邻的节点只有左、右两个孩子节点，所以就不用for循环了。
        dfs(root->left);
        dfs(root->right);
    }
```

树的BFS一般形式（仅需按照层的顺序访问到每一个节点即可）

```cpp
    void bfs(TreeNode* root) {
        queue<TreeNode*> q;
        q.push(root);
        while (q.size()) {
            auto x = q.front(); q.pop();
            //访问当前节点x
            if (x->left) q.push(x->left);
            if (r->right) q.push(x->right);
        }
    }
```

树的BFS特殊形式（不仅要访问到节点，还要了解到节点的所属层次）

```cpp
    void bfs(TreeNode* root) {
        queue<TreeNode*> q;
        q.push(root);
        while (q.size()) {
            int n = q.size(); //注意这里不可以使用q.size()来代替n
            for (int i = 0; i < n; ++i) {
                auto x = q.front(); q.pop();
                //访问当前节点x
                if (x->left) q.push(x->left);
                if (r->right) q.push(x->right);
            }
        }
    }
```

二叉树的前、中、后序遍历（迭代版本）

```cpp
    void pre_dfs(TreeNode* root) {
        cout << root->val << endl;  //访问节点root
        pre_dfs(root->left);
        pre_dfs(root->right);
    }

    void in_dfs(TreeNode* root) {
        
        cout << root->val << endl;  //访问节点root
        in_dfs(root->left);
        in_dfs(root->right);
    }

    void post_dfs(TreeNode* root) {
        post_dfs(root->left);
        post_dfs(root->right);
        cout << root->val << endl;  //访问节点root
    }
```

二叉树的前、中、后序遍历（统一非迭代版本）

如同递归版本一样，非递归版本的代码形式也是完全一致的，区别仅在于节点的压栈顺序不同，特别容易记忆。

```cpp
    void pre_travel(TreeNode* root) {
        stack<TreeNode*> s;
        s.push(root);

        while (s.size()) {
            auto x = s.top(); s.pop();
            if (x) {
                //由于是前序遍历，所以节点访问序是：中，左，右；又由于是栈（后进先出），所以入栈顺序是：右、左、中
                if (x->right) s.push(x->right);
                if (x->left) s.push(x->left);
                s.push(x);
                s.push(NULL);
            } else {  //前一个指针是null，说明下一个就是要访问的节点
                x = s.top(); s.pop(); 
                cout << x->val << endl;  //访问节点x
            }
        }
    }

    void in_travel(TreeNode* root) {
        stack<TreeNode*> s;
        s.push(root);

        while (s.size()) {
            auto x = s.top(); s.pop();
            if (x) {
                //由于是中序遍历，所以节点访问序是：左，中，右；又由于是栈（后进先出），所以入栈顺序是：右、中、左
                if (x->right) s.push(x->right);
                s.push(x);
                s.push(NULL);
                if (x->left) s.push(x->left);
            } else {  //前一个指针是null，说明下一个就是要访问的节点
                x = s.top(); s.pop(); 
                cout << x->val << endl;  //访问节点x
            }
        }
    }

    void post_travel(TreeNode* root) {
        stack<TreeNode*> s;
        s.push(root);

        while (s.size()) {
            auto x = s.top(); s.pop();
            if (x) {
                //由于是后序遍历，所以节点访问序是：左，右，中；又由于是栈（后进先出），所以入栈顺序是：中、右、左
                s.push(x);
                s.push(NULL);
                if (x->right) s.push(x->right);
                if (x->left) s.push(x->left);
            } else {  //前一个指针是null，说明下一个就是要访问的节点
                x = s.top(); s.pop(); 
                cout << x->val << endl;  //访问节点x
            }
        }
    }

    //不关心访问顺序，仅需要每一个节点能够访问到（也就是前序遍历）
     void no_care_travel(TreeNode* root) {
        stack<TreeNode*> s;
        s.push(root);

        while (s.size()) {
            auto x = s.top(); s.pop();
            if (x) {
                //visit x directly
                if (x->right) s.push(x->right);
                if (x->left) s.push(x->left);
            } 
        }
    }
```

树的深度求解（递归子问题的视角）

如果从**递归子问题的视角**来看，为了求得树的深度，我们需要解决两个子问题：左右子树的深度分别是多少。在解决了这两个子问题之后，总的问题的解就等于 1 + max(left_depth, right_depth) 了。

从这个视角来看，确实是没有回溯发生的。具体代码如下：

```cpp
  int treeDepth(TreeNode* root) {
        if (!root) return 0;
        int left_depth = treeDepth(root->right);
        int right_depth = treeDepth(root->left);
        return 1 + max(left_depth, right_depth);
    }
```

树的深度求解（二叉树遍历的视角）

如果从二叉树遍历的视角来看呢， 我为了求得树的深度，我需要**访问到所有的叶子节点**，并记录下每一个叶子节点的深度，然后与当前的最大深度去比较。

```cpp
class Solution {
public:
    int result;
    void getDepth(TreeNode* node, int depth) {
        result = depth > result ? depth : result; // 中

        if (node->left == NULL && node->right == NULL) return ;

        if (node->left) { // 左
            depth++;    // 深度+1
            getDepth(node->left, depth);
            depth--;    // 回溯，深度-1
        }
        if (node->right) { // 右
            depth++;    // 深度+1
            getDepth(node->right, depth);
            depth--;    // 回溯，深度-1
        }
        return ;
    }
    int maxDepth(TreeNode* root) {
        result = 0;
        if (root == 0) return result;
        getDepth(root, 1);
        return result;
    }
};
```

树的深度求解（二叉树遍历的视角，局部变量隐藏回溯细节）

还是上面的思路，但是下面的写法会更加精简，同时也隐藏了回溯细节，让人感觉不到回溯的存在。

```cpp
class Solution {
public:
    int result;
    void getDepth(TreeNode* node, int depth) {
        result = depth > result ? depth : result; // 中

        if (node->left == NULL && node->right == NULL) return ;

        if (node->left) { // 左
            //注意：这里depth+1作为一个临时变量传给子节点
            getDepth(node->left, depth + 1);
        }
        if (node->right) { // 右
            getDepth(node->right, depth + 1);
        }
        return ;
    }
    int maxDepth(TreeNode* root) {
        result = 0;
        if (root == 0) return result;
        getDepth(root, 1);
        return result;
    }
};
```

## 二叉树相关题目索引

|  题目分类 | 题目名称 |考察点   |其他说明|
|  ----  | ---- |----  |----  |
|二叉树遍历| [获取树的深度](../treeDepth.html)  ||
|二叉树遍历 | [最低公共祖先](../lowest_ancestor.html)  ||
|二叉树遍历| [二叉树镜像](../mirror.html)  ||
|二叉树遍历 | [判断二叉树是否对称](../isSymmetric.html)  ||
|二叉树遍历 | [判定是否平衡树](../isBalanced.html)  ||
|二叉树遍历 | [二叉树子结构](../hasSubtree.html)  ||
|二叉树遍历 | [二叉树的序列化与反序列化](../deserialize.html)  |二叉树遍历|
|二叉树构建 | [根据前序序列与中序序列重建二叉树](pre_in_build.html)  ||
|二叉树层次遍历 | [从上往下打印出二叉树的每个结点](../printFromTopToBottom.html)  ||
|二叉搜索树遍历| [二叉搜索树转有序双向链表](../tree2list.html)  ||
|二叉搜索树遍历 | [获取第k个节点](../kthNode.html)  ||
|二叉搜索树遍历 | [判断该数组是不是某二叉搜索树的后序遍历的结果](../verifySequenceOfBST.html)  ||
|二叉搜索树遍历 | [中序遍历序列的下一个节点](../inorderSuccessor.html)  ||
|二叉树遍历系列 | [二叉树中结点值的和为输入整数的所有路径](../findPathInTree.html)  ||



