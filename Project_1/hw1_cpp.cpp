#include <iostream>
#include <cstring>

using namespace std;

void judge(char *string , int count){  //The function to determine if the string is a palindrome.
    
    int i=0,j=0,len=0;

    for(i=0,j=0;i<count;i++)  //Eliminate the characters other than English.
        if((65<=string[i] && string[i]<=90) || (97<=string[i] && string[i]<=122))
            string[j]=tolower(string[i]) , j++;
    string[j]='\0';

    len=strlen(string);  //Calculate the new string length.

    if(len==0)  //No English letters in argument . Print error message.
        cout << "Error! No English letters in argument ! This is not a palindrome." << endl ;

    else if(len==1)  //If the English letters length is 1, it must be a palindrome.
        cout << "This is a palindrome :) !" << endl ;

    else{   //Using loop determine if the string is a palindrome.
        for(i=0;i<len/2;i++){  //Match the beginning and end of the string until the middle of the string.
            if(string[i]==string[len-1-i]){ 
                if( i==((len/2)-1) )  //Print the success message after comparing.
                    cout << "This is a palindrome :) !" << endl ;  
                continue;
            }
            else{  //Jump out of the loop if different.
                cout << "This is not a palindrome :( !" << endl ;
                break;
            }
        }
    }
}

int main( int argc , char *argv[]) {

    if(argc!=2)  //If the number of argument is wrong, print an error message.
        cout << "Error! Please enter correct number of potential palindrome in argument !" << endl;
    else{
        int len=0;

        len =strlen(argv[1]);
	    judge(argv[1],len);  //determine if the string is a palindrome
    }
    
	return 0;
}