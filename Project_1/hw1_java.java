import java.io.*;

public class hw1_java {

    public static String reverse(String palindrome){  //Custom function that reversed string.

    String reversestr="" ;  //Used to be an inverted string.
    int i = 0;

    for( i=palindrome.length()-1 ; i >= 0 ; i--)  //Copy from the end of the string to a new string.
      reversestr = reversestr + palindrome.charAt(i);
    
    return reversestr; //Return the new string
    }// end reverse function

	public static void main(String args[]){

        if(args.length!=1) {   //If the number of argument is wrong, print an error message.
            System.out.println("Error! Please enter correct number of potential palindrome in argument !"); 
            }

        else {
                args[0] = args[0].toLowerCase();  //Convert all characters to lowercase
                args[0] = args[0].replaceAll( "\\p{Punct}", "" );  //Eliminate the punctuation
                args[0] = args[0].replaceAll(" ", "");  //Eliminatie the white space

            int len=args[0].length();

            if (len==0)  //No English letters in argument . Print error message .
                System.out.println("Error! No English letters in argument ! This is not a palindrome.");

            else{
                String judge;
                judge = reverse(args[0]);  //Reverse the original string
            
                if(args[0].equals(judge))  //Print the message after comparing two strings
                    System.out.println("This is a palindrome :) !");
                else
                    System.out.println("This is not a palindrome :( !");
            }
        }
	} // end main
} // end of class hw1_java
