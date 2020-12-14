//Giovanni J Moscato 
//11/23/2019
//Program 8
//ZID:Z1820207

//Includes 
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <cstring>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <string>


//Namespace
using namespace std;

//Main routine
int main(int argc, char* argv[])
{
	//Note: Not actually using original argument values for the program 

		//Repeat the child process
	while (true)
	{

		string command, argument1, argument2, argument3, argument4;
		char str[250];

		//The interpreter should repeatedly print a prompt and wait for the user to enter a command with arguments:
		cout << "Enter command: ";
		cin.getline(str, 250);
		//Special exit feature 
		if (!strcmp(str, "exit"))
		{
			exit(EXIT_SUCCESS);
		}




		// Character array to hold our new strings 
		char * arr[5];
		// Position of argument entered
		int argentered = 0;

		//Create deliminator we want to check for. In this case we want to check for a space.
		const char delim[2] = " ";
		// Returns first token after a space
		char* c = strtok(str, delim);



		// Keep printing tokens while one of the 
		// delimiters present in str[]. 
		while (c != NULL)
		{
			// Each section has memory allocated to it with malloc. It's first casted to type char* and the string length is +1 to compensate for the NULL character
			// at the end of strings!
			arr[argentered] = static_cast<char*> (malloc(strlen(c) + 1));
			// Copy the string into character array
			arr[argentered] = c;

			// If we are at position 0 then the user should have entered a command as the first argument
			if (argentered == 0)
			{
				//Command should be set to the string "c" that we broke apart and is represented by a pointer at position 0 in our section array
				command = arr[argentered];
			}
			//Set the rest of the arguments equal to the array argument
			else if (argentered == 1)
			{
				argument1 = arr[argentered];
			}

			else if (argentered == 2)
			{
				argument2 = arr[argentered];
			}

			else if (argentered == 3)
			{
				argument3 = arr[argentered];
			}

			else if (argentered == 4)
			{
				argument4 = arr[argentered];
			}
			else
			{
				cout << "error: user can specify up to 4 arguments or options to the command " << endl;
				exit(EXIT_FAILURE);
			}

			//Increment if the user entered another argument 
			argentered++;

			// Splits str[] according to given delimiters.
			// and returns next token. It needs to be called
			// in a loop to get all tokens. It returns NULL
			// when there are no more tokens.
			c = strtok(NULL, delim);
		}



		//Algorithm: call fork to create a child process to perform each command

		//Fork variables 
		int pid = fork();
		int rs, status;


		//Check for fork error
		if (pid == -1)
		{
			perror("fork");
			exit(EXIT_FAILURE);
		}

		//While we are in the child process
		while (pid == 0)
		{
			//We have to check of none, or up to 4 arguments are entered.
			if (argentered == 1)
			{
				//Set the return status equal to execlp where we only entered a command so no arguments are needed. 
				//Command.c_str() is the name of the file, command.c_str() is the "argument" because there is no argumet
				//Algorithm: call exec in the child process to make the child become the program that is to be executed
				rs = execlp(command.c_str(), command.c_str(), (char*)NULL);
				if (rs == -1)
				{
					//If there was an error with the command exit
					perror(command.c_str());
					exit(EXIT_FAILURE);
				}
			}

			if (argentered == 2)
			{
				rs = execlp(command.c_str(), command.c_str(), argument1.c_str(), (char*)NULL);
				if (rs == -1)
				{
					perror(command.c_str());
					exit(EXIT_FAILURE);
				}
			}

			if (argentered == 3)
			{
				rs = execlp(command.c_str(), command.c_str(), argument1.c_str(), argument2.c_str(), (char*)NULL);
				if (rs == -1)
				{
					perror(command.c_str());
					exit(EXIT_FAILURE);
				}
			}

			if (argentered == 4)
			{
				rs = execlp(command.c_str(), command.c_str(), argument1.c_str(), argument2.c_str(), argument3.c_str(), (char*)NULL);
				if (rs == -1)
				{
					perror(command.c_str());
					exit(EXIT_FAILURE);
				}
			}

			if (argentered == 5)
			{
				rs = execlp(command.c_str(), command.c_str(), argument1.c_str(), argument2.c_str(), argument3.c_str(), argument4.c_str(), (char*)NULL);
				if (rs == -1)
				{
					perror(command.c_str());
					exit(EXIT_FAILURE);
				}
			}
		}
		//Algorithm: call wait in the parent process so that the interpreter does not print the next prompt until the command is finished.
		wait(&status);
	}
	return 0;
}
