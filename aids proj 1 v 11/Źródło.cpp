#include <iostream>
using namespace std;

struct CharNode {
    char value;
    CharNode* next;

    CharNode(char val) :value(val), next(nullptr) {};
};



class Node {
public:
    CharNode* charList;
    Node* next;

    Node() {
        charList = nullptr;
        next = nullptr;
    }
};

class Stack {


public:
    Node* head;
    Stack() {
        head = nullptr;
    }
    ~Stack() {
		deleteStackRecursive(head);
    }
    // ' FUNCTIONS
    void Push() {

        Node* newNode = new Node();

        newNode->next = head;
        head = newNode;
    }
    // , FUNCTIONS
    void Pop() {
        if (head == nullptr) return;
        Node* temp = head;
        head = head->next;
        delete temp;
    }



    // : FUNCTIONS
    void PushCopy() {
        if (head == nullptr) return; 

        // Tworzymy nowy węzeł stosu
        Node* newNode = new Node();

        newNode->charList = PushCopyRekurencja(head->charList);

        // Umieszczamy nowy węzeł
        newNode->next = head;
        head = newNode;
    }

    CharNode* PushCopyRekurencja(CharNode* original) {
        if (original == nullptr) {
            return nullptr;
        }

        // Tworzymy nowy węzeł z bieżącą wartością
        CharNode* newNode = new CharNode(original->value);

        newNode->next = PushCopyRekurencja(original->next);

        return newNode;
    }
    // ; FUNCTIONS
    void ChangePlace() {
        if (head == nullptr || head->next == nullptr) return;

        CharNode* temp = head->charList;
        head->charList = head->next->charList;
        head->next->charList = temp;
    }
    // & FUNCTIONS
    void PrintStack() {
        if (head == nullptr) {
            return;
        }
        printStackRecursive(head, 0);
    }

    void printStackRecursive(Node* current, int currentDepth) {
        // Najpierw schodzimy do końca stosu
        if (current->next != nullptr) {
            printStackRecursive(current->next, currentDepth + 1);
        }

        // drukujemy bieżący węzeł
        cout << currentDepth << ": ";
        printCharListRecursive(current->charList);
        cout << endl;
    }

    // Funkcja do drukowania listy znaków
    void printCharListRecursive(CharNode* charCurrent) {
        if (charCurrent == nullptr) {
            return; // warunek stopu
        }
        cout << charCurrent->value;
        printCharListRecursive(charCurrent->next);
    }

	//@ FUNCTIONS

    int listToInt(CharNode* list) {
        if (list == nullptr) return 0;

        // Sprawdzamy czy liczba jest ujemna
        bool isNegative = checkIfNegative(list);

        int num = convertDigitsToInt(list, isNegative);

        return isNegative ? -num : num;

    }

    bool checkIfNegative(CharNode* node) {
        if (node == nullptr) return false; 
        if (node->next == nullptr) { 
            return (node->value == '-');
        }
        return checkIfNegative(node->next);
    }

    // Funkcja konwertuje cyfry na liczbę
    int convertDigitsToInt(CharNode* node, bool isNegative, int multiplier = 1) {
        if (node == nullptr || node->value == '-') return 0;
        int currentDigit = node->value - '0';
        int nextValue = convertDigitsToInt(node->next, isNegative, multiplier * 10);
        return currentDigit * multiplier + nextValue;
    }

    void At() {
        if (head == nullptr) return; 

        //Pobiera  liczbę A z wierzchołka
        int A = listToInt(head->charList);
        Pop();

        // Znajduje A-ty element rekurencyjnie
        Node* target = findNodeAtDepth(head, A);
        if (target == nullptr) return; // Nie ma tylu elementów

        CharNode* copy = PushCopyRekurencja(target->charList);

        //Wklada kopię na stos
        Node* newNode = new Node();
        newNode->charList = copy;
        newNode->next = head;
        head = newNode;
    }


    Node* findNodeAtDepth(Node* current, int depth) {
        if (current == nullptr) return nullptr; // Koniec stosu
        if (depth == 0) return current; // Znaleźliśmy właściwy węzeł
        return findNodeAtDepth(current->next, depth - 1); // Szukamy głębiej
    }

	//. FUNCTIONS

    void DotFunction() {
        char inputChar;
        cin >> inputChar;
        if (head == nullptr) {
            Push();
        }
        CharNode* newCharNode = new CharNode(inputChar);

        newCharNode->next = head->charList;
        head->charList = newCharNode;

    }
	// > FUNCTIONS

