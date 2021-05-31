/* This program calculates the total number of possible different cell phone numbers for a given area code, international country
 * code, and the length of their cell numbers
 */

#include <iostream>
#include "console.h"
#include "testing/SimpleTest.h"
#include "simpio.h"
#include "strlib.h"
using namespace std;


void generatePhoneNumbersPR(int length, string soFar, int areaCode, int internationalCountryCode, int firstX, int lastX) {
    if (length == soFar.size()) {
        string firstThree = soFar.substr(0, firstX);
        string lastFour = soFar.substr(firstX, lastX);
        cout << '+' << internationalCountryCode <<  '(' << areaCode << ')' << firstThree << "-" << lastFour << endl;
    }
    else {
        for (int i = 0; i <= 9; i++) {
            if (soFar[0] != '0' && soFar[0] != '1')
                generatePhoneNumbersPR(length, soFar + integerToString(i), areaCode, internationalCountryCode, firstX, lastX);
        }
    }
}
int raiseToPower(int base, int phoneNumberLength) {
    if (phoneNumberLength == 0) return 1;
    return base * raiseToPower(base, phoneNumberLength - 1);
}
int totalNumbersAvailable(int phoneNumberLength) {
    int possibilities = raiseToPower(10, phoneNumberLength);
    cout << "There are " << 8 * (possibilities) << " different phone number possibilities for your area code." << endl;
    return possibilities;
}

void generatePhoneNumbersPR(int phoneNumberLength, int areaCode, int internationalCountryCode, int firstX, int nextX) {
    generatePhoneNumbersPR(phoneNumberLength, "", areaCode, internationalCountryCode, firstX, nextX);
    totalNumbersAvailable(phoneNumberLength);
}

void generatePhoneNumbersI(int length, int areaCode, int internationalCountryCode) {
    string phoneNumber = "";
    for (int i = 0; i < length - 1; i++) {
        phoneNumber += '0';
    }
    phoneNumber = '2' + phoneNumber;
    int totalPerm = totalNumbersAvailable(length);
    int temp = stringToInteger(phoneNumber);
    for (int i = 0; i < totalPerm; i ++) {
        temp ++;
        phoneNumber = integerToString(temp);
        string firstThree = phoneNumber.substr(0, 3);
        string lastFour = phoneNumber.substr(3, 4);
        cout << '+' << internationalCountryCode <<  '(' << areaCode << ')' << phoneNumber.substr(0, 3)
             << "-" << phoneNumber.substr(3, 4) << endl;
    }
}


/*
 * This sample main brings up testing menu.
 */
int main() {
    if (runSimpleTests(SELECTED_TESTS)) {
        return 0;
    }
    cout << "All done, exiting" << endl;
    return 0;
}

PROVIDED_TEST("Sample use of SimpleTest")
{
    totalNumbersAvailable(7);
    generatePhoneNumbersPR(7, "", 956, 1, 3, 4);
    generatePhoneNumbersBR(7, 956, 1);
    generatePhoneNumbersI(7, 956, 1);
}
