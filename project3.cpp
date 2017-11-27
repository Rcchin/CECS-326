#include <unistd.h>
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <iostream>
#include <fstream> 
#include <string>
#include <sys/types.h>
#include <sys/wait.h>
#include <algorithm>
using namespace std; 

//Converts 'string' into lowercase using std::tolower()
string toLowerCase(string &str) 
{
	int length = str.length(); 
	for(int i = 0; i < length; i++)
	 {
		str[i] = tolower(str[i]);
	 }
	return str; 	
}


int main() {

	//ifstream and ofstream to read and write
	ifstream file("Text.txt");
	ofstream fileout("Text2.txt");
	//declare/initialize variables
	
	//word to search for
	string input; 
	//current word in text file
	string word; 
	//word to replace word in text file
	string rword;
	string temp;

	//Used to rename file
	char oldname[] = "Text.txt";
	char newname[] = "Text2.txt";
	//number of occurences
	int count=0; 
	//Used for while loop
	bool pass = true;
	//stores the childPID
	long childPID; 
	int result;
	
	//Repeat unless user enters !wq when promped to search
	while(pass) 
	{
		//Prompt user to enter a word to serach for
		cout << "\nEnter a word to search."<< endl;
		cin >> input;
		
		//cout<<"Enter replacement word." <<endl;
		//cin>>rword;
		

		//If the user wants to quit enter "!wq"
		if(input != "!wq")
		 {
			//Prompt user to enter a replacemnt word
			cout<<"Enter replacement word." <<endl;
			cin>>rword;
			//spawn child process. Child executes if blcok
			childPID = fork(); 
			if(childPID == 0) 
			{ 
				while(file >> word) 
					{
					word = toLowerCase(word);
					input = toLowerCase(input); 
					if(word == input){
						count++;
						word = rword;
						
					}
					word += " ";
					fileout<< word;
					
				}
				//Print out the count
				cout << "Number of occurences: " << count << endl;
				
				//deletes old file and renames new text file with the old one
				remove(oldname);
				result = rename(newname,oldname);




				//Injected bug. 
				if (count == 0) 
				{
					for(int i = 0; i < 1; i++) 
					{
						//clear buffer
						file.clear(); 
						file.seekg(0,file.beg); 
						while(file >> word) 
						{
							
						}
						cout << ".";
						i=-1;//Bug condition
					}
				}
				//If search successful end
				break;
			} 
			//else if is run by Parent block.
			else if(childPID > 0)
		        { 
				//waits for child process to finish
				wait(0); 
				
			}
			//When child and parent are both done the file buffer and count should be resetted.
			count = 0;
			//clear buffer and set the cursor to the beginning of the file
			file.clear(); 
			file.seekg(0,file.beg); 
		}
	
		else
	        { //User entered "!wq" 
			pass = false;
			break;
		}  
	}
	//Close the file and end program
	file.close();
	fileout.close();
	return 0;
}