    void GreaterFunction() {
        if (head == nullptr || head->charList == nullptr) {
            return;
        }

        //Wypisz pierwszy znak z listy na wierzchołku
        CharNode* firstChar = head->charList;
        cout << firstChar->value; 

        Pop();  
    }


	//- FUNCTIONS
    void MinusFunction() {
        if (head == nullptr) {
            Push();
            head->charList = new CharNode('-');
            return;
        }

        if (head->charList == nullptr) {
            head->charList = new CharNode('-');
            return;
        }

        processMinusRecursive(&(head->charList));
    }

    void deleteStackRecursive(Node* node) {
        if (!node) return;
        deleteStackRecursive(node->next); 
        deleteCharListRecursive(node->charList); 
        delete node; 
    }

    void processMinusRecursive(CharNode** nodePtr) {
        CharNode* current = *nodePtr;

        if (current->next == nullptr) {
            if (current->value == '-') {
                // Usuwamy minus
                delete current;
                *nodePtr = nullptr;
            }
            else {
                // Dodajemy minus na końcu
                current->next = new CharNode('-');
            }
            return;
        }

        processMinusRecursive(&(current->next));
    }

	//^ FUNCTIONS

    void HoodFunction() {
        if (head == nullptr || head->charList == nullptr) {
            return; 
        }

        processHoodRecursive(&(head->charList));
    }

    void processHoodRecursive(CharNode** nodePtr) {
        CharNode* current = *nodePtr;

        if (current->next == nullptr) {
            if (current->value == '-') {
                // Usuwamy minus
                delete current;
                *nodePtr = nullptr;
            }
            return;
        }

        processHoodRecursive(&(current->next));
    }

// [ FUNCTIONS
    void convertToASCII() {
        if (!head) return;

        //Pobiera pierwszy znak i zdejmij węzeł
        Node* listNode = head;
        head = head->next;

        char firstChar = (listNode->charList) ? listNode->charList->value : 0;
        int asciiValue = (int)firstChar;

        // Usuwa starą listw 
        deleteCharListRecursive(listNode->charList);
        delete listNode;

        // 3. Tworzy nową listę z cyframi ASCII
        if (asciiValue == 0) {
            Push();
            head->charList = new CharNode('0');
        }
        else {
            Push();
            head->charList = createASCIIDigitsRecursive(asciiValue);
        }
    }

    // Usuwa listę znakow
    void deleteCharListRecursive(CharNode* node) {
        if (!node) return;
        deleteCharListRecursive(node->next);
        delete node;
    }

    // Tworzy listę cyfr
    CharNode* createASCIIDigitsRecursive(int value) {
        if (value == 0) return nullptr;

        int digit = value % 10;
        CharNode* newNode = new CharNode('0' + digit);
        newNode->next = createASCIIDigitsRecursive(value / 10);
        return newNode;
    }

    // ] FUNCTIONS

    void ConvertToChar() {
        if (!head || !head->charList) return;  

        int asciiValue = listToInt(head->charList);
        Pop();
        asciiValue = asciiValue % 128;
        Push();
        head->charList = new CharNode(static_cast<char>(asciiValue));
    }

	// $ FUNCTIONS

    void DollarFunction() {
        if (!head) {
            return;
        }
        CharNode* firstNode = head->charList;

        head->charList = firstNode->next;
        firstNode->next = nullptr;
		//wklada nowy węzeł na stos
        Node* newNode = new Node();
        newNode->charList = firstNode;
        newNode->next = head;
        head = newNode;
    }

	// # FUNCTIONS


    void HashFunction() {
        if (!head || !head->next) return;

        //Zdejmuje drugą listę (listA)
        Node* listA = head->next;
        head->next = listA->next;

        // Dolacza listę z wierzchołka na koniec listy A
        listA->charList = appendListsRecursive(listA->charList, head->charList);

        //Przenodi połączoną listę z powrotem na wierzchołek
        head->charList = listA->charList;

        // Zwolnia węzeł
        listA->charList = nullptr;
        delete listA;
    }

    CharNode* appendListsRecursive(CharNode* mainList, CharNode* listToAppend) {
        if (!mainList) {
            return listToAppend;
        }
        mainList->next = appendListsRecursive(mainList->next, listToAppend);
        return mainList;
    }

