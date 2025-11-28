#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>

//CAU TRUC DU LIEU
typedef struct {
    char accountId[20];     // Ma tai khoan
    char fullName[50];      // Ho va ten
    char phone[15];         // So dien thoai
    double balance;         // So du
    int status;             // Trang thai (1=Active, 0=Locked)
} Account;

//BIEN TOAN CUC
Account accountList[100] = {     // Luu toi da 100 tai khoan
    {"CNTT0001", "Nguyen Van An", "0912345678", 5000000, 1},
    {"CNTT0002", "Tran Thi Binh", "0931122334", 12500000, 0},
    {"CNTT0003", "Le Hoang Nam", "0928877665", 2300000, 1},
    {"KTQD0001", "Pham Bao Long", "0965566778", 7600000, 1},
    {"KTQD0002", "Vo Hong Dao", "0909988776", 11000000, 0}
}; 
int accountCount = 5;

//HAM HO TRO

//Kiem tra so dien thoai co 10 chu so khong
int isAllDigitsAndLength10(const char *str) {
    // 1. Kiem tra do dai
    if (strlen(str) != 10) {
        return 0; // Khong phai 10 ky tu
    }
    // 2. Kiem tra tung ky tu co phai la chu so khong
    for (int i = 0; str[i] != '\0'; i++) {
        if (!isdigit(str[i])) {
            return 0; // Co ky tu khong phai so
        }
    }
    return 1; // Hop le
}
// Kiem tra ID co ton tai khong. Tra ve index hoac -1.
int findAccountIndex(const char* id) {
    for (int i = 0; i < accountCount; i++) {
        if (strcmp(accountList[i].accountId, id) == 0) 
		return i;
    }
    return -1;
}

// Kiem tra so dien thoai bi trung lap
int checkPhoneDuplication(const char* phone, int excludeIndex) {
    for (int i = 0; i < accountCount; i++) {
        // Chi so sanh neu khong phai tai khoan can loai tru
        if (i != excludeIndex && strcmp(accountList[i].phone, phone) == 0) {
            return 1; // Bi trung
        }
    }
    return 0; // Khong trung
}

//Them tai khoan moi
void createAccount() {
    if (accountCount >= 100) {
        printf("\nLoi: Danh sach da day. Khong the them tai khoan moi.\n");
    }

    Account newAcc;
    char inputBuffer[50]; // Buffer chung cho cac input string
    int isValid = 0; 
    printf("\n--- THEM TAI KHOAN ---\n");

    // 1. Nhap ID (Su dung fgets) & Validation
    do {
        printf("Nhap Account ID: ");
        fgets(inputBuffer, sizeof(inputBuffer), stdin);
        inputBuffer[strcspn(inputBuffer, "\n")] = 0; // Thay \n bang \0
        
        if (strlen(inputBuffer) == 0) {
            printf("Loi: ID khong duoc rong.\n");
            continue;
        }
        if (findAccountIndex(inputBuffer) != -1) {
            printf("Loi: ID da ton tai.\n");
            continue;
        }
        strcpy(newAcc.accountId, inputBuffer);
        isValid = 1; 
    } while (isValid == 0);

    // 2. Nhap Ho Ten (Su dung fgets) & Validation
    isValid = 0;
    do {
        printf("Nhap ho va ten: ");
        fgets(newAcc.fullName, sizeof(newAcc.fullName), stdin);
        newAcc.fullName[strcspn(newAcc.fullName, "\n")] = 0; // Thay \n bang \0

        if (strlen(newAcc.fullName) == 0) {
            printf("Loi: Ho ten khong duoc rong.\n");
            continue;
        }
        isValid = 1;
    } while (isValid == 0);

    // 3. Nhap So dien thoai (Su dung fgets) & Validation
    isValid = 0;
    do {
        printf("Nhap so dien thoai: ");
        fgets(newAcc.phone, sizeof(newAcc.phone), stdin);
        newAcc.phone[strcspn(newAcc.phone, "\n")] = 0; // Thay \n bang \0
        if (!isAllDigitsAndLength10(newAcc.phone)) {
            printf("Loi: So dien thoai phai co CHINH XAC 10 chu so va chi chua so.\n");
            continue;
        }
        if (strlen(newAcc.phone) == 0) {
            printf("Loi: So dien thoai khong duoc rong.\n");
            continue;
        }
        if (checkPhoneDuplication(newAcc.phone, -1) == 1) {
             printf("Loi: So dien thoai da ton tai.\n");
             continue;
        }
        isValid = 1;
    } while (isValid == 0);

    // Gan mac dinh & Them
    newAcc.balance = 0;
    newAcc.status = 1;
    accountList[accountCount++] = newAcc;

    printf("\nThanh cong: Them tai khoan ID %s thanh cong!\n", newAcc.accountId);
}

