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

typedef struct {
    char transId[20];
    char senderId[20];
    char receiverId[20];
    double amount;
    char type[20];
    char datetime[30];
} Transaction;

//BIEN TOAN CUC
Account accountList[100] = {     // Luu toi da 100 tai khoan
    {"CNTT0001", "Nguyen Van An", "0912345678", 5000000, 1},
    {"CNTT0002", "Tran Thi Binh", "0931122334", 12500000, 0},
    {"CNTT0003", "Le Hoang Nam", "0928877665", 2300000, 1},
    {"CNTT0004", "Nguyen Tuan Anh", "0964363488", 120000000, 1},
    {"CNTT0005", "Hoang Hai Yen", "0991234657", 0, 0},
    {"CNTT0006", "Le Van Dai", "0932627658", 500000, 1},
    {"KTQD0001", "Pham Bao Long", "0965566778", 7600000, 1},
    {"KTQD0002", "Vo Hong Dao", "0909988776", 11000000, 0},
    {"KTQD0003", "Lo Vi Song", "0964657283", 990000, 1},
    {"KTQD0004", "Le Thanh Vinh", "0945467385", 20000000, 0}
}; 
int accountCount = 10;

// Khoi tao mang Transaction va bien dem
Transaction transactionList[200] = {}; // Luu toi da 200 giao dich
int transactionCount = 0;

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
        printf("Khong co tai khoan trong he thong.\n");
        return; // Thoat ham
    }

    int page = 1; // Trang hien tai
    int totalPages = (accountCount + 9) / 10; // Tong so trang, cong them 9 de lam tron len
    char choice[10]; // Luu lua chon nguoi dung (N, P, Q)

    while (1) { // Vong lap chinh cho phan trang
        // Tinh chi so bat dau va ket thuc cho trang hien tai
        int startIndex = (page - 1) * 10; // Tai khoan dau trang
        int endIndex = startIndex + 10;   // Tai khoan cuoi trang
        if (endIndex > accountCount) endIndex = accountCount; // Khong vuot qua so luong tai khoan

        // Hien thi thong tin trang hien tai
        printf("\n===== TRANG %d / %d =====\n", page, totalPages);
        printTableHeader(); // In header bang

        // In tung tai khoan trong trang
        for (int i = startIndex; i < endIndex; i++) {
            printAccount(accountList[i]); // In thong tin tung tai khoan
        }

        // Dong ket thuc bang
        printf("+--------------------+----------------------------------+--------------+----------------+------------+\n");

        // Hien thi lua chon: N = next page, P = previous page, Q = thoat
        printf("\nNhap N de xem trang tiep theo, P de quay lai trang truoc, Q de thoat: ");
        fgets(choice, sizeof(choice), stdin);                   // Doc tu ban phim
        choice[strcspn(choice, "\n")] = 0;                     // Loai bo ky tu \n

        if (strlen(choice) == 0) 
		continue; // Neu nguoi dung chi bam Enter -> lap lai

        if (choice[0] == 'N' || choice[0] == 'n') {           // Chon trang tiep theo
            if (page < totalPages) {                          // Neu chua phai trang cuoi
                page++;                                       // Tang trang
            } else {
                printf("Ban dang o trang cuoi.\n");           // Bao dang o trang cuoi
            }
        } else if (choice[0] == 'P' || choice[0] == 'p') {    // Chon quay lai trang truoc
            if (page > 1) {                                   // Neu chua phai trang dau
                page--;                                       // Giam trang
            } else {
                printf("Ban dang o trang dau.\n");            // Bao dang o trang dau
            }
        } else if (choice[0] == 'Q' || choice[0] == 'q') {    // Chon thoat
		    printf("Da thoat trang\n");
            break;                                            // Thoat vong lap -> ket thuc ham
        } else {
            printf("Lua chon khong hop le.\n");               // Nhap sai ky tu
        }
    }
}