    // < FUNCTIONS


    bool hasTrailingMinus(CharNode* node) {
        if (!node) return false; 
        if (!node->next) return node->value == '-'; 
        return hasTrailingMinus(node->next); 
    }

    CharNode* deleteTrailingMinus(CharNode* node) {
        if (!node) {
            return nullptr; 
        }

        node->next = deleteTrailingMinus(node->next);

        if (node->value == '-' && !node->next) {
            delete node;
            return nullptr; 
        }

        return node; 
    }



    // -1 = pierwsze < drugie
    //  0 = rowne
    // +1 = pierwsze > rdgie
    int compareReversedLists(CharNode* list1, CharNode* list2, bool hadMinus) {
        if (!list1 && !list2) return 0;
        if (!list1 || !list2)
            return list1 ? +1 : -1;

        int sub = compareReversedLists(list1->next, list2->next, hadMinus);
        if (sub != 0) return sub;

        if (list1->value != list2->value) {
            if (hadMinus) {
                return (list1->value > list2->value) ? -1 : +1;
            }
            else {
                return (list1->value < list2->value) ? -1 : +1;
            }
        }
        return 0; 
    }

    bool getLastElement(CharNode* b, CharNode* a, bool hadMinus) {
        return compareReversedLists(b, a, hadMinus) < 0;
    }







    void LesserFunction() {
        if (!head || !head->next) {
            Push();
            head->charList = new CharNode('0');
            return;
        }

        CharNode* listA = head->charList;
        CharNode* listB = head->next->charList;

        Pop();
        Pop();

        if (isZeroList(listA) && isZeroList(listB)) {
            Push();
            head->charList = new CharNode('0');
            return;
        }

        listA = lepszeZero(listA);
        listB = lepszeZero(listB);

        bool isLess = LesserRecurention(listB, listA);

        char result = isLess ? '1' : '0';
        Push();
        head->charList = new CharNode(result);
    }


    bool LesserRecurention(CharNode* b, CharNode* a) {
        bool hadMinus = false;
        bool isNegA = hasTrailingMinus(a);
        bool isNegB = hasTrailingMinus(b);
        if (isNegA == true && isNegB == false) return false;
        if (isNegA == false && isNegB == true) return true;
        if (isNegA == true && isNegB == true) {
            a = deleteTrailingMinus(a);
            b = deleteTrailingMinus(b);
            int lenA = getLength(a);
            int lenB = getLength(b);
            hadMinus = true;

            if (lenA > lenB) {
                return false;
            }
            else if (lenA < lenB) {
                return true;
            }
            else {
                return(getLastElement(b, a, hadMinus));
            }
        }
        a = deleteTrailingMinus(a);
        b = deleteTrailingMinus(b);
        int lenA = getLength(a);
        int lenB = getLength(b);

        if (lenA > lenB) {
            return true;
        }
        else if (lenA < lenB) {
            return false;
        }
        else {
            return(getLastElement(b, a, hadMinus));
        }
        return false;
    }


    int getLength(CharNode* node) {
        if (!node) return 0; 
        if (node->value == '-') {
            return getLength(node->next); // Ignorujemy znak '-'
        }
        return 1 + getLength(node->next);
    }


    CharNode* lepszeZeroHelper(CharNode* node, bool& canDelete) {
        if (!node) {
            canDelete = true; // Możemy usuwać — jesteśmy na końcu listy
            return nullptr;
        }

        node->next = lepszeZeroHelper(node->next, canDelete);

        if (node->value == '-') {
            // Skipujemy '-', traktujemy jakby go nie było
            return node;
        }

        if (canDelete && node->value == '0') {
            CharNode* temp = node->next;
            delete node;
            return temp;
        }
        else {
            canDelete = false; // Trafiliśmy na coś innego niż '0' — dalej już nie usuwamy
            return node;
        }
    }

    CharNode* lepszeZero(CharNode* node) {
        bool canDelete = true;
        return lepszeZeroHelper(node, canDelete);
    }



    bool isZeroList(CharNode* node) {
        if (!node) return true; 
        if (node->next == nullptr && node->value == '-') return true; 
        if (node->value != '0') return false; 
        return isZeroList(node->next);
    }


