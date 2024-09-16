#include<iostream>
#include<string>
using namespace std;

/*1�����һ���ݽṹ��������ʾĳһ���д����Ļ�����Ϣ��
	�˺�(string)������(��Ĭ��E��(string)������������(struct:int,int,int)��
	��������(enum)�������ۼ���(double)����Ϣ(double)����������(double)��
	������Ϣ������

2��������Ը����д���������Ϣ�Ĳ�������ɾ�Ĳ�

�����½��˻�
ɾ��ɾ���˻�
�ģ��������롢��ȡ��
�飺��ѯ����ѯ������Ϣ����ѯ�����ۼ�������ѯ�˺�
*/

//�����д����ۼ������岻��ȷ����ϵͳ������ĳ��ʱ�����ֽ����������������ת�˱䶯
//�����ۼ������¼���Ϣ���ڼ��㹦��δ��ȫ
//�������������ϰC++��������̣�������ҵ����C++ʵ��

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
	void Save(double money);//���
	bool Draw(double money);//ȡ��
	double Check_Balance() const;//��ѯ���
	double Check_Interest() const;//��ѯ������Ϣ
	double Check_Cumulative() const;//��ѯ�����ۼ���
	string Check_Account() const;//��ѯ�˺�
	string Check_Name() const;//��ѯ����
	Date Check_Opening() const;//��ѯ��������
	Deposit Check_Type() const;//��ѯ��������
	bool Password_Valid(string password) const;//�����Ƿ�Ϸ�
	void Change_Password(string password);//��������
	bool Transfer(double money, Depositor_Basic& payee);//ת��

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
	//�������
	if (this->password == password) {
		return true;
	}
	else {
		return false;
	}
}
void Depositor_Basic::Save(double money) {
	//���
	Update_Cumulative(money);
	Update_Balance(money);
}