//CAP NHAT THONG TIN
void updateAccount() {
    char id[20];
    char tempName[50], tempPhone[15];
    int changesMade = 0;

    printf("\n--- CAP NHAT THONG TIN ---\n");

    // 1. Nhap ID can sua (Su dung fgets) & Validation
    while(1) {
	    printf("Nhap Account ID can sua: ");
        fgets(id, sizeof(id), stdin);
        id[strcspn(id, "\n")] = 0; // Thay \n bang \0
        
        if(id, strlen(id) == 0) {
    	    printf("Loi. ID khong duoc rong.\n");
    	    continue;
	    }
	    break;
	}
	
    int index = findAccountIndex(id);
    if (index == -1) {
        printf("Loi: Khong tim thay tai khoan voi ID: %s.\n", id);
        return;
    }
        
    Account* currentAcc = &accountList[index];
    printf("\nThong tin hien tai: Ten: %s | SDT: %s\n", currentAcc->fullName, currentAcc->phone);

    // 2. Nhap Ho Ten moi (Su dung fgets)

    while (1) {
        printf("Nhap ho va ten moi: ");
        fgets(tempName, sizeof(tempName), stdin);
        tempName[strcspn(tempName, "\n")] = '\0'; // thay \n bang \0

        if (strlen(tempName) == 0) {
            printf("Loi: Ho ten moi khong duoc de rong.\n");
        } else {
            // sao chep an toan vao fullName
            strncpy(currentAcc->fullName, tempName, sizeof(currentAcc->fullName) - 1);
            currentAcc->fullName[sizeof(currentAcc->fullName) - 1] = '\0'; // dam bao ket thuc chuoi
            changesMade++;
            break;
        }
    }

    // 3. Nhap So dien thoai moi (Su dung fgets) & Validation
    int phoneValid = 0;
    do {
        printf("Nhap so dien thoai moi: ");
        fgets(tempPhone, sizeof(tempPhone), stdin);
        tempPhone[strcspn(tempPhone, "\n")] = 0; // Thay \n bang \0

        if (strlen(tempPhone) > 0) {
        	if (!isAllDigitsAndLength10(tempPhone)) {
                printf("Loi: So dien thoai moi phai co CHINH XAC 10 chu so va chi chua so.\n");
                continue;
            }
            // Kiem tra trung lap, loai tru chinh no (index)
            if (checkPhoneDuplication(tempPhone, index) == 1) {
                printf("Loi: So dien thoai moi da bi trung lap.\n");
            } else {
                strcpy(currentAcc->phone, tempPhone);
                changesMade++;
                phoneValid = 1;
            }
        } else {
            phoneValid = 1; // De trong la hop le
        }
    } while (phoneValid == 0);
    
    // Thong bao ket qua
    if (changesMade > 0) {
        printf("\nCap nhat thanh cong .\n");
    } else {
        printf("\nThong tin: Khong co thong tin nao duoc cap nhat.\n");
    }
}

