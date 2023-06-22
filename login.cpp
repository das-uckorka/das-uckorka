#include <iostream>
#include <map>
#include <string>

#define Login 'L'
#define Register 'R'

#define THE_LOGIN_IS_ALREDY_EXIST 1
#define WRONG_PASSWORD 2
#define WRONG_LOGIN 3
#define TOO_MUCH_TRYING 4
#define DIFFERENT_PASSWORDS 5

std::map<std::string, std::string> USERS {{"admin", "1234"}};

// Messages
void error_message(uint32_t);
void succesfully_message();

// Login or register

void register_user();
void login_user();

// Get functions
std::string get_password_require();
std::string get_login();
std::string get_password();


int main() {
	char update = 'Y';
	while (update == 'Y') {
		std::cout << "Log in or register? (L/R)" << std::endl;
		char answer;
		std::cin >> answer;

		switch (answer) {
		case Login:
			login_user();
			break;
		case Register:
			register_user();
			break;
		}

		std::cout << USERS.size() << std::endl;

		std::cout << "Continue? (Y/n)" << std::endl;
		std::cin >> update;
	}

	return 0;
}

std::string get_login() {
	std::cout << "Nickname: ";
	std::string LOGIN;
	std::cin >> LOGIN;
	return LOGIN;
}

std::string get_password() {
	std::cout << "Password: ";
	std::string PASSWORD;
	std::cin >> PASSWORD;
	return PASSWORD;
}

void register_user() {
	std::string LOGIN = get_login();
	auto it = USERS.find(LOGIN);



	while (it != USERS.end()) {
		error_message(THE_LOGIN_IS_ALREDY_EXIST);
		LOGIN = get_login();
		it = USERS.find(LOGIN);
	}

	std::string PASSWORD = get_password();

	std::string REQUAIRE_PASSWORD = get_password_require();

	while (REQUAIRE_PASSWORD != PASSWORD) {
		error_message(DIFFERENT_PASSWORDS);
		REQUAIRE_PASSWORD = get_password_require();
	}

	USERS.emplace(LOGIN, PASSWORD);


	succesfully_message();
}

void login_user() {
	std::string LOGIN = get_login();
	auto it = USERS.find(LOGIN);


	while (it == USERS.end()) {
		error_message(WRONG_LOGIN);

		LOGIN = get_login();
		it = USERS.find(LOGIN);

	}
	uint32_t counter_try = 1;
	std::string PASSWORD = get_password();
	while (PASSWORD != USERS.at(LOGIN)) {
		error_message(WRONG_PASSWORD);

		PASSWORD = get_password();

		counter_try++;
		if (counter_try == 3) error_message(TOO_MUCH_TRYING);
	}

	succesfully_message();
}


std::string get_password_require() {
	std::cout << "Require your password: ";
	std::string REQUAIRE_PASSWORD;
	std::cin >> REQUAIRE_PASSWORD;

	return REQUAIRE_PASSWORD;
}


void error_message(uint32_t ERROR_NUMBER) {
	switch (ERROR_NUMBER) {
	case THE_LOGIN_IS_ALREDY_EXIST:
		std::cout << "This nickname is already exist.\n";
		break;
	case TOO_MUCH_TRYING:
		std::cout << "Too much trying to input password, try later.";
		system("pause");
		break;
	case WRONG_LOGIN:
		std::cout << "This login doesn't exist. Try one more time.\n";
		break;
	case WRONG_PASSWORD:
		std::cout << "This password is wrong. Try again.\n";
		break;
	case DIFFERENT_PASSWORDS:
		std::cout << "The passwords are not the same.\n";
	}
}

void succesfully_message() {
	std::cout << "Succesfully done!" << '\n';
}
