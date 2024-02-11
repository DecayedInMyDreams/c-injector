#include "main.h"


int main() {
	std::string title = "Tear Injector [" + std::string(config::pname) + "]";
	SetConsoleTitleA(title.c_str());

	config::pid = getpid(config::pname);
	Sleep(1000);
	if (!config::pid) {
		cout << "\n\n\n";
		cout << "			[!] ";
		cout << "Failed To Get Process ID.. Make Sure Is " << config::pname << " Open." << endl;
		Sleep(5000);
		return 0;
	}
	else {
		cout << "\n\n\n";
		cout << "			[+] ";
		cout << "Got process id: ";
		cout << config::pid << endl;


		HANDLE hp = OpenProcess(PROCESS_ALL_ACCESS, 0, config::pid);
		if (!hp && hp == INVALID_HANDLE_VALUE)
		{
			cout << "			[!] ";
			cout << "Failed To Open Process" << endl;
		}
		if (hp && hp != INVALID_HANDLE_VALUE) {
			cout << "			[+] ";
			cout << "Opened Process" << endl;
			Sleep(1000);
			void* loc = VirtualAllocEx(hp, 0, MAX_PATH, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);

			if (loc)
			{
				WriteProcessMemory(hp, loc, config::dllpath, strlen(config::dllpath) + 1, 0);
				cout << "			[+] ";
				cout << "Wrote Process Memory" << endl;
			}
			else {
				cout << "			[!] ";
				cout << "Failed To Write Process Memory" << endl;
			}

			Sleep(1000);
			HANDLE ht = CreateRemoteThread(hp, 0, 0, (LPTHREAD_START_ROUTINE)LoadLibraryA, loc, 0, 0);

			if (ht)
			{
				CloseHandle(ht);
				cout << "			[+] ";
				cout << "Created Remote Thread" << endl;
			}
			else {
				cout << "			[!] ";
				cout << "Failed To Create Remote Thread" << endl;
			}

			if (hp)
			{
				CloseHandle(hp);
				cout << "			[+] ";
				cout << "Injected" << endl;
			}
			Sleep(5000);
			return 0;
		}
	}


	Sleep(1000);
}