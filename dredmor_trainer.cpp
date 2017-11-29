#include "dredmor_trainer.hpp"

using namespace std;

void exit_with_error(char *err, HANDLE *hProcess)
{
	cout << "[!] " << err << endl;
	CloseHandle(hProcess);
	cin.get();
	exit(1);
}

#pragma comment(lib, "user32.lib")
int main()
{
	HWND dWin = FindWindow(0, _T(winStr));
	HANDLE hProcess;
	DWORD pid;
    int canRead;
    int canWrite;

	cout << ">> Searching for " << winStr << " window\n";
	if (!dWin)
		exit_with_error(ERROR_NOT_OPEN, &hProcess);

	// save pid
	GetWindowThreadProcessId(dWin, &pid);

	// try to open the process
	hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pid);
	if (!hProcess)
		exit_with_error(ERROR_PROCESS, &hProcess);

	DWORD BaseAddr;
	DWORD gold;
	unsigned int addGold = 900000;

	// read base addr into BaseAddr
	canRead = ReadProcessMemory(hProcess, (void*)BASEADDR, &BaseAddr, 4, NULL);
	if (!canRead)
		exit_with_error(ERROR_MEMORY_READ, &hProcess);

	// read gold offset
	canRead = ReadProcessMemory(hProcess, (void*)(BaseAddr+OFFSET_GOLD), &gold, sizeof(gold), NULL);
	if (!canRead)
		exit_with_error(ERROR_MEMORY_READ, &hProcess);

	cout << "You have " << gold << " gold\n";
	if (gold < 900000) {
		cout << "Adding 900,000 gold\n";
		canWrite = WriteProcessMemory(hProcess, (void*)(BaseAddr+OFFSET_GOLD), &addGold, sizeof(addGold), NULL);
	}
	
	CloseHandle(hProcess);
	return 0;
}