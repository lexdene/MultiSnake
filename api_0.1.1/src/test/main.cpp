#include "../request/jrequestlogin.h"

#include <QHostAddress>

int main(){
    JRequestLogin login;
    login.connectToHost(QHostAddress("127.0.0.1"),37373);
    login.login("a","b",ROLE_GAMEDESIGNER);
}