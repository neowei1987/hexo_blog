请用栈实现一个队列，支持如下四种操作：

push(x) – 将元素x插到队尾；
pop() – 将队首的元素弹出，并返回该元素；
peek() – 返回队首元素；
empty() – 返回队列是否为空；
注意：

你只能使用栈的标准操作：push to top，peek/pop from top, size 和 is empty；
如果你选择的编程语言没有栈的标准库，你可以使用list或者deque等模拟栈的操作；
输入数据保证合法，例如，在队列为空时，不会进行pop或者peek等操作；
样例
MyQueue queue = new MyQueue();

queue.push(1);
queue.push(2);
queue.peek();  // returns 1
queue.pop();   // returns 1
queue.empty(); // returns false

```cpp
class MyQueue {
public:
    stack<int> is;
    stack<int> os;
    
    /** Initialize your data structure here. */
    MyQueue() {
        
    }
    
    /** Push element x to the back of queue. */
    void push(int x) {
        is.push(x);
    }
    
    /** Removes the element from in front of queue and returns that element. */
    int pop() {
        if (os.empty()) {
            while (!is.empty()) {
                os.push(is.top());
                is.pop();
            }
        }
        int r = os.top();
        os.pop();
        return r;
    }
    
    /** Get the front element. */
    int peek() {
        if (os.empty()) {
            while (!is.empty()) {
                os.push(is.top());
                is.pop();
            }
        }
        return os.top();
    }
    
    /** Returns whether the queue is empty. */
    bool empty() {
        return is.empty() && os.empty();
    }
};

/**
 * Your MyQueue object will be instantiated and called as such:
 * MyQueue obj = MyQueue();
 * obj.push(x);
 * int param_2 = obj.pop();
 * int param_3 = obj.peek();
 * bool param_4 = obj.empty();
 */
```