//SAP XEP DANH SACH
void sortAccounts() {
    char input[10];   // Mang de luu lua chon nguoi dung (chuoi nhap)
    int choice;       // Bien chuyen chuoi sang so (1 hoac 2)

    // 1. Nhap lua chon hop le
    while (1) {
        printf("\n=== SAP XEP TAI KHOAN ===\n");
        printf("1. Sap xep theo so du giam dan\n");    // Lua chon 1: theo so du giam dan
        printf("2. Sap xep theo ho ten (A-Z)\n");      // Lua chon 2: theo ho ten A->Z
        printf("Nhap lua chon: ");
        
        fgets(input, sizeof(input), stdin);               // Doc chuoi nguoi dung nhap
        input[strcspn(input, "\n")] = 0;                 // Loai bo ky tu \n o cuoi chuoi

        // Kiem tra rong
        if (strlen(input) == 0) {
            printf("Loi: Lua chon khong duoc de trong.\n");
            continue; // quay lai nhap lai
        }

        // Kiem tra hop le: phai chi nhap '1' hoac '2'
        if (strlen(input) != 1 || (input[0] != '1' && input[0] != '2')) {
            printf("Loi: Lua chon khong hop le. Vui long nhap 1 hoac 2.\n");
            continue; // quay lai nhap lai
        }

        choice = input[0] - '0';   // Chuyen ky tu '1' hoac '2' sang so nguyen 1 hoac 2
        break;                      // Nhap hop le -> thoat vong lap
    }

    // 2. Bubble Sort
    // Su dung thuat toan Bubble Sort: duyet tung cap tai khoan, doi cho neu khong dung thu tu
    for (int i = 0; i < accountCount - 1; i++) {       // Vong lap ngoai: tu tai khoan dau den tai khoan thu 2 cuoi
        for (int j = i + 1; j < accountCount; j++) {   // Vong lap trong: so sanh i voi tat ca cac phan tu sau no
            int needSwap = 0; // Bien kiem tra co can doi cho hay khong

            switch (choice) {
                case 1: // Lua chon 1: Sap xep theo so du giam dan
                    if (accountList[i].balance < accountList[j].balance) {
                        needSwap = 1; // Neu so du i < so du j -> doi cho
                    }
                    break;

                case 2: // Lua chon 2: Sap xep theo ho ten A->Z
                    if (strcmp(accountList[i].fullName, accountList[j].fullName) > 0) {
                        needSwap = 1; // Neu ho ten i dung sau ho ten j trong bang chu cai -> doi cho
                    }
                    break;
            }

            // Hoan vi neu can
            if (needSwap) {
                Account temp = accountList[i];   // Luu tam tai khoan i
                accountList[i] = accountList[j]; // Gan tai khoan j vao vi tri i
                accountList[j] = temp;           // Gan tai khoan i da luu tam vao vi tri j
            }
        }
    }

    printf("\nSap xep thanh cong.\n"); // Bao nguoi dung da sap xep xong
}

//HAM HO TRO GIAO DICH

 //Tao ID giao dich tu dong theo format T-yyyyMMdd-xxxxx
 //idBuffer: Vung nho de luu ID duoc tao ra

void generateTransactionId(char *idBuffer) {
    time_t now = time(NULL);
    struct tm *t = localtime(&now);

    // Dinh dang thoi gian (yyyyMMdd)
    char dateStr[9];
    strftime(dateStr, sizeof(dateStr), "%Y%m%d", t);

    // Dung so luong giao dich hien tai + 1 de tao so thu tu (00001, 00002...)
    sprintf(idBuffer, "T-%s-%05d", dateStr, transactionCount + 1);
}

// Lay thoi gian hien tai (yyyy-MM-dd HH:mm:ss)
// dtBuffer: Vung nho de luu chuoi thoi gian

void getCurrentDateTime(char *dtBuffer) {
    time_t now = time(NULL);
    struct tm *t = localtime(&now);
    strftime(dtBuffer, 30, "%Y-%m-%d %H:%M:%S", t);
}

// Them giao dich vao danh sach (Luu log giao dich)
//senderId: ID nguoi gui
// receiverId: ID nguoi nhan
// amount: So tien
//type: Loai ("Out" hoac "In")

void addTransaction(const char* senderId, const char* receiverId, double amount, const char* type) {
    if (transactionCount >= 200) {
        printf("\nLoi: Lich su giao dich da day. Khong the them log moi.\n");
        return;
    }

    Transaction newTrans;
    generateTransactionId(newTrans.transId); // Tao ID tu dong
    strcpy(newTrans.senderId, senderId);
    strcpy(newTrans.receiverId, receiverId);
    newTrans.amount = amount;
    strcpy(newTrans.type, type); 

    getCurrentDateTime(newTrans.datetime); // Lay thoi gian hien tai

    transactionList[transactionCount++] = newTrans; // Them vao mang va tang bien dem
}

