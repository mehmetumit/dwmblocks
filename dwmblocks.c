#include "dwmblocks.h"

//opens process *cmd and stores output in *output
void getcmd(const Block *block, char *output) {
	if (block->signal)
		*output++ = block->signal;
	strcpy(output, block->icon);
	FILE *cmdBlock = popen(block->command, "r");
	if (!cmdBlock)
		return;
	int charOffset = strlen(block->icon);
	//Merge icon and command output
	fgets(output+charOffset , CMDLENGTH-charOffset -delimLen, cmdBlock);
	charOffset = strlen(output);
	if (charOffset == 0) {
		//return if block and command output are both empty
	}else {
		//only chop off newline if one is present at the end
		charOffset = output[charOffset-1] == '\n' ? charOffset-1 : charOffset;
		if (delim[0] != '\0') {
		//add delim to output
		strncpy(output+charOffset, delim, delimLen); 
		} else//no delimeter
			output[charOffset++] = '\0';
	}
	pclose(cmdBlock);
	return;
}

void getcmds(int time) {
	const Block* current;
	for (unsigned int i = 0; i < LENGTH(blocks); i++) {
		current = blocks + i;
		if ((current->interval != 0 && time % current->interval == 0) || time == -1)
			getcmd(current,statusbar[i]);
	}
}

void getsigcmds(unsigned int signal) {
	const Block *current;
	for (unsigned int i = 0; i < LENGTH(blocks); i++) {
		current = blocks + i;
		if (current->signal == signal)
			getcmd(current,statusbar[i]);
	}
}

void setupsignals() {
	struct sigaction sa = { .sa_sigaction = sighandler, .sa_flags = SA_SIGINFO };
#ifndef __OpenBSD__
	    /* initialize all real time signals with dummy handler */
    for (int i = SIGRTMIN; i <= SIGRTMAX; i++) {
         signal(i, dummysighandler);
		sigaddset(&sa.sa_mask, i);
	}
#endif

	for (unsigned int i = 0; i < LENGTH(blocks); i++) {
		if (blocks[i].signal > 0)
			sigaction(SIGMINUS+blocks[i].signal, &sa, NULL);
	}
}

int getstatus(char *str, char *last) {
	strcpy(last, str);
	str[0] = '\0';
	for (unsigned int i = 0; i < LENGTH(blocks); i++)
		strcat(str, statusbar[i]);
	str[strlen(str)-strlen(delim)] = '\0';
	return strcmp(str, last);//0 if they are the same
}

#ifndef NO_X
void setroot() {
	if (!getstatus(statusstr[0], statusstr[1]))//Only set root if text has changed.
		return;
	XStoreName(dpy, root, statusstr[0]);
	XFlush(dpy);
}

int setupX() {
	dpy = XOpenDisplay(NULL);
	if (!dpy) {
		fprintf(stderr, "dwmblocks: Failed to open display\n");
		return 0;
	}
	screen = DefaultScreen(dpy);
	root = RootWindow(dpy, screen);
	return 1;
}
#endif

void pstdout() {
	if (!getstatus(statusstr[0], statusstr[1]))//Only write out if text has changed.
		return;
	printf("%s\n",statusstr[0]);
	fflush(stdout);
}

void statusloop() {
	setupsignals();
	int time = 0;//69 year uptime not possible to overflow 
	getcmds(-1);
	while (1) {
		getcmds(time++);
		writestatus();//update status bar
		if (!statusContinue)
			break;
		sleep(1.0);//wait 1 sec and control again
	}
}

void sighandler(int signum, siginfo_t *si, void *ucontext){
	if (si->si_value.sival_int) {
		pid_t parent = getpid();
		if (fork() == 0) {
#ifndef NO_X
			if (dpy)
				close(ConnectionNumber(dpy));
#endif
			int i;
			for (i = 0; i < LENGTH(blocks) && blocks[i].signal != signum-SIGRTMIN; i++);

			char shcmd[1024];
			sprintf(shcmd, "%s; kill -%d %d", blocks[i].command, SIGRTMIN+blocks[i].signal, parent);
			char *cmd[] = { "/bin/sh", "-c", shcmd, NULL };
			char button[2] = { '0' + si->si_value.sival_int, '\0' };
			setenv("BUTTON", button, 1);
			setsid();
			execvp(cmd[0], cmd);
			perror(cmd[0]);
			exit(EXIT_SUCCESS);
		}
	} else {
		getsigcmds(signum-SIGPLUS);
		writestatus();
	}
}

void termhandler() {
	statusContinue = 0;
}

void chldhandler() {
	while (0 < waitpid(-1, NULL, WNOHANG));
}

int main(int argc, char** argv) {
	for (int i = 0; i < argc; i++) {//Handle command line arguments
		if (!strcmp("-d",argv[i]))
			strncpy(delim, argv[++i], delimLen);
		else if (!strcmp("-p",argv[i]))
			writestatus = pstdout;
	}
#ifndef NO_X
	if (!setupX())//Failed to open display
		return 1;
#endif
	delim[delimLen-1] = '\0';
	signal(SIGTERM, termhandler);
	signal(SIGINT, termhandler);
	signal(SIGCHLD, chldhandler);
	statusloop();
#ifndef NO_X
	XCloseDisplay(dpy);
#endif
	return 0;
}
