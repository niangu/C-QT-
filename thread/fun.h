#ifndef FUN_H
#define FUN_H
#include<atomic>
#include<iostream>
#include<thread>
#include<mutex>
void func(int& counter)
{
    for(int i=0;i<10000;++i)
    {
        ++counter;
    }
}

void func_2(std::atomic<int>& counter)
{
    for(int i=0;i<10000;++i)
    {
        ++counter;
    }
}

void counter(int id,int numIterations)
{
    for(int i=0;i<numIterations;++i){
        std::cout<<"Counter"<<id<<"has value";
        std::cout<<i<<std::endl;
    }
}
/*                                 异常处理                                   */
/*
exception_ptr current_exception() noexcept;返回对象引用目前正在处理的异常，或者目前正在处理异常的副本
void rethrow_exception(exception_ptr p);重新抛出异常
exception_ptr make_exception_ptr(E e) noexcept;
*/
void doSomeWork() throw(std::runtime_error)
{
    for(int i=0;i<5;++i)
        std::cout<<i<<std::endl;
    std::cout<<"Thread throwing a runtime_error exception..."<<std::endl;
    throw std::runtime_error("Exception from thread");
}

void threadFunc(std::exception_ptr& err)
{
    try {
        doSomeWork();
    } catch (...) {
        std::cout<<"Thread caught exception, returning exception..."<<std::endl;
        err=std::current_exception();//获得正在被处理异常的引用，然后赋值给exception_ptr参数
    }
}

void doWorkInThread() throw(std::runtime_error)
{
    std::exception_ptr error;
    std::thread t{threadFunc,std::ref(error)};
    t.join();
    if(error)
    {
        std::cout<<"Main thread received exception,rethrowing it..."<<std::endl;
        std::rethrow_exception(error);//通过在主线程中重新抛出异常，异常已经从一个线程转移到另一个线程
    }
    else
        std::cout<<"Main thread did not receive any exception."<<std::endl;
}
/*                                异常处理                                          */

std::mutex mut1;
std::mutex mut2;
void process()
{
    std::unique_lock<std::mutex> lock1(mut1, std::defer_lock_t());//第二个参数告诉unique_lock不要在构造期间获得锁
    std::unique_lock<std::mutex> lock2(mut2, std::defer_lock_t());
    std::lock(lock1,lock2);//获得俩个锁，总是以这样的顺序在所有线程中调用lock()不会导致任何死锁
    //像这样lock(lock2,lock1);可能产生死锁
}
//结合std::call_once()和std::once_flag可以确保某个函数或方法正好只被调用一次，不论有多少个线程试图调用call_once()
class Data
{
public:
    void operator()()
    {
        std::call_once(mOnceFlag,&Data::init,this);
        std::cout<<"Work"<<std::endl;
    }
protected:
    void init()
    {
        std::cout<<"init()"<<std::endl;
        mMemory=new char[24];
    }
    mutable std::once_flag mOnceFlag;
    mutable char* mMemory;
};

class Counter
{
public:
    Counter(int id, int numIterations):mId(id),mNumIterations(numIterations)
    {

    }
    void operator()()const
    {
        for(int i=0;i<mNumIterations;++i)
        {
            std::cout<<"Counter"<<mId<<"has value";
            std::cout<<i<<std::endl;
        }
    }
protected:
    int mId;
    int mNumIterations;
};

class Request
{
public:
    Request(int id):mId(id){}
    void process()
    {
        std::cout<<"Processing request"<<mId<<std::endl;
    }

protected:
   int mId;
};

//以线程安全的方式写入流
class Counter_2
{
public:
    Counter_2(int id, int numIterations):mId(id),mNumIterations(numIterations)
    {}
    void operator()()const
    {
        for(int i=0;i<mNumIterations; ++i){
            std::lock_guard<std::mutex>lock(mMutex);
            std::cout<<"Counter"<<mId<<"has value";
            std::cout<<i<<std::endl;
        }
    }
protected:
    int mId;
    int mNumIterations;
    static std::mutex mMutex;
};
std::mutex Counter_2::mMutex;
//使用定时锁
class Counter_3
{
public:
    Counter_3(int id,int numIterations):mId(id),mNumIterations(numIterations)
    {}
    void operator()()const
    {
        for(int i=0;i<mNumIterations;++i)
        {
            std::unique_lock<std::timed_mutex>lock(mTimedMutex,std::chrono::milliseconds(200));
            if(lock)
            {
                std::cout<<"Counter"<<mId<<"has value";
                std::cout<<i<<std::endl;
            }else{
                //Lock not acquired in 2- ms
            }
        }
    }
protected:
    int mId;
    int mNumIterations;
    static std::timed_mutex mTimedMutex;
};
std::timed_mutex Counter_3::mTimedMutex;

//双重检查锁定
class MyClass
{
public:
    void init(){std::cout<<"Init"<<std::endl;}
};
MyClass var;
bool initialized = false;
std::mutex mut;
void func_3()
{
    if(!initialized){//防止获得一个不需要获得的锁
        std::unique_lock<std::mutex>lock(mut);
        if(!initialized)//确保没有其他线程在第一次initialized检查和获得锁之间执行初始化
        {
            var.init();
            initialized=true;
        }
    }
    std::cout<<"OK"<<std::endl;
}

#endif // FUN_H
