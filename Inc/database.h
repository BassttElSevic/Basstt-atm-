#pragma once
#include<string>
#include<vector>

struct AccountInfo{
    std::string CardNumber;
    std::string password;
    std::string name;
    double balance;

    AccountInfo(std::string CardNumber,std::string password,std::string name,double balance):CardNumber(CardNumber),password(password),name(name),balance(balance){}

};

// 数据查询基类
class DataQuery {
public:
    virtual ~DataQuery() = default;
    virtual AccountInfo get_account_info(const std::string& CardNumber) = 0;
    virtual double getBalance(const std::string& CardNumber) = 0;
    virtual bool verifyPassword(const std::string& CardNumber, const std::string& password) = 0;
};

// 数据更新基类
class DataUpdate {
public:
    virtual ~DataUpdate() = default;
    virtual bool updateBalance(const std::string& CardNumber, double balance) = 0;
    virtual bool changePassword(const std::string& CardNumber, const std::string& new_password) = 0;
};

// 数据库实现类，继承自数据查询和数据更新基类
class AccountDatabase : public DataQuery, public DataUpdate {
private:
    static std::vector<AccountInfo> account_info;
    // 初始化测试数据
    static void initializeTestData();

public:
    // 实现数据查询接口
    AccountInfo get_account_info(const std::string& CardNumber) override;
    double getBalance(const std::string& CardNumber) override;
    bool verifyPassword(const std::string& CardNumber, const std::string& password) override;
    
    // 实现数据更新接口
    bool updateBalance(const std::string& CardNumber, double balance) override;
    bool changePassword(const std::string& CardNumber, const std::string& new_password) override;
    
    // 初始化数据库
    static void init();
};

// 修复声明错误
// extern std::vector<AccountInfo> account_info;