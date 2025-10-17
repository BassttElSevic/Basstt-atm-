#pragma once
#include "database.h"
#include <string>
#include <iostream>

class action : public DataQuery, public DataUpdate {
private:
    std::string CardNumber;
    
public:
    action(const std::string& cardNumber);
    
    // 继承并实现DataQuery接口
    AccountInfo get_account_info(const std::string& CardNumber) override;
    double getBalance(const std::string& CardNumber) override;
    bool verifyPassword(const std::string& CardNumber, const std::string& password) override;
    
    // 继承并实现DataUpdate接口
    bool updateBalance(const std::string& CardNumber, double balance) override;
    bool changePassword(const std::string& CardNumber, const std::string& new_password) override;
    
    // Action模块核心功能
    void showBalance();                           // 查询余额
    bool deposit(double amount);                  // 存款
    bool withdraw(double amount);                 // 取款
    bool transfer(const std::string& toCardNumber, double amount); // 转账
    
    // 操作检验功能
    bool validateAmount(double amount);           // 检验金额是否有效
    bool validateCardNumber(const std::string& cardNumber); // 检验卡号是否有效
};