	//= FUNCTIONS
    void EqualFunction() {
        if (!head || !head->next) {
            Push();
            head->charList = new CharNode('0');
            return;
        }

        CharNode* listA = head->charList;
        CharNode* listB = head->next->charList;

        bool areEqual = compareEqualRecursive(listA, listB);

        Pop();
        Pop();

        Push();
        head->charList = new CharNode(areEqual ? '1' : '0');
    }

    // Sprawdzanie równości list
    bool compareEqualRecursive(CharNode* a, CharNode* b) {
        if (isZeroList(a) && isZeroList(b)) return true;

        bool isNegA = hasTrailingMinus(a);
        bool isNegB = hasTrailingMinus(b);
        if (isNegA != isNegB) return false;

        // Usuwa leading zera i minusy
        a = lepszeZero(a);
        b = lepszeZero(b);
		a = deleteTrailingMinus(a);
		b = deleteTrailingMinus(b);

        // Porównanie
        if (!a && !b) return true;
        if (!a || !b) return false;
        if (a->value != b->value) return false;

        return compareEqualRecursive(a->next, b->next);
    }

	// ! FUNCTIONS

    void ExclamantionFunction() {
        if (!head) {
            Push();
            head->charList = new CharNode('1');
            return;
        }

        bool shouldNegate = checkNegationCondition(head->charList);

        deleteCharListRecursive(head->charList);

        head->charList = new CharNode(shouldNegate ? '1' : '0');
    }

    // sprawdzaj warunek negacji (pusta lista lub pojedyncze 0)
    bool checkNegationCondition(CharNode* node) {
        if (!node) return true; // Pusta lista
        if (!node->next && node->value == '0') return true; // Pojedyncze '0'
        return false; // Inne przypadki
    }

	//~ FUNCTIONS

    void TildeOperation(int instructionPointer) {
        Push();
        head->charList = intToCharList(instructionPointer);
    }

    //(sprawdz czy sie nie powtarzaa)
    CharNode* intToCharList(int number) {
        if (number == 0) {
            return new CharNode('0');
        }

        return convertNumberRecursive(abs(number), nullptr, number < 0);
    }

    CharNode* convertNumberRecursive(int num, CharNode* head, bool isNegative) {
        if (num == 0) {
            if (isNegative) {
                // Dodajemy minus na końcu listy
                CharNode* minusNode = new CharNode('-');
                if (!head) {
                    return minusNode;
                }
                appendDigitRecursive(head, minusNode);
            }
            return head;
        }

        CharNode* newNode = new CharNode('0' + (num % 10));
        if (!head) {
            head = newNode;
        }
        else {
            appendDigitRecursive(head, newNode);
        }
        return convertNumberRecursive(num / 10, head, isNegative);
    }


    void appendDigitRecursive(CharNode* current, CharNode* newNode) {
        if (!current->next) {
            current->next = newNode;
        }
        else {
            appendDigitRecursive(current->next, newNode);
        }
    }

	// ? FUNCTIONS

    void QuestionFunction(int& instructionPointer) {
        if (!head || !head->next) return; 

        // Pobiera wartość T (numer skoku)
        int T = listToInt(head->charList);
        Pop();

        // Pobiera listę W (warunek)
        CharNode* W = head->charList;
        Pop();

        bool shouldJump = checkConditionRecursive(W);

        // Jeśli warunek spełniony - zmień wskaźnik instrukcji
        if (shouldJump) {
            instructionPointer = T - 1; // -1 bo pętla for w main i tak zwiększy
        }

        deleteCharListRecursive(W);
    }

    // Sprawdzająca warunek
    bool checkConditionRecursive(CharNode* node) {
        if (!node) return false;                   
        if (node->next == nullptr && node->value == '0') return false; 
        return true; 
    }

    //+ FUNCTIONS

    CharNode* addTrailingMinus(CharNode* node) {
        if (!node) {
            return new CharNode('-');
        }


        node->next = addTrailingMinus(node->next);

        if (!node->next && node->value != '-') {
            node->next = new CharNode('-');
        }

        return node; 
    }



