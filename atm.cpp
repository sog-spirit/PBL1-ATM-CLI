#include <bits/stdc++.h>
#include <conio.h>
#include "atm.hpp"
#include <windows.h>

#define MAX 50000000
#define MIN 50000

UserList userList;

char *GetTime(void) {
    time_t rawtime;
    struct tm *timeInfo;

    time(&rawtime);
    timeInfo = localtime(&rawtime);

    static char _retval[20];
    strftime(_retval, sizeof(_retval), "%d-%m-%Y %H:%M:%S", timeInfo);

    return _retval;
}

void AdminLoginForm(IdType userId, PinType userPin) {
    printf("\n\nDang nhap danh cho nhan vien ngan hang.\n");
    printf("\nTai khoan: "); gets(userId);
    printf("\nMat khau: "); HidePin(userPin);
}

bool AdminVerify(IdType userId, PinType userPin, UserList userList) {
    UserList p = userList;
    while (p != NULL) {
        if (strcmp((*p).UserId, userId) == 0 && strcmp((*p).UserPin, userPin) == 0 && (*p).UserType == ADMIN)
            return true;
        p = (*p).next;
    }
    return false;
}

void UserLoginForm(IdType userId, PinType userPin) {
    printf("\n\nNgan hang xin kinh chao.\n");
    printf("\nTai khoan: "); gets(userId);
    printf("\nMat khau: "); HidePin(userPin);
}

bool UserVerify(IdType userId, PinType userPin, UserList userList) {
    UserList p = userList;
    while (p != NULL) {
        if (strcmp((*p).UserId, userId) == 0 && strcmp((*p).UserPin, userPin) == 0 && (*p).UserType == USER)
            return true;
        p = (*p).next;
    }
    return false;
}

void ProjectLogo() {
    printf("\n\n-----------------------------------------------");
    printf("\n|      Do An Co So         De tai 701         |");
    printf("\n|                                             |");
    printf("\n|   Phan mem tren may ATM bang ngon ngu C     |");
    printf("\n|                                             |");
    printf("\n|   Nguoi thuc hien: To Ba Thanh              |");
    printf("\n|                    Nguyen Tien Hung         |");
    printf("\n|                                             |");
    printf("\n|   Giao vien huong dan: Tran Ho Thuy Tien    |");
    printf("\n-----------------------------------------------\n\n");
}

void UserMenu(int &choice) {
    printf("\n\n-----------------------------------------------");
    printf("\n|  ABCBANK                                    |");
    printf("\n|                                             |");
    printf("\n|             Kinh chao quy khach!            |");
    printf("\n|                                             |");
    printf("\n|  1. Rut tien                                |");
    printf("\n|                                             |");
    printf("\n|  2. Gui tien                                |");
    printf("\n|                                             |");
    printf("\n|  3. Kiem tra tai khoan                      |");
    printf("\n|                                             |");
    printf("\n|  4. Dang xuat                               |");
    printf("\n-----------------------------------------------");
    printf("\n\n Lua chon cua quy khach: ");
    GetChoice(choice);
    while (!(choice==1 || choice==2 || choice==3 || choice==4)) {
        printf("Khong hop le. Hay nhap lai. Lua chon cua ban: ");
        GetChoice(choice);
    }
}

void AdminMenu(int &choice) {
    printf("\n\n-----------------------------------------------");
    printf("\n|            Menu chinh cua ADMIN             |");
    printf("\n|                                             |");
    printf("\n|  1. Khoi dong he thong                      |");
    printf("\n|                                             |");
    printf("\n|  2. Dang xuat, shutdown may ATM             |");
    printf("\n|                                             |");
    printf("\n-----------------------------------------------");
    printf("\n\n Lua chon: ");
    GetChoice(choice);
    while (!(choice==1 || choice==2)) {
        printf("Khong hop le. Hay nhap lai. Lua chon cua ban: ");
        GetChoice(choice);
    }
}

void InsertAccountToUserList(UserList &userList, IdType newId, PinType newPin, int userType, int newAccountBalance) {
    UserList newUser;
    newUser = new User;
    strcpy((*newUser).UserId, newId);
    strcpy((*newUser).UserPin, newPin);
    (*newUser).AccountBalance = newAccountBalance;
    (*newUser).UserType = (UserType) userType;
    (*newUser).TodayAttempt = 0;
    (*newUser).next = userList;
    userList = newUser;
    // printf("%s %s %d %d\n", newId, newPin, userType, newAccountBalance);
}

