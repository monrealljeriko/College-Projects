#include <iostream>
#include <stdlib.h> // for generating random account number
#include <unistd.h> // for sleep time in loading UI
#include<time.h> // for transaction reciept, the date and time

using namespace std;

class FMSfunctionality {
    private:
        string accountCredentials[500][6]; // 50 user accounts and 6 of their information/details
        int rowIdx, idxDefine, idxReciever; // index identifier
        long double accountBalance[500]; // users account balance
        long double openingBalance = 500.00, currentBalance[500], maintainingBalance = openingBalance; // 
        int accountNumber[500]; // account numbers are generated when user start to create account
        int registerCounts = -1, registerLimits = 500; // counts and limits of creation an account
        string transactionHistory[1000][3];
        int transHistCounts = -1, transHistLimits = 1000; 
        
    public:
        // this will apply when an specific account is sucessfully deleted
        // the deleted account's location will be available for use in registering an account
        void deleteTransactHistory() {
            char confirmation;
            cout << "\n ---------o(O)o ---------\n\n You are about to delete all \n\t  history." << endl << endl;
            
            while (true) {
                cout << " Please CONFIRM (Y/N) : "; 
                cin >> confirmation; 
                //function toupper() to accept 'y' char
                if (toupper(confirmation) == 'Y') { // confirmation to delete all history
                    transHistCounts = -1;
                    system("cls");
                    cout << "\n ---------o(O)o---------\n\n Deleting"; dots();
                    cout <<"\n ---------o(O)o---------\n\n Successfully deleted!\n\n "; pauseCleartxt();
                    break;
                }
                if (toupper(confirmation) == 'N') { // cancelled, function toupper() to accept 'n' char
                    system("cls");
                    cout <<"\n ---------o(O)o---------\n\n Deletion of transaction history\n\thas been Cancelled!\n\n "; pauseCleartxt();
                    break;
                }
                cin.ignore(256, '\n');
            }
            system("cls");
        }
        void applyDelete() { 
            // initialized temporary handler for accountCredentials[][], accountBalance[], accountNumbeer[] values
            string temp_accCreden;  
            long double temp_accBal;
            int temp_accNum, temp_idxList, temp_idxData;

            for (temp_idxList = 0; temp_idxList < registerCounts + 1; temp_idxList++) {
                if (accountBalance[temp_idxList] == 0 ) { // transfer values of accountBalance[] to temp_accBal
                    temp_accBal = accountBalance[temp_idxList];
                    accountBalance[temp_idxList] = accountBalance[temp_idxList + 1];
                    accountBalance[temp_idxList + 1] = temp_accBal;
                }
                if (accountNumber[temp_idxList] == 0) { // transfer values of accountNumbeer[] to temp_accNum
                    temp_accNum = accountNumber[temp_idxList];
                    accountNumber[temp_idxList] = accountNumber[temp_idxList + 1];
                    accountNumber[temp_idxList + 1] = temp_accNum;
                }
                // transfer values of accountCredentials[][] to temp_accCreden
                for (temp_idxData = 0; temp_idxData < 6; temp_idxData++) {
                    if (accountCredentials[temp_idxList][temp_idxData] == "") {
                        // +1 to get the next value and transfer to temp
                        temp_accCreden = accountCredentials[temp_idxList][temp_idxData];
                        accountCredentials[temp_idxList][temp_idxData] = accountCredentials[temp_idxList + 1][temp_idxData];
                        accountCredentials[temp_idxList + 1][temp_idxData] = temp_accCreden;
                    }
                }
            }
            registerCounts = registerCounts - 1; // when admin perform deletion of an account, registerCounts decrease to 1
        }
        // method to delete certain account
        void deleteAccount(int selected) {
            char confirmation;
            if (selected == -1) {
                cout << "\n ---------o(O)o ---------\n\n You are about to delete all \n\t  accounts." << endl << endl;
            }
            else {
                cout << "\n ---------o(O)o ---------\n\n You are about to delete " << endl;
                cout << " '" << accountCredentials[selected][0] << "'s' account." << endl << endl;
            }
            while (true) {
                cout << " Please CONFIRM (Y/N) : "; 
                cin >> confirmation; 
                //function toupper() to accept 'y' char
                if (toupper(confirmation) == 'Y') { // confirmation to delete all accounts
                    if (selected == -1) {
                        registerCounts = selected;
                    }
                    else {  // perform specific account deletion
                        for (int idxDelete = 0; idxDelete < 6; idxDelete++) {
                            accountCredentials[selected][idxDelete] = ""; // equal to "", for sorting in applyDelete
                        }
                        accountNumber[selected] = 0; // equal to 0, for sorting in applyDelete
                        accountBalance[selected] = 0;
                        applyDelete();
                    }
                    system("cls");
                    cout << "\n ---------o(O)o---------\n\n Deleting"; dots();
                    cout <<"\n ---------o(O)o---------\n\n Successfully deleted!\n\n "; pauseCleartxt();
                    break;
                }
                if (toupper(confirmation) == 'N') { // cancelled, function toupper() to accept 'n' char
                    system("cls");
                    cout <<"\n ---------o(O)o---------\n\n Account/s deletion has been\n\tCancelled!\n\n "; pauseCleartxt();
                    break;
                }
                cin.ignore(256, '\n');
            }
        }
        // to accpet only integers when selecting an account for deletion
        int selectingAccountRestriction() {
            int selectAccount;

            while (true) { // will only stop when users enter available list
                cout << "\n ---------o(O)o---------\n\n    [ Account lists ]" << endl;
                cout << "\n ---------o(O)o---------\n " << endl;
                for (int idxName = 0; idxName < registerCounts + 1; idxName++) { // display names available to delete
                    cout << " " << idxName + 1 << ". " << accountCredentials[idxName][0] << endl;
                }
                cout << "\n ---------o(O)o---------\n\n Delete an acount based on \n its position on a list.\n" << endl;
                cout << " Selected : "; 
                cin >> selectAccount;
                cout << "\n ---------o(O)o---------\n\n Processing"; dots();
                
                if (!cin) { // if selectAccount is not an integer
                    cout << "\n ---------o(O)o---------\n\n Only integers may be entered!\n\n "; 
                    cin.clear(); cin.ignore(256, '\n'); // clear buffer and ignore
                }
                else if (selectAccount > registerCounts + 1 || selectAccount < 1) { // selected is not on the list
                    cout << "\n ---------o(O)o---------\n\n The entered value is not \n\ton the list!\n\n "; 
                }
                else return selectAccount - 1; // return selected minus 1, because array index always start at 0
                pauseCleartxt();
            }
        }
        // check to see if any accounts have already been registered
        void checkRegistration() {
            if (registerCounts == -1) { // when registerCounts is equal to -1 means no account exists
                cout << "\n ---------o(O)o---------\n\n No registered account yet!\n\n "; 
                pauseCleartxt(); adminControl(); // return to main main menu if any account not exists
            }
        }
        // all account details/information  
        void adminControl() { 
            char chosen; 
            rowIdx = registerCounts;
            string label[6] = {" Full name", " Address  ", " Birthdate", " Contact number", "\n Username", " Password"};

            while (chosen != '0') { // will only stop when it's equal to 0 or break it operationlly
                cout << "\n ---------o(O)o---------\n\n OPTIONS :\n";
                cout << "\n (1) Display all accounts\n (2) Delete a specific account\n (3) Delete all accounts" << endl;
                cout << " (4) Accounts transaction history\n (0) Logout" << endl;
                cout << "\n Enter here : ";
                cin >> chosen; system("cls");

                cin.ignore(256, '\n'); 
                switch (chosen) {
                    case '1':
                        loading();
                        checkRegistration(); // goto checkRegistration to verified if any account exists
                        cout << "\n ---------o(O)o---------\n\n   [ Accounts Status ]" << endl;
                        cout << "\n ---------o(O)o---------\n " << endl;
                        
                        for (int idxList = 0; idxList < registerCounts + 1; idxList++) { // display all accounts
                            cout << "\t   [" << idxList + 1 << "]\n" << endl;
                                
                            for (int idxData = 0; idxData < 6; idxData++) {
                                cout << label[idxData]  << " : " << accountCredentials[idxList][idxData] << endl;
                            }
                            cout << " -----------------------" << endl;
                            cout << " Account Number : " << accountNumber[idxList] << endl;
                            cout << " Balance  : P" <<  accountBalance[idxList] << endl;
                            cout << "\n ---------o(O)o---------\n\n ";
                        }
                        pauseCleartxt();
                        break;
                    case '2':
                        loading();
                        int selected; 
                        checkRegistration(); // goto checkRegistration to verified if any account exists
                        selected = selectingAccountRestriction(); // goto selectingAccountRestriction and selecting an account to be delete
                        deleteAccount(selected); // goto deleteAccount to finish deleting
                        break;
                    case '3':
                        loading();
                        checkRegistration(); // goto checkRegistration to verified if any account exists
                        deleteAccount(-1); // value -1 is only to set in performing all account deletion
                        break;
                    case '4':
                        loading();
                        char chosen;
                        if (transHistCounts == -1) {
                            cout << "\n ---------o(O)o---------\n\n No transaction history yet!\n\n "; pauseCleartxt(); 
                            break;
                        }

                        while (chosen != '0') {
                            cout << "\n ---------o(O)o---------\n\n [ Transaction History ]" << endl;
                            cout << "\n ---------o(O)o---------\n " << endl;
                            for (int historyList = 0; historyList < transHistCounts + 1; historyList++) { // display all history
                                cout << " " << historyList + 1 << ". ";
                                for (int historyData = 0; historyData < 3; historyData++) {
                                    cout << transactionHistory[historyList][historyData];
                                }
                                cout << endl;
                            }
                            cout << "\n ---------o(O)o---------\n\n";
                            cout << " (1) Delete all history\n (0) Back" << endl;
                            cout << "\n Enter here : ";
                            cin >> chosen; system("cls");
                            cin.ignore(256, '\n');

                            switch (chosen) {
                                case '1':
                                    loading();
                                    deleteTransactHistory();
                                    adminControl();
                                    break;
                                case '0':
                                    loading();
                                    adminControl();
                                    break;
                                default:
                                    cout << "\n ---------o(O)o---------\n\n The entered value is not \n\ton the list!\n\n "; pauseCleartxt();
                                    break;
                            }
                        }
                        break;
                    case '0':
                        cout << "\n ---------o(O)o---------\n\n Logging out"; dots();
                        FMSstart();
                        break;
                    default:
                        cout << "\n ---------o(O)o---------\n\n The entered value is not \n\ton the list!\n\n "; pauseCleartxt();
                        break;
                }
            }
        }
        // this is to confirm the update of details/information of a specific account
        void applyUpdate(int option) {
            char confirmation;
            system("cls");

            cout << "\n ---------o(O)o---------\n\n Updating"; dots();
            cout << "\n ---------o(O)o---------\n\n Successfully Updated!\n\n "; pauseCleartxt();
                
            if (option >= 5 && option <= 8) {
                cout << "\n ---------o(O)o---------\n\n Session expired!" << endl;
                cout << " Please login again. \n" << endl; 
                    
                while (true) {
                    cout << " CONTINUE (Y/N) : ";
                    cin >> confirmation; 
                    cin.ignore(256, '\n');
                    loading(); 
                    if (toupper(confirmation) == 'Y') { 
                        system("cls"); accountLogin(); // goto accountLogin to relogin
                    } 
                    if (toupper(confirmation) == 'N') { 
                        system("cls"); FMSstart();  // return to main menu
                    } 
                }
            }
        }
        // method to select an specific update/s
        void selectedUpdate(int selected, int idx) {
            string updateLabel[6] = {" Full name", " Address  ", " Birthdate", " Contact number", " Username", " Password"};
                
            if (selected == 6) {
                cout << "\n ---------o(O)o---------\n\n Enter your new...\n" << endl;
                cout << " Username : ";
                getline(cin, accountCredentials[idx][selected - 2]); // selected minus 2 is the index location of username
                cout << " Password : ";
                getline(cin, accountCredentials[idx][selected - 1]); // selected minus 1 is the index location of password
            }
            else if (selected == 7) {
                cout << "\n ---------o(O)o---------\n\n Enter your new Account details.\n" << endl;
                // update account informations
                for (int idxUpdate = 0; idxUpdate < 6; idxUpdate++) {
                    if (idxUpdate == 4) cout << endl;
                    cout << updateLabel[idxUpdate] << " : ";
                    getline(cin, accountCredentials[idx][idxUpdate]);
                }
            }
            else {
                cout << "\n ---------o(O)o---------\n\n Enter your new" << updateLabel[selected] << endl;
                cout << " > ";
                getline(cin, accountCredentials[idx][selected]);
            }
        }
        // method to update details/information of a specific account
        void updateAccount() {
            int selectOption;

            while (true) {
                cout << "\n ---------o(O)o---------\n\n Update only your...\n" << endl;
                cout << " (1) Full name\n (2) Address\n (3) Birthdate\n (4) Contact number" << endl; 
                cout << " (5) Username\n (6) Password\n -----------------------" << endl; 
                cout << " (7) Update both your username\n     and password" << endl;
                cout << " (8) Update all of your\n     Information\n (0) Back" << endl;
                cout << "\n Enter here : ";
                cin >> selectOption; system("cls");
                cin.ignore(256, '\n');

                loading();
                if (!cin) { // if selectOption is not an integer
                    cout << "\n ---------o(O)o---------\n\n Only integers may be entered!\n\n "; pauseCleartxt();
                    cin.clear(); cin.ignore(256, '\n'); // clear buffer and ignore
                }
                    else if (selectOption <= 8 && selectOption >= 1) { 
                    selectedUpdate(selectOption - 1, idxDefine);
                    applyUpdate(selectOption);
                    break;
                }
                else if (selectOption == 0) { break; }
                else { // selected is not on the list
                    cout << "\n ---------o(O)o---------\n\n The entered value is not \n\tan option!\n\n "; pauseCleartxt();
                    break;
                }
            }
        }
        // account details/information
        void accountStatus(int idx) { 
            char chosen;
            string label[6] = {" Full name", " Address  ", " Birthdate"," Contact number", "\n Username", " Password"};

            while (chosen != '0') {
                cout << "\n ---------o(O)o---------\n\n   [ Account Status ]\n" << endl;
                for (int idxData = 0; idxData < 6; idxData++) {
                    cout << label[idxData]  << " : " << accountCredentials[idx][idxData] << endl;
                }
                cout << " -----------------------" << endl;
                cout << " Account Number : " << accountNumber[idx] << endl;
                cout << " Total Balance  : P" <<  accountBalance[idx] << endl;
                cout << "\n ---------o(O)o---------\n"<< endl;
                cout << " (1) Make changes to your account\n (0) Back" << endl;
                cout << "\n Enter here : "; 
                cin >> chosen; system("cls");
    
                cin.ignore(256, '\n');
                switch (chosen) {
                    case '1':
                        loading();
                        updateAccount();
                        break;
                    case '0':
                        accountOption();
                        break;
                    default:
                        cout << "\n ---------o(O)o---------\n\n The entered value is not \n\ton the list!\n\n "; pauseCleartxt();
                        break;
                }
            }
        }
        void transactionReciept(string type, int amount, int idx, long double new_accBalance) {
            time_t now = time(0);
            tm *ltm = localtime(&now);

            cout << "\n ---------o(O)o---------\n\n\t[ FMS reciept ]\n" << endl;
            cout<< " " << 1+ltm->tm_mon << "/" << ltm->tm_mday << "/";
            cout<< 1900+ltm->tm_year << " - ";
            cout<< ltm->tm_hour << ":";
            cout<< ltm->tm_min << ":";
            cout<< 1+ltm->tm_sec << "\t FMS00" << transHistCounts + 1 << endl;
            cout << "\n    ACC. NUMBER" << endl;
            cout << " XXX" << accountNumber[idx] << endl;
            cout << "\n    TRANSACTION\n " << type << "\t\t P" << amount << endl;
            cout << " AVAILABLE BALANCE\t P" << new_accBalance << endl;
            cout << "\n ---------o(O)o---------\n\n";
            pauseCleartxt();
        }
        // transfer balance
        int transferBalance(int transferAmount, int idx) { 
            string transAmt = to_string(transferAmount); // convert integer (accountBalance) to string
            long double new_accBalance = accountBalance[idx] - transferAmount; // decrease balance
            accountBalance[idxReciever] += transferAmount; // increase balance of reciever
            currentBalance[idxReciever] += transferAmount;
            currentBalance[idx] = new_accBalance - openingBalance;
            transactionHistory[transHistCounts][0] = accountCredentials[idx][0]; // records history
            transactionHistory[transHistCounts][1] = " transferred "; //
            transactionHistory[transHistCounts][2] = transAmt + " pesos\n    to " + accountCredentials[idxReciever][0]; //
            cout << "\n ---------o(O)o---------\n\n Successfully transfered!\n\n ";
            system("pause"); system("cls");
            cout << "\n ---------o(O)o---------\n\n Your new balance is P" << new_accBalance;
            cout << "\n\n ---------o(O)o---------\n\n Redirecting"; dots();
            transactionReciept("Transfer Cash", transferAmount, idx, new_accBalance);

            return new_accBalance;
        }
        // decrease balance
        int accountWithdraw(int withdrawAmount, int idx) { 
            string withAmt = to_string(withdrawAmount); // convert integer (accountBalance) to string
            long double new_accBalance = accountBalance[idx] - withdrawAmount; // decrease balance
            currentBalance[idx] = new_accBalance - openingBalance;
            transactionHistory[transHistCounts][0] = accountCredentials[idx][0]; // records history
            transactionHistory[transHistCounts][1] = " withdrawn "; //
            transactionHistory[transHistCounts][2] = withAmt + " pesos"; //
            cout << "\n ---------o(O)o---------\n\n Successfully withdrawn!\n\n ";
            system("pause"); system("cls");
            cout << "\n ---------o(O)o---------\n\n Your new balance is P" << new_accBalance;
            cout << "\n\n ---------o(O)o---------\n\n Redirecting"; dots();
            transactionReciept("Withdraw Cash", withdrawAmount, idx, new_accBalance);

            return new_accBalance;
        }
        // increase balance
        int accountDeposit(int depositAmount, int idx) {
            string depAmt = to_string(depositAmount); // convert integer (accountBalance) to string
            long double new_accBalance = accountBalance[idx] + depositAmount; // increase balance
            currentBalance[idx] = new_accBalance - openingBalance;
            transactionHistory[transHistCounts][0] = accountCredentials[idx][0]; // records history
            transactionHistory[transHistCounts][1] = " deposited "; // 
            transactionHistory[transHistCounts][2] = depAmt + " pesos"; //
            cout << "\n ---------o(O)o---------\n\n Successfully deposited!\n\n ";
            system("pause"); system("cls");
            cout << "\n ---------o(O)o---------\n\n Your new balance is P" << new_accBalance;
            cout << "\n\n ---------o(O)o---------\n\n Redirecting"; dots();
            transactionReciept("Deposit Cash", depositAmount, idx, new_accBalance);

            return new_accBalance;
        }
        // display balance
        void displayBalance(int idx) { 
            cout << "\n ---------o(O)o---------\n\n Maintaining balance : P" << maintainingBalance << endl;
            cout << " Amount withdrawable : P" << accountBalance[idx] - maintainingBalance << endl;
            cout << "\n Total Balance : P" << accountBalance[idx] << "\n\n ";
            pauseCleartxt();
        }
        // to accpet only integers as input for the amount number (deposit, withdraw, tranfer)
        int transactionRestriction(int option) {
            int amount;
            string transactions[3] = {"deposit", "withdraw", "transfer"};

            while (true) {
                cout << "\n ---------o(O)o---------\n\n Enter amount to " << transactions[option]<< ".\n P";
                cin >> amount; // amount input
                cout << "\n ---------o(O)o---------\n\n Processing"; dots();
                    
                if (!cin) {  // if amount is not an integer
                    cout << "\n ---------o(O)o---------\n\n Only integers may be entered!\n\n "; pauseCleartxt();
                    cin.clear(); cin.ignore(256, '\n'); // clear buffer and ignore
                }
                else if (amount < 1) {
                    cout << "\n ---------o(O)o---------\n\n Enter a valid Amount number!\n\n "; pauseCleartxt();
                }
                else return amount;
            }
        }
        // method for transaction confirmation
        int transactionConfirmation(int option) {
            char confirmation; 
            string transactions[3] = {"deposit", "withdraw", "transfer"};

            while (true) {
                cout << " Please CONFIRM (Y/N) : "; 
                cin >> confirmation; 

                if (toupper(confirmation) == 'Y') { return 0; } // return -1 for verification that it's a yes
                if (toupper(confirmation) == 'N') {
                    system("cls");
                    cout <<"\n ---------o(O)o---------\n\n The " << transactions[option] << " has been Cancelled!\n\n "; pauseCleartxt();
                    return -1;
                }
            }
        }
        // traverse the existing accounts and return if founded
        int findAccountNumber(int tranferBy_accNum) { 
            for (int scan = 0; scan < registerCounts + 1; scan++) {
                if (accountNumber[scan] == tranferBy_accNum) 
                    return scan; // return the last iteration index
            }
            return -1; // return -1 if not 
        }
        // transacton options for users
        void accountOption() { 
            int idx = idxDefine; // specified index based on user logins
            long double depositAmount, withdrawAmount, transferAmount; // user inputs
            char chosen;
            int confirmResult;

            loading();
            while (chosen != '0') {
                cout << "\n ---------o(O)o---------\n\n OPTIONS :\n";//*option lists
                cout << "\n (1) Balance \n (2) Desposit \n (3) Withdraw";
                cout << "\n (4) Transfer \n (5) Status \n (0) Logout" << endl;
                cout << "\n Enter here : ";
                cin >> chosen; system("cls");
                cin.ignore(256, '\n');
                
                switch (chosen) {
                    case '1':
                        loading();
                        displayBalance(idx);// goto display balance
                        break;
                    case '2':
                        loading();
                        depositAmount = transactionRestriction(0); // value 0 is only to set that it's a transaction for deposti
                        cout << "\n ---------o(O)o ---------\n\n You are about to deposit P" << depositAmount << endl << endl;;
                        
                        confirmResult = transactionConfirmation(0);
                        if (confirmResult == -1) { break; } // when confirmation result is equal to -1 means user cancelled the transaction
                        transHistCounts++;
                        accountBalance[idx] = accountDeposit(depositAmount, idx); // goto accountDeposit and balance will update after
                        break;
                    case '3':
                        loading();
                        withdrawAmount = transactionRestriction(1); // value 1 is only to set that it's a transaction for withdraw

                        if (withdrawAmount > currentBalance[idx]) {
                            if (currentBalance[idx] == 0 && withdrawAmount == maintainingBalance) {
                                cout << "\n ---------o(O)o---------\n\n Maintaining balance must \n      be maintain!\n\n "; pauseCleartxt();
                                break;
                            }
                            cout << "\n ---------o(O)o---------\n\n Insuficient Balance." << endl;
                            cout <<" Check your balance!\n\n "; pauseCleartxt();
                            break;
                        }
                        cout << "\n ---------o(O)o ---------\n\n You are about to withdraw P" << withdrawAmount << endl << endl;
                        
                        confirmResult = transactionConfirmation(1);
                        if (confirmResult == -1) { break; } // when confirmation result is equal to -1 means user cancelled the transaction
                        transHistCounts++;
                        accountBalance[idx] = accountWithdraw(withdrawAmount, idx); //*goto accountDeposit and balance will update after
                        break;
                    case '4':
                        loading();
                        int tranferBy_accNum, searchAccountNumber; 
                        cout << "\n ---------o(O)o---------\n\n Transfer   balance   by \n     account number.\n" << endl;
                        cout << " Enter here : ";
                        cin >> tranferBy_accNum;
                        cout << "\n ---------o(O)o---------\n\n Searching"; dots();
                        searchAccountNumber = findAccountNumber(tranferBy_accNum);

                        if (searchAccountNumber == -1) {
                            cout << "\n ---------o(O)o---------\n" << endl;
                            cout << " Unable to find account number!\n\n "; pauseCleartxt();
                            break; 
                        }
                        if (accountNumber[searchAccountNumber] == accountNumber[idx]) {
                            cout << "\n ---------o(O)o---------\n" << endl;
                            cout << " Self-transfer is not allowed!\n\n "; pauseCleartxt();
                            break;
                        }
                        
                        idxReciever = searchAccountNumber; // specified the index of reviever
                        transferAmount = transactionRestriction(2); // value 2 is only to set that it's a transaction for tranferring balance
                        
                        if (transferAmount > currentBalance[idx]) {
                            if (currentBalance[idx] == 0 && transferAmount == maintainingBalance) {
                                cout << "\n ---------o(O)o---------\n\n Maintaining balance must \n      be maintain!\n\n " << endl; pauseCleartxt();
                                break;
                            }
                            cout << "\n ---------o(O)o---------\n\n Insuficient Balance." << endl;
                            cout <<" Check your balance!\n\n "; pauseCleartxt();
                            break;
                        }
                        cout << "\n ---------o(O)o ---------\n\n You are about to transfer P" << transferAmount << endl;
                        cout << " to '" << accountCredentials[searchAccountNumber][0] << "'s' account."<< endl << endl;
                            
                        confirmResult = transactionConfirmation(2);
                        if (confirmResult == -1) { break; } // when confirmation result is equal to -1 means user cancelled the transaction
                        transHistCounts++; // increment index of transactionHistroy
                        accountBalance[idx] = transferBalance(transferAmount, idx);//*goto transferBalance and balance will update after
                        break;
                    case '5':   
                        loading();
                        accountStatus(idx); // goto user accound status
                        break;
                    case '0':
                        cout << "\n ---------o(O)o---------\n\n Logging out"; dots();
                        FMSstart();
                        break;
                    default:
                        cout << "\n ---------o(O)o---------\n\n The entered value is not \n\ton the list!\n\n "; pauseCleartxt();
                        break;
                }
            }   
        }
        // checking if username is already taken/existed
        string checkUserTaken(string desiredUsername) {
            for (int idxCheck = 0; idxCheck < registerCounts + 1; idxCheck++) {
                if (accountCredentials[idxCheck][4] == desiredUsername) {
                    return "Taken";
                }
            }
            return desiredUsername;
        }
        // for the creation of account
        void accountRegister(int registerCounts) {
            string label[6] = {" Full name", " Address  ", " Birthdate", " Contact number", "\n Desired username", " Desired password"};
            string checkUserResult,  desiredUsername, desiredPassword;
            rowIdx = registerCounts;

            cout << "\n ---------o(O)o---------\n" << endl;
            // account informations
            for (int fill = 0; fill < 4; fill++) {
                cout << label[fill] << " : ";
                getline(cin, accountCredentials[rowIdx][fill]);
            }

            while (checkUserResult != "Available") {
                cout << label[4] << " : ";
                getline(cin, desiredUsername);
                cout << label[5] << " : ";
                getline(cin, desiredPassword);

                checkUserResult = checkUserTaken(desiredUsername);
                if (checkUserResult == "Taken") {
                    system("cls");
                    cout << "\n ---------o(O)o---------\n\n Username already taken!" << endl;
                    cout << "\n ---------o(O)o---------" << endl;
                }
                else {
                    accountCredentials[rowIdx][4] = desiredUsername;
                    accountCredentials[rowIdx][5] = desiredPassword;
                    break;
                }
            }
            cout << "\n ---------o(O)o---------\n";
            // account number is generated at random
            accountNumber[rowIdx] = (rand() * 500) + 1234;
            cout << "\n Your account number is\n\t " << accountNumber[rowIdx] << endl;

            while (true) {
                cout << "\n ---------o(O)o---------\n\n Opening balance : P";
                cin >> accountBalance[rowIdx]; // opening balance
                cin.ignore(256, '\n');
                    
                cout << "\n "; pauseCleartxt();
                cout << "\n ---------o(O)o---------\n\n Registering"; dots();
                    
                if (!cin) { // if accountBalance[rowIdx] is not an integer
                    cout << "\n ---------o(O)o---------\n\n Only integers may be entered!\n\n "; pauseCleartxt();
                    cin.clear(); cin.ignore(256, '\n');   // clear buffer and ignore
                }
                else if (accountBalance[rowIdx] < 0) {
                    cout << "\n ---------o(O)o---------\n\n Enter valid Amount number!\n\n "; pauseCleartxt();
                }
                else if (accountBalance[rowIdx] < openingBalance) {
                    cout << "\n ---------o(O)o---------\n\n Minimum opening balance\n\t is P500\n\n "; pauseCleartxt();
                }
                else break;
            }
            currentBalance[rowIdx] = accountBalance[rowIdx] - maintainingBalance;
            cout << "\n ---------o(O)o---------\n\n Successfully registered!\n\n ";
            system("pause"); system("cls");
        }
        // admin login verification
        string validateAdmin(string adminUsername, string adminPassword) {
            if (adminUsername == "admin" && adminPassword == "@admin123") {
                return "Success";
            }
            else return "Invalid username or password!";
        }
        // admin login section
        void adminLogin() { 
            string adminUsername, adminPassword, checkAdminUserPass;
            int loginAttempts = 0;

            //return to main menu if loginAttempts equals to 3
            while (loginAttempts != 3) { 
                cout << "\n ---------o(O)o---------\n\n Username : ";
                getline(cin, adminUsername);
                cout << " Password : ";
                getline(cin, adminPassword);
                checkAdminUserPass = validateAdmin(adminUsername, adminPassword);
                cout << "\n ---------o(O)o---------\n\n Logging in"; dots();
                    
                if (checkAdminUserPass == "Success") {
                    cout << "\n ---------o(O)o---------\n\n Successfully login!\n\n "; pauseCleartxt();
                    cout << "\n ---------o(O)o---------\n\n Setting up"; dots(); loading();
                    adminControl();//*goto account status
                }
                else cout << "\n ---------o(O)o---------\n\n " << checkAdminUserPass << "\n\n "; pauseCleartxt();

                loginAttempts++;
            }
            cout << "\n ---------o(O)o---------\n\n Maximum login attempts\n\treached!\n\n "; pauseCleartxt();
        }
        // user login verification
        string findUsernamePassword(string loginUsername, string loginPassword) {
            string searchResult;
            for (int rowScan = 0; rowScan < registerCounts + 1; rowScan++) {
                if (accountCredentials[rowScan][4] == loginUsername) {
                    if (accountCredentials[rowScan][5] == loginPassword) {
                        idxDefine = rowScan;
                        return "Account exists!";
                    }
                }
                if (accountCredentials[rowScan][5] == loginPassword) {
                    if (accountCredentials[rowScan][4] == loginUsername) {
                        idxDefine = rowScan;
                        return "Account exists!";
                    }
                }
                if (loginUsername == "" && loginPassword == "") {
                    return "Enter a string value!";
                }
            }
            return "Invalid username or password!";
        }
        // user login section
        void accountLogin() { 
            string loginUsername, loginPassword, searchUserPass;
            int loginAttempts = 0;
                
            //return to main menu if loginAttempts equals to 3
                while (loginAttempts != 3) { 
                cout << "\n ---------o(O)o---------\n\n Username : ";
                getline(cin, loginUsername);
                cout << " Password : ";
                getline(cin, loginPassword);  
                cout << "\n ---------o(O)o---------\n\n Logging in"; dots();
                searchUserPass = findUsernamePassword(loginUsername, loginPassword);
                    
                if (searchUserPass == "Account exists!") {
                    cout << "\n ---------o(O)o---------\n\n Successfully login!\n\n "; pauseCleartxt();
                    cout << "\n ---------o(O)o---------\n\n Setting up"; dots();
                    accountOption();//*goto account status
                }
                else cout << "\n ---------o(O)o---------\n\n " << searchUserPass << "\n\n "; pauseCleartxt();

                loginAttempts++;
            }
            cout << "\n ---------o(O)o---------\n\n Maximum login attempts\n\treached!\n\n "; pauseCleartxt();
        }
        // fund management system start
        void FMSstart() {
            char chosen;
            
            while (chosen != '0') {
                cout << "\n ---------o(O)o---------\n\n Fund Management System" << endl;
                cout << "\n ---------o(O)o---------\n\n (1) Login\n (2) Register \n (3) Admin control\n (0) Exit\n";
                cout << "\n Enter here : ";
                cin >> chosen;  system("cls");
                cin.ignore(256, '\n');
                    
                switch (chosen) {
                    case '1':
                        loading();

                        if (registerCounts == -1) { // when registerCounts is equal to -1 means no account exists
                            cout << "\n ---------o(O)o---------\n\n It appears you don't have an account!" << endl;
                            cout << " To login, you must first register.\n\n "; pauseCleartxt();
                            break;
                        }
                        accountLogin();
                        break;
                    case '2':
                        loading();
                        registerCounts++; // increment 

                        if (registerCounts > registerLimits - 1) {
                         cout << "\n Account registration limits\n\t have been reached." << endl;
                            break;
                        }
                        accountRegister(registerCounts);
                        break;
                    case '3':
                        loading(); adminLogin();
                        break;
                    case '0':
                        cout << "\n ---------o(O)o---------\n\n Exiting"; dots();
                        cout << "\n ---------o(O)o---------\n\n Thank you for trying \n Fund Management System.\n";//*warm exit
                        exit(0);
                        break;
                    default:
                        cout << "\n ---------o(O)o---------\n\n The entered value is not \n\ton the list!\n\n "; pauseCleartxt();
                        break;
                }
            }
        }
        // will pause the program and clear the console text after
        void pauseCleartxt() { 
            system("pause"); system("cls");
        }
        // loading 
        void loading() { 
            cout << "\n ---------o(O)o---------\n\n Loading";
            for (int i = 0; i < 3; i++) {
                cout << "."; sleep(1);
            }
            system("cls");
        }
        // three dots
        void dots() { 
            for (int i = 0; i < 3; i++) {
                cout << "."; sleep(1);
            }
            system("cls");
        }
};

