// Problem 02.03
// ASCII classification



#include <iostream>
#include <print>



int main() {

    char ch;

    std::cin >> ch;
    if (ch <= 32 || ch >= 127) { // implicit ascii conversion to int
	return 1;		 // check the task given restrictions
    }

    switch (ch) {
        // GCC extention for switch ranges:
        case 'A' ... 'Z':
            std::print("Capital letter\n");
            break;
        case 'a' ... 'z':
            std::print("Lowercase letter\n");
            break;
        case '0' ... '9':
            std::print("Digit\n");
            break;
        case '.': case ',': case ':': case ';': case '!': case '?': case '-': // fallthrough
            std::print("Punctuation mark\n");
            break;
        default:
            std::print("Other characters\n");
            break;
    }

    return 0;

}
