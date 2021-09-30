//Modify this file to change what commands output to your statusbar, and recompile using the make command.
static const Block blocks[] = {
	/*Icon*/	/*Command*/		/*Update Interval*/	/*Update Signal*/
	{"", "gweath",	21600,		0},
	{"", "gcpu",	5,		0},
	{"", "gsens",	5,		0},
	{"", "gmem",	5,		0},
	{"", "gwifi",	1,		0},
	{"", "gbr",		0,		0},
	{"", "gsound",	0,		0},
	{"", "gbat",	5,		0},
	{"", "gdate",	60,		0},
};

//sets delimeter between status commands. NULL character ('\0') means no delimeter.
//[] -> tell the compiler to determine the size of the array which equals 4 now
static char delim[] = " | ";
static unsigned int delimLen = sizeof(delim);