// main method of the program
int main() {
    FMSfunctionality objFMSfunc;
        
    cout << "\n Starting"; objFMSfunc.dots(); 
    cout << "\n\tWelcome to";

    cout << "\n ---------o(O)o---------\n [ Fund Management System ]\n ---------o(O)o---------" <<endl;
    cout << "\n Getting in"; objFMSfunc.dots();

    cout << "\n [Note: Must read this first!]\n\n ";
    objFMSfunc.pauseCleartxt();

    cout << "\n ~ This simple Fund Management " << endl;
    cout << " system was developed by " << endl; 
    cout << " JERIKO L. MONREAL.\n\n ";
    objFMSfunc.pauseCleartxt();

    cout << "\n ~ Which enable users to create" <<endl;
    cout << " an account and login.\n\n "; 
    objFMSfunc.pauseCleartxt();

    cout << "\n ~ There is P500 minimum opening" << endl;
    cout << " balance and cannot be withdrawn.\n\n "; 
    objFMSfunc.pauseCleartxt();
        
    cout << "\n ~ User can deposit and withdraw;" << endl;
    cout << " tranfer funds to other accounts.\n\n "; 
    objFMSfunc.pauseCleartxt();

    cout << "\n ~ There is an administrator" << endl;
    cout << " who has access to view" << endl;
    cout << " and delete account/s." << endl;
    cout << " -------------------------------" << endl;
    cout << " ~ LOGINS" << endl;
    cout << " username : admin" << endl;
    cout << " password : @admin123 \n\n "; 
    objFMSfunc.pauseCleartxt();
        
    cout << "\n Thank you for reading!\n\n "; 
    objFMSfunc.pauseCleartxt();

    cout << "\n Almost there!"; objFMSfunc.dots();

    objFMSfunc.FMSstart();

     return 0;
}
