#include <iostream>
#include <string>
#include <cmath>

using namespace std;

// Node structure for Doubly Linked List
struct BitNode {
    int bit;
    BitNode* next;
    BitNode* prev;
};

class BinaryNumber {
public:
    BitNode* head;
    BitNode* tail;

    BinaryNumber() {
        head = NULL;
        tail = NULL;
    }

    // append bit at tail
    void appendBit(int b) {
        BitNode* newNode = new BitNode();
        newNode->bit = b;
        newNode->next = NULL;
        newNode->prev = NULL;

        if (head == NULL) {
            head = newNode;
            tail = newNode;
            return;
        }

        tail->next = newNode;
        newNode->prev = tail;
        tail = newNode;
    }

    // prepend bit at head
    void prependBit(int b) {
        BitNode* newNode = new BitNode();
        newNode->bit = b;
        newNode->prev = NULL;
        newNode->next = NULL;

        if (head == NULL) {
            newNode->next = NULL;
            head = tail = newNode;
        } else {
            newNode->next = head;
            head->prev = newNode;
            head = newNode;
        }
    }

    // pad to multiples of 8 bits
    void padToByteMultiple() {
        int length = 0;
        BitNode* temp = head;

        while (temp != NULL) {
            length++;
            temp = temp->next;
        }

        int remainder = length % 8;
        if (remainder != 0 || length == 0) {
            int needed = (8 - remainder) % 8;
            if (length == 0) needed = 8;

            for (int i = 0; i < needed; i++) {
                prependBit(0);
            }
        }
    }

    // 1. Store Binary Number
    void storeBinary(string bits) {
        // clear old nodes if any
        clear();

        for (int i = 0; i < bits.length(); i++) {
            if (bits[i] == '0' || bits[i] == '1') {
                appendBit(bits[i] - '0');
            }
        }

        padToByteMultiple();
    }

    void clear() {
        BitNode* curr = head;
        while (curr != NULL) {
            BitNode* nxt = curr->next;
            delete curr;
            curr = nxt;
        }
        head = NULL;
        tail = NULL;
    }

    // display binary bits in 8-bit grouped format
    void display() {
        if (head == NULL) {
            cout << "00000000";
            return;
        }

        BitNode* temp = head;
        int count = 0;

        while (temp != NULL) {
            cout << temp->bit;
            count++;

            if (count % 8 == 0 && temp->next != NULL) {
                cout << " "; // group separator
            }

            temp = temp->next;
        }
    }

    // 2. 1's Complement
    void onesComplement() {
        BitNode* temp = head;

        while (temp != NULL) {
            // flip bit
            temp->bit = (temp->bit == 0) ? 1 : 0;
            temp = temp->next;
        }
    }

    // 3. 2's Complement (1's complement + 1 using binary addition on DLL)
    void twosComplement() {
        onesComplement();

        // add 1 via DLL traversal from tail
        int carry = 1;
        BitNode* temp = tail;

        while (temp != NULL && carry > 0) {
            int sum = temp->bit + carry;

            temp->bit = sum % 2;
            carry = sum / 2;

            temp = temp->prev;
        }

        if (carry > 0) {
            prependBit(carry);
            padToByteMultiple();
        }
    }

    // 6. Conversion to Decimal
    unsigned long long toDecimal() {
        unsigned long long decVal = 0;
        unsigned long long base = 1;

        BitNode* temp = tail;

        while (temp != NULL) {
            if (temp->bit == 1) {
                decVal += base;
            }

            base = base * 2;
            temp = temp->prev;
        }

        return decVal;
    }

    // deep copy helper
    BinaryNumber clone() {
        BinaryNumber copyNum;
        BitNode* temp = head;

        while (temp != NULL) {
            copyNum.appendBit(temp->bit);
            temp = temp->next;
        }

        return copyNum;
    }

    // shift left by 1 (multiply by 2)
    void shiftLeft() {
        appendBit(0);
        padToByteMultiple();
    }
};