void InitializeUserList(UserList &userList) {
    char line[256], string1[9], string2[7], string3[20], string4[20], string5[20], temp[20];
    IdType userId;
    PinType userPin;
    int userType, accountBalance, userAttempt;
    FILE *input = fopen("account.txt", "r");
    if (input == NULL) {
        printf("\nLoi: khong tim thay account.txt. Ket thuc chuong trinh.");
        exit(0);
    }
    while(!feof(input)) {
        if (fgets(line, sizeof(line), input) == NULL) break;
        // printf("%s\n", line);
        // char *token = strtok(line, " ");
        // strcpy(userId, token);
        // token = strtok(NULL, " ");
        // strcpy(userPin, token);
        // token = strtok(NULL, " ");
        // strcpy(temp, token);
        // accountBalance = atoi(temp);
        // token = strtok(NULL, " ");
        // strcpy(temp, token);
        // userType = atoi(token);
        // token = strtok(NULL, " ");
        // userAttempt = atoi(token);
        // printf("%s %s %s %d %d\n", userId, userPin, accountBalance, userType, userAttempt);
        // while(token != NULL) {
        //     printf("%s ", token);
        //     token = strtok(NULL, " ");
        // }
        printf("DEBUG: %s\n", line);
        sscanf(line, "%s %s %s %s %s\n", string1, string2, string3, string4, string5);
        printf("sscanf result: %s %s %s %s %s\n", string1, string2, string3, string4, string5);
        strcpy(userId, string1);
        strcpy(userPin, string2);
        strcpy(temp, string3); accountBalance = atoi(temp);
        strcpy(temp, string4); userType = atoi(temp);
        printf("%s %s %d %d\n", userId, userPin, accountBalance, userType);
        InsertAccountToUserList(userList, userId, userPin, userType, accountBalance);
    }
    fclose(input);
}

void UpdateUserInUserList(UserList &userList) {
    UserList p = userList;
    FILE *output = fopen("account.txt", "w");
    while (p != NULL) {
        fprintf(output, "%s %s %d %d %d\n", (*p).UserId, (*p).UserPin, (*p).AccountBalance, (*p).UserType, (*p).TodayAttempt);
        p = (*p).next;
    }
    fclose(output);
}

void UserInfo(UserList userList, IdType userId) {
    UserList p = userList;
    FILE *output = fopen("ATMlog.txt", "a");
    while (p != NULL) {
        if (strcmp((*p).UserId, userId) == 0) break;
        p = (*p).next;
    }
    printf("\n-----------------------------------------------");
    printf("\n\nThong tin ve tai khoan:");
    printf("\n\nSo tai khoan: %s", (*p).UserId);
    printf("\n\nSo du hien tai: %d", (*p).AccountBalance);
    printf("\n\n-----------------------------------------------");
    Sleep(2000);
    fprintf(output, "\n***************\nTai khoan %s da thuc hien truy van tai khoan vao ngay %s", (*p).UserId, GetTime());
    fclose(output);
}

void WithdrawMoney(UserList &userList, IdType userId) {
int value = 0;
    UserList p = userList;
    FILE *output = fopen("ATMlog.txt", "a");
    while (p != NULL) {
        if (strcmp((*p).UserId, userId) == 0) break;
        p = (*p).next;
    }
    if ((*p).AccountBalance < 50000) {
        printf("\nSo du cua ban khong du de thuc hien giao dich nay.\n\nQuay tro ve menu...");
        Sleep(2000); 
        return;
    }
    printf("\n\n***LUU Y***\nSo tien toi thieu (50,000). So tien toi da (50,000,000). So tien rut la boi cua 10,000.\n\nSo tien muon rut: ");
	GetUserInputMoneyValue(value);
	while (!(value%10000==0 && value<=MAX && value>=MIN && (*p).AccountBalance >=value)) {
        printf("\n\nSo tien khong hop le hoac khong du de thuc hien giao dich.\n\nSo tien muon rut: ");
        GetUserInputMoneyValue(value);
    }
    (*p).AccountBalance -= value;
    (*p).TodayAttempt += 1;
    printf("\nQuy khach da rut thanh cong %d VND.\nSo du moi cua quy khach la %d VND.\nSo du cu: %d VND.", value, (*p).AccountBalance, (*p).AccountBalance + value);
    fprintf(output, "\n***************\nTai khoan %s da rut %d VND vao ngay %s.\nSo du cu: %d VND.\nSo du moi: %d VND", (*p).UserId, value, GetTime(), (*p).AccountBalance + value, (*p).AccountBalance);
    fclose(output);
}

void DepositMoney(UserList &userList, IdType userId) {
    int value;
    UserList p = userList;
    FILE *output=fopen("ATMlog.txt", "a");
    while (p != NULL) {
        if (strcmp((*p).UserId, userId) == 0) break;
        p = (*p).next;
    }
    printf("\n\n***LUU Y***\nSo tien toi thieu (50,000). So tien toi da (50,000,000).\n\nSo tien ban muon nap: ");
    GetUserInputMoneyValue(value);
    while (!(value%10000==0 && value<=MAX && value>=MIN)) {
        printf("\n\nSo tien khong hop le. So tien ban muon nap: ");
        GetUserInputMoneyValue(value);
    }
    (*p).AccountBalance += value;
    printf("\n\nQuy khach da nap thanh cong %d VND.\nSo du moi: %d VND.\nSo du cu: %d VND", value, (*p).AccountBalance, (*p).AccountBalance - value);
    fprintf(output, "\n***************\nTai khoan %s da nap %d VND vao ngay %s.\nSo du cu: %d VND.\nSo du moi: %d VND.", (*p).UserId, value, GetTime(), (*p).AccountBalance - value, (*p).AccountBalance);
    fclose(output);
}

