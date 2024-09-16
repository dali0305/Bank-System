#include<iostream>
#include<string>
using namespace std;

/*1）设计一数据结构，用来表示某一银行储户的基本信息：
	账号(string)、姓名(暂默认E）(string)、开户年月日(struct:int,int,int)、
	储蓄类型(enum)、存入累加数(double)、利息(double)、帐面总数(double)。
	附加信息：密码

2）定义针对该银行储户基本信息的操作：增删改查

增：新建账户
删：删除账户
改：更改密码、存款、取款
查：查询余额、查询当期利息、查询存入累加数、查询账号
*/

//本题中存入累加数定义不明确，此系统中视作某段时期内现金存入总量，不考虑转账变动
//存入累加数更新及利息定期计算功能未补全
//本代码仅用于练习C++面向对象编程，后续作业均由C++实现

class Depositor_Basic {
public:
	enum Deposit {
		Demand,
		Fixed,
		Savings,
		Recurring
	};
	struct Date {
		int year;
		int month;
		int day;
	};
	Depositor_Basic();
	Depositor_Basic(string account, string name, int year, int month, int day, int type, string password);
	bool Check_Password(string password);
	void Save(double money);//存款
	bool Draw(double money);//取款
	double Check_Balance() const;//查询余额
	double Check_Interest() const;//查询当期利息
	double Check_Cumulative() const;//查询存入累加数
	string Check_Account() const;//查询账号
	string Check_Name() const;//查询姓名
	Date Check_Opening() const;//查询开户日期
	Deposit Check_Type() const;//查询储蓄类型
	bool Password_Valid(string password) const;//密码是否合法
	void Change_Password(string password);//更改密码
	bool Transfer(double money, Depositor_Basic& payee);//转账

protected:
	string account;
	string name;
	Date opening;
	Deposit type;
	double cumulative;
	double interest;
	double balance;
	string password;
	void Update_Cumulative(double money) {
		cumulative += money;
	}
	void Update_Interest(double money) {
		interest += money;
	}
	void Update_Balance(double money) {
		balance += money;
	}
};

Depositor_Basic::Depositor_Basic() {
}
Depositor_Basic::Depositor_Basic(string account, string name, int year, int month, int day, int type, string password) {
	this->account = account;
	this->name = name;
	this->opening.year = year;
	this->opening.month = month;
	this->opening.day = day;
	this->password = password;
	this->type = static_cast<Deposit>(type);
	this->cumulative = 0;
	this->interest = 0;
	this->balance = 0;
}
bool Depositor_Basic::Check_Password(string password) {
	//检查密码
	if (this->password == password) {
		return true;
	}
	else {
		return false;
	}
}
void Depositor_Basic::Save(double money) {
	//存款
	Update_Cumulative(money);
	Update_Balance(money);
}

bool Depositor_Basic::Draw(double money) {
	//取款
	if (money > balance) {
		return false;
	}
	else {
		Update_Cumulative(-money);
		Update_Balance(-money);
		return true;
	}
}

