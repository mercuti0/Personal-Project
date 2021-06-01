/* This program calculates the total number of possible different cell phone numbers for a given area code, international country
 * code, and the length of their cell numbers (after the area and international country code).
 */

#include <iostream>
#include "console.h"
#include "testing/SimpleTest.h"
#include "strlib.h"
using namespace std;

/* This function recursively print all the possible permutations of a phone number.
 */
void generatePhoneNumbersPR(int length, string phoneNumber, int areaCode, int internationalCountryCode, int firstX, int lastX, Vector<int>& totalPerm) {
    // Base case: once the the string has been added the required length of the new phone number, we print it and move on
    if (length == phoneNumber.size()) {
        if (phoneNumber.substr(1, 2) != "11") {
            // Phone numbers in different countries can be formatted a bit differently, hence we separate the two usign the given inputs
            string startX = phoneNumber.substr(0, firstX);
            string nextX = phoneNumber.substr(firstX, lastX);
            // Phone numbers cannot be led by a 0 or 1
            if (phoneNumber[0] != '0' && phoneNumber[0] != '1') {
//                cout << '+' << internationalCountryCode <<  '(' << areaCode << ")" << startX << "-" << nextX << endl;
                totalPerm.add(stringToInteger(phoneNumber));
            }
        }
    }
    else {
        // Phone numbers include numbers 0 to 9
        for (int i = 0; i <= 9; i++) {
            // Phone numbers don't start with a leading 0 or 1, or end with 11
            if (phoneNumber[0] != '0' && phoneNumber[0] != '1')
                generatePhoneNumbersPR(length, phoneNumber + integerToString(i), areaCode, internationalCountryCode, firstX, lastX, totalPerm);
        }
    }
}

/* This helper function calcualtes the power of base 10 to the power of the length of phone numbers - 1, giving us the
 * place (millionth, billionth) to which the permutations can go up to. This function was obtained from Section 2. Big-O
 * and Recursion.
 */
int raiseToPower(int base, int phoneNumberLength) {
    if (phoneNumberLength == 0) return 1;
    return base * raiseToPower(base, phoneNumberLength - 1);
}

/* This function calculates the total number of permutations of an area code given the length of a phone number.
 */
int totalNumbersAvailable(int phoneNumberLength) {
    // Calculate the total permutations
    int possibilities = raiseToPower(10, phoneNumberLength - 1);
    // Multiply by the total available leading numbers (2-9) and subtract the numbers starting with N11 (80,000).
    int validPossibilities = (8 * (possibilities)) - 80000;
    cout << "There are " << validPossibilities << " different phone number possibilities for your area code." << endl;
    return validPossibilities;
}

/* This function would be for the user to input their values and have the recursion begin.
 */
Vector<int> generatePhoneNumbersPR(int phoneNumberLength, int areaCode, int internationalCountryCode, int firstX, int nextX) {
    Vector<int> totalPerm;
    // Overload function and include only the necessary inputs.
    generatePhoneNumbersPR(phoneNumberLength, "", areaCode, internationalCountryCode, firstX, nextX, totalPerm);
    // Print total numbers avilable for given phone number length
    totalNumbersAvailable(phoneNumberLength);
    return totalPerm;
}

/* This function iteratively prints all the possible permutations of a phone number.
 */
Vector<int> generatePhoneNumbersI(int length, int areaCode, int internationalCountryCode, int firstX, int nextX) {
    Vector<int> totalPerm;
    string phoneNumber = "";
    // Add the total length of the phone number minus the leading first number
    for (int i = 0; i < length - 1; i++) {
        phoneNumber += '0';
    }
    // We start creating the phone numbers at the lowest possible leading value, 2
    string topSize = '1' + phoneNumber + '0';
    phoneNumber = '2' + phoneNumber;
    // Calculate the total number of phone numbers available
    int numberOfPerm = raiseToPower(10, length);
    // If the number of permutations is less than the valid amount, then this is being run for testing purposes.
    if (numberOfPerm < 0) {
        numberOfPerm = stringToInteger(topSize);
    }
    int temp = stringToInteger(phoneNumber);
    for (int i = 0; i < numberOfPerm; i ++) {
        // Continue to add the phone number value
        phoneNumber = integerToString(temp);
        // Phone numbers in different countries can be formatted a bit differently, hence we separate the two usign the given inputs
        string firstThree = phoneNumber.substr(0, firstX);
        string lastFour = phoneNumber.substr(firstX, nextX);
        // While the second and third value are not 11, we can print the remaining values since we automatically not start at 1 or 0
        if (phoneNumber.substr(1, 2) != "11" && phoneNumber[0] != '0' && phoneNumber[0] != '1') {
//            cout << '+' << internationalCountryCode <<  '(' << areaCode << ")" << firstThree << "-" << lastFour << endl;
            totalPerm.add(stringToInteger(phoneNumber));
        }
        temp ++;
    }
    return totalPerm;
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

PROVIDED_TEST("Test that both the iterative and recursive functions return the same value. Time test each operation.")
{
    int usNumbers = totalNumbersAvailable(7);
    int swedenNumbers = totalNumbersAvailable(9);
    EXPECT_EQUAL(usNumbers, 7920000);
    EXPECT_EQUAL(swedenNumbers, 799920000);
    Vector<int> PRtest = generatePhoneNumbersPR(7, 1, 1, 3, 4);
    Vector<int> Itest = generatePhoneNumbersI(7, 1, 1, 3, 4);
    int last = PRtest[PRtest.size() -1];
    int last1 = Itest[Itest.size() -1];
    cout << last << "  " << last1 << endl;
    EXPECT_EQUAL(generatePhoneNumbersI(1, 1, 1, 1, 0), generatePhoneNumbersPR(1, 1, 1, 1, 0));
    EXPECT_EQUAL(generatePhoneNumbersI(2, 1, 1, 2, 0), generatePhoneNumbersPR(2, 1, 1, 2, 0));
    EXPECT_EQUAL(generatePhoneNumbersI(3, 1, 1, 3, 0), generatePhoneNumbersPR(3, 1, 1, 3, 0));
    EXPECT_EQUAL(generatePhoneNumbersI(7, 1, 1, 3, 4), generatePhoneNumbersPR(7, 1, 1, 3, 4));
//    TIME_OPERATION(1, generatePhoneNumbersPR(1, 1, 1, 1, 0));
//    TIME_OPERATION(2, generatePhoneNumbersPR(2, 1, 1, 2, 0));
//    TIME_OPERATION(3, generatePhoneNumbersPR(3, 1, 1, 3, 0));
//    TIME_OPERATION(1, generatePhoneNumbersI(1, 1, 1, 1, 0));
//    TIME_OPERATION(2, generatePhoneNumbersI(2, 1, 1, 2, 0));
//    TIME_OPERATION(5, generatePhoneNumbersPR(7, 1, 1, 3, 4));

//    generatePhoneNumbersPR(3, 956, 1, 3, 0);
//    generatePhoneNumbersI(3, 956, 1, 3, 0);
//    generatePhoneNumbersPR(7, 956, 1, 3, 4);
//    generatePhoneNumbersI(7, 956, 1, 3, 4);
}
