#include "textquery.h"
#include<fstream>
#include<sstream>
#include<iterator>
#include<iostream>
using namespace std;
TextQuery::TextQuery(ifstream &is):file(new vector<string>)
{
    string text;
    while (getline(is, text))
    {
        file->push_back(text);
        int n = file->size() - 1;
        istringstream line(text);
        string word;
        while(line >> word)
        {
            auto &lines = wm[word];
            if (!lines)
                lines.reset(new set<line_no>);
            lines->insert(n);
        }
    }
}

TextQuery::QueryResult::QueryResult(std::string,std::shared_ptr<std::set<line_no>>,std::shared_ptr<std::vector<std::string>>) {}

//QueryResult类嵌套在TextQuery中,下面为QueryResult定义一个静态成员
int TextQuery::QueryResult::static_mem = 1024;

//返回类型必须指明QueryResult是一个嵌套类
TextQuery::QueryResult TextQuery::query(const string &sought) const
{
    //如果我们没有找到sought，则返回set的指针
    static shared_ptr<set<line_no>> nodata(new set<line_no>);
    //使用find而非下标以避免向wm中添加单词
    auto loc = wm.find(sought);
    if(loc==wm.end())
        return QueryResult(sought, nodata, file);
    else
        return QueryResult(sought, loc->second, file);
}

string make_plural(size_t ctr, const string &word, const string &ending)
{
    return (ctr>1) ? word + ending:word;
}
ostream &print(ostream & os, const TextQuery::QueryResult &qr)
{
 os << qr.sought<<"occurs"<<qr.lines->size()<<" "<<make_plural(qr.lines->size(),"time", "s")<<endl;
 for(auto num : *qr.lines)
     //os << "\t(line " << num +1 << ")" << *(qr.file->begin() +num)<< endl;
     os << "\t(line " << num +1 << ")" <<endl;
 return os;

}
