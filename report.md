# 简易 ATM 模拟系统 课程作业报告（个人作业版）

项目地址：[Basstt-atm-](https://github.com/BassttElSevic/Basstt-atm-)
备注，请看第二版，第一版有个小bug
主要语言：C++  
主要模块（与仓库一致）：land（登录）、action（操作）、codemanage（密码管理）、database（数据服务）、quit（退出）

---

## 一、需求分析（做了什么，打算达到什么效果）

- 登录
  - 输入卡号和密码登录；最多允许输错 3 次，超过则提示锁定并结束（用于演示简单安全策略）。
  - 提供“忘记密码”入口，进入密码管理模块修改密码。
- 账户操作（登录成功后）
  - 查询余额：显示当前账户余额。
  - 存款（充值）：向当前账户增加指定金额。
  - 取款：从当前账户扣减指定金额，余额不足则提示失败。
  - 转账：向其他账户转账，要求对方卡号存在、金额合法且余额充足。
  - 操作校验：对金额、卡号进行基本校验，非法输入会给出错误提示。（我添加了检验模块，可以防止在输入非数字时无限循环
- 密码管理
  - 校验旧密码并修改为新密码。
- 退出
  - 正常退出程序。

预期效果（基于控制台演示）：
- 菜单简单清晰，输入有提示；出错时给出明确的原因；常见操作（查、充、取、转）能够顺利完成演示。

---

## 二、程序设计（模块、类、函数与关系）

项目文件（节选，来自 Inc/ 目录）：
- database.h：数据模型与数据接口（DataQuery/DataUpdate），以及 AccountDatabase 实现
- land.h：登录模块，负责采集输入、校验与流程控制（含忘记密码入口）
- action.h：操作模块，负责查余额、存款、取款、转账与输入校验
- codemanage.h：密码管理（声明）
- quit.h：退出模块（声明）

1) 数据与接口（database.h）
- 数据模型
  - struct AccountInfo
    - 字段：CardNumber、password、name、balance（double）
- 接口设计
  - class DataQuery
    - get_account_info(CardNumber)
    - getBalance(CardNumber)
    - verifyPassword(CardNumber, password)
  - class DataUpdate
    - updateBalance(CardNumber, balance)
    - changePassword(CardNumber, new_password)
- 数据库实现
  - class AccountDatabase : public DataQuery, public DataUpdate
    - 使用静态 std::vector<AccountInfo> 作为“内存数据库”
    - 提供 init()/initializeTestData() 初始化演示数据
    - 实现查询与更新接口（余额读取/更新、密码校验/修改）

2) 登录模块（land.h）
- class land : public DataQuery
  - 成员：CardNumberInput、passwordInput、loginAttempts
  - 主要方法：
    - CardNumber_input() / password_input()：读取用户输入
    - login()：处理“最多 3 次尝试”的登录流程
    - passwordforget()：进入密码管理流程（修改成功后返回/结束）
    - getCardNumber()：返回当前输入的卡号
  - 说明：land 通过实现 DataQuery 的方法，内部创建 AccountDatabase 对象进行实际的数据查询（转发式实现）。

3) 操作模块（action.h）
- class action : public DataQuery, public DataUpdate
  - 成员：CardNumber（当前登录卡号）
  - 主要方法（与 README 一致）：
    - showBalance()：查询余额
    - deposit(double)：存款
    - withdraw(double)：取款
    - transfer(const std::string& toCardNumber, double)：转账
    - validateAmount(double)、validateCardNumber(string)：输入校验
  - 说明：action 同时具备读写权限，先做校验，再调用 AccountDatabase 更新余额。

4) 密码管理与退出（codemanage.h、quit.h）
- codemanage：完成密码核对与修改（通过 AccountDatabase 的 changePassword）
- quit：统一退出入口（为后续落盘/收尾预留）

5) 关键流程（算法简述）
- 登录（3 次机会）
  1) 读取卡号与密码
  2) verifyPassword() 成功则进入 action；失败则 loginAttempts++，超过 3 次提示锁定并结束
- 存款
  1) validateAmount(amount) > 0
  2) 读取当前余额 + amount，updateBalance()，输出新余额