    void PlusFunction() {
        if (!head || !head->next) return; 

        CharNode* listA = head->charList;
        CharNode* listB = head->next ? head->next->charList : nullptr;
        if (getLength(listA) < 12 && getLength(listB) < 12) {//jesli liczby sa male bierze funsmall
            PlusFunctionSmall();
            return;
        }
        //Usuwamy zera
        listA = lepszeZero(listA);
        listB = lepszeZero(listB);

        bool isNegA = hasTrailingMinus(listA);
        bool isNegB = hasTrailingMinus(listB);
		bool isLess = LesserRecurention(listB, listA);//Sprawdza ktora liczba mniejsza


        listA = deleteTrailingMinus(listA);
        listB = deleteTrailingMinus(listB);
		bool isLessABS = LesserRecurention(listB, listA);//Sprawdza ktora liczba mniejsza bez znaku
        int lenA = getLength(listA);
        int lenB = getLength(listB);
        bool BshorterA = false;
        bool areEqual = false;
        if (lenA > lenB) {
            BshorterA = true;
        }
        if (lenA == lenB) {
            areEqual = true;
        }



        Pop();
        Pop();

        Push();
        if (isNegA && isNegB) {
            // Obie liczby są ujemne
            head->charList = addListsRecursivePlus(listA, listB);
            head->charList = lepszeZero(head->charList);
            head->charList = addTrailingMinus(head->charList);


        }
        else if (isNegA) {

            if (areEqual) {
                if (!isLessABS) {
                    if (!isLess) {
                        head->charList = addListsRecursiveMinusA(listA, listB, BshorterA);
                    }
                    else if (isLess) {
                        head->charList = addListsRecursiveMinusA(listA, listB, BshorterA);
                    }
                }
                else {
                    if (!isLess) {
                        head->charList = addListsRecursiveMinusA(listB, listA, BshorterA);
                    }
                    else if (isLess) {
                        head->charList = addListsRecursiveMinusA(listA, listB, BshorterA);
                    }
                }

            }

            else if (isLessABS) {
                head->charList = addListsRecursiveMinusA(listB, listA, BshorterA);
            }
            else if (!isLessABS) {
                head->charList = addListsRecursiveMinusA(listA, listB, BshorterA);
            }

            if (head->charList && head->charList->value != '0') {
                head->charList = lepszeZero(head->charList);

            }
            if ((head->charList && head->charList->value == '0' && head->charList->next && head->charList->next->value == '0') || (head->charList && head->charList->value == '0' && head->charList->next == nullptr)) {
                head->charList = new CharNode('0');
            }
            else if (head->charList && (isLessABS && !isLess)) {
                head->charList = addTrailingMinus(head->charList);
            }



        }
        else if (isNegB) {
            if (areEqual) {
                if (isLessABS) {
                    if (!isLess) {
                        head->charList = addListsRecursiveMinusA(listB, listA, BshorterA);
                    }
                    else if (isLess) {
                        head->charList = addListsRecursiveMinusA(listB, listA, BshorterA);
                    }
                }
                else {
                    if (!isLess) {
                        head->charList = addListsRecursiveMinusA(listB, listA, BshorterA);
                    }
                    else if (isLess) {
                        head->charList = addListsRecursiveMinusA(listA, listB, BshorterA);
                    }
                }

            }

            else if (isLessABS) {
                head->charList = addListsRecursiveMinusA(listB, listA, BshorterA);
            }
            else if (!isLessABS) {
                head->charList = addListsRecursiveMinusA(listA, listB, BshorterA);
            }

            if (head->charList && head->charList->value != '0') {
                head->charList = lepszeZero(head->charList);

            }
            if ((head->charList && head->charList->value == '0' && head->charList->next && head->charList->next->value == '0') || (head->charList && head->charList->value == '0' && head->charList->next == nullptr)) {
                head->charList = new CharNode('0');
            }
            else if (head->charList && (!isLessABS && isLess)) {
                head->charList = addTrailingMinus(head->charList);
            }
        }


        else {
            // Obie liczby są dodatnie
            head->charList = addListsRecursivePlus(listA, listB);
            if (head->charList && head->charList->value != '0') {
                head->charList = lepszeZero(head->charList);

            }
        }
    }


    CharNode* addListsRecursivePlus(CharNode* a, CharNode* b, int carry = 0) {
        if (!a && !b && carry == 0) return nullptr;


        int valueA = (a ? a->value - '0' : 0);
        int valueB = (b ? b->value - '0' : 0);



        // Oblicza sumę z uwzględnieniem przeniesienia
        int sum = valueA + valueB + carry;

        // Oblicza nową cyfrę i przeniesienie
        carry = 0;
        if (sum >= 10) {
            carry = 1; // Przeniesienie
            sum -= 10; // Korekta dla wartości większej niż 9
        }

        // Tworzymy nowy węzeł z bieżącą cyfrą
        CharNode* newNode = new CharNode('0' + sum);

        newNode->next = addListsRecursivePlus(a ? a->next : nullptr, b ? b->next : nullptr, carry);

        return newNode;
    }