// 4. Binary Addition
BinaryNumber addBinary(BinaryNumber& num1, BinaryNumber& num2) {
    BinaryNumber result;

    BitNode* p1 = num1.tail;
    BitNode* p2 = num2.tail;
    int carry = 0;

    while (p1 != NULL || p2 != NULL || carry > 0) {
        int bit1 = (p1 != NULL) ? p1->bit : 0;
        int bit2 = (p2 != NULL) ? p2->bit : 0;

        int total = bit1 + bit2 + carry;
        result.prependBit(total % 2);

        carry = total / 2;

        if (p1 != NULL) p1 = p1->prev;
        if (p2 != NULL) p2 = p2->prev;
    }

    result.padToByteMultiple();
    return result;
}

// 5. Binary Multiplication (Repeated addition + shifting)
BinaryNumber multiplyBinary(BinaryNumber& num1, BinaryNumber& num2) {
    BinaryNumber product;
    product.storeBinary("0");

    BinaryNumber shiftedMultiplicand = num1.clone();
    BitNode* p2 = num2.tail;

    while (p2 != NULL) {
        if (p2->bit == 1) {
            product = addBinary(product, shiftedMultiplicand);
        }

        // shift multiplicand left by 1
        shiftedMultiplicand.appendBit(0);
        p2 = p2->prev;
    }

    product.padToByteMultiple();
    return product;
}

int main() {
    cout << "Binary Arithmetic Operations (Doubly Linked List)" << endl;

    // 1. Storing Binary Numbers
    BinaryNumber numA, numB;

    cout << "\n[1] Storing Binary Numbers in 8-bit Grouped DLL:" << endl;
    numA.storeBinary("110101");      // Decimal 53
    numB.storeBinary("1011");        // Decimal 11

    cout << "Number A (Binary): "; numA.display(); 
    cout << " -> Decimal: " << numA.toDecimal() << endl;

    cout << "Number B (Binary): "; numB.display(); 
    cout << " -> Decimal: " << numB.toDecimal() << endl;

    // 2. 1's Complement
    cout << "\n[2] 1's Complement of Number A:" << endl;
    BinaryNumber numA_1s = numA.clone();
    numA_1s.onesComplement();
    cout << "1's Complement: "; numA_1s.display();
    cout << " -> Decimal: " << numA_1s.toDecimal() << endl;

    // 3. 2's Complement
    cout << "\n[3] 2's Complement of Number A:" << endl;
    BinaryNumber numA_2s = numA.clone();
    numA_2s.twosComplement();
    cout << "2's Complement: "; numA_2s.display();
    cout << " -> Decimal: " << numA_2s.toDecimal() << endl;

    // 4. Binary Addition
    cout << "\n[4] Binary Addition (A + B):" << endl;
    BinaryNumber sum = addBinary(numA, numB);
    cout << "Sum (Binary):   "; sum.display();
    cout << " -> Decimal: " << sum.toDecimal() << " (Expected: 53 + 11 = 64)" << endl;

    // 5. Binary Multiplication
    cout << "\n[5] Binary Multiplication (A * B):" << endl;
    BinaryNumber product = multiplyBinary(numA, numB);
    cout << "Product (Bin):  "; product.display();
    cout << " -> Decimal: " << product.toDecimal() << " (Expected: 53 * 11 = 583)" << endl;

    // 6. Decimal Conversion demonstration for a multi-byte binary number
    cout << "\n[6] Extended Multi-byte Binary Demonstration (> 8 bits):" << endl;
    BinaryNumber multiByte;
    multiByte.storeBinary("10010010110"); // 11 bits -> padded to 16 bits (2 bytes)
    cout << "11-bit Input:   10010010110" << endl;
    cout << "Stored in DLL:  "; multiByte.display();
    cout << " -> Decimal: " << multiByte.toDecimal() << endl;

    return 0;
}
