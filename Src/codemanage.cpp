#include "../Inc/codemanage.h"
#include <iostream>
#include <string>
using namespace std;

codemanage::codemanage(const std::string& cardNumber) : CardNumber(cardNumber) {
    // 构造函数，保存卡号信息
}

// 实现DataQuery接口
AccountInfo codemanage::get_account_info(const std::string& CardNumber) {
    AccountDatabase db;
    return db.get_account_info(CardNumber);
}

double codemanage::getBalance(const std::string& CardNumber) {
    AccountDatabase db;
    return db.getBalance(CardNumber);
}

bool codemanage::verifyPassword(const std::string& CardNumber, const std::string& password) {
    AccountDatabase db;
    return db.verifyPassword(CardNumber, password);
}

// 实现DataUpdate接口
bool codemanage::updateBalance(const std::string& CardNumber, double balance) {
    AccountDatabase db;
    return db.updateBalance(CardNumber, balance);
}

bool codemanage::changePassword(const std::string& CardNumber, const std::string& new_password) {
    AccountDatabase db;
    return db.changePassword(CardNumber, new_password);
}

// 密码管理特定功能
bool codemanage::verifyCurrentUserPassword(const std::string& password) {
    // 验证当前用户输入的密码是否正确
    AccountDatabase db;
    return db.verifyPassword(CardNumber, password);
}

bool codemanage::changeUserPassword(const std::string& old_password, const std::string& new_password, const std::string& confirm_password) {
    // 首先验证旧密码是否正确
    if (!verifyCurrentUserPassword(old_password)) {
        cout << "原密码错误！" << endl;
        return false;
    }
    
    // 检查新密码和确认密码是否一致
    if (new_password != confirm_password) {
        cout << "新密码与确认密码不一致！" << endl;
        return false;
    }
    
    // 检查新密码长度是否为6位
    if (new_password.length() != 6) {
        cout << "密码必须为6位数字！" << endl;
        return false;
    }
    
    // 检查新密码是否全为数字
    for (char c : new_password) {
        if (!isdigit(c)) {
            cout << "密码必须为6位数字！" << endl;
            return false;
        }
    }
    
    // 更新密码
    AccountDatabase db;
    if (db.changePassword(CardNumber, new_password)) {
        cout << "密码修改成功！" << endl;
        return true;
    } else {
        cout << "密码修改失败！" << endl;
        return false;
    }
}
