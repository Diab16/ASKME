#include <bits\stdc++.h>
using namespace std;

class Answer
{
private:
	string ans;
	string from;
public:
	Answer(string ans_, string from_);
	string getAns();
	string getFrom();
};

class Question
{
private:
	string question;
	string from;
	string to;
	vector<Answer>answers;
public:
	Question(string q, string from_);
	string getQ();
	//void setQ(string q);
	string getQfrom();
	//void setQfrom();
	string getQto();
	//void setQto();
	void addAns(Answer nA);
	void prtintAns();
};

class User
{
private:
	string userName;
	string pass;
	vector<Question>QuToMe;
	vector<pair<int, int>>QuFromMe; //the indexes of the question  (first user indes, second question index)

	int index;
public:
	User(string userName_, string pass_, int index_);
	string getUserName();
	string getPass();
	void printQuToMe();
	void printQuFromMe();
	int addQ(string Q, string from_);
	void qFromMe(int uInd, int qInd);
	void answerQu(string myUserName);
	void deleteQu();
};


class runAskfm
{
private:
	vector<User> users;
	int curruntUserIndex;
public:
	void startMenu();
	void mainMenu();
	int Login();
	int Register();
	void askQu();
	void listSystemUsers();
	void feed();
	void logout();
	void wrongInput();
	int findUser(string user_);
};

void runAskfm::startMenu()
{
	cout << "\t 1-Login\n";
	cout << "\t 2-Register\n";
	cout << "Enter your choice number:";
	int c;
	cin >> c;
	while (c < 1 || c>2)
	{
		wrongInput();
		cout << "Enter your choise number:";
		cin >> c;
	}
	if (c == 1)
		curruntUserIndex = Login();
	else // c==2
		curruntUserIndex = Register();
	mainMenu();
}

int runAskfm::findUser(string user_)
{
	for (int i = 0; i < users.size(); i++)
	{
		if (users[i].getUserName() == user_)
			return i;
	}
	return -1;
}

int runAskfm::Login()
{
	string userName, pass;
	cout << "Enter your username and password: ";
	cin >> userName >> pass;
	int userIndex = findUser(userName);
	while (userIndex == -1 || (userIndex < -1 && users[userIndex].getPass() != pass))
	{
		wrongInput();
		userIndex= Login();
	}
	return userIndex;
}

int runAskfm::Register()
{
	string userName, pass;
	cout << "user name must be unique\nEnter username and password: ";
	cin >> userName >> pass;
	int userIndex = findUser(userName);
	if (userIndex !=-1) // not valid userName
	{
		wrongInput();
		userIndex = Register();
	}
	else
	{
		userIndex = users.size();
		User n(userName, pass, userIndex);
		users.push_back(n);
	}
	return userIndex;
}

void runAskfm::wrongInput()
{
	cout << "wrong input try again\n\a";
}

User::User(string userName_, string pass_, int index_)
{
	userName = userName_; pass = pass_; index = index_;
}

void runAskfm::mainMenu()
{
	int c;
	cout << "Main Menu\n"
		<< "\t1-Print question to me\n"
		<< "\t2-Print question from me\n"
		<< "\t3-Answer question\n"
		<< "\t4-Delete \n"
		<< "\t5-Ask \n"
		<< "\t6-List system users\n"
		<< "\t7-Feed\n"
		<< "\t8-Logout\n";
	cout << "Enter your choice: ";
	cin >> c;
	while (c < 1 || c>8)
	{
		wrongInput();
		cout << "Enter your choice: ";
		cin >> c;
	}
	if (c == 1)
		users[curruntUserIndex].printQuToMe();
	else if (c == 2)
		users[curruntUserIndex].printQuFromMe();
	else if (c == 3)
		users[curruntUserIndex].answerQu(users[curruntUserIndex].getUserName());
	else if (c == 4)
		users[curruntUserIndex].deleteQu();
	else if (c == 5)
		askQu();
	else if (c = 6)
		listSystemUsers();
	else if (c == 7)
		feed();
	else //if (c == 8)
		logout();

}

