/*
 * The MIT License (MIT)
 *
 * Copyright (c) 2015 Mark Guerra
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this
 * software and associated documentation files (the "Software"), to deal in the Software
 * without restriction, including without limitation the rights to use, copy, modify, merge,
 * publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons
 * to whom the Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or
 * substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
 * INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE
 * AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
 * DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF
 * OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#include <sstream>
#include <stack>
#include <iostream>

#include "bignumber.h"


BigNumber::BigNumber(std::string number) :
    _numberString(number)
{
}

BigNumber BigNumber::add(BigNumber other) {
    if (this->isNegative() || other.isNegative()) {
        if (this->isNegative() && other.isNegative()) {
            return this->negate().add(other.negate()).negate();
        }
        else if (this->isNegative() && !other.isNegative()) {
            return this->negate().subtract(other).negate();
        }
        else {
            return other.negate().subtract(*this).negate();
        }
    }
    std::string results;
    int carry = 0;
    BigNumber num1 = other > *this ? other : *this;
    BigNumber num2 = other > *this ? *this : other;
    int diff = int(num1._numberString.size() - num2._numberString.size());
    for (int i = 0; i < diff; i++) {
        num2._numberString.insert(num2._numberString.begin(), '0');
    }
    for (int i = int(num1._numberString.size() - 1); i >= 0; i--) {
        int sum = (num1._numberString[i] - '0') + (num2._numberString[i] - '0') + carry;
        carry = 0;
        if (sum <= 9 || i == 0) {
            results.insert(0, std::to_string(sum));
        }
        else {
            results.insert(0, std::to_string(sum % 10));
            carry = 1;
        }
    }
    return BigNumber(results);
}


BigNumber BigNumber::subtract(BigNumber other) {
    if (this->isNegative() || other.isNegative()) {
        if (this->isNegative() && other.isNegative()) {
            return this->negate().add(other.negate()).negate();
        }
        else if (this->isNegative() && !other.isNegative()) {
            return this->negate().add(other).negate();
        }
        else {
            return other.negate().add(*this);
        }
    }
    std::string results;
    int n = 0, p = 0;
    bool takeOffOne = false;
    bool shouldBeTen = false;

    if (*this < other) {
        //Negative answer
        std::string t = other.subtract(*this).negate().getString();
        for (unsigned int i = 1; i < t.length(); ++i) {
            if (t[i] != '0') break;
            t.erase(1, 1);
        }
        return BigNumber(t);
    }

    int i = int(this->_numberString.size() - 1);
    for (int j = int(other._numberString.size() - 1); j >= 0; j--) {
        if (((this->_numberString[i] - '0') < (other._numberString[j] - '0')) && i > 0) {
            n = char((this->_numberString[i] - '0') + 10);
            takeOffOne = true;
            if (j > 0 || this->_numberString[i - 1] != '0') {
                p = char((this->_numberString[i - 1] - '0') - 1);
                if (p == -1) {
                    p = 9;
                    shouldBeTen = true;
                }
                takeOffOne = false;
            }
            if (shouldBeTen) {
                int index = i - 1;
                for (int a = i - 1; (this->_numberString[a] - '0') == 0; a--) {
                    this->_numberString[a] = (p + '0');
                    index--;
                }
                int t = (this->_numberString[index] - '0') - 1;
                this->_numberString[index] = (t + '0');
            }
            this->_numberString[i - 1] = (p + '0');
            shouldBeTen = false;
        }
        std::stringstream ss;
        if (((this->_numberString[i] - '0') == (other._numberString[j] - '0'))) {
            ss << "0";
        }
        else {
            if (n <= 0) {
                ss << ((this->_numberString[i] - '0') - (other._numberString[j] - '0'));
            }
            else {
                ss << (n - (other._numberString[j] - '0'));
            }
        }

        results.insert(0, ss.str());
        i--;
        n = 0;
    }
    if (takeOffOne) {
        std::string number = "";
        for (int i = this->_numberString.length() - other._numberString.length() - 1; i >= 0; i--) {
            if (this->_numberString[i] == '0') {
                number += "0";
                continue;
            }
            else {
                number.insert(number.begin(), this->_numberString[i]);
                int n = atoi(number.c_str());
                n--;
                this->_numberString.replace(0, number.size(), std::to_string(n));
                break;
            }
        }
    }
    while (i >= 0) {
        std::stringstream ss;
        if (i == 0) {
            if (this->_numberString[i] - '0' != 0) {
                ss << (this->_numberString[i] - '0');
                results.insert(0, ss.str());
            }
        }
        else {
            ss << (this->_numberString[i] - '0');
            results.insert(0, ss.str());
        }

        i--;
    }
    //In the case of all 0's, we only want to return one of them
    if (results.find_first_not_of('0') == std::string::npos) {
        results = "0";
    }

    return BigNumber(results);
}


BigNumber BigNumber::multiply(BigNumber other) {
    if (this->isNegative() || other.isNegative()) {
        if (this->isNegative() && other.isNegative()) {
            return this->negate().multiply(other.negate());
        }
        else if (this->isNegative() && !other.isNegative()) {
            return this->negate().multiply(other).negate();
        }
        else {
            return other.negate().multiply(*this).negate();
        }
    }
    int carry = 0;
    int zeroCounter = 0;
    std::vector<std::string> results;
    BigNumber num1 = other > *this ? other : *this;
    BigNumber num2 = other > *this ? *this : other;
    for (unsigned int i = 0; i < num1._numberString.size() - num2._numberString.size(); i++) {
        num2._numberString.insert(num2._numberString.begin(), '0');
    }
    for (int i = (num2._numberString.size() - 1); i >= 0; i--) {
        std::string rr;
        for (int j = int(num1._numberString.size() - 1); j >= 0; j--) {
            int val = ((num2._numberString[i] - '0') * (num1._numberString[j] - '0')) + carry;
            carry = 0;
            if (val > 9 && j != 0) {
                int dig = val % 10;
                carry = val / 10;
                rr.insert(0, std::to_string(dig));
            }
            else {
                rr.insert(0, std::to_string(val));
            }
        }
        if (zeroCounter > 0) {
            for (int x = 0; x < zeroCounter; x++) {
                rr.append("0");
            }
        }
        zeroCounter++;
        results.push_back(rr);
    }
    std::vector<BigNumber> bigNumbers;
    for (unsigned int i = 0; i < results.size(); i++) {
        bigNumbers.push_back(BigNumber(results[i]));
    }
    BigNumber b("0");
    for (unsigned int i = 0; i < bigNumbers.size(); i++) {
        b = b.add(bigNumbers[i]);
    }
    if (b._numberString.find_first_not_of('0') != std::string::npos) {
        b = BigNumber(b._numberString.erase(0, b._numberString.find_first_not_of('0')));
    }
    else {
        //In the case of all 0's, we only want to return one of them
        b = BigNumber("0");
    }
    return b;

}

BigNumber BigNumber::pow(int exponent) {
    if (exponent < 0) {
        std::cerr << "Powers less than 0 are not supported" << std::endl;
    }
    BigNumber result("1");
    while (exponent > 0) {
        if (exponent & 1) {
            result = result.multiply(*this);
        }
        *this = this->multiply(*this);
        exponent /= 2;
    }
    return result;
}

std::string BigNumber::getString() {
    return this->_numberString;
}

void BigNumber::setString(const std::string &newStr) {
    this->_numberString = newStr;
}

BigNumber BigNumber::negate() {
    if (this->_numberString[0] == '-') {
        this->_numberString.erase(0, 1);
    }
    else {
        this->_numberString.insert(this->_numberString.begin(), '-');
    }
    return *this;
}

bool BigNumber::equals(const BigNumber &other) {
    return this->_numberString == other._numberString;
}

int BigNumber::digits() {
    return this->_numberString.size() - this->isNegative() ? 1 : 0;
}

bool BigNumber::isNegative() const {
    return this->_numberString[0] == '-';
}

bool BigNumber::isPositive() {
    return !this->isNegative();
}

bool BigNumber::isEven() {
    return this->_numberString[this->_numberString.length() - 1] % 2 == 0;
}

bool BigNumber::isOdd() {
    return !this->isEven();
}

std::ostream &operator<<(std::ostream &os, const BigNumber &num) {
    os << num._numberString;
    return os;
}

BigNumber operator+(BigNumber b1, const BigNumber &b2) {
    return b1.add(b2);
}

BigNumber operator-(BigNumber b1, const BigNumber &b2) {
    return b1.subtract(b2);
}

BigNumber operator*(BigNumber b1, const BigNumber &b2) {
    return b1.multiply(b2);
}

BigNumber operator^(BigNumber b1, const int &b2) {
    return b1.pow(b2);
}

bool operator==(BigNumber b1, const BigNumber &b2) {
    return b1.equals(b2);
}

bool operator>(BigNumber b1, const BigNumber &b2) {
    if (b1.isNegative() || b2.isNegative()) {
        if (b1.isNegative() && b2.isNegative()) {
            BigNumber bt = b2;
            b1._numberString.erase(0, 1);
            bt._numberString.erase(0, 1);
            return b1 < bt;
        }
        else {
            return !(b1.isNegative() && !b2.isNegative());
        }
    }
    if (b1 == b2) {
        return false;
    }
    if (b1._numberString.size() > b2._numberString.size()) {
        return true;
    }
    else if (b2._numberString.size() > b1._numberString.size()) {
        return false;
    }
    else {
        for (unsigned int i = 0; i < b1._numberString.size(); i++) {
            if (b1[i] == (b2._numberString[i] - '0')) {
                continue;
            }
            return b1[i] > (b2._numberString[i] - '0');
        }
    }
    return false;
}

bool operator<(BigNumber b1, const BigNumber &b2) {
    return !(b1 == b2) && !(b1 > b2);
}

bool operator>=(BigNumber b1, const BigNumber &b2) {
    return b1 > b2 || b1 == b2;
}

bool operator<=(BigNumber b1, const BigNumber &b2) {
    return b1 < b2 || b1 == b2;
}

int BigNumber::operator[](int index) {
    if (this->_numberString[index] == '-') {
        std::cerr << "You cannot get the negative sign from the number" << std::endl;
    }
    return this->_numberString[index] - '0';
}

BigNumber& BigNumber::operator=(const BigNumber &other) {
    this->_numberString = other._numberString;
    return *this;
}

BigNumber& BigNumber::operator+=(const BigNumber &other) {
    *this = *this + other;
    return *this;
}

BigNumber& BigNumber::operator-=(const BigNumber &other) {
    *this = *this - other;
    return *this;
}

BigNumber& BigNumber::operator*=(const BigNumber &other) {
    *this = *this * other;
    return *this;
}