//Giao dich Chuyen khoan
// Thuc hien tru tien, cong tien va luu log, voi kiem tra nhap lieu chat che
void transferMoney() {
    char senderId[20], receiverId[20], inputAmount[30];
    double amount;
    int senderIndex, receiverIndex;
    int isValidInput = 0; // Bien co kiem tra input cho vong lap nhap lai

    printf("\n--- GIAO DICH CHUYEN KHOAN ---\n");

    // 1. NHAP VA KIEM TRA ID NGUOI GUI (senderId)
    do {
        printf("Nhap ID nguoi gui (senderId): ");
        fgets(senderId, sizeof(senderId), stdin);
        senderId[strcspn(senderId, "\n")] = 0;

        if (strlen(senderId) == 0) {
            printf("Loi: Account ID nguoi gui khong duoc de trong.\n");
            continue; 
        }

        senderIndex = findAccountIndex(senderId);
        if (senderIndex == -1) {
            printf("Loi: Khong tim thay tai khoan nguoi gui voi ID: %s.\n", senderId);
            continue; 
        }

        if (accountList[senderIndex].status == 0) {
            printf("Loi: Tai khoan GUI (%s) dang bi KHOA (Locked). Khong the thuc hien giao dich.\n", senderId);
            return; 
        }
        isValidInput = 1;
    } while (isValidInput == 0);

    // 2. NHAP VA KIEM TRA ID NGUOI NHAN (receiverId)
    isValidInput = 0;
    do {
        printf("Nhap ID nguoi nhan (receiverId): ");
        fgets(receiverId, sizeof(receiverId), stdin);
        receiverId[strcspn(receiverId, "\n")] = 0;

        if (strlen(receiverId) == 0) {
            printf("Loi: Account ID nguoi nhan khong duoc de trong.\n");
            continue;
        }
        
        if (strcmp(senderId, receiverId) == 0) {
            printf("Loi: Khong the chuyen tien cho chinh minh. Vui long nhap ID khac.\n");
            continue;
        }

        receiverIndex = findAccountIndex(receiverId);
        if (receiverIndex == -1) {
            printf("Loi: Khong tim thay tai khoan nguoi nhan voi ID: %s.\n", receiverId);
            continue;
        }
        isValidInput = 1;
    } while (isValidInput == 0);

    // 3. NHAP VA KIEM TRA SO TIEN (amount)
    isValidInput = 0;
    do {
        printf("Nhap so tien can chuyen (amount): ");
        fgets(inputAmount, sizeof(inputAmount), stdin);
        inputAmount[strcspn(inputAmount, "\n")] = 0;

        if (strlen(inputAmount) == 0) {
            printf("Loi: So tien chuyen khong duoc de trong.\n");
            continue;
        }
        
        amount = atof(inputAmount);
        if (amount <= 0) {
            printf("Loi: So tien chuyen phai la so va lon hon 0.\n");
            continue;
        }

        if (amount > accountList[senderIndex].balance) {
            printf("Loi: So du hien tai (%0.2lf VND) khong du de thuc hien giao dich %0.2lf VND.\n", 
                   accountList[senderIndex].balance, amount);
            continue; 
        }
        isValidInput = 1; 
    } while (isValidInput == 0);

    // 4. THUC HIEN LOGIC XU LY GIAO DICH (Transaction Logic)
    
    printf("\nThuc hien chuyen tien...\n");
    accountList[senderIndex].balance -= amount; // Tru tien nguoi gui
    accountList[receiverIndex].balance += amount; // Cong tien nguoi nhan

    // 5. LUU LOG GIAO DICH (Logging)
    // Chi luu GIAO DICH GOC 1 LAN.
    // Vi ham printTransaction da tu loai bo log nao la "In" hay "Out" dua tren targetId.
    addTransaction(senderId, receiverId, amount, "N/A"); // Su dung "N/A" hoac bat ky gia tri nao, vi no khong duoc su dung

    // 6. THONG BAO KET QUA (Output)
    printf("\n\n*** CHUYEN KHOAN THANH CONG ***\n");
    printf("So tien da chuyen: %0.2lf VND\n", amount);
    printf("Nguoi gui (%s) | So du moi: %0.2lf VND\n", senderId, accountList[senderIndex].balance);
    printf("Nguoi nhan (%s) | So du moi: %0.2lf VND\n", receiverId, accountList[receiverIndex].balance);
}

// HAM HO TRO CHUC NANG 8

// In header bang lich su giao dich

void printTransactionTableHeader() {
    printf("\n+--------------------+---------------------+--------------+--------------+------------------+---------------------+\n");
    printf("| Transaction ID     | Thoi gian           | Tai khoan doi| Loai GD      | So Tien          | Chi tiet            |\n");
    printf("+--------------------+---------------------+--------------+--------------+------------------+---------------------+\n");
}

