#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
#include <locale.h>

int wmain(int argc, wchar_t *argv[]) {

	if (argc > 1) {

		// 密码输入
	 	if (0 == wcscmp(argv[1], L"pass")) {
	 		int input;
	 		int ptr = 0;
	 		char text[255] = "";
			while (++ptr < 255) {
				input = _getch();
				if (input == 13 || input == 10) {
					break;
				}
				sprintf(text, "%s%c", text, input);
			}
			// php exec() 会自动去除尾部的空白, 但密码应该支持空白符,
			// 这里追加一个字符，便于 php 端处理
			printf("%sz", text);
			return 0;
        }


        // 按键监听
        if (0 == wcscmp(argv[1], L"key")) {
            setlocale(LC_ALL, "");
            wchar_t input;
            while (1 == 1) {
                input = _getwch();
                // https://docs.microsoft.com/en-us/cpp/c-runtime-library/reference/getch-getwch?view=msvc-160#remarks
                if (0 == input || 0xE0 == input) {
                    printf("%c", input);
                    printf("%c", _getwch());
                } else {
                    wprintf(L"%c", input);
                }
                fflush(stdout);
                if (3 == input) {
                    break;
                }
            }
            return 0;
        }
	}

	// 获取窗口尺寸
    CONSOLE_SCREEN_BUFFER_INFO info;
	HANDLE tmpConsole = CreateConsoleScreenBuffer(GENERIC_READ, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);

	// can't use `GetStdHandle(STD_OUTPUT_HANDLE)` as it doesn't work when output is redirected
	GetConsoleScreenBufferInfo(tmpConsole, &info);
	CloseHandle(tmpConsole);

	int columns = info.dwMaximumWindowSize.X;
	int rows = info.dwMaximumWindowSize.Y;

	printf("%d\n%d", columns, rows);
	return 0;
}