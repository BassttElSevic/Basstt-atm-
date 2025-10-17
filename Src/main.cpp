//这是程序的主干部分，模拟atm机的主程序
#include "../Inc/land.h"
#include "../Inc/action.h"
#include "../Inc/codemanage.h"
#include "../Inc/quit.h"
#include "../Inc/database.h"
#include <iostream>
#include <string>
#include <windows.h>
using namespace std;

int main() {
    // 初始化数据库
    AccountDatabase::init();
    
    //解决中文乱码问题
    SetConsoleOutputCP(65001);  // UTF-8的代码页
    SetConsoleCP(65001);        // 输入也设置为UTF-8
    
    cout << "==================================" << endl;
    cout << "     欢迎使用ATM模拟系统         " << endl;
    cout << "==================================" << endl;
    
    // 登录模块
    land loginModule;
    bool loggedIn = false;
    int loginChoice;
    
    while (!loggedIn) {
        cout << "\n--------- 登录界面 ---------" << endl;
        cout << "1. 登录" << endl;
        cout << "2. 忘记密码" << endl;
        cout << "3. 退出系统" << endl;
        cout << "请选择操作: ";
        cin >> loginChoice;
        
        switch (loginChoice) {
            case 1: {
                loginModule.CardNumber_input();
                loginModule.password_input();
                loggedIn = loginModule.login();
                break;
            }
            case 2: {
                loginModule.passwordforget();
                break;
            }
            case 3: {
                cout << "感谢使用ATM系统，再见！" << endl;
                return 0;
            }
            default: {
                cout << "无效选择，请重新输入！" << endl;
                break;
            }
        }
    }
    
    // 登录成功，进入主操作界面
    string currentUserCard = loginModule.getCardNumber();
    action actionModule(currentUserCard);
    
    int operationChoice;
    bool exitSystem = false;
    
    while (!exitSystem) {
        cout << "\n--------- 主菜单 ---------" << endl;
        cout << "1. 查询余额" << endl;
        cout << "2. 存款" << endl;
        cout << "3. 取款" << endl;
        cout << "4. 转账" << endl;
        cout << "5. 修改密码" << endl;
        cout << "6. 退出系统" << endl;
        cout << "请选择操作: ";
        cin >> operationChoice;
        
        switch (operationChoice) {
            case 1: {
                // 查询余额
                actionModule.showBalance();
                break;
            }
            case 2: {
                // 存款
                double depositAmount;
                cout << "请输入存款金额: ";
                cin >> depositAmount;
                actionModule.deposit(depositAmount);
                break;
            }
            case 3: {
                // 取款
                double withdrawAmount;
                cout << "请输入取款金额: ";
                cin >> withdrawAmount;
                actionModule.withdraw(withdrawAmount);
                break;
            }
            case 4: {
                // 转账
                string toCardNumber, confirmCardNumber;
                double transferAmount;
                cout << "请输入目标卡号: ";
                cin >> toCardNumber;
                cout << "请再次输入目标卡号以确认: ";
                cin >> confirmCardNumber;
                
                // 检查两次输入的卡号是否一致
                if (toCardNumber != confirmCardNumber) {
                    cout << "两次输入的卡号不一致，转账失败！" << endl;
                    break;
                }
                
                cout << "请输入转账金额: ";
                cin >> transferAmount;
                actionModule.transfer(toCardNumber, transferAmount);
                break;
            }
            case 5: {
                // 修改密码
                codemanage passwordManager(currentUserCard);
                string oldPassword, newPassword, confirmPassword;
                cout << "请输入原密码: ";
                cin >> oldPassword;
                cout << "请输入新密码（6位数字）: ";
                cin >> newPassword;
                cout << "请再次输入新密码以确认: ";
                cin >> confirmPassword;
                passwordManager.changeUserPassword(oldPassword, newPassword, confirmPassword);
                break;
            }
            case 6: {
                // 退出系统
                quit quitModule(currentUserCard);
                if (quitModule.confirmExit()) {
                    quitModule.saveAndExit();
                    exitSystem = true;
                }
                break;
            }
            default: {
                cout << "无效选择，请重新输入！" << endl;
                break;
            }
        }
        
        // 暂停一下，让用户能看到操作结果
        if (!exitSystem && operationChoice >= 1 && operationChoice <= 5) {
            cout << "\n按回车键继续...";
            cin.ignore();
            cin.get();
        }
    }
    
    return 0;
}