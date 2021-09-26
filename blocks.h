//Modify this file to change what commands output to your statusbar, and recompile using the make command.
static const Block blocks[] = {
	/*Icon*/	/*Command*/		/*Update Interval*/	/*Update Signal*/
	{"Mem:", "free -h | awk '/^Mem/ { print $3\"/\"$2 }' | sed s/i//g",	30,		0},
	{"", "date '+%b %d (%a) %I:%M:%S%p'",					5,		0},
};

//sets delimeter between status commands. NULL character ('\0') means no delimeter.
//[] -> tell the compiler to determine the size of the array which equals 4 now
static char delim[] = " | ";
static unsigned int delimLen = sizeof(delim);