//QUAN LY TRANG THAI
void manageStatus() {
    char id[20];
    char answer[10];

    printf("\n----- QUAN LY TRANG THAI TAI KHOAN (LOCK / UNLOCK) -----\n");

    // 1. Nhap ID
    while(1) {
        printf("Nhap account ID: ");
        fgets(id, sizeof(id), stdin);
        id[strcspn(id, "\n")] = '\0';
        
		if(id, strlen(id) == 0) {
			printf("Loi. ID khong duoc rong.\n");
			continue;
		}
		break;
    }
    // 2. Kiem tra ton tai
    int index = findAccountIndex(id);
    if (index == -1) {
        printf("Loi: Khong tim thay tai khoan.\n");
        return;
    }
    
    
    // 3. Xac dinh trang thai hien tai
    if (accountList[index].status == 1) {
        // Tai khoan dang mo, xac nhan khoa
        while (1) {
            printf("Tai khoan dang HOAT DONG. Ban muon KHOA tai khoan? (Y/N): ");
            fgets(answer, sizeof(answer), stdin);
            answer[strcspn(answer, "\n")] = '\0';

            if (strlen(answer) == 0) {
                printf("Loi: Vui long nhap Y hoac N.\n");
                continue;
            }

            char c = answer[0];

            if (c == 'Y' || c == 'y') {
                accountList[index].status = 0;
                printf("\nThanh cong: Tai khoan da duoc KHOA.\n");
                printf("Tai khoan nay khong the thuc hien giao dich chuyen tien.\n");
                return;
            } 
            else if (c == 'N' || c == 'n') {
                printf("\nThong bao: Huy thao tac.\n");
                return;
            } 
            else {
                printf("Loi: Chi duoc nhap Y/N.\n");
            }
        }
    } 
    
    else {
        // Tai khoan dang khoa, xac nhan mo
        while (1) {
            printf("Tai khoan dang BI KHOA. Ban muon MO KHOA tai khoan? (Y/N): ");
            fgets(answer, sizeof(answer), stdin);
            answer[strcspn(answer, "\n")] = '\0';

            if (strlen(answer) == 0) {
                printf("Loi: Vui long nhap Y hoac N.\n");
                continue;
            }

            char c = answer[0];

            if (c == 'Y' || c == 'y') {
                accountList[index].status = 1;
                printf("\nThanh cong: Tai khoan da duoc MO KHOA.\n");
                return;
            } 
            else if (c == 'N' || c == 'n') {
                printf("\nThong bao: Huy thao tac.\n");
                return;
            } 
            else {
                printf("Loi: Chi duoc nhap Y/N.\n");
            }
        }
    }
}

//HAM HO TRO CHO CHUC NANG TRA CUU

// Ham ho tro: Chuyen chuoi thanh chu thuong de so sanh khong phan biet chu hoa/chu thuong
void toLowerString(char *dest, const char *src, size_t maxLen) {
    size_t len = strlen(src);
    // Dam bao khong vuot qua kich thuoc mang dich
    if (len >= maxLen) len = maxLen - 1;

    for (size_t i = 0; i < len; i++) {
        dest[i] = tolower((unsigned char)src[i]);
    }
    dest[len] = '\0';
}

// Ham ho tro: In header bang (da can chinh)
void printTableHeader() {
    printf("\n+--------------------+----------------------------------+--------------+----------------+------------+\n");
    printf("| Account ID         | Ho va Ten                        | So dien thoai| So Du          | Trang thai |\n");
    printf("+--------------------+----------------------------------+--------------+----------------+------------+\n");
}

// Ham ho tro: In thong tin mot tai khoan (da can chinh)
void printAccount(const Account acc) {
    printf("| %-18s | %-32s | %-12s | %-14.2lf | %-10s |\n",
           acc.accountId, acc.fullName, acc.phone, acc.balance,
           acc.status == 1 ? "Active" : "Locked");
}

