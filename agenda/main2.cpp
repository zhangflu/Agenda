#include "AgendaUI.hpp"
#include <csignal>
#include <cstdlib>
using std::cout;
int keepRunning = 1;
void sig_handler(int sig)
{
	if (sig == SIGINT)
	{
		keepRunning = 0;
		cout << "\nTerminated by Ctrl + C signal!\n";
		cout << "The data has been saved!\n";
	}
}
AgendaUI core;
int main(){
	signal(SIGINT,sig_handler);
	core.OperationLoop();
	system("rm tmeetings.csv");
	system("rm tusers.csv");
	system("pause");
	return 0;
}