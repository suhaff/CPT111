#include <iostream>
#include <iomanip>
#include <string>
using namespace std;

// Forward declaration
class Person;

// ---------------------- Class Relief ----------------------
class Relief {
private:
    float indiv, medical, lifestyle, insurance;

public:
    Relief() : indiv(9000), medical(0), lifestyle(0), insurance(0) {}

    void setRelief(float m, float l, float i) {
        medical = (m > 7000) ? 7000 : m;
        lifestyle = (l > 4000) ? 4000 : l;
        insurance = (i > 6000) ? 6000 : i;
    }

    float getTotalRelief() const {
        float total = indiv + medical + lifestyle + insurance;
        return total;
    }

    void showRelief() const {
        cout << fixed << setprecision(2);
        cout << "Tax Relief Information\n";
        cout << "---------------------------------\n";
        cout << "Individual: RM" << indiv << endl;
        cout << "Medical Expenses: RM" << medical << endl;
        cout << "Lifestyle: RM" << lifestyle << endl;
        cout << "Insurance: RM" << insurance << endl;
        cout << "Total Relief: RM" << getTotalRelief() << endl;
    }
};

// ---------------------- Class Person ----------------------
class Person {
private:
    string id;
    float income, otherIncome, mtd;

public:
    Person() : id(""), income(0), otherIncome(0), mtd(0) {}

    friend void inputPerson(Person &p);

    float getIncome() const { return income; }
    float getOtherIncome() const { return otherIncome; }
    float getMTD() const { return mtd; }
    string getId() const { return id; }

    void showPerson() const {
        cout << fixed << setprecision(2);
        cout << "Individual Tax Information\n";
        cout << "---------------------------------\n";
        cout << "ID: " << id << endl;
        cout << "Income: RM" << income << endl;
        cout << "Other Income: RM" << otherIncome << endl;
        cout << "MTD: RM" << mtd << endl;
        cout << "Total Income: RM" << income + otherIncome << endl;
    }
};

// Friend function (used for input)
void inputPerson(Person &p) {
    cout << "Enter ID: ";
    cin >> p.id;
    cout << "Enter income: RM";
    cin >> p.income;
    cout << "Enter other income (0 if none): RM";
    cin >> p.otherIncome;
    cout << "Enter MTD (total monthly tax deduction): RM";
    cin >> p.mtd;
}

// ---------------------- Class TaxSummary ----------------------
class TaxSummary : public Person {
private:
    Relief relief;
    float totalIncome, totalRelief, chargeableIncome, totalTax, payable;
    string status;

    // Helper: Compute tax by range
    float computeTax(float chargeable) {
        if (chargeable <= 5000) return 0;
        else if (chargeable <= 20000) return (chargeable - 5000) * 0.01;
        else if (chargeable <= 35000) return 150 + (chargeable - 20000) * 0.03;
        else if (chargeable <= 50000) return 600 + (chargeable - 35000) * 0.06;
        else if (chargeable <= 70000) return 1500 + (chargeable - 50000) * 0.11;
        else if (chargeable <= 100000) return 3700 + (chargeable - 70000) * 0.19;
        else if (chargeable <= 400000) return 9400 + (chargeable - 100000) * 0.25;
        else if (chargeable <= 600000) return 84400 + (chargeable - 400000) * 0.26;
        else if (chargeable <= 2000000) return 136400 + (chargeable - 600000) * 0.28;
        else return 528400 + (chargeable - 2000000) * 0.30;
    }

public:
    TaxSummary() : totalIncome(0), totalRelief(0), chargeableIncome(0),
                   totalTax(0), payable(0), status("Undefined") {}

    void inputRelief() {
        float m, l, i;
        cout << "Enter medical expenses (max 7000): RM";
        cin >> m;
        cout << "Enter lifestyle expenses (max 4000): RM";
        cin >> l;
        cout << "Enter insurance (max 6000): RM";
        cin >> i;
        relief.setRelief(m, l, i);
    }

    void calculateTax() {
        totalIncome = getIncome() + getOtherIncome();
        totalRelief = relief.getTotalRelief();
        chargeableIncome = totalIncome - totalRelief;
        if (chargeableIncome < 0) chargeableIncome = 0;

        totalTax = computeTax(chargeableIncome);
        payable = totalTax - getMTD();
        status = (payable > 0) ? "Pay Tax" : "Refund";
    }

    void displaySummary() {
        cout << fixed << setprecision(2);
        cout << "\n========== TAX SUMMARY ==========\n";
        cout << "Total Income: RM" << totalIncome << endl;
        cout << "Total Relief: RM" << totalRelief << endl;
        cout << "Chargeable Income: RM" << chargeableIncome << endl;
        cout << "Total Tax Payable: RM" << totalTax << endl;
        cout << "MTD: RM" << getMTD() << endl;
        cout << "Status: " << status << endl;
        cout << "Tax Payable/Refund for the year: RM" << fabs(payable) << endl;
        cout << "=================================\n";
    }

    void showAll() {
        showPerson();
        cout << endl;
        relief.showRelief();
        cout << endl;
        displaySummary();
    }
};

// ---------------------- Main Function ----------------------
int main() {
    const int SIZE = 3; // you can change this if needed
    TaxSummary taxpayers[SIZE];
    int choice, index = 0;

    do {
        cout << "\n========= Individual Tax App (ITA) =========\n";
        cout << "1. Input new taxpayer info\n";
        cout << "2. Enter relief information\n";
        cout << "3. Calculate and display summary\n";
        cout << "4. Show all taxpayers\n";
        cout << "5. Exit\n";
        cout << "Choose an option: ";
        cin >> choice;

        switch (choice) {
        case 1:
            if (index < SIZE) {
                inputPerson(taxpayers[index]);
                index++;
            } else {
                cout << "Record limit reached.\n";
            }
            break;

        case 2:
            if (index == 0) {
                cout << "No records found.\n";
            } else {
                int i;
                cout << "Enter taxpayer index (0 to " << index - 1 << "): ";
                cin >> i;
                if (i >= 0 && i < index)
                    taxpayers[i].inputRelief();
                else
                    cout << "Invalid index.\n";
            }
            break;

        case 3:
            if (index == 0) {
                cout << "No records found.\n";
            } else {
                int i;
                cout << "Enter taxpayer index (0 to " << index - 1 << "): ";
                cin >> i;
                if (i >= 0 && i < index) {
                    taxpayers[i].calculateTax();
                    taxpayers[i].showAll();
                } else {
                    cout << "Invalid index.\n";
                }
            }
            break;

        case 4:
            if (index == 0) cout << "No records to show.\n";
            else {
                for (int i = 0; i < index; i++) {
                    cout << "\n----- Taxpayer " << i << " -----\n";
                    taxpayers[i].showAll();
                }
            }
            break;

        case 5:
            cout << "Exiting program...\n";
            break;

        default:
            cout << "Invalid choice. Try again.\n";
        }
    } while (choice != 5);

    return 0;
}