bool Depositor_Basic::Draw(double money) {
	//ȡ��
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
	//��ѯ���
	return balance;
}
double Depositor_Basic::Check_Interest() const {
	//��ѯ������Ϣ
	return interest;
}
double Depositor_Basic::Check_Cumulative() const {
	//��ѯ�����ۼ���
	return cumulative;
}
string Depositor_Basic::Check_Account() const {
	//��ѯ�˺�
	return account;
}
string Depositor_Basic::Check_Name() const {
	//��ѯ����
	return name;
}
Depositor_Basic::Date Depositor_Basic::Check_Opening() const {
	//��ѯ��������
	return opening;
}
Depositor_Basic::Deposit Depositor_Basic::Check_Type() const {
	//��ѯ��������
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
	//��������
	this->password = password;
}
bool Depositor_Basic::Transfer(double money, Depositor_Basic& payee) {
	//ת��
	if (money > balance) {
		return false;
	}
	else {
		Update_Balance(-money);
		payee.Update_Balance(money);
		return true;
	}
}
//����ʱ��˳��ʹ�����Ա�洢������Ϣ
//�����б�һ���б�װaccount��һ���б�װDepositor_Basic����
//ʹ�ýṹ�壬���Ŀռ��С��β��ָ��
struct Depositor {
	Depositor_Basic Depositor_list[10];
	int last = -1;
}depositor;
struct Account {
	string account_list[10] = { "0","0","0","0","0","0","0","0","0","0" };
	int last = -1;
}account_numbers;
//�˴����޸ģ���ʵ���½��˻�����
/*Depositor_Basic Depositor_list[2] = {
	Depositor_Basic("111", "Alice", 2005, 3, 5, 0, "111"),
	Depositor_Basic("222", "Bob", 2005, 3, 5, 0, "222")
};
string account_list[2] = { Depositor_list[0].Check_Account(), Depositor_list[1].Check_Account()};*/
//����ʱ������account�б��ҵ���Ӧ��account�����ض�Ӧ��Depositor_Basic����
//�������Ͳ��Һ��������ض�Ӧ��Depositor_Basic������±�+1�����û�ҵ�����0
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
	cout << "��ӭʹ�����д�����Ϣ����ϵͳ��" << endl;
	//ѡ����
	cout << "��ѡ���ܣ�" << endl;
	cout << "0.�½��˻�" << endl;
	cout << "1.���" << endl;
	cout << "2.ȡ��" << endl;
	cout << "3.��ѯ���" << endl;
	cout << "4.��ѯ������Ϣ" << endl;
	cout << "5.��ѯ�����ۼ���" << endl;
	cout << "6.��������" << endl;
	cout << "7.ת��" << endl;
	cout << "8.ɾ���˻�" << endl;
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
		//�½��˻�
		cout << "���������˻��˺ţ�" << endl;
		string new_account;
		cin >> new_account;
		cout << "���������˻�������" << endl;
		string new_name;
		cin >> new_name;
		cout << "���������˻����������գ�" << endl;
		int new_year, new_month, new_day;
		cin >> new_year >> new_month >> new_day;
		cout << "���������˻��������ͣ�" << endl;
		cout << "0.����" << endl;
		cout << "1.����" << endl;
		cout << "2.����" << endl;
		cout << "3.���ڴ���" << endl;
		int new_type;
		cin >> new_type;
		cout << "���������˻����룺" << endl;
		string new_password;
		cin >> new_password;
		Depositor_Basic new_depositor(new_account, new_name, new_year, new_month, new_day, new_type, new_password);
		depositor.Depositor_list[depositor.last + 1] = new_depositor;
		account_numbers.account_list[account_numbers.last + 1] = new_account;
		depositor.last++;
		account_numbers.last++;
		cout << "�½��˻��ɹ���" << endl;
		cout << "�˻���Ϣ��" << endl;
		cout << "�˺ţ�" << new_depositor.Check_Account() << endl;
		cout << "������" << new_depositor.Check_Name() << endl;
		cout << "�������ڣ�" << new_depositor.Check_Opening().year << "��" << new_depositor.Check_Opening().month << "��" << new_depositor.Check_Opening().day << "��" << endl;
		cout << "�������ͣ�" << new_depositor.Check_Type() << endl;
		cout << "�����ۼ�����" << new_depositor.Check_Cumulative() << endl;
		cout << "��Ϣ��" << new_depositor.Check_Interest() << endl;
		cout << "��" << new_depositor.Check_Balance() << endl;
		return;
	}
	default:
		break;
	}
	//��¼�׶�
	cout << "�����������˻��˺ţ�" << endl;
	string account;
	cin >> account;
	//�����˺�
	int index = Find_Depositor(account);
	while (index == 0) {
		cout << "δ�ҵ���Ӧ�˻������������롣" << endl;
		cin >> account;
		index = Find_Depositor(account);
	}
	cout << "�ҵ���Ӧ�˻�������������" << endl;

	string password;
	cin >> password;
	while (!depositor.Depositor_list[index-1].Check_Password(password)) {
		cout << "����������������롣" << endl;
		cin >> password;
	}
	cout << "��¼�ɹ���" << endl;


	switch (choice) {
	case Create: {
		//�½��˻�
		cout << "���������˻��˺ţ�" << endl;
		string new_account;
		cin >> new_account;
		cout << "���������˻�������" << endl;
		string new_name;
		cin >> new_name;
		cout << "���������˻����������գ�" << endl;
		int new_year, new_month, new_day;
		cin >> new_year >> new_month >> new_day;
		cout << "���������˻��������ͣ�" << endl;
		cout << "0.����" << endl;
		cout << "1.����" << endl;
		cout << "2.����" << endl;
		cout << "3.���ڴ���" << endl;
		int new_type;
		cin >> new_type;
		cout << "���������˻����룺" << endl;
		string new_password;
		cin >> new_password;
		Depositor_Basic new_depositor(new_account, new_name, new_year, new_month, new_day, new_type, new_password);
		depositor.Depositor_list[depositor.last + 1] = new_depositor;
		account_numbers.account_list[account_numbers.last + 1] = new_account;
		depositor.last++;
		account_numbers.last++;
		cout << "�½��˻��ɹ���" << endl;
		break;
	}
	case Save: {
		//���
		cout << "���������" << endl;
		double money;
		cin >> money;
		depositor.Depositor_list[index - 1].Save(money);
		cout << "���ɹ���" << endl;
		break;
	}
	case Draw: {
		//ȡ��
		cout << "������ȡ���" << endl;
		double money;
		cin >> money;
		if (depositor.Depositor_list[index - 1].Draw(money)) {
			cout << "ȡ��ɹ���" << endl;
		}
		else {
			cout << "���㣡" << endl;
		}
		break;
	}
	case Check_Balance: {
		//��ѯ���
		cout << "�������Ϊ��" << depositor.Depositor_list[index - 1].Check_Balance() << endl;
		break;
	}
	case Check_Interest: {
		//��ѯ������Ϣ
		cout << "���ĵ�����ϢΪ��" << depositor.Depositor_list[index - 1].Check_Interest() << endl;
		break;
	}
	case Check_Cumulative: {
		//��ѯ�����ۼ���
		cout << "���Ĵ����ۼ���Ϊ��" << depositor.Depositor_list[index - 1].Check_Cumulative() << endl;
		break;
	}
	case Change_Password: {
		//��������
		cout << "�����������룺" << endl;
		string new_password;
		cin >> new_password;
		if (depositor.Depositor_list[index - 1].Password_Valid(new_password)) {
			depositor.Depositor_list[index - 1].Change_Password(new_password);
			cout << "��������ɹ���" << endl;
		}
		else {
			cout << "���벻�Ϸ���" << endl;
		}
		break;
	}
	case Transfer: {
		//ת��
		cout << "������ת�˽�" << endl;
		double money;
		cin >> money;
		cout << "������Է��˻��˺ţ�" << endl;
		string payee_account;
		cin >> payee_account;
		int payee_index = Find_Depositor(payee_account);
		if (payee_index == 0) {
			cout << "δ�ҵ��Է��˻���ת��ʧ�ܡ�" << endl;
		}
		else {
			if (depositor.Depositor_list[index - 1].Transfer(money, depositor.Depositor_list[payee_index - 1])) {
				cout << "ת�˳ɹ���" << endl;
			}
			else {
				cout << "���㣡" << endl;
			}
		}
		break;
	}

	case Delete_Account: {
		//ɾ����Ӧ��Depositor_Basic����
		for (int i = index - 1; i < sizeof(depositor.Depositor_list) / sizeof(depositor.Depositor_list[0])-1; i++) {
			depositor.Depositor_list[i] = depositor.Depositor_list[i+1];
		}
		depositor.last--;
		//ɾ����Ӧ��account
		for (int i = index - 1; i < sizeof(depositor.Depositor_list) / sizeof(depositor.Depositor_list[0])-1; i++) {
			account_numbers.account_list[i] = account_numbers.account_list[i+1];
		}
		account_numbers.last--;
		cout << "ɾ���˻��ɹ���" << endl;
	}
	break;
	default: {
		cout << "�����������" << endl;
		break;
	}
	}
}

int main() {
	bool flag = true;
	while (flag) {
		run();
		cout << "����Y�˳�ϵͳ��" << endl;
		char choice;
		cin >> choice;
		if (choice == 'Y' || choice == 'y') {
			flag = false;
		}
	}
	return 0;
}