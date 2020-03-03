#ifndef LLSTACK_H
#define LLSTACK_H
//    generic stack defined as a doubly linked list
#include<list>

template<class T>
class LLStack{
public:
    LLStack(){}
    void clear(){
    lst.clear();
    }
    bool isEmpty() const{
        return lst.empty();
    }
    T& topEl(){
        return lst.back();
    }
    T pop(){
        T el = lst.back();
        lst.pop_back();
        return el;
    }
    void push(const T& el){
        lst.push_back(el);
    }
private:
    std::list<T>lst;

};




#endif // LSSTACK_H
