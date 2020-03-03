#ifndef TEXTQUERY_H
#define TEXTQUERY_H

#include<iostream>
#include<vector>
#include<memory>
#include<map>
#include<set>
//嵌套类
class TextQuery
{
public:
    class QueryResult;
    using line_no = std::vector<std::string>::size_type;
    TextQuery(std::ifstream&);
    QueryResult query(const std::string&) const;
private:
    std::shared_ptr<std::vector<std::string>> file; //输入文件
    //每个单词到它所在行号的集合的映射
    std::map<std::string, std::shared_ptr<std::set<line_no>>> wm;
};
//QueryResult是TextQuery的成员，下面的代码负责定义QueryResult
class TextQuery::QueryResult{
    //位于类的作用域内，因此我们不必对QueryResult形参进行限定
    friend std::ostream& print(std::ostream&, const QueryResult&);
public:
    //无需定义QueryResult::line_no
    //嵌套类可以可以直接使用外层类的成员，无需对该成员的名字进行限定
    QueryResult(std::string,std::shared_ptr<std::set<line_no>>,std::shared_ptr<std::vector<std::string>>);
    static int static_mem;
private:
    std::string sought;
    std::shared_ptr<std::set<line_no>> lines;
    std::shared_ptr<std::vector<std::vector<std::string>>> file;
};

#endif // TEXTQUERY_H