double Depositor_Basic::Check_Balance() const {
	//查询余额
	return balance;
}
double Depositor_Basic::Check_Interest() const {
	//查询当期利息
	return interest;
}
double Depositor_Basic::Check_Cumulative() const {
	//查询存入累加数
	return cumulative;
}
string Depositor_Basic::Check_Account() const {
	//查询账号
	return account;
}
string Depositor_Basic::Check_Name() const {
	//查询姓名
	return name;
}
Depositor_Basic::Date Depositor_Basic::Check_Opening() const {
	//查询开户日期
	return opening;
}
Depositor_Basic::Deposit Depositor_Basic::Check_Type() const {
	//查询储蓄类型
	return type;
}
bool Depositor_Basic::Password_Valid(string password) const {
	if (password.size() < 3 || password.size() > 8) {
		return false;
	}
	else
	{
		return true;
	}
}
void Depositor_Basic::Change_Password(string password) {
	//更改姓名
	this->password = password;
}
bool Depositor_Basic::Transfer(double money, Depositor_Basic& payee) {
	//转账
	if (money > balance) {
		return false;
	}
	else {
		Update_Balance(-money);
		payee.Update_Balance(money);
		return true;
	}
}
//按照时间顺序使用线性表存储储户信息
//两个列表，一个列表装account，一个列表装Depositor_Basic对象
//使用结构体，存表的空间大小和尾部指针
struct Depositor {
	Depositor_Basic Depositor_list[10];
	int last = -1;
}depositor;
struct Account {
	string account_list[10] = { "0","0","0","0","0","0","0","0","0","0" };
	int last = -1;
}account_numbers;
//此处待修改，以实现新建账户功能
/*Depositor_Basic Depositor_list[2] = {
	Depositor_Basic("111", "Alice", 2005, 3, 5, 0, "111"),
	Depositor_Basic("222", "Bob", 2005, 3, 5, 0, "222")
};
string account_list[2] = { Depositor_list[0].Check_Account(), Depositor_list[1].Check_Account()};*/
//查找时，遍历account列表，找到对应的account，返回对应的Depositor_Basic对象
//定义整型查找函数，返回对应的Depositor_Basic对象的下标+1，如果没找到返回0
int Find_Depositor(string account) {
	for (int i = 0; i <= depositor.last; i++) {
		if (account_numbers.account_list[i] == account) {
			return i+1;
		}
	}
	return 0;
}
using namespace std;
void run() {
	cout << "欢迎使用银行储户信息管理系统！" << endl;
	//选择功能
	cout << "请选择功能：" << endl;
	cout << "0.新建账户" << endl;
	cout << "1.存款" << endl;
	cout << "2.取款" << endl;
	cout << "3.查询余额" << endl;
	cout << "4.查询当期利息" << endl;
	cout << "5.查询存入累加数" << endl;
	cout << "6.更改密码" << endl;
	cout << "7.转账" << endl;
	cout << "8.删除账户" << endl;
	enum Function {
		Create,
		Save,
		Draw,
		Check_Balance,
		Check_Interest,
		Check_Cumulative,
		Change_Password,
		Transfer,
		Delete_Account
	};

	int choice_int;
	cin >> choice_int;
	Function choice = static_cast<Function>(choice_int);
	switch (choice) {
	case Create: {
		//新建账户
		cout << "请输入新账户账号：" << endl;
		string new_account;
		cin >> new_account;
		cout << "请输入新账户姓名：" << endl;
		string new_name;
		cin >> new_name;
		cout << "请输入新账户开户年月日：" << endl;
		int new_year, new_month, new_day;
		cin >> new_year >> new_month >> new_day;
		cout << "请输入新账户储蓄类型：" << endl;
		cout << "0.活期" << endl;
		cout << "1.定期" << endl;
		cout << "2.储蓄" << endl;
		cout << "3.定期储蓄" << endl;
		int new_type;
		cin >> new_type;
		cout << "请输入新账户密码：" << endl;
		string new_password;
		cin >> new_password;
		Depositor_Basic new_depositor(new_account, new_name, new_year, new_month, new_day, new_type, new_password);
		depositor.Depositor_list[depositor.last + 1] = new_depositor;
		account_numbers.account_list[account_numbers.last + 1] = new_account;
		depositor.last++;
		account_numbers.last++;
		cout << "新建账户成功！" << endl;
		cout << "账户信息：" << endl;
		cout << "账号：" << new_depositor.Check_Account() << endl;
		cout << "姓名：" << new_depositor.Check_Name() << endl;
		cout << "开户日期：" << new_depositor.Check_Opening().year << "年" << new_depositor.Check_Opening().month << "月" << new_depositor.Check_Opening().day << "日" << endl;
		cout << "储蓄类型：" << new_depositor.Check_Type() << endl;
		cout << "存入累加数：" << new_depositor.Check_Cumulative() << endl;
		cout << "利息：" << new_depositor.Check_Interest() << endl;
		cout << "余额：" << new_depositor.Check_Balance() << endl;
		return;
	}
	default:
		break;
	}
	//登录阶段
	cout << "请输入您的账户账号：" << endl;
	string account;
	cin >> account;
	//查找账号
	int index = Find_Depositor(account);
	while (index == 0) {
		cout << "未找到对应账户，请重新输入。" << endl;
		cin >> account;
		index = Find_Depositor(account);
	}
	cout << "找到对应账户，请输入密码" << endl;

	string password;
	cin >> password;
	while (!depositor.Depositor_list[index-1].Check_Password(password)) {
		cout << "密码错误，请重新输入。" << endl;
		cin >> password;
	}
	cout << "登录成功！" << endl;


	switch (choice) {
	case Create: {
		//新建账户
		cout << "请输入新账户账号：" << endl;
		string new_account;
		cin >> new_account;
		cout << "请输入新账户姓名：" << endl;
		string new_name;
		cin >> new_name;
		cout << "请输入新账户开户年月日：" << endl;
		int new_year, new_month, new_day;
		cin >> new_year >> new_month >> new_day;
		cout << "请输入新账户储蓄类型：" << endl;
		cout << "0.活期" << endl;
		cout << "1.定期" << endl;
		cout << "2.储蓄" << endl;
		cout << "3.定期储蓄" << endl;
		int new_type;
		cin >> new_type;
		cout << "请输入新账户密码：" << endl;
		string new_password;
		cin >> new_password;
		Depositor_Basic new_depositor(new_account, new_name, new_year, new_month, new_day, new_type, new_password);
		depositor.Depositor_list[depositor.last + 1] = new_depositor;
		account_numbers.account_list[account_numbers.last + 1] = new_account;
		depositor.last++;
		account_numbers.last++;
		cout << "新建账户成功！" << endl;
		break;
	}
	case Save: {
		//存款
		cout << "请输入存款金额：" << endl;
		double money;
		cin >> money;
		depositor.Depositor_list[index - 1].Save(money);
		cout << "存款成功！" << endl;
		break;
	}
	case Draw: {
		//取款
		cout << "请输入取款金额：" << endl;
		double money;
		cin >> money;
		if (depositor.Depositor_list[index - 1].Draw(money)) {
			cout << "取款成功！" << endl;
		}
		else {
			cout << "余额不足！" << endl;
		}
		break;
	}
	case Check_Balance: {
		//查询余额
		cout << "您的余额为：" << depositor.Depositor_list[index - 1].Check_Balance() << endl;
		break;
	}
	case Check_Interest: {
		//查询当期利息
		cout << "您的当期利息为：" << depositor.Depositor_list[index - 1].Check_Interest() << endl;
		break;
	}
	case Check_Cumulative: {
		//查询存入累加数
		cout << "您的存入累加数为：" << depositor.Depositor_list[index - 1].Check_Cumulative() << endl;
		break;
	}
	case Change_Password: {
		//更改密码
		cout << "请输入新密码：" << endl;
		string new_password;
		cin >> new_password;
		if (depositor.Depositor_list[index - 1].Password_Valid(new_password)) {
			depositor.Depositor_list[index - 1].Change_Password(new_password);
			cout << "更改密码成功！" << endl;
		}
		else {
			cout << "密码不合法！" << endl;
		}
		break;
	}
	case Transfer: {
		//转账
		cout << "请输入转账金额：" << endl;
		double money;
		cin >> money;
		cout << "请输入对方账户账号：" << endl;
		string payee_account;
		cin >> payee_account;
		int payee_index = Find_Depositor(payee_account);
		if (payee_index == 0) {
			cout << "未找到对方账户，转账失败。" << endl;
		}
		else {
			if (depositor.Depositor_list[index - 1].Transfer(money, depositor.Depositor_list[payee_index - 1])) {
				cout << "转账成功！" << endl;
			}
			else {
				cout << "余额不足！" << endl;
			}
		}
		break;
	}

	case Delete_Account: {
		//删除对应的Depositor_Basic对象
		for (int i = index - 1; i < sizeof(depositor.Depositor_list) / sizeof(depositor.Depositor_list[0])-1; i++) {
			depositor.Depositor_list[i] = depositor.Depositor_list[i+1];
		}
		depositor.last--;
		//删除对应的account
		for (int i = index - 1; i < sizeof(depositor.Depositor_list) / sizeof(depositor.Depositor_list[0])-1; i++) {
			account_numbers.account_list[i] = account_numbers.account_list[i+1];
		}
		account_numbers.last--;
		cout << "删除账户成功！" << endl;
	}
	break;
	default: {
		cout << "功能输入错误！" << endl;
		break;
	}
	}
}

int main() {
	bool flag = true;
	while (flag) {
		run();
		cout << "（按Y退出系统）" << endl;
		char choice;
		cin >> choice;
		if (choice == 'Y' || choice == 'y') {
			flag = false;
		}
	}
	return 0;
}