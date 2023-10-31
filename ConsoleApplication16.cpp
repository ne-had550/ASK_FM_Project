#include <iostream>
#include <fstream>
#include <vector>
#include <string>
using namespace std;
int x;
int number;
string tem;
string tem2;
void Menu() {
	cout << "Menu : " << endl;
	cout << "   1 : login" << endl;
	cout << "   2 : sign up" << endl;
	cout << "Enter 1 or 2 : " <<  endl;
	cin >> x;
}
void Menu2() {
	cout << "Menu : " << endl;
	cout << "      1:print questions to me " << endl;
	cout << "      2:print questions from me" << endl;
	cout << "      3:answer question" << endl;
	cout << "      4:delete question" << endl;
	cout << "      5:ask question" << endl;
	cout << "      6:list system users" << endl;
	cout << "      7:feed" << endl;
	cout << "      8:logout" << endl;
	cout << "enter number in range 1 - 8" << endl;
}
class user {
public:
	string name;
	string password;
	string id;
public:
	user() {
		name = "";
		password = "";
		id = "";
	}
};
struct QA {
	string quest;
	string to;
	string from;
	string id;
};
struct ANS {
	string answer;
	string IDD;
};
vector<user>v;
vector<QA>A;
vector<ANS>a;
vector<string>s1;
vector<string>s2;
vector<string>us;
class service : public user{
public:
	void sort_users() {
		v.clear();
		fstream myfile("uesrs.txt", ios::in);
		int c = 0;
		string temp;
		user S;
		while (getline(myfile, temp)) {
			if (c % 3 == 0) {
				S.name = temp;
			}
			else if (c % 3 == 1) {
				S.id = temp;
			}
			else if (c % 3 == 2) {
				S.password = temp;
				v.push_back(S);
			}
			c++;
		}
		myfile.close();

	}
	void sort_questions() {
		A.clear();
		fstream mfile("questions.txt", ios::in);
		int cm = 0;
		string temp;
		QA S;
		while (getline(mfile, temp)) {
			if (cm % 4 == 0) {
				S.quest = temp;
			}
			else if (cm % 4 == 1) {
				S.to = temp;
			}
			else if (cm % 4 == 2) {
				S.from = temp;
			}
			else if (cm % 4 == 3) {
				S.id = temp;
				A.push_back(S);
			}
			cm++;
		}
		mfile.close();

	}
	void sort_answers() {
		a.clear();
		fstream ffile("answers.txt", ios::in);
		int cn = 0;
		string temp;
		ANS S;
		while (getline(ffile, temp)) {
			if (cn % 2 == 0) {
				S.answer = temp;
			}
			else if (cn % 2 == 1) {
				S.IDD = temp;
				a.push_back(S);
			}
			cn++;
		}
		ffile.close();

	}
	void showallusers() {
		sort_questions();
		sort_users();
		sort_answers();
		if (v.size() == 0) {
			cout << "there is no users to show " << endl;
		}
		else {
			for (int i = 0; i < v.size(); i++) {
				cout << "ID " << v[i].id << "     " << "name: " << v[i].name << endl;
			}
		}
	}
	void questions_from_me(string idd) {
		sort_questions();
		sort_users();
		sort_answers();
		bool fine = 0;
		bool ok = 0;
		for (int j = 0; j < A.size(); j++) {
			if (A[j].from == idd) {
				ok = 1;
				for (int h = 0; h < a.size(); h++) {
					if (A[j].id == a[h].IDD) {
						cout << "[" << A[j].id << "]" << " ";
						cout << A[j].quest << " to ID " << A[j].to << endl;
						cout << "answer   " << a[h].answer << endl;
						fine = 1;
						break;
					}
					else {
						fine = 0;
					}
				}
				if (fine == 0) {
					cout << "[" << A[j].id << "]" << " ";
					cout << A[j].quest << " to ID " << A[j].to << endl;
					cout << "not answered yet " << endl;
				}
			}
		}
		if (ok == 0) {
			cout << "there is no questions" << endl;
		}
	}
	bool check_from_quections(string g) {
		sort_questions();
		sort_users();
		sort_answers();
		for (int i = 0; i < A.size(); i++) {
			if (A[i].from == g) {
				return 1;
			}
		}
		return 0;
	}
	bool check_to_quections(string g) {
		sort_questions();
		sort_users();
		sort_answers();
		for (int i = 0; i < A.size(); i++) {
			if (A[i].to == g) {
				return 1;
			}
		}
		return 0;
	}
	void questions_to_me(string idd) {
		sort_questions();
		sort_users();
		sort_answers();
		bool ok = 0;
		bool fn = 0;
		for (int j = 0; j < A.size(); j++) {
			if (A[j].to == idd) {
				ok = 1;
				for (int kl = 0; kl < a.size(); kl++) {
					if (A[j].id == a[kl].IDD) {
						cout << "[" << A[j].id << "]" << " ";
						cout << A[j].quest << " from ID " << A[j].from << endl;
						cout << "answer   " << a[kl].answer << endl;
						fn = 1;
						break;
					}
					else {
						fn = 0;
					}
				}
				if (fn == 0) {
					cout << "[" << A[j].id << "]" << " ";
					cout << A[j].quest << " from ID " << A[j].from << endl;
					cout << "not answerd yet" << endl;
				}
			}
		}
		if (ok == 0) {
			cout << "there is no questions !" << endl;
		}
	}
	bool check_id_user(string s , string r) {
		vector<string>us;
		sort_questions();
		sort_users();
		sort_answers();
		bool ok = 0;
		for (int i = 0; i < v.size(); i++) {
			if (v[i].id != s) {
				us.push_back(v[i].id);
			}
		}
		for (int i = 0; i < us.size(); i++) {
			if (us[i] == r) {
				ok = 1;
				return 1;
			}
		}
		if (ok == 0) {
			return 0;
		}
	}
	bool check_id_quection(string g , string f) {
		vector<string>s1;
		sort_questions();
		sort_users();
		sort_answers();
		bool ok = 0;
		for (int i = 0; i < A.size(); i++) {
			if (A[i].to == g) {
				s1.push_back(A[i].id);
			}
		}
		for (int i = 0; i < s1.size(); i++) {
			if (f == s1[i]) {
				ok = 0;
				return 1;
			}
			else {
				ok = 1;
			}
		}
		if (ok == 1) {
			return 0;
		}
	}
	bool check_idd_quection(string g, string f) {
		vector<string>s2;
		sort_questions();
		sort_users();
		sort_answers();
		bool ok = 0;
		for (int i = 0; i < A.size(); i++) {
			if (A[i].from == g) {
				s2.push_back(A[i].id);
			}
		}
		for (int i = 0; i < s2.size(); i++) {
			if (f == s2[i]) {
				ok = 0;
				return 1;
			}
			else {
				ok = 1;
			}
		}
		if (ok == 1) {
			return 0;
		}
	}
	void answer_question(string s) {
		sort_questions();
		sort_users();
		sort_answers();
		ANS AW;
		string f;
		string ff;
		for (int j = 0; j < A.size(); j++) {
			if (A[j].id == s) {
				ff = s;
				AW.IDD = s;
				cout << "well , write your answer " << endl;
				cin.ignore();
				getline(cin, f);
				fstream ffile("answers.txt", ios::app);
				ffile << f << endl;
				ffile << s << endl;
				ffile.close();
				AW.answer = f;
				AW.IDD = A[j].id;
				a.push_back(AW);
			}
		}
	}
	void deletee(string gs) {
		sort_questions();
		sort_users();
		sort_answers();
		for (int i = 0; i < A.size(); i++) {
			if (A[i].id == gs) {
				A.erase(A.begin() + i);
				for (int j = 0; j < a.size(); j++) {
					if (a[j].IDD == gs) {
						a.erase(a.begin() + j);
					}
				}
			}
		}
	}
	void feed() {
		sort_questions();
		sort_users();
		sort_answers();
		if (A.size() == 0) {
				cout << "There are no questions answered in the system " << endl;
		}
		else {
			bool z = 0;
			for (int k = 0; k < A.size(); k++) {
				for (int g = 0; g < a.size(); g++) {
					if (A[k].id == a[g].IDD) {
						z = 1;
						cout << "[" << A[k].id << "]" << " ";
						cout << A[k].quest << " from ID " << A[k].from << " to ID " << A[k].to << endl;
						cout << "answer   " << a[g].answer << endl;
					}
				}
			}
			if (z == 0) {
				cout<<"There are no questions answered in the system " << endl;
			}
		}
	}
	bool unique_id(string sg) {
		bool k = 0;
		for (int b = 0; b < v.size(); b++) {
			if (v[b].id == sg) {
				k = 1;
				return 0;
			}
		}
		if (k == 0) {
			return 1;
		}
	}
	bool unique_username(string sg) {
		bool k = 0;
		for (int b = 0; b < v.size(); b++) {
			if (v[b].name == sg) {
				k = 1;
				return 0;
			}
		}
		if (k == 0) {
			return 1;
		}
	}
	void sign_up() {
		sort_questions();
		sort_users();
		sort_answers();
		user s1;
		fstream myfile("uesrs.txt",ios::app);
		cout << "enter your name " << endl;
		cin >> name;
		while (unique_username(name) != 1) {
			cout << "this username Already exists , write another username" << endl;
			cin >> name;
		}
		s1.name = name;
		cout << "enter your id " << endl;
		cin >> id;
		while (unique_id(id) != 1 || id[0]=='-') {
			cout << "invalid ID , write another one" << endl;
			cin >> id;
		}
		s1.id = id;
		tem2 = id;
		cout << "enter your password " << endl;
		cin >> password;
		while (password.size() < 8) {
			cout << "invalid password , your password should be at least 8 characters"<<endl;
				cin >> password;
		}
		s1.password = password;
		myfile <<name<<endl;
		myfile <<id<<endl;
		myfile <<password<<endl;
		v.push_back(s1);
		myfile.close();
		Menu2();
		cin >> number;
		while (number != 8) {
			if (number == 6) {
				showallusers();
			}
			if (number == 7) {
				feed();
			}
			if (number == 5) {
				bool kk = 0;
				QA M;
				fstream mfile("questions.txt", ios::app);
				string te;
				string s, l = "100";
				tem = v[v.size() - 1].id;
				M.from = tem;
				for (int kg = 0; kg < v.size(); kg++) {
					if (v[kg].id != tem2) {
						kk = 1;
						cout << "ID " << v[kg].id << "     " << "name: " << v[kg].name << endl;
					}
				}
				if (kk == 0) {
					cout << "there is no users to ask them" << endl;
				}
				else {
					cout << "enter user id " << endl;
					cin >> te;
					while (check_id_user(tem2, te) != 1) {
						cout << "invalid id user" << endl;
						cin >> te;
						check_id_user(tem2, te);
					}
					M.to = te;
					cout << "enter question text " << endl;
					cin.ignore();
					getline(cin, s);
					M.quest = s;
					if (A.size() == 0) {
						M.id = l;
					}
					else {
						fstream mfile("questions.txt", ios::in);
						int cm = 0;
						string temp;
						while (getline(mfile, temp)) {
							if (cm % 4 == 3) {
								int tn = stoi(temp);
								tn++;
								M.id = to_string(tn);
								l = to_string(tn);
							}
							cm++;
						}
						mfile.close();
					}
					mfile << s << endl;
					mfile << te << endl;
					mfile << tem << endl;
					mfile << l << endl;
					mfile.close();
					A.push_back(M);
				}
			}
			if (number == 1) {
				questions_to_me(tem2);
			}
			if (number == 2) {
				questions_from_me(tem2);
			}
			if (number == 3) {
				if (A.size() == 0 || check_to_quections(tem2) == 0) {
					cout << "there is no questions to answer !" << endl;
				}
				else {
					questions_to_me(tem2);
					cout << "enter question id" << endl;
					string km;
					cin >> km;
					while (check_id_quection(tem2, km) != 1) {
						cout << "invalid ID , write anthor one " << endl;
						cin >> km;
						check_id_quection(tem2, km);
					}
					answer_question(km);
				}
			}
			if (number == 4) {
				if (A.size() == 0 || check_from_quections(tem2)==0) {
					cout << "there is no questions to delete !" << endl;
				}
				else {
					questions_from_me(tem2);
					cout << "enter question id " << endl;
					string g;
					cin >> g;
					while (check_idd_quection(tem2 , g) != 1) {
						cout << "invalid ID , write anthor one " << endl;
						cin >> g;
						check_idd_quection(tem2,g);
					}
					deletee(g);
					fstream mfile("questions.txt" , ios::out);
					for (int v = 0; v < A.size(); v++) {
						mfile << A[v].quest << endl;
						mfile << A[v].to << endl;
						mfile << A[v].from << endl;
						mfile << A[v].id << endl;
					}
					mfile.close();
					fstream ffile("answers.txt" , ios::out);
					ANS MN;
					for (int v = 0; v < a.size(); v++) {
						ffile << a[v].answer << endl;
						ffile << a[v].IDD << endl;
					}
					ffile.close();
				}

			}
			Menu2();
			cin >> number;
		}
	}
	 void signin() {
		 sort_questions();
		 sort_users();
		 sort_answers();
		 int c = 0;
		 bool found = 0;
		 while (found == 0) {
			 string s, pas, ID;
			 cout << "enter your name " << endl;
			 cin >> name;
			 s = name;
			 cout << "enter your password " << endl;
			 cin >> password;
			 pas = password;
			 for (int i = 0; i < v.size(); i++) {
				 if (v[i].name == s &&  v[i].password == pas) {
					 tem = v[i].id;
					 found = 1;
					 break;
				 }
			 }
			 if (found == 1) {
				 cout << "you are logged in " << endl;

				 Menu2();
				 cin >> number;
				 while (number != 8) {
					 if (number == 6) {
						 showallusers();
					 }
					 if (number == 5) {
						 QA M;
						 string te;
						 bool m = 0;
						 string l = "100";
						 string s;
						 M.from = tem;
						 for (int j = 0; j < v.size(); j++) {
							 if (v[j].id != tem) {
								 m = 1;
								 cout << "ID " << v[j].id << "     " << "name: " << v[j].name << endl;
							 }
						 }
						 if (m == 0) {
							 cout << "there are no users to ask them " << endl;
						 }
						 else {
						 cout << "enter user id " << endl;
						 cin >> te;
						 while (check_id_user(tem, te) != 1) {
							 cout << "invalid id user" << endl;
							 cin >> te;
							 check_id_user(tem, te);
						 }
						 M.to = te;
						 cout << "enter question text " << endl;
						 cin.ignore();
						 getline(cin, s);
						 M.quest = s;
						 if (A.size() == 0) {
							 M.id = l;
						 }
						 else {
							 fstream mfile("questions.txt", ios::in);
							 int cm = 0;
							 string temp;
							 while (getline(mfile, temp)) {
								 if (cm % 4 == 3) {
									 int tn = stoi(temp);
									 tn++;
									 M.id = to_string(tn);
									 l = to_string(tn);
								 }
								 cm++;
							 }
							 mfile.close();
						 }
						 fstream mfile("questions.txt", ios::app);
						 mfile << s << endl;
						 mfile << te << endl;
						 mfile << tem << endl;
						 mfile << l << endl;
						 mfile.close();
						 A.push_back(M);
					 }
					 }
					 if (number == 1) {
						 questions_to_me(tem);
					 }
					 if (number == 2) {
						 questions_from_me(tem);
					 }
					 if (number == 3) {
						 if (A.size() == 0 || check_to_quections(tem) == 0) {
							 cout << "there is no questions to answer !" << endl;
						 }
						 else {
							 questions_to_me(tem);
							 cout << "enter question id" << endl;
							 string km;
							 cin >> km;
							 while (check_id_quection(tem, km) != 1) {
								 cout << "invalid ID , write anthor one " << endl;
								 cin >> km;
								 check_id_quection(tem, km);
							 }
							 answer_question(km);
						 }
					 }
					 if (number == 4) {
						 if (A.size() == 0 || check_from_quections(tem) == 0) {
							 cout << "there is no questions to delete !" << endl;
						 }
						 else {
							 questions_from_me(tem);
							 cout << "enter question id " << endl;
							 string g;
							 cin >> g;
							 while (check_idd_quection(tem, g) != 1) {
								 cout << "invalid ID , write anthor one " << endl;
								 cin >> g;
								 check_idd_quection(tem2, g);
							 }
							 deletee(g);
							 fstream mfile("questions.txt", ios::out);
							 for (int v = 0; v < A.size(); v++) {
								 mfile << A[v].quest << endl;
								 mfile << A[v].to << endl;
								 mfile << A[v].from << endl;
								 mfile << A[v].id << endl;
							 }
							 mfile.close();
							 fstream ffile("answers.txt", ios::out);
							 ANS MN;
							 for (int v = 0; v < a.size(); v++) {
								 ffile << a[v].answer << endl;
								 ffile << a[v].IDD << endl;
							 }
							 ffile.close();
						 }
					 }
					 if (number == 7) {
						 feed();
					 }
					 Menu2();
					 cin >> number;
				 }
			 }
			 else {
				 cout << "enter correct name & password !" << endl;
			 }
		 }
	}
};
int main()
{
	service ob;
	ob.sort_users();
	ob.sort_questions();
	ob.sort_answers();
	Menu();
	if (x == 1) {
		ob.signin();
	}
	else {
		ob.sign_up();
	}

}
