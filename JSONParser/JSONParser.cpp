/*	Created by: Nick Moyer
	Created on: 6/16/17
	This program parses a JSON file by creating a text file with only the key data elemets on each line */


#include <iostream>
#include <string>
#include <fstream>

using namespace std;
int pos;

/*	Parses each element in the JSON array by looking at the key-value pairs
	Extracts the value and returns this as a string */
string parseLine(string val) {
	// Set up local variables
	string res = "                                       ";
	char c = ' ';
	int i = 0;

	// Get the first character of the value, either " or start of value
	c = val[pos];
	if (c == '"') {
		pos++;
	}
	
	// Iterate over the string until the , or } character is reached 
	while (c != '"') {
		// Build the temp string as an array of char
		c = val[pos];
		// Check for errors
		if ((c == ']')||(c == ',')) {
			return " ";
		}
		res[i] = c;
		pos++;
		i++;
	}

	// Null terminate the array to make it a propper string and remove the extra " character
	res[i] = '\0';
	res[i - 1] = '\0';

	// Return the string
	return res;
}

int main()
{
	// Set up local variables
	ifstream rawData;
	ofstream parsedData, tempData;
	string line, val;
	char c = ' ';

	// Initilize global variable
	pos = 0;

	// Open the input and output files
	rawData.open("getData.json");
	parsedData.open("result.txt");
	if (rawData.is_open()) {
		// Add the contents of the file to a string
		getline(rawData, line);

		// Iterate over the string until the JSON array is reached
		while (c != '[') {
			c = line[pos];
			pos++;
		}

		// Iterate over the string until the end of the JSON array
		while (c != ']') {
			c = line[pos];
			pos++;
			// Check for the start of the value
			if (c == ':') {
				pos++;
				val = parseLine(line);
				// Only print useful stuff
				if (val != " ") {
					parsedData << val + "\n";
				}
			}
		}

		// Close the files
		parsedData.close();
		rawData.close();
	}

	return 0;
}