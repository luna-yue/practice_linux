#include "TcpServer.hpp"
#include "Servercal.hpp"

Servercal calculator; //计算器


void HandleMess(weak_ptr<Connection>tmp)
{
    if(tmp.expired())
    return;
    auto it=tmp.lock();
    string res= calculator.Cal(it->GetInBuffer());//从输入缓冲区读取处理数据
    if(res.empty())
    return;
    it->GetInBuffer().pop_back();
    it->AddOutBuffer(res);
    it->_send_cb(it);
}
int main()
{
    shared_ptr<TcpServer> p =make_shared<TcpServer>(8888,HandleMess);
    p->Init();
    p->loop();
}