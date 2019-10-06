#include <iostream>
#include <cstring>
#include <cstdlib>
#include <cstdio>

using namespace std;

//Define the content of the linked list
struct words{
    char data[32];
    int number;

    struct words *next;
};
typedef struct words Words;

//Remove extra space from strings
void removed(char a[] , int N){
	int i,j;
	char b[128];

	for(i=0,j=0;i<N-1;i++,j++)
		if(a[i]==' ')
			if(a[i-1]==' ')
				j--;
			else
				b[j]=a[i];
		else
			b[j]=a[i];

	b[j]='\0';
	strcpy(a,b);
}

//Insert new node into linked list.
Words *insert( Words *head , char input[] ){  

    int count=1;
    Words *node = new Words;  //Create a new node
    Words *last , *current;

    strcpy(node->data,input);  //Set data
    
    //If the linked list is empty then the new node is the new header.
    if(head == NULL){
        node->number=1;  //This date first appeared in the linked list
        node->next=NULL;
        return node;
    }

    //Connect the new node to the back of the linked list
    else{
        last=NULL;
        current=head;
        while(current!=NULL){  //Calculate how many times this data has appeared in the linked list
            if(strcmp(current->data,input)==0)
                count++;
            last=current;
            current=current->next;
        }
        last->next=node;
        node->number=count;  //This data has appeared count-1 times
        node->next=NULL;
        return head;
    }
}

//Clear all the nodes in the linked list
Words *clear(Words *head){
    if (head==NULL)
        return NULL;

    Words *next = head->next;
    delete head;

    return clear(next);
}

//Transfer words from string to another string
char *trans(char key[] , char input[]){
    char *ptr=NULL,*qtr=NULL;

    ptr=input;
    qtr=key;

    while(*ptr==' ')
        ptr++;

    while( *ptr!=' ' && *ptr!='\0' )
        *qtr++=*ptr++;
    *qtr='\0';

    return ptr;
}

//Main program
int main (void) {
    char input[128];
    Words *head=NULL;

    cout << ">Please enter your command" << endl;
    cout << ">" ;

    //Read instructions
    while( fgets( input, 128 , stdin)!=NULL ){
        char *ptr=NULL,*qtr=NULL;
        char first[32];

        removed(input,strlen(input));
        ptr=trans(first,input);

        //When the instruction is load
        if(strcmp("load",first)==0){
            FILE *pFile;
            char temp[256],second[32];

            //No file name after load
            if(*ptr=='\0'){
                cout << "ERROR: Invalid command" << endl;
                cout << ">" ;
                continue;
            }

            strcpy(second , ptr+1);
            pFile = fopen ( second , "r" );

            //No file found
            if (pFile == NULL)
                cout << "ERROR: Error reading from file" << endl;
            else{
                head=clear(head);
                while ( fgets (temp , 256 , pFile) != NULL ){  //Read the contents of the file and store it in the string
                    temp[strlen(temp)-1]='\0';
                    ptr=temp ;
                    while(*ptr!='\0'){
                        qtr=second;
                        while((*ptr==39) || (47<*ptr && *ptr<58) || (64<*ptr && *ptr<91) || (96<*ptr && *ptr<123)){
                            *qtr++=*ptr++;  //Store words in strings in another string
                        }
                        if(second[0]==' ')
                            ptr++;
                        else if((second[0]==39) || (47<second[0] && second[0]<58) || (64<second[0] && second[0]<91) || (96<second[0] && second[0]<123)){
                            *qtr='\0';
                            head=insert(head,second);  //Create a node when the string is a valid string
                            second[0]='\0';
                            ptr++;
                        }
                        else
                            ptr++;
                    }
                }
            }
        }

        //When the instruction is locate
        else if(strcmp("locate",first)==0){
            char second[32],third[32];
            int flag=0,number=0,count=0;
            unsigned int i=0;
            Words *current;

            ptr=trans(second,ptr);
            for(i=0;i<strlen(second);i++){
                if((second[i]==39) || (47<second[i] && second[i]<58) || (64<second[i] && second[i]<91) || (96<second[i] && second[i]<123))
                    continue;  //Check for illegal characters in words
                else{
                    flag=1;
                    break;
                }
            }
            if(flag==1){
                cout << "ERROR: Invalid command" << endl;
                cout << ">" ;
                continue;
            }

            strcpy(third,ptr+1);
            for(i=0;i<strlen(third);i++){
                if( 47<third[i] && third[i]<58 ){
                    continue;  //Check if illegal characters exist in number
                }
                else
                    flag=1;
            }
            if(flag==1){
                cout << "ERROR: Invalid command" << endl;
                cout << ">" ;
                continue;
            }

            number=atoi(third);
            if(number<1){  //When number is less than 1 is an error condition
                cout << "ERROR: Invalid command" << endl;
                cout << ">" ;   
                continue;
            }

            //Compare whether there is a match item in the word list
            for(count=1,current=head;current!=NULL;current=current->next,count++) 
                if(strcmp(current->data,second)==0 && current->number == number){
                    flag=1;
                    break;
                }

            //No matches found in the word list
            if(flag==0){
                cout << "No matching entry" << endl;
                cout << ">" ;
                continue;
            }

            //matches found in the word list
            cout << count << endl;
        }

        //When the instruction is new
        else if(strcmp("new",first)==0){
            if(input[3]!='\0')  //There is a character present after the instruction
                cout << "ERROR: Invalid command" << endl; 
            else
                head=clear(head);
        }

        //When the instruction is end
        else if(strcmp("end",first)==0){
            if(input[3]!='\0')  //There is a character present after the instruction
                cout << "ERROR: Invalid command" << endl; 
            else
                break;
        }

        //When an instruction does not exist
        else
            cout << "ERROR: Invalid command" << endl;

        cout << ">" ;

    }
	return 0;
}