    CharNode* addListsRecursiveMinusA(CharNode* a, CharNode* b, bool BshorterA, int carry = 0) {

        if (!a && !b) {
            carry = 0;
        }
        if (!a && !b && carry == 0) return nullptr;


        int valueA = (a ? a->value - '0' : 0);
        int valueB = (b ? b->value - '0' : 0);



        // Oblicz sumę z uwzględnieniem przeniesienia
        int sum = valueB - valueA + carry;

        // Oblicz nową cyfrę i przeniesienie
        carry = 0;
        if (sum < 0) {
            carry = -1; // Pożyczka
            sum += 10; // Korekta dla ujemnej wartości
        }

        if (sum >= 10) {
            carry = 1; // Przeniesienie
            sum -= 10; // Korekta dla wartości większej niż 9
        }

        // Tworzymy nowy węzeł z bieżącą cyfrą
        CharNode* newNode = new CharNode('0' + sum);

        newNode->next = addListsRecursiveMinusA(a ? a->next : nullptr, b ? b->next : nullptr, BshorterA, carry);

        return newNode;
    }


    CharNode* addListsRecursiveMinusB(CharNode* a, CharNode* b, bool BshorterA, int carry = 0) {
        if (!a && !b) {
            carry = 0;
        }
        if (!a && !b && carry == 0) return nullptr;


        int valueA = (a ? a->value - '0' : 0);
        int valueB = (b ? b->value - '0' : 0);



        // Oblicz sumę z uwzględnieniem przeniesienia
        int sum = -valueB + valueA + carry;

        // Oblicz nową cyfrę i przeniesienie
        carry = 0;
        carry = 0;
        if (sum < 0) {
            carry = -1; // Pożyczka
            sum += 10; // Korekta dla ujemnej wartości
        }

        if (sum >= 10) {
            carry = 1; // Przeniesienie
            sum -= 10; // Korekta dla wartości większej niż 9
        }

        // Tworzymy nowy węzeł z bieżącą cyfrą
        CharNode* newNode = new CharNode('0' + sum);

        newNode->next = addListsRecursiveMinusB(a ? a->next : nullptr, b ? b->next : nullptr, BshorterA, carry);


        return newNode;
    }


    void PlusFunctionSmall() {//sumujemy male liczby
        if (!head || !head->next) return;

        int A = listToInt(head->charList);
        Pop();
        int B = listToInt(head->charList);
        Pop();

        long long C = (long long)A + (long long)B;

        Push();
        head->charList = intToCharList((int)C);
    }


};

int main() {
    Stack stack;
    char program[20000];
    cin >> program;

    for (int i = 0; program[i] != '\0'; i++) {  // Wczytuje polecenia aż do końca wejscia 
        char polecenie = program[i];
        switch (polecenie) {
        default:
            if (stack.head != nullptr) {
                CharNode* newChar = new CharNode(polecenie);
                newChar->next = stack.head->charList;
                stack.head->charList = newChar;
            }
            break;
        case '\'':
            stack.Push();
            break;
        case ',':
            stack.Pop();
            break;
        case ':':
            stack.PushCopy();
            break;
        case ';':
            stack.ChangePlace();
            break;
        case '@':
            stack.At();
            break;
        case '&':
            stack.PrintStack();
            break;
        case '.':
            stack.DotFunction();
            break;
        case '>':
            stack.GreaterFunction();
            break;
        case'-':
            stack.MinusFunction();
            break;
        case '^':
            stack.HoodFunction();
            break;
        case '[':
            stack.convertToASCII();
            break;
        case ']':
            stack.ConvertToChar();
            break;
        case '$':
            stack.DollarFunction();
            break;
        case '#':
            stack.HashFunction();
            break;
        case '<':
            stack.LesserFunction();
            break;
        case '=':
            stack.EqualFunction();
            break;
        case '!':
            stack.ExclamantionFunction();
            break;
        case '~':
            stack.TildeOperation(i);
            break;
        case '?':
            stack.QuestionFunction(i);
            break;
        case '+':
            stack.PlusFunction();
            break;
     
 
        }
    }
    return 0;
}