void runAskfm::listSystemUsers()
{
	for (int i = 0; i < users.size(); i++)
	{
		cout << "->" << users[i].getUserName() << "\n";
	}
}
void runAskfm::feed()
{
	for (int i = 0; i < users.size(); i++)
	{
		users[i].printQuToMe();
		cout << "///////////////////////////////////////////////\n";
	}
}
void runAskfm::logout()
{
	system("CLS");// clear screen
	curruntUserIndex = -1;
	startMenu();
}

string User::getUserName()
{
	return userName;
}
string User::getPass()
{
	return pass;
}
void User::printQuToMe()
{
	cout << "The questions to you\n";
	for (int i = 0; i < QuToMe.size(); i++)
	{
		cout << "\tq" << i + 1 << ")" << QuToMe[i].getQ() << "\n\tfrom: " << QuToMe[i].getQfrom() << "\n";
		QuToMe[i].prtintAns();
	}

}
void User::printQuFromMe()///////////////need inhertance/////////////////
{
	for (int i = 0; i < QuFromMe.size(); i++)
	{
		//users[QuFromMe[i].first].QuToMe[QuFromMe[i].second]
		/*
		//q print
		cout << "\tq" << i + 1 << ")" << users[QuFromMe[i].first].QuToMe[QuFromMe[i].second].getQ()
		<< "\n\tto: " << users[QuFromMe[i].first].QuToMe[QuFromMe[i].second].getQto() << "\n";
		users[QuFromMe[i].first].QuToMe[QuFromMe[i].second].prtintAns();
		*/
	}
}

void runAskfm::askQu()
{
	string user_, q_;
	cout << "Enter the username that you want to ask him: ";
	cin >> user_;
	int userIndex = findUser(user_);
	while (userIndex == -1)
	{
		wrongInput();
		cout << "Enter the username that you want to ask him: ";
		cin >> user_;
	}
	cout << "Enter your question\n\t";
	cin >> q_;
	int qIndex = users[userIndex].addQ(q_, users[curruntUserIndex].getUserName());
	users[curruntUserIndex].qFromMe(userIndex, qIndex);
}
int User::addQ(string q,string from_)
{
	Question n(q, from_);
	QuToMe.push_back(n);
	return QuToMe.size() - 1;
}
void User::qFromMe(int uInd, int qInd)//the indexes of the question  (first user index, second question index)
{
	QuFromMe.back() = make_pair(uInd, qInd);
}

Question::Question(string q, string from_)
{
	question = q;
	from = from_;
}
void User::answerQu(string myUserName)//Question to me
{
	int qNum;
	cout << "Enter Question Number: ";
	cin >> qNum;
	cout << "Enter your answer\n\t";
	string myAns;
	cin >> myAns;
	Answer n(myAns, myUserName);
	QuToMe[qNum].addAns(n);
}
void User::deleteQu()/////////////////////delete from QuFromMe problem(bug)
{
	int n;
	cout << "Enter the question that you want to delete: ";
	cin >> n;
	QuToMe.erase(QuToMe.begin() + n);
}

string Question::getQ()
{
	return question;
}
string Question::getQfrom()
{
	return from;
}
string Question::getQto()
{
	return to;
}
void Question::addAns(Answer nA)
{
	answers.push_back(nA);
}

void Question::prtintAns()
{
	for (int i = 0; i < answers.size(); i++)
	{
		cout << "\t-" << answers[i].getAns() << "\tfrom: " << answers[i].getFrom() << "\n";
	}
}

Answer::Answer(string ans_,string from_)
{
	ans = ans_;
	from = from_;
}

string Answer::getAns()
{
	return ans;
}
string Answer::getFrom()
{
	return from;
}


int main()
{
    runAskfm n;
    n.startMenu();
    return 0;
}