//CHUC NANG TRA CUU
void searchAccount() {
    char keyword[50];
    Account foundAccounts[100]; // Mang tam luu cac tai khoan tim thay
    int foundCount = 0;
    char lowerKeyword[50]; 
    char lowerFullName[50]; 
    char lowerAccountId[20]; 

    printf("\n--- TRA CUU TAI KHOAN (ID hoac Ten) ---\n");

    // 1. Nhap tu khoa (Input theo so do)
    printf("Nhap tu khoa (ID hoac Ten): ");
    fgets(keyword, sizeof(keyword), stdin);
    keyword[strcspn(keyword, "\n")] = '\0';

    if (strlen(keyword) == 0) {
        printf("Loi: Tu khoa khong duoc rong.\n");
        return;
    }

    // Chuyen tu khoa sang chu thuong de tim kiem khong phan biet hoa/thuong
    toLowerString(lowerKeyword, keyword, sizeof(lowerKeyword));

    // 2. Xu ly logic tim kiem
    for (int i = 0; i < accountCount; i++) {
        // Chuyen ID va Ten tai khoan sang chu thuong de so sanh
        toLowerString(lowerAccountId, accountList[i].accountId, sizeof(lowerAccountId));
        toLowerString(lowerFullName, accountList[i].fullName, sizeof(lowerFullName));

        // So sanh: Tu khoa co trong ID HOAC trong Ten khong? (Tim kiem mot phan - strstr)
        if (strstr(lowerAccountId, lowerKeyword) != NULL || strstr(lowerFullName, lowerKeyword) != NULL) {
            foundAccounts[foundCount++] = accountList[i];
        }
    }

    // 3. Hien thi ket qua (Quyet dinh/Output theo so do)
    if (foundCount == 0) {
        // Dung (Dung) -> Thong bao that bai (Output - That bai)
        printf("\n=> THONG BAO: Khong co ket qua phu hop voi tu khoa '%s'.\n", keyword);
    } else {
        // Sai (Sai) -> Hien thi danh sach phu hop (Output - Thanh cong)
        printf("\n=> KET QUA: %d tai khoan phu hop voi tu khoa '%s':\n", foundCount, keyword);
        printTableHeader(); 
        for (int i = 0; i < foundCount; i++) {
            printAccount(foundAccounts[i]); 
        }
        // Dong cuoi cung phai khop voi header
        printf("+--------------------+----------------------------------+--------------+----------------+------------+\n"); 
    }
}

//DANH SACH PHAN TRANG
void listAllAccounts() {
    // Kiem tra danh sach rong
    if (accountCount == 0) {
        printf("Khong co tai khoan nao trong he thong.\n");
        return;
    }

    int page = 1;
    int index = 0;

    while (index < accountCount) {

        printf("\n===== TRANG %d =====\n", page);
        printTableHeader();

        // In toi da 10 tai khoan moi trang
        for (int i = 0; i < 10 && index < accountCount; i++, index++) {
            printAccount(accountList[index]);
        }

        printf("+--------------------+----------------------------------+--------------+----------------+------------+\n");

        // Neu con tai khoan thi cho bam Enter de xem trang tiep theo
        if (index < accountCount) {
            printf("\nBam Enter de xem trang tiep theo...");
            getchar();
            page++;
        }
    }

    printf("\nDa hien thi het danh sach tai khoan.\n");
}

// HAM HO TRO: Trich xuat Ten (last name) de phuc vu sap xep dung cach
// Ham nay tim vi tri cua khoang trang cuoi cung trong chuoi Ho ten.
// Sau do, no tra ve con tro chi vao ky tu ngay sau khoang trang do, 
// chinh la chuoi Ten can thiet de so sanh.
//
// Dau vao (const char* fullName): Chuoi Ho ten day du (Vi du: "Nguyen Van An").
// Dau ra (const char*): Tra ve con tro toi ky tu dau tien cua Ten (Vi du: "An").
const char* extractLastName(const char* fullName) {
    // strrchr() tim vi tri cuoi cung cua ky tu ' ' trong chuoi
    const char* lastSpace = strrchr(fullName, ' ');
    
    // Kiem tra truong hop khong co khoang trang nao
    if (lastSpace == NULL) {
        // Neu khong tim thay, Ho ten chi co mot tu, tra ve toan bo Ho ten.
        return fullName; 
    }

    // lastSpace + 1: Tra ve chuoi bat dau tu ky tu ngay sau khoang trang cuoi cung (la Ten)
    return lastSpace + 1; 
}

