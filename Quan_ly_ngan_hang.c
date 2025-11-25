#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

// --- CAU TRUC DU LIEU ---
typedef struct {
    char accountId[20];     // Ma tai khoan
    char fullName[50];      // Ho va ten
    char phone[15];         // So dien thoai
    double balance;         // So du
    int status;             // Trang thai (1=Active, 0=Locked)
} Account;

// --- BIEN TOAN CUC ---
Account accountList[100];       // Luu toi da 100 tai khoan
int accountCount = 0;

// --- HAM HO TRO ---

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
        printf("\nLoi: Mang da day. Khong the them tai khoan moi.\n");
        return;
    }

    Account newAcc;
    char inputBuffer[50]; // Buffer chung cho cac input string
    int isValid = 0; 
    printf("\n--- THEM TAI KHOAN ---\n");

    // 1. Nhap ID (Su dung fgets) & Validation
    do {
        printf("Nhap Account ID: ");
        if (fgets(inputBuffer, sizeof(inputBuffer), stdin) == NULL) 
		continue;
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
        if (fgets(newAcc.fullName, sizeof(newAcc.fullName), stdin) == NULL) continue;
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
        if (fgets(newAcc.phone, sizeof(newAcc.phone), stdin) == NULL) continue;
        newAcc.phone[strcspn(newAcc.phone, "\n")] = 0; // Thay \n bang \0

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

// --- F02: CAP NHAT THONG TIN ---
void updateAccount() {
    char id[20];
    char tempName[50], tempPhone[15];
    int changesMade = 0;

    printf("\n--- CAP NHAT THONG TIN ---\n");

    // 1. Nhap ID can sua (Su dung fgets) & Validation
    printf("Nhap Account ID can sua: ");
    if (fgets(id, sizeof(id), stdin) == NULL) return;
    id[strcspn(id, "\n")] = 0; // Thay \n bang \0

    int index = findAccountIndex(id);
    if (index == -1) {
        printf("Loi: Khong tim thay tai khoan voi ID: %s.\n", id);
        return;
    }

    Account* currentAcc = &accountList[index];
    printf("\nThong tin hien tai: Ten: %s | SDT: %s\n", currentAcc->fullName, currentAcc->phone);

    // 2. Nhap Ho Ten moi (Su dung fgets)
    printf("Nhap ho va ten moi: ");
    if (fgets(tempName, sizeof(tempName), stdin) == NULL) return;
    tempName[strcspn(tempName, "\n")] = 0; // Thay \n bang \0

    if (strlen(tempName) > 0) {
        strcpy(currentAcc->fullName, tempName);
        changesMade++;
    }

    // 3. Nhap So dien thoai moi (Su dung fgets) & Validation
    int phoneValid = 0;
    do {
        printf("Nhap so dien thoai moi: ");
        if (fgets(tempPhone, sizeof(tempPhone), stdin) == NULL) return;
        tempPhone[strcspn(tempPhone, "\n")] = 0; // Thay \n bang \0

        if (strlen(tempPhone) > 0) {
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

//MENU
int main() {
    int choice;
    do {
        printf("\n========== MINI BANKING SYSTEM ==========\n");
        printf("1.Them tai khoan\n");
        printf("2.Cap nhat thong tin\n");
        printf("0.Thoat\n");
        printf("Nhap lua chon: ");
        scanf("%d", &choice);
        getchar();
        switch(choice) {
            case 1: createAccount(); 
			    break;
            case 2: updateAccount(); 
			    break;
            case 0: 
			    printf("\nCam on vi da den!\n");
				break; 
            default: 
			    printf("\nLoi: Lua chon khong hop le.\n");
        }
    } while(choice != 0);

    return 0;
}

