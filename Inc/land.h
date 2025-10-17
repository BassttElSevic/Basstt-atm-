//这是登录系统的模块
#pragma once
#include "database.h"
#include <string>
#include <iostream>
#include <windows.h>

class land : public DataQuery
{
    private:
        std::string CardNumberInput;
        std::string passwordInput;
        int loginAttempts;
        
    public:
        land(); // 构造函数
        void passwordforget();
        void CardNumber_input();
        void password_input();
        bool login(); //判断密码是否正确
        std::string getCardNumber(); // 获取输入的卡号
        
        // 实现DataQuery接口
        AccountInfo get_account_info(const std::string& CardNumber) override { 
            AccountDatabase db;
            return db.get_account_info(CardNumber);
        }
        
        double getBalance(const std::string& CardNumber) override {
            AccountDatabase db;
            return db.getBalance(CardNumber);
        }
        
        bool verifyPassword(const std::string& CardNumber, const std::string& password) override {
            AccountDatabase db;
            return db.verifyPassword(CardNumber, password);
        }
};