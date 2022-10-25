#ifndef ATM_HPP_
#define ATM_HPP_
typedef char IdType[9];
typedef char PinType[7];
enum UserType {USER, ADMIN};
struct User
{
    IdType UserId;
    PinType UserPin;
    UserType UserType;
    int TodayAttempt, AccountBalance;
    User *next;
};
typedef User *UserList;

char *GetTime(void);
void AdminLoginForm(IdType userId, PinType userPin);
bool AdminVerify(IdType userId, PinType userPin, UserList userList);
void UserLoginForm(IdType userId, PinType userPin);
bool UserVerify(IdType userId, PinType userPin, UserList userList);
void ProjectLogo();
void UserMenu(int &choice);
void AdminMenu(int &choice);
void InsertAccountToUserList(UserList &userList, IdType newId, PinType newPin, int userType, int newAccountBalance);
void InitializeUserList(UserList &userList);
void UpdateUserInUserList(UserList &userList);
void UserInfo(UserList userList, IdType userId);
void WithdrawMoney(UserList &userList, IdType userId);
void DepositMoney(UserList &userList, IdType userId);
bool IsOverTodayAttempt(UserList &userList, IdType userId);
void ATM(UserList &userList);
void GetChoice(int &choice);
void HidePin(char password[]);
void GetUserInputMoneyValue(int &value);
void System(UserList &userList);
#endif