//	Copyright (C) 2008, 2012 Vaptistis Anogeianakis <nomad@cornercase.gr>
/*
 *	This file is part of Picture Renamer.
 *
 *	Picture Renamer is free software: you can redistribute it and/or modify
 *	it under the terms of the GNU General Public License as published by
 *	the Free Software Foundation, either version 3 of the License, or
 *	(at your option) any later version.
 *
 *	Picture Renamer is distributed in the hope that it will be useful,
 *	but WITHOUT ANY WARRANTY; without even the implied warranty of
 *	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *	GNU General Public License for more details.
 *
 *	You should have received a copy of the GNU General Public License
 *	along with Picture Renamer.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <stdio.h>
#include <iostream>
using std::cout;
using std::cerr;
using std::endl;

#include <stdlib.h>
#include <string.h>

#pragma warning(disable : 4996)

#define MAX_PATH_LENGTH 10240

int main()
{	
	char contentsListName[L_tmpnam];
	FILE *contentsList;

	char dirCommand[1024] = "dir /s /a:-d-s /b /o:-d /t:w>>";	// to do: change the dir command.

	unsigned int c;
	unsigned int l;
	char currentFileName[MAX_PATH_LENGTH];
	char newFileName[MAX_PATH_LENGTH];
	char *lastDot;
	char *lastBackSlash;

		// create a file with the contents of the folder and it's subfolders.
	tmpnam(contentsListName);	// create a name for a temporary file and save it in contentsListName.
	strcat(dirCommand,contentsListName);	// complement the dirCommand with the file name.
	system(dirCommand);	// send the command to the system.

		// rename the files
	if(contentsList = fopen(contentsListName,"r"))	// if you can open the contentsList file.
	{
		c = 0;
		while(fgets(currentFileName,MAX_PATH_LENGTH,contentsList))	// for each file in the list.
		{
				// prepare the new name.
			*strrchr(currentFileName,'\n') = '\0';
			lastDot = strrchr(currentFileName,'.');
			lastBackSlash = strrchr(currentFileName,'\\');

			strncpy(newFileName,currentFileName,l = (lastBackSlash - currentFileName + 1));
			sprintf(&newFileName[l],"IMG_%04u%s",++c,lastDot);

				// rename the file.
			if(rename(currentFileName,newFileName))	// if you fail to rename the file
				cerr<<"could not rename file "<<currentFileName<<"."<<endl;	// notify the user for the error.
		} // end while

			// once you have finished using the contentsList file,
		fclose(contentsList);	// close it.
	}
	else	// if you can't open the contentsList file.
		cerr<<"could not open file "<<contentsListName<<" for reading."<<endl;	// notify for error.

		// delete the contents list file when you don't need it any more.
	if(remove(contentsListName))
		cerr<<"could not delete file "<<contentsListName<<"."<<endl;	// notify on failure to delete.

	system("PAUSE");
	return 0;
} // end function main
