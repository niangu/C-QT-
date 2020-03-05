#include <QCoreApplication>
#include<vector>
#include<thread>
#include<functional>

#include"fun.h"
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    /*
    //不使用原子操作，产生竞争形为
    int counter = 0;
    std::vector<std::thread>threads;
    for(int i=0;i<10;++i)
    {
        threads.push_back(std::thread{func,std::ref(counter)});//std::ref按引用传递参数
    }
    for(auto& t:threads){
        t.join();
    }
    std::cout<<"Result="<<counter<<std::endl;

    //使用原子类型，避免线程竞争
    std::atomic<int>counter_2(0);
    std::vector<std::thread>threads_2;
    for(int i=0;i<10;++i){
        threads_2.push_back(std::thread{func_2,std::ref(counter_2)});
    }
    for(auto& t:threads_2)
    {
        t.join();//join只是为了阻塞，实际应用中不需要，可利用其他
    }
    std::cout<<"Result_2="<<counter_2<<std::endl;
    */
    /*
    //在多个线程中并行运行counter()函数，sync_with_stdio(true)保证线程安全的
    std::cout.sync_with_stdio(true);
    std::thread t1(counter,1,6);
    std::thread t2(counter, 2, 4);
    t1.join();
    t2.join();
*/
    /*
    //通过函数对象初始化线程
    //1
    std::cout.sync_with_stdio(true);
    std::thread t1{Counter(1,20)}; //传递构造函数
    //2
    Counter c(2, 12);
    std::thread t2(c);//传递一个实例
    //3
    std::thread t3(Counter(3, 10));//与花括号的区别在于,不能传递没有参数的构造函数，也可以添加额外的圆括号，防止编译器将这行代码解释为函数声明
    //比如：std::thread t3((Counter()))

    //等待线程完成
    t1.join();
    t2.join();
    t3.join();
    */
    /*
    //通过lambda创建线程
    std::cout.sync_with_stdio(true);
    std::thread t1([] (int id,int numIterations)
    {
        for(int i=0;i<numIterations;++i)
        {
            std::cout<<"Counter"<<id<<"has values";
            std::cout<<i<<std::endl;
        }
    },1,5);
    t1.join();
    */
    /*
    //通过成员函数创建线程
    std::cout.sync_with_stdio(true);
    Request req(100);
    std::thread t{&Request::process, &req};//多个线程访问同一个对象，需要注意线程安全
    t.join();
    */
    /*
    //线程本地存储，每个线程共享一个唯一的k副本，而每一个线程都有自己的n副本
    std::thread_local int n;
    int k;
    */
    /*
    //异常处理
    std::cout.sync_with_stdio(true);
    try {
        doWorkInThread();
    } catch (const std::exception &e) {
        std::cout<<"Main function caught:"<<e.what()<<"'"<<std::endl;
    }
    */
    //process();
    /*
    std::cout.sync_with_stdio(true);
    Data d;
    std::thread t1{std::ref(d)};
    std::thread t2{std::ref(d)};
    std::thread t3{std::ref(d)};
    t1.join();
    t2.join();
    t3.join();
    */
    //双重检查锁定
    std::cout.sync_with_stdio(true);
    std::vector<std::thread>threads;
    for(int i=0;i<5;++i)
        threads.push_back(std::thread{func_3});
    for(auto& t:threads)
        t.join();
    return a.exec();
}
