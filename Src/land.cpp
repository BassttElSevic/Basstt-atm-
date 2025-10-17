#include "../Inc/land.h"
#include <iostream>
#include <string>
using namespace std;

land::land() : loginAttempts(0) {
    // 初始化登录尝试次数
}

void land::CardNumber_input() {
    cout << "请输入卡号：";
    cin >> CardNumberInput;
}

void land::password_input() {
    cout << "请输入密码：";
    cin >> passwordInput;
}

bool land::login() {
    // 使用数据库模块验证卡号和密码
    AccountDatabase db;
    bool isAuthenticated = db.verifyPassword(CardNumberInput, passwordInput);
    
    if (!isAuthenticated) {
        loginAttempts++;
        if (loginAttempts >= 3) {
            cout << "密码错误次数过多，卡号已被锁定！" << endl;
            return false;
        } else {
            cout << "密码错误，您还有 " << (3 - loginAttempts) << " 次机会" << endl;
            return false;
        }
    } else {
        cout << "登录成功！欢迎 " << db.get_account_info(CardNumberInput).name << "!" << endl;
        return true;
    }
}

void land::passwordforget() {
    cout << "请联系当地银行客服修改密码" << endl;
}

std::string land::getCardNumber() {
    return CardNumberInput;
}