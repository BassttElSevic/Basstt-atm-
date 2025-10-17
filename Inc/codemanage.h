#pragma once
#include "database.h"
#include <string>
#include <iostream>

class codemanage : public DataQuery, public DataUpdate {
private:
    std::string CardNumber;
    
public:
    codemanage(const std::string& cardNumber);
    
    // 继承并实现DataQuery接口
    AccountInfo get_account_info(const std::string& CardNumber) override;
    double getBalance(const std::string& CardNumber) override;
    bool verifyPassword(const std::string& CardNumber, const std::string& password) override;
    
    // 继承并实现DataUpdate接口
    bool updateBalance(const std::string& CardNumber, double balance) override;
    bool changePassword(const std::string& CardNumber, const std::string& new_password) override;
    
    // 密码管理特定功能
    bool changeUserPassword(const std::string& old_password, const std::string& new_password, const std::string& confirm_password);
    bool verifyCurrentUserPassword(const std::string& password);
};