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

#ifndef BIGNUMBER_H
#define BIGNUMBER_H

#include <vector>
#include <string>
#include <iostream>

/* BigNumber class
 * Stores a very large number
 * Also contains functions and operators to perform mathematical operations on them
 */
class BigNumber {
public:
    /* Main constructor
     * Initializes member variables with number values
     *  Params:
     *    string number - the big number represented as a string
     *  Returns: None
     */
    BigNumber(std::string number);

    BigNumber(long long number);

    /* Add function
     * Adds another big number to the current instance
     *  Params:
     *    BigNumber other - the other big number to be added
     *  Returns:
     *    The sum of the two big numbers
     */
    BigNumber add(BigNumber other);
    BigNumber add(long long &other);
    BigNumber add(std::string &other);

    /* Subtract function
     * Subracts another big number from the current instance
     *  Params:
     *    BigNumber other - the other big number to be subtracted
     *  Returns:
     *    The difference of the two big numbers
     */
    BigNumber subtract(BigNumber other);

    /* Multiply function
     * Multiplies the big number by another big number
     *  Params:
     *    BigNumber other - the other big number to multiply by
     *  Returns:
     *    The product of the two numbers
     */
    BigNumber multiply(BigNumber other);

    /* pow function
     * Raises the big number to the power of the exponent
     *  Params:
     *    BigNumber exponent - the exponent to raise the big number to
     *  Returns:
     *    The new big number after being raised to the provided exponent
     */
    BigNumber pow(int exponent);

    /* getString function
     * Turns the big number into an std::string and returns it
     *  Params: None
     *  Returns:
     *    The big number represented as an std::string
     */
    std::string getString();

    /* setString function
     * Sets the actual number string to a new string
     *  Params:
     *    std::string newStr - the new string
     *  Returns: None
     */
    BigNumber setString(const std::string &newStr);

    /* negate function
     * Makes the big number negative
     *  Params: None
     *  Returns: The newly negated big number
     */
    BigNumber negate();

    /* equals function
     * Checks if the other big number is equal to this one
     *  Params:
     *    BigNumber other - the other big number being compared
     *  Returns:
     *    True if equal, otherwise false
     */
    bool equals(const BigNumber &other);

    /* digits function
     * Returns the number of digits in the big number
     * Params: None
     * Returns:
     *    The number of digits in the big number
     */
    int digits();

    /*
     * Method: isNegative
     * Determines whether a big number is negative
     * Parameters: None
     * Returns:
     *   True if negative, otherwise false
     */
    bool isNegative() const;

    /*
     * Method: isPositive
     * Determines whether a big number is positive
     * Parameters: None
     * Returns:
     *   True if positive, otherwise false
     */
    bool isPositive();

    /*
     * Method: isEven
     * Determines whether a big number is even
     * Parameters: None
     * Returns:
     *   True if even, otherwise false
     */
    bool isEven();

    /*
     * Method: isOdd
     * Determines whether a big number is odd
     * Parameters: None
     * Returns:
     *   True if odd, otherwise false
     */
    bool isOdd();

    /*
     * Method: abs
     * Gets the absolute value of the big number
     * Parameters: None
     * Returns:
     *  A Big Number containing the absolute value
     */
    BigNumber abs() const;

    //Operator overloads

    //Output stream operator
    friend std::ostream &operator<<(std::ostream &os, const BigNumber &num);
    //Plus operator
    friend BigNumber operator+(BigNumber b1, const BigNumber &b2);
    friend BigNumber operator+(BigNumber b1, const long long &b2);
    friend BigNumber operator+(BigNumber b1, const std::string &b2);
    //Minus operator
    friend BigNumber operator-(BigNumber b1, const BigNumber &b2);
    //Multiplication operator
    friend BigNumber operator*(BigNumber b1, const BigNumber &b2);

    //Exponent operator
    friend BigNumber operator^(BigNumber b1, const int &b2);
    //Equals operator
    friend bool operator==(BigNumber b1, const BigNumber &b2);
    friend bool operator==(BigNumber b1, const long long &b2);
    friend bool operator==(BigNumber b1, const std::string &b2);
    //Greater than operator
    friend bool operator>(BigNumber b1, const BigNumber &b2);
    //Less than operator
    friend bool operator<(BigNumber b1, const BigNumber &b2);
    //Greater than or equal to operator
    friend bool operator>=(BigNumber b1, const BigNumber &b2);
    //Less than or equal to operator
    friend bool operator<=(BigNumber b1, const BigNumber &b2);

    //Assignment operator
    BigNumber& operator=(const BigNumber &other);
    BigNumber& operator=(const long long &other);
    BigNumber& operator=(const std::string &other);
    BigNumber& operator+=(const BigNumber &other);
    BigNumber& operator-=(const BigNumber &other);
    BigNumber& operator*=(const BigNumber &other);

    //Increment/Decrement operators
    BigNumber& operator++();    //Prefix
    BigNumber& operator--();    //Prefix
    BigNumber operator++(int); //Postfix
    BigNumber operator--(int); //Postfix

    //Index operator
    int operator[](int index);

private:
    std::string _numberString;      //The big number represented as a string
};



#endif