#include<iostream>
#include"Protocol.hpp"
enum{
    div_zero=1,
    mod_zero,
    wrong_oper,
    wrong_package 
};
class Servercal{
    public:
    string Cal( string&package)
    {
        //cout<<"package:"<<package<<endl;
        string content;
        if(!decode(package,&content))
        {
            //lg(Error,"wrong package");
            return "";
        }
        request req;
        if(!req.Deserialize(content))
        {
            lg(Error,"Deserialize failed");
            return "";
        }
        response res;
        res.code=0;
        if(req.op=='+')
        {
           res.result=req.x+req.y;
        }
        else if(req.op=='-')
        {
            res.result=req.x-req.y;
        }
        else if(req.op=='*')
        {
            res.result=req.x*req.y;
        }
        else if(req.op=='/')
        {
            if(req.y==0)
            res.code=div_zero;
            else
            res.result=req.x/req.y;
        }
        else
        res.code=wrong_oper;
    //cout<<res.result<<"result  "<<res.code<<"code "<<req.x<<" "<<req.op<<" "<<req.y<<endl;
    content.clear();
        res.Serialize(&content);
        
        content=encode(content);
        //cout<<content<<endl;
        return content;
    }
};