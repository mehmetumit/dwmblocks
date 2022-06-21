//Modify this file to change what commands output to your statusbar, and recompile using the make command.
static const Block blocks[] = {
	/*Icon*/	/*Command*/		/*Update Interval*/	/*Update Signal*/
	//{"", "gweath",	10800,	1},
	{"", "grecord",	0,		1},
	{"", "gcpu",	10,		2},
	{"", "gmem",	10,		3},
	{"", "gnets",	1,		4},
	{"", "gsigstr",	10,		5},
	{"", "gbr",		0,		6},
	{"", "gsound",	0,		7},
	{"", "gbat",	10,		8},
	{"", "gdate",	60,		9},
};

//sets delimeter between status commands. NULL character ('\0') means no delimeter.
static char delim[] = " | ";
static unsigned int delimLen = sizeof(delim);