// CHUC NANG 6: SAP XEP DANH SACH
void sortAccounts() {
    int ch;
    char inputCh[5];
    int validChoice = 0;

    printf("\n--- SAP XEP DANH SACH ---\n");

    // 1. Vong lap de nhap va kiem tra lua chon
    do {
        printf("1. Sap xep theo HO TEN (Uu tien Ten, sau do den Ho ten day du)\n");
        printf("2. Sap xep theo SO DU (Tang dan)\n");
        printf("Nhap lua chon: ");

        if (fgets(inputCh, sizeof(inputCh), stdin) == NULL) {
            printf("Loi: Khong doc duoc du lieu.\n");
            return;
        }
        inputCh[strcspn(inputCh, "\n")] = '\0';
        
        if(strlen(inputCh)==0) {
        	printf("Loi. Lua chon khong duoc rong\n");
        	continue;
		}
		
        if(strlen(inputCh) != 1 || (inputCh[0] != '1' && inputCh[0] != '2')) {
            printf("Loi: Lua chon khong hop le (chi duoc nhap 1 hoac 2). Vui long nhap lai.\n");
            continue;
        }

        ch = atoi(inputCh);
        validChoice = 1;
    } while (validChoice == 0);


    // 2. Thuc hien sap xep Bubble Sort
    for (int i = 0; i < accountCount - 1; i++) {
        for (int j = i + 1; j < accountCount; j++) {
            
            int needSwap = 0;
            
            switch (ch) {
                case 1:
                {
                    // SAP XEP THEO TEN (LAST NAME)
                    // Can co ham ho tro 'extractLastName' o dau file.
                    const char* lastName_i = extractLastName(accountList[i].fullName);
                    const char* lastName_j = extractLastName(accountList[j].fullName);

                    int nameCompare = strcmp(lastName_i, lastName_j);

                    if (nameCompare > 0) {
                        needSwap = 1; // Ten A lon hon Ten B -> swap
                    } else if (nameCompare == 0) {
                        // Ten trung nhau -> Sap xep tiep theo toan bo Ho ten (de co thu tu on dinh)
                        int fullCompare = strcmp(accountList[i].fullName, accountList[j].fullName);
                        if (fullCompare > 0) {
                            needSwap = 1;
                        }
                    }
                    break;
                }
                
                case 2:
                // SAP XEP THEO SO DU (TANG DAN)
                    if (accountList[i].balance > accountList[j].balance) {
                        needSwap = 1;
                    }
                    break;
            }

            if (needSwap) {
                // Thao tac hoan vi (Swap)
                Account temp = accountList[i];
                accountList[i] = accountList[j];
                accountList[j] = temp;
            }
        }
    }

    printf("\nDa sap xep danh sach xong. Vui long chon chuc nang 5 (Danh sach) de kiem tra.\n");
}

//MENU
int main() {
    int choice=-1;
    char inputMenu[10];
    do {
        printf("\n+--------- Quan ly ngan hang ---------+\n");
        printf("|1.Them tai khoan                     |\n");
        printf("|2.Cap nhat thong tin                 |\n");
        printf("|3.Quan ly trang thai                 |\n");
        printf("|4.Tra cuu                            |\n");
        printf("|5.Danh sach                          |\n");
        printf("|6.Sap xep danh sach                  |\n");
        printf("|7.Giao dich chuyen khoan             |\n");
        printf("|8.Lich su giao dich                  |\n");
        printf("|0.Thoat                              |\n");
        printf("+-------------------------------------+\n");
        printf("Nhap lua chon: ");
        //Kiem tra lua chon phai la so
        fgets(inputMenu, sizeof(inputMenu), stdin);
        inputMenu[strcspn(inputMenu, "\n")] = '\0';
        if (strlen(inputMenu) == 0) {
            printf("Loi: Lua chon khong duoc rong.\n");
            continue; // quay lai menu
        }
        int isNumber = 1;
        for (int i = 0; i < strlen(inputMenu); i++) {
            if (inputMenu[i] < '0' || inputMenu[i] > '9') {
                isNumber = 0;
                break;
            }
        }
        if (!isNumber) {
            printf("Loi: Lua chon phai la so.\n");
            continue;
        }
        choice = atoi(inputMenu);
        
        switch(choice) {
            case 1: createAccount(); 
			    break;
            case 2: updateAccount(); 
			    break;
			case 3: manageStatus();
			    break;
			case 4: searchAccount();
			    break;
			case 5: listAllAccounts();
			    break;
			case 6: sortAccounts();
			    break;
			case 7:
			case 8:
            case 0: 
			    printf("\nCam on vi da den!\n");
				break; 
            default: 
			    printf("\nLoi: Lua chon khong hop le.\n");
        }
    } while(choice != 0);

    return 0;
}

