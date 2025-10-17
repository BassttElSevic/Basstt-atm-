#include "../Inc/action.h"
#include <iostream>
#include <iomanip>
#include <cmath>
using namespace std;

action::action(const std::string& cardNumber) : CardNumber(cardNumber) {
    // 构造函数，保存卡号信息
}

// 实现DataQuery接口
AccountInfo action::get_account_info(const std::string& CardNumber) {
    AccountDatabase db;
    return db.get_account_info(CardNumber);
}

double action::getBalance(const std::string& CardNumber) {
    AccountDatabase db;
    return db.getBalance(CardNumber);
}

bool action::verifyPassword(const std::string& CardNumber, const std::string& password) {
    AccountDatabase db;
    return db.verifyPassword(CardNumber, password);
}

// 实现DataUpdate接口
bool action::updateBalance(const std::string& CardNumber, double balance) {
    AccountDatabase db;
    return db.updateBalance(CardNumber, balance);
}

bool action::changePassword(const std::string& CardNumber, const std::string& new_password) {
    AccountDatabase db;
    return db.changePassword(CardNumber, new_password);
}

// 查询余额功能
void action::showBalance() {
    double balance = getBalance(CardNumber);
    if (balance >= 0) {
        cout << "您的账户余额为: ￥" << fixed << setprecision(2) << balance << endl;
    } else {
        cout << "查询余额失败，请稍后重试！" << endl;
    }
}

// 存款功能
bool action::deposit(double amount) {
    // 首先验证金额
    if (!validateAmount(amount)) {
        return false;
    }
    
    // 获取当前余额
    double currentBalance = getBalance(CardNumber);
    if (currentBalance < 0) {
        cout << "存款失败，无法获取账户信息！" << endl;
        return false;
    }
    
    // 更新余额
    double newBalance = currentBalance + amount;
    if (updateBalance(CardNumber, newBalance)) {
        cout << "存款成功！存入金额: ￥" << fixed << setprecision(2) << amount << endl;
        cout << "当前余额: ￥" << newBalance << endl;
        return true;
    } else {
        cout << "存款失败，请稍后重试！" << endl;
        return false;
    }
}

// 取款功能
bool action::withdraw(double amount) {
    // 首先验证金额
    if (!validateAmount(amount)) {
        return false;
    }
    
    // 检查取款金额是否为100的整数倍
    if (static_cast<int>(amount) % 100 != 0) {
        cout << "取款失败，取款金额必须为100的整数倍！" << endl;
        return false;
    }
    
    // 检查单笔取款限额（假设单笔限额为3000元）
    if (amount > 3000) {
        cout << "取款失败，单笔取款金额不能超过3000元！" << endl;
        return false;
    }
    
    // 获取当前余额
    double currentBalance = getBalance(CardNumber);
    if (currentBalance < 0) {
        cout << "取款失败，无法获取账户信息！" << endl;
        return false;
    }
    
    // 检查余额是否充足
    if (currentBalance < amount) {
        cout << "取款失败，余额不足！当前余额: ￥" << fixed << setprecision(2) << currentBalance << endl;
        return false;
    }
    
    // 更新余额
    double newBalance = currentBalance - amount;
    if (updateBalance(CardNumber, newBalance)) {
        cout << "取款成功！取出金额: ￥" << fixed << setprecision(2) << amount << endl;
        cout << "当前余额: ￥" << newBalance << endl;
        return true;
    } else {
        cout << "取款失败，请稍后重试！" << endl;
        return false;
    }
}

// 转账功能
bool action::transfer(const std::string& toCardNumber, double amount) {
    // 首先验证金额
    if (!validateAmount(amount)) {
        return false;
    }
    
    // 检查单笔转账限额（假设单笔限额为5000元）
    if (amount > 5000) {
        cout << "转账失败，单笔转账金额不能超过5000元！" << endl;
        return false;
    }
    
    // 验证目标卡号
    if (!validateCardNumber(toCardNumber)) {
        cout << "转账失败，目标卡号无效！" << endl;
        return false;
    }
    
    // 检查不能转账给自己
    if (CardNumber == toCardNumber) {
        cout << "转账失败，不能转账给自己！" << endl;
        return false;
    }
    
    // 获取当前账户余额
    double fromBalance = getBalance(CardNumber);
    if (fromBalance < 0) {
        cout << "转账失败，无法获取转出账户信息！" << endl;
        return false;
    }
    
    // 检查余额是否充足
    if (fromBalance < amount) {
        cout << "转账失败，余额不足！当前余额: ￥" << fixed << setprecision(2) << fromBalance << endl;
        return false;
    }
    
    // 获取目标账户余额
    double toBalance = getBalance(toCardNumber);
    if (toBalance < 0) {
        cout << "转账失败，无法获取转入账户信息！" << endl;
        return false;
    }
    
    // 更新转出账户余额
    double newFromBalance = fromBalance - amount;
    if (!updateBalance(CardNumber, newFromBalance)) {
        cout << "转账失败，更新转出账户失败！" << endl;
        return false;
    }
    
    // 更新转入账户余额
    double newToBalance = toBalance + amount;
    if (!updateBalance(toCardNumber, newToBalance)) {
        // 如果转入账户更新失败，需要回滚转出账户的余额
        updateBalance(CardNumber, fromBalance);
        cout << "转账失败，更新转入账户失败！" << endl;
        return false;
    }
    
    cout << "转账成功！转出金额: ￥" << fixed << setprecision(2) << amount << endl;
    cout << "转出账户当前余额: ￥" << newFromBalance << endl;
    return true;
}

// 操作检验功能 - 检验金额是否有效
bool action::validateAmount(double amount) {
    if (amount <= 0) {
        cout << "操作失败，金额必须大于0！" << endl;
        return false;
    }
    
    if (amount > 10000) {
        cout << "操作失败，单次操作金额不能超过10000元！" << endl;
        return false;
    }
    
    // 检查金额是否为有效数值（例如，小数点后不超过2位）
    double intpart;
    double fracpart = modf(amount, &intpart);
    if (fracpart != 0 && fracpart * 100 != static_cast<int>(fracpart * 100)) {
        cout << "操作失败，金额格式不正确！" << endl;
        return false;
    }
    
    return true;
}

// 操作检验功能 - 检验卡号是否有效
// ... existing code ...

// 操作检验功能 - 检验卡号是否有效
bool action::validateCardNumber(const std::string& cardNumber) {
    // 简单验证卡号长度
    if (cardNumber.length() != 16) {
        return false;
    }
    
    // 验证卡号是否全为数字
    for (char c : cardNumber) {
        if (!isdigit(c)) {
            return false;
        }
    }
    
    // 验证卡号是否存在
    AccountInfo account = get_account_info(cardNumber);
    if (account.CardNumber.empty()) {
        return false;
    }
    
    return true;
}