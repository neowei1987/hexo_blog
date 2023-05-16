---
title: 操作系统-自己实现mutex
date: 2022-02-25 10:33:03
updated:
mathjax: true
categories:
tags: 
- 操作系统
---

```cpp
#include <windows.h>
#include <intrin.h>

class Benaphore
{
private:
    LONG m_counter;
    HANDLE m_semaphore;

public:
    Benaphore()
    {
        m_counter = 0;
        m_semaphore = CreateSemaphore(NULL, 0, 1, NULL);
    }

    ~Benaphore()
    {
        CloseHandle(m_semaphore);
    }

    void Lock()
    {
        if (_InterlockedIncrement(&m_counter) > 1) // x86/64 guarantees acquire semantics
        {
            WaitForSingleObject(m_semaphore, INFINITE);
        }
    }

    void Unlock()
    {
        if (_InterlockedDecrement(&m_counter) > 0) // x86/64 guarantees release semantics
        {
            ReleaseSemaphore(m_semaphore, 1, NULL);
        }
    }
};
```

If you port this code to another CPU architecture, such as that in the Xbox 360 or a multicore iOS device, you’ll have to replace the _InterlockedIncrement macro with something which **explicitly guarantees acquire and release semantics**.

支持递归的互斥锁

```cpp
// Define this to {} in a retail build:
#define LIGHT_ASSERT(x) { if (!(x)) DebugBreak(); }
 
class RecursiveBenaphore
{
private:
    LONG m_counter;
    DWORD m_owner;
    DWORD m_recursion;
    HANDLE m_semaphore;
 
public:
    RecursiveBenaphore::RecursiveBenaphore()
    {
        m_counter = 0;
        m_owner = 0;            // an invalid thread ID
        m_recursion = 0;
        m_semaphore = CreateSemaphore(NULL, 0, 1, NULL);
    }
 
    RecursiveBenaphore::~RecursiveBenaphore()
    {
        CloseHandle(m_semaphore);
    }
 
    void Lock()
    {
        DWORD tid = GetCurrentThreadId();
        if (_InterlockedIncrement(&m_counter) > 1) // x86/64 guarantees acquire semantics
        // x86 和 x64 上，_InterlockedIncrement调用会生成一条lock xadd指令，该指令充当完整的内存屏障，保证获取和释放语义
        //此属性是 x86/64 独有的
        {
            if (tid != m_owner)
                WaitForSingleObject(m_semaphore, INFINITE);
        }
        //--- We are now inside the Lock ---
        m_owner = tid;
        m_recursion++;
    }
 
    void Unlock()
    {
        DWORD tid = GetCurrentThreadId();
        LIGHT_ASSERT(tid == m_owner);
        DWORD recur = --m_recursion;
        if (recur == 0)
            m_owner = 0; //先设置为0，再去_InterlockedDecrement
        DWORD result = _InterlockedDecrement(&m_counter); // x86/64 guarantees release semantics
        if (result > 0)
        {
            if (recur == 0)
                ReleaseSemaphore(m_semaphore, 1, NULL);
        }
        //--- We are now outside the Lock ---
    }

    bool TryLock()
    {
        DWORD tid = GetCurrentThreadId();
        if (m_owner == tid)
        {
            // Already inside the lock
            _InterlockedIncrement(&m_counter);
        }
        else
        {
            LONG result = _InterlockedCompareExchange(&m_counter, 1, 0);
            if (result != 0)
                return false;
            //--- We are now inside the Lock ---
            m_owner = tid;
        }
        m_recursion++;
        return true;
    }
};
```
