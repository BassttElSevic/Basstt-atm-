#include"../Inc/database.h"
#include<iostream>
#include<string>
#include<vector>

// 定义静态成员变量
std::vector<AccountInfo> AccountDatabase::account_info;

// 初始化数据库
void AccountDatabase::init() {
    if (account_info.empty()) {
        initializeTestData();
    }
}

// 初始化测试数据 - 私有方法
void AccountDatabase::initializeTestData() {
    account_info.push_back(AccountInfo("1234567890123456", "123456", "张三", 10000.0));
    account_info.push_back(AccountInfo("1234567890123457", "654321", "李四", 10000.0));
    account_info.push_back(AccountInfo("1234567890123458", "111111", "王五", 10000.0));
    account_info.push_back(AccountInfo("1234567890123459", "000000", "赵六", 10000.0));
    account_info.push_back(AccountInfo("1234567890123460", "999999", "钱七", 10000.0));
    account_info.push_back(AccountInfo("1145141919810", "114514", "田所浩二", 10000.0));
}

// 实现数据查询接口
AccountInfo AccountDatabase::get_account_info(const std::string& CardNumber) {
    // 确保数据已初始化
    if (account_info.empty()) {
        initializeTestData();
    }
    
    for(const auto& account : account_info) {
        if(account.CardNumber == CardNumber) {
            return account;
        }
    }
    // 如果未找到匹配的账号，返回一个默认的AccountInfo对象
    return AccountInfo("", "", "", 0.0);
}

double AccountDatabase::getBalance(const std::string& CardNumber) {
    // 确保数据已初始化
    if (account_info.empty()) {
        initializeTestData();
    }
    
    for(const auto& account : account_info) {
        if(account.CardNumber == CardNumber) {
            return account.balance;
        }
    }
    return -1.0; // 返回-1表示未找到账户
}

bool AccountDatabase::verifyPassword(const std::string& CardNumber, const std::string& password) {
    // 确保数据已初始化
    if (account_info.empty()) {
        initializeTestData();
    }
    
    for(const auto& account : account_info) {
        if(account.CardNumber == CardNumber) {
            return account.password == password;
        }
    }
    return false; // 未找到账户或密码错误
}

// 实现数据更新接口
bool AccountDatabase::updateBalance(const std::string& CardNumber, double balance) {
    // 确保数据已初始化
    if (account_info.empty()) {
        initializeTestData();
    }
    
    for(auto& account : account_info) {
        if(account.CardNumber == CardNumber) {
            account.balance = balance;
            return true;
        }
    }
    return false;
}

bool AccountDatabase::changePassword(const std::string& CardNumber, const std::string& new_password) {
    // 确保数据已初始化
    if (account_info.empty()) {
        initializeTestData();
    }
    
    for(auto& account : account_info) {
        if(account.CardNumber == CardNumber) {
            account.password = new_password;
            return true;
        }
    }
    return false;
}