// CAP NHAT LOGIC HAM HO TRO IN AN

//In chi tiet mot giao dich tu goc nhin cua targetId
// trans: Cau truc giao dich can in
//targetId: ID tai khoan dang xem lich su

void printTransaction(const Transaction trans, const char* targetId) {
    char partnerId[20];
    char typeDisplay[20]; 
    double displayAmount;

    // Kiem tra giao dich nay la In hay Out DOI VOI targetId
    
    // TRUONG HOP 1: targetId la NGUOI GUI
    if (strcmp(trans.senderId, targetId) == 0) { 
        // Vi targetId la Nguoi Gui (Sender) nen giao dich nay la OUT
        strcpy(partnerId, trans.receiverId); // Doi tac la nguoi nhan
        strcpy(typeDisplay, "Out");          // Loai GD la Out
        displayAmount = trans.amount;
    } 
    // TRUONG HOP 2: targetId la NGUOI NHAN
    else if (strcmp(trans.receiverId, targetId) == 0) { 
        // Vi targetId la Nguoi Nhan (Receiver) nen giao dich nay la IN
        strcpy(partnerId, trans.senderId); // Doi tac la nguoi gui
        strcpy(typeDisplay, "In");         // Loai GD la In
        displayAmount = trans.amount;
    } else {
        return; // Khong phai giao dich lien quan, bo qua
    }

    // In thong tin giao dich ra bang
    // Note: Su dung typeDisplay de xac dinh dong chu 'Chuyen tien' hay 'Nhan tien'
    printf("| %-18s | %-19s | %-12s | %-12s | %-16.2lf | %-19s |\n",
        trans.transId, trans.datetime, partnerId, typeDisplay, displayAmount,
        strcmp(typeDisplay, "Out") == 0 ? "Chuyen tien" : "Nhan tien");
}

//Lich su Giao dich (View Transaction History)
// Truy xuat va hien thi tat ca cac giao dich ma tai khoan da tham gia.
void viewTransactionHistory() {
    char targetId[20];
    // Mang tam de luu cac giao dich tim thay lien quan den targetId
    Transaction foundTransactions[200]; 
    int foundCount = 0; // Bien dem so luong giao dich tim thay

    printf("\n--- XEM LICH SU GIAO DICH ---\n");

    // 1. NHAP VA KIEM TRA ID TAI KHOAN
    while(1) {
        printf("Nhap Account ID muon xem lich su (targetId): ");
        fgets(targetId, sizeof(targetId), stdin);
        targetId[strcspn(targetId, "\n")] = 0;

        if (strlen(targetId) == 0) {
            printf("Loi: Account ID khong duoc de trong.\n");
            continue;
        }
        
        // Kiem tra ton tai tai khoan (Validation)
        if (findAccountIndex(targetId) == -1) {
            // Sai -> Bao loi (Output That bai)
            printf("\nLoi: Tai khoan khong ton tai.\n");
            return; 
        }
        break;
    }
    
    // 2. TRUY XUAT DU LIEU LICH SU
    // Duyet qua toan bo lich su giao dich hien co
    for (int i = 0; i < transactionCount; i++) {
        // Kiem tra giao dich ma tai khoan tham gia (Gui di (sender) HOAC Nhan ve (receiver))
        if (strcmp(transactionList[i].senderId, targetId) == 0 || strcmp(transactionList[i].receiverId, targetId) == 0) {
            foundTransactions[foundCount++] = transactionList[i]; // Luu vao mang tam
        }
    }

    // 3. KIEM TRA KET QUA TRUY XUAT
    // Kiem tra co giao dich nao duoc tim thay khong
    if (foundCount == 0) {
        // Sai -> Thong bao khong co lich su (Output That bai)
        printf("\nHe thong chua co giao dich nao cho tai khoan %s.\n", targetId);
        return;
    }

    // 4. HIEN THI DANH SACH (Output Thanh cong)
    printf("\n=> LICH SU GIAO DICH CUA TAI KHOAN %s (%d giao dich):\n", targetId, foundCount);
    printTransactionTableHeader();
    
    // In tu giao dich moi nhat den cu nhat (Duyet nguoc mang foundTransactions)
    for (int i = foundCount - 1; i >= 0; i--) {
        printTransaction(foundTransactions[i], targetId);
    }
    // Dong chan bang
    printf("+--------------------+---------------------+--------------+--------------+------------------+---------------------+\n");
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
			case 7: transferMoney();
			    break;
			case 8: viewTransactionHistory();
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

