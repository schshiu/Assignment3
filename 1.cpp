// Shiu Chung Haang
// 3035483653
/ /calculate large digit numbers

#include <iostream>
#include <string>

using namespace std;

struct Node
{
    int value;
    Node * next;
};

void print_list(Node * head)  //official custom function
{
    Node * current = head;
    while (current != NULL)
    {
        // process the current node, e.g., print the content
        cout << current->value << " -> ";
        current = current->next;
    }
    cout << "NULL\n";
}

void tail_insert(Node * & head, Node * & tail, int num) //official custom function
{
    Node * p = new Node;
    p->value = num;
    p->next = NULL;

    if (head == NULL) {
        head = p;
        tail = p;
    }
    else {
        tail->next = p;
        tail = p;
    }
}

void head_insert(Node * & head, int num)  //official custom function
{
    Node * p = new Node;
    p->value = num;
    p->next = head;
    head = p;
}

void makelist(Node * & head, size_t strlen, string number) {  //put into linked list function
    string temp, temp2;
    int num = 0;
    temp = number;
    
    // literally consider all situation as there is not a lot
    if (strlen < 3) {
        num = stoi(temp);
        head_insert(head, num);
    }
    else {
        for (int i = 0; i < strlen; ++i) {
            if (strlen % 3 == 0) {
                temp2 = temp2 + temp[i];
                if (temp2.size() == 3) {
                    num = stoi(temp2);
                    head_insert(head, num);
                    temp2 = "";
                }
            }
            else if (strlen % 3 == 1) {
                if (i == 0) {
                    temp2 = temp2 + temp[i];
                    num = stoi(temp2);
                    head_insert(head, num);
                    temp2 = "";
                }
                else {
                    temp2 = temp2 + temp[i];
                    if (temp2.size() == 3) {
                        num = stoi(temp2);
                        head_insert(head, num);
                        temp2 = "";
                    }
                }
            }
            else if (strlen % 3 == 2) {
                if (i == 0) {
                    temp2 = temp2 + temp[i];
                }
                else if (i == 1) {
                    temp2 = temp2 + temp[i];
                    num = stoi(temp2);
                    head_insert(head, num);
                    temp2 = "";
                }
                else {
                    temp2 = temp2 + temp[i];
                    if (temp2.size() == 3) {
                        num = stoi(temp2);
                        head_insert(head, num);
                        temp2 = "";
                    }
                }
            }
        }
    }
}

int main() {
    string str_userinput;
    size_t plus_location;
    string str_firstnumber, str_secondnumber;
    
    // get input
    getline(cin, str_userinput);
    
    // seperate into two strings
    plus_location = str_userinput.find("+");
    str_firstnumber = str_userinput.substr(0 , plus_location - 1);
    str_secondnumber = str_userinput.substr(plus_location + 2);
    
    // get string length
    size_t firstnum_len, secondnum_len;
    firstnum_len = str_firstnumber.size();
    secondnum_len = str_secondnumber.size();
    
    //put into linked list
    Node * head1 = NULL;
    Node * head2 = NULL;
    Node * head3 = NULL, *tail3 = NULL;
    
    makelist(head1, firstnum_len, str_firstnumber);
    makelist(head2, secondnum_len, str_secondnumber);
    
    print_list(head1);
    print_list(head2);
    
    //Calculation
    int carry, sum;
    sum = carry = 0;
    while (head1 != NULL || head2 != NULL) {
        sum = carry + (head1 ? head1->value : 0) + (head2 ? head2->value : 0);
        carry = (sum >= 1000) ? 1 : 0;
        sum = sum % 1000;
        tail_insert(head3, tail3, sum);
        if (head1) {
            head1 = head1->next;
        }
        if (head2) {
            head2 = head2->next;
        }
    }
    if (carry > 0) {
        tail_insert(head3, tail3, carry);
    }
    print_list(head3);
    
    string result;
    string zeros = "00";
    string zero = "0";
    Node * current = head3;
    
    // revert back into string form to print
    while (current != NULL) {
        int x = 0;
        x = current->value;
        if (to_string(x).size() == 1) {
            result = zeros + to_string(x) + result;
        }
        else if (to_string(x).size() == 2) {
            result = zero + to_string(x) + result;
        }
        else {
            result = to_string(x) + result;
        }
            current = current->next;
    }
    
    while (result[0] == '0') {
        result = result.substr(1);
    }
    cout << result << endl;
}