- 取款
  1) validateAmount(amount) > 0
  2) 余额充足则扣减并 updateBalance()，否则提示“余额不足”
- 转账
  1) validateAmount(amount) 与 validateCardNumber(toCard)
  2) 校验自身余额充足；对方卡号存在
  3) 自身余额扣减 + 对方余额增加，分别 updateBalance() 后提示成功
- 改密
  1) 校验旧密码
  2) changePassword() 为新密码并提示完成

平台与依赖：
- C++ 标准库
- land.h 引入 <windows.h>，主要面向 Windows 终端演示

---

## 三、程序效果展示（文字说明 + 终端示例）

说明：下列为真实交互逻辑的文字版示例。若提交报告时需要截图，建议将实际运行的终端截图放到 docs/screenshots/ 目录，并在报告中替换为对应图片路径。

- 登录与输错限制（land）
```text
欢迎使用简易ATM系统
请输入卡号: 6214 8888 0000 1234
请输入密码: ******
登录成功！

(若密码错误)
密码错误，还有 2 次机会。
...
密码错误，已达 3 次，账户被锁定。
```
要点说明：采用 3 次机会的简单限制；密码核验通过 AccountDatabase::verifyPassword。

- 主菜单与查询余额（action）
```text
===== 账户操作 =====
[1] 查询余额
[2] 存款（充值）
[3] 取款
[4] 转账
[5] 修改密码
[0] 退出
请选择: 1

当前余额：1234.50 元
```
要点说明：余额来自 AccountDatabase::getBalance；仅显示当前登录账户的余额。

- 存款（充值）（action::deposit）
```text
请选择: 2
请输入充值金额：500.00
充值成功，新余额：1734.50 元
```
要点说明：先校验金额；金额合法则读取旧余额并累加后 updateBalance。

- 取款（action::withdraw）
```text
请选择: 3
请输入取款金额：2000.00
余额不足，请重新输入。

请输入取款金额：200.00
取款成功，新余额：1534.50 元
```
要点说明：余额不足会直接提示；成功则扣减余额并 updateBalance。

- 转账（action::transfer）
```text
请选择: 4
请输入对方卡号：6214 8888 0000 5678
请输入转账金额：100.00
转账成功。当前余额：1434.50 元
```
要点说明：同时校验金额和对方卡号；完成后分别更新双方账户余额。

- 修改密码（codemanage）
```text
请选择: 5
请输入原密码：******
请输入新密码：******
请再次输入新密码：******
修改成功，请重新登录。
```
要点说明：调用 changePassword 完成密码更新；为了演示简单明了，没有做复杂度检查。

- 退出（quit）
```text
请选择: 0
感谢使用，已退出系统。
```

---

## 四、总结分析（现实与理想的差距、原因与改进）

1) 与理想系统的差距
- 数据不持久：当前使用内存静态容器保存账户信息，程序退出后数据丢失。
- 金额精度：余额使用 double，极端情况下可能出现精度问题。
- 安全性基础：密码以明文字段参与核验，只做了“输错 3 次限制”，没有哈希与盐。
- 转账原子性：转账由两次余额更新组成，缺少“同时成功或同时失败”的事务保证。
- 平台依赖：使用了 <windows.h>，主要在 Windows 终端演示，跨平台性一般。
- 无交易记录：未实现流水/日志，无法回看历史操作。

2) 原因（个人作业的现实情况）
- 时间与精力有限，优先完成“能跑通的核心功能”，不引入数据库等额外依赖。
- 练习 C++ 基础语法和模块划分为主，安全与事务特性暂不展开。
- 以演示为目标，采用最简单的内存数据和 double 金额。

3) 可行的后续小步改进（按成本从低到高）
- 金额类型改为整数“分”（long long），避免精度误差（工作量小，收益明显）。
- 简单文件持久化（CSV/JSON）：启动时加载、退出时保存（无需引入数据库）。
- 密码基本安全：至少做哈希（带盐更好），避免明文保存。
- 简易流水记录：把每次操作记一行文本，方便演示“查看最近操作”。
- 条件编译去掉强依赖 <windows.h>，或为 Linux 增加分支。