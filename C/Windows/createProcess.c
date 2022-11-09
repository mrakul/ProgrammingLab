#include <windows.h>
#include <stdio.h>
#include <tchar.h>

void _tmain(int argc, TCHAR *argv[])
{
    STARTUPINFO startupInfo;
    PROCESS_INFORMATION processInfo;

    ZeroMemory(&startupInfo, sizeof(startupInfo));
    startupInfo.cb = sizeof(startupInfo);
    ZeroMemory(&processInfo, sizeof(processInfo));

    // Force to pass argument to
    if (argc != 2){
        printf("Usage: %s [cmdline]\n", argv[0]);
        return;
    }

    // Start the child process.
    if (!CreateProcess(NULL,   // No module name (use command line)
        argv[1],        // Command line
        NULL,           // Process handle not inheritable
        NULL,           // Thread handle not inheritable
        FALSE,          // Set handle inheritance to FALSE
        0,              // No creation flags
        NULL,           // Use parent's environment block
        NULL,           // Use parent's starting directory
        &startupInfo,            // Pointer to STARTUPINFO structure
        &processInfo)            // Pointer to PROCESS_INFORMATION structure
        ){
            printf("CreateProcess failed (%lu).\n", GetLastError());
            return;
    }

    // Wait until child process exits
    WaitForSingleObject(processInfo.hProcess, INFINITE);

    // Close process and thread handles.
    CloseHandle(processInfo.hProcess);
    CloseHandle(processInfo.hThread);
}