bool IsOverTodayAttempt(UserList &userList, IdType userId) {
    UserList p = userList;
    while (p != NULL) {
        if (strcmp((*p).UserId, userId) == 0) break;
        p = (*p).next;
    }
    if ((*p).TodayAttempt < 5) return true;
    return false;
}

void ATM(UserList &userList) {
    printf("\nBat dau khoi tao chuong trinh...");
    Sleep(2000);
    printf("Khoi tao thanh cong.");
    Sleep(1000);
    int user_choice; IdType id; PinType pin;
    do {
        user_choice=0;
        ProjectLogo();
        UserLoginForm(id, pin);
        while (!UserVerify(id, pin, userList)) {
            if (AdminVerify(id, pin, userList)) break;
            printf("\n\nSai ten tai khoan hoac mat khau.\n");
            UserLoginForm(id, pin);
        }
        while (!(user_choice == 4) && !(AdminVerify(id, pin, userList))){
            UserMenu(user_choice);
            switch(user_choice) {
                case 1:
                    if(!IsOverTodayAttempt(userList, id)) {
                        printf("\n\nTai khoan cua ban da vuot qua han muc giao dich trong ngay. ");
                        Sleep(2000);
                        printf("\n\nQuay tro ve menu...");
                        Sleep(2000);
                        break;
                    }
                    WithdrawMoney(userList, id);
                    break;
                case 2:
                    if (!IsOverTodayAttempt(userList, id)) {
                        printf("\n\nTai khoan cua ban da vuot qua han muc giao dich trong ngay. ");
                        Sleep(2000);
                        printf("\n\nQuay tro ve menu...");
                        Sleep(2000);
                        break;
                    }
                    DepositMoney(userList, id);
                    break;
                case 3:
                    UserInfo(userList, id);
                    break;
                case 4:
                    printf("\n\nCam on nguoi dung da su dung dich vu ATM.");
                    Sleep(2000);
                    break;
                default:
                    printf("\n\nKhong hop le.");
                    break;
            }
        }
    } while (!AdminVerify(id, pin, userList));
    printf("\n\nTro ve cua so admin...");
    Sleep(2000);
    ProjectLogo();
}

void GetChoice(int &choice) {
    char buf[15];
    char *end;
    while(1) {
        gets(buf);
        if (buf[0]=='\0'){
            printf("\nKhong hop le. Hay nhap lai. Lua chon cua ban: ");
            gets(buf);
        }
        int n = strtol(buf, &end, 10);
        if (end == buf+strlen(buf)) break;
        else printf("\nKhong hop le. Hay nhap lai. Lua chon cua ban: ");
    }
    choice = atoi(buf);
}

void HidePin(char pin[]) {
    int p = 0;
    do {
        pin[p] = getch();
        if (pin[p] != '\r') {
            printf("*");
        }
        p++;
    } while (pin[p-1] != '\r');
    pin[p-1] = '\0';
}

void GetUserInputMoneyValue(int &value) {
    char buf[15];
    char *end;
    while(1) {
        gets(buf);
        if (buf[0] == '\0') {
            printf("So tien khong hop le hoac khong du de thuc hien giao dich.\n\nSo tien muon rut: "); gets(buf);
        }
        int n=strtol(buf, &end, 10);
        if (end == buf+strlen(buf)) break;
        else printf("So tien khong hop le hoac khong du de thuc hien giao dich.\n\nSo tien muon rut: ");
    }
    value = atoi(buf);
}

void System(UserList &userList) {
    int admin_choice = 0, user_choice = 0;
	IdType adminId, userId;
	PinType adminPin, userPin;
	InitializeUserList(userList);
	ProjectLogo();
	while (!(admin_choice==2)) {
		admin_choice = 0;
		do {
			AdminLoginForm(adminId, adminPin);
			if (!AdminVerify(adminId, adminPin, userList))
                printf("\n\nSai ten tai khoan hoac mat khau.\n");
		} while(!AdminVerify(adminId, adminPin, userList));

        do {
            AdminMenu(admin_choice);
            switch(admin_choice) {
                case 1:
                    ATM(userList);
                    break;
                case 2:
                    printf("\n\nCap nhat file account.txt...");
                    Sleep(2000);
                    UpdateUserInUserList(userList);
                    printf("\n\nShutdown may ATM...");
                    Sleep(2000);
                    exit(0);
                default:
                    printf("\n\nKhong hop le.");
                    break;
            }
        } while (!(admin_choice==1));
    }
}