二叉树的路径打印

```
bool find(node* r, node* target)
{
    stack.push(r); //把当前节点压入栈中
    if (r == target)
    {
        return true;
    }
    else
    {
        if (r->left)
        {
            if (find(r->left, target))
            {
            return true;
            }
        else
        {
            stack.pop(); //如果在左子树种没有找到，则出栈复原路径
        }
    }

    if (r->right)
    {
        if (find(r->right, target))
        {
        return true;
        }
        else
        {
            stack.pop();//如果在右子树种没有找到，则出栈复原路径
        }
    }
    {
    return false;
    }
}
```
stack遍历出来既是路径~