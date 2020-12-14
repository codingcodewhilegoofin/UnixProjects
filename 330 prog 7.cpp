
// Giovanni Moscato z1820207
// Assignmnet 7: IO managment

// Algorithm:
// Check to see if the output file exists. If it doesn't, create it. Life is simpler if a newly created file is closed at the end of this step.
// 	Check the permissions of the output file. If any permissions exist, print a useful error message and exit.
		//	Change the permissions on the file to allow writing by the user.
			// 	Open the file for output. If the "-c" command line option is present, make sure the file is truncated.
				//	 Write the message from the command line to the output file. Write an additional newline character so that the output has a nicer format.			
//Clear the permissions and close the file. (These two operations can be performed in either order, but the implementation is slightly different.)

//Library includes:
#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <cstring>

//System call includes:
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>


//Main part of the program: 
using namespace std;

int main(int argc, char* argv[])
{
	//First check if the correct number of arguments have been given. If not issue the correct error message
	if (argc < 2)
	{
		cerr << "Usage:seclog [-c] out_file message_string where the message_string is appended to file out_file. The -c option clears the file before the message is appended \n";
		cout << endl;
		exit(EXIT_FAILURE);
	}
	else
	{
		//Global variables
		char* instr = argv[1];
		int rs;
		struct stat buffer;

		//-c OPTION!!!!!!
		if (strcmp(instr, "-c") == 0)
		{
			//check if argument 2 file exists
			// call stat system call
			rs = stat(argv[2], &buffer);
			if (rs == -1)
			{
				perror(argv[2]);
				exit(EXIT_FAILURE);
			}

			if (rs == 0)
			{
				//Part 2 of the algorithm:
				// Check the permissions of the output file. If any permissions exist, print a useful error message and exit.
				// If the file has any permissions at all, the file should be rejected as insecure, and the program should exit.
				if ((buffer.st_mode & 777) != 0)
				{
					cerr << "Usage: output file is not secure.  Ignoring. \n";
					cout << endl;
					exit(EXIT_FAILURE);
				}
				else
				{
					//Part 3 of the algorithm:
					//Change the permissions on the file to allow writing by the user.
					rs = chmod(argv[2], 0200);
					if (rs == -1)
					{
						perror(argv[2]);
						exit(EXIT_FAILURE);
					}

					int fd = open(argv[2], O_WRONLY | O_TRUNC | O_CREAT, 0200);
					rs = write(fd, argv[3], strlen(argv[3]));
					if (rs == -1)
					{
						perror(argv[1]);
						exit(EXIT_FAILURE);
					}
					cout << endl;

					//Change file permissions back to none
					rs = chmod(argv[2], 0000);
					if (rs == -1)
					{
						perror(argv[2]);
						exit(EXIT_FAILURE);
					}
				}
			}
		}

		//NOT USING -c OPTION***************************************
		// call stat system call
		rs = stat(argv[1], &buffer);
		if (rs == -1)
		{
			perror(argv[1]);
			exit(EXIT_FAILURE);
		}
		//check if argument 1 file exists
		 /* Handle regular file */
		// Part one of the algortithm:
		// Check to see if the output file exists. If it doesn't, create it. Life is simpler if a newly created file is closed at the end of this step.
		if (rs == 0)
		{
			//FILE exists!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
			//Part 2 of the algorithm:
			// Check the permissions of the output file. If any permissions exist, print a useful error message and exit.
			// If the file has any permissions at all, the file should be rejected as insecure, and the program should exit.
			if ((buffer.st_mode & 777) != 0)
			{
				cerr << "Usage: output file is not secure.  Ignoring. \n";
				cout << endl;
				exit(EXIT_FAILURE);
			}
			else
			{
				//Part 3 of the algorithm:
				//Change the permissions on the file to allow writing by the user.
				rs = chmod(argv[1], 0200);
				if (rs == -1)
				{
					perror(argv[1]);
					exit(EXIT_FAILURE);
				}

				int fd = open(argv[1], O_WRONLY | O_APPEND | O_CREAT, 0200);
				rs = write(fd, argv[2], strlen(argv[2]));
				if (rs == -1)
				{
					perror(argv[1]);
					exit(EXIT_FAILURE);
				}
				cout << endl;

				rs = chmod(argv[1], 0000);
				if (rs == -1)
				{
					perror(argv[1]);
					exit(EXIT_FAILURE);
				}
			}
		}
		// FILE DOES NOT EXIST
		// Part one of the algortithm:
		// Check to see if the output file exists. If it doesn't, create it. Life is simpler if a newly created file is closed at the end of this step.
		else
		{
			open(argv[1], O_WRONLY | O_CREAT, 0200);
			rs = close(1);
			if (rs == -1)
			{
				perror(argv[1]);
				exit(EXIT_FAILURE);
			}

		}
	}
}

