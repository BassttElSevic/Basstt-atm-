#include "../Inc/quit.h"
#include <iostream>
#include <string>
#include <windows.h>
using namespace std;

quit::quit(const std::string& cardNumber) : CardNumber(cardNumber) {
    // 构造函数，保存卡号信息
}

void quit::saveAndExit() {
    cout << "正在保存数据..." << endl;
    // 在这个简单的实现中，数据已经在操作过程中实时保存了
    // 如果需要额外的保存操作，可以在这里添加
    Sleep(1000);
    cout << "数据保存成功！" << endl;
    cout << "正在退卡..." << endl;
    Sleep(1000);
    cout << "卡已退出，请取回您的银行卡！" << endl;
    cout << "感谢使用ATM系统,再见!" << endl;
    
    // 退出程序
    exit(0);
}

bool quit::confirmExit() {
    char choice;
    cout << "确定要退出系统吗？(y/n): ";
    cin >> choice;
    
    if (choice == 'y' || choice == 'Y') {
        return true;
    } else {
        return false;
    }
}