#include <iostream>
#include <string>

#ifdef __unix__
#include <sys/io.h>
#endif
#ifdef _WIN32
#include <io.h>
#endif
extern "C" {
#include <fcntl.h>
#include <stdio.h>

#ifdef _WIN32
#include <Windows.h>
#ifndef __MINGW32__
#include <VersionHelpers.h>
#endif
#endif
}
#include <codecvt>
#include <cstdio>
#include <cstring>
#include <fstream>
#include <locale>

#ifdef _WIN64  // Windows 10
constexpr int16_t BUFFER_SIZE = 1024;
void enable_stdout_buffering(void) {
  setvbuf(stdout, nullptr, _IOFBF, BUFFER_SIZE);
}
#endif

constexpr char cp_utf16le[] = ".1200";  // UTF-16 little-endian locale.
constexpr char cp_utf8[] = ".65001";    // UTF-8 locale.
void setup_locale(void) {
  setlocale(LC_ALL, cp_utf16le);
}

#ifdef _WIN32
#define _O_WTEXT 0x10000    // file mode is UTF16 (translated)
#define _O_U16TEXT 0x20000  // file mode is UTF16 no BOM (translated)
#define _O_U8TEXT 0x40000   // file mode is UTF8  no BOM (translated)
void set_stdout_encoding(void) {
  _setmode(_fileno(stdout), 0x20000);
}
#endif

#ifdef _WIN32
static unsigned int oldCodePage{0};
void set_console_utf8_codepage(void) {
  oldCodePage = GetConsoleOutputCP();
  if (!SetConsoleOutputCP(CP_UTF8)) {
    throw std::runtime_error("Can't set utf-8 codepage for console output");
  }
}

void restore_console_output_codepage(void) {
  SetConsoleOutputCP(oldCodePage);
}
#endif
constexpr const bool IS_WIDE = WIDE;
int main() {
  // 1. preparing the application
  if constexpr (IS_WIDE) {
#ifdef _WIN32
    set_stdout_encoding();
#endif
#ifdef __unix__
    setlocale(LC_ALL, "en_US.UTF-8");
#endif
  }

#ifdef _WIN32
  set_console_utf8_codepage();
#endif

#ifdef _WIN64&& __MINGW32__  // Windows 10 or MinGW64
  if (!IsWindows10OrGreater()) {
    enable_stdout_buffering();
  }
#endif

  // 2. define data
  std::string differentCultureText = "Greek: αβγδ; German: Übergrößenträger; Russian: Михаил; Japan: 存在する";
  std::string englishText = "Some english text";
  std::string russianText = "Простой русский текст";

  std::wstring w_differentCultureText =
      L"Greek: αβγδ; German: Übergrößenträger; Russian: Михаил; Japan: "
      L"存在する";
  std::wstring w_englishText = L"Some english text";
  std::wstring w_russianText = L"Простой русский текст";

  const char* c_differentCultureText = "Greek: αβγδ; German: Übergrößenträger; Russian: Михаил; Japan: 存在する";
  const wchar_t* wc_differentCultureText =
      L"Greek: αβγδ; German: Übergrößenträger; Russian: Михаил; Japan: "
      L"存在する";

  // 3. test output
  if constexpr (!IS_WIDE) {
    std::cout << "============" << std::endl;
    printf("[printf][multiculture_s_s][string] %s(%lu)\n", differentCultureText.c_str(), differentCultureText.size());
    printf("[printf][english_s_s][string] %s(%lu)\n", englishText.c_str(), englishText.size());
    printf("[printf][russian_s_s][string] %s(%lu)\n", russianText.c_str(), russianText.size());
    printf("[printf][multiculture_s_s][chars] %s(%lu)\n", c_differentCultureText, strlen(c_differentCultureText));

    std::cout << "============" << std::endl;
    printf("[printf][multiculture_ls_s][string] %ls(%lu)\n", differentCultureText.c_str(), differentCultureText.size());
    printf("[printf][english_ls_s][string] %ls(%lu)\n", englishText.c_str(), englishText.size());
    printf("[printf][russian_ls_s][string] %ls(%lu)\n", russianText.c_str(), russianText.size());
    printf("[printf][multiculture_ls_s][chars] %ls(%lu)\n", c_differentCultureText, strlen(c_differentCultureText));

    std::cout << "============" << std::endl;
    printf(
        "[printf][multiculture_s_ws][string] %s(%lu)\n", w_differentCultureText.c_str(), differentCultureText.size());
    printf("[printf][english_s_ws][string] %s(%lu)\n", w_englishText.c_str(), englishText.size());
    printf("[printf][russian_s_ws][string] %s(%lu)\n", w_russianText.c_str(), russianText.size());
    printf("[printf][multiculture_s_ws][chars] %s(%lu)\n", wc_differentCultureText, strlen(c_differentCultureText));

    std::cout << "============" << std::endl;
    printf(
        "[printf][multiculture_ls_ws][string] %ls(%lu)\n", w_differentCultureText.c_str(), differentCultureText.size());
    printf("[printf][english_ls_ws][string] %ls(%lu)\n", w_englishText.c_str(), englishText.size());
    printf("[printf][russian_ls_ws][string] %ls(%lu)\n", w_russianText.c_str(), russianText.size());
    printf("[printf][multiculture_ls_ws][chars] %ls(%lu)\n", wc_differentCultureText, strlen(c_differentCultureText));

    std::cout << "============" << std::endl;
    std::printf(
        "[std::printf][multiculture_s_s][string] %s(%lu)\n", differentCultureText.c_str(), differentCultureText.size());
    std::printf("[std::printf][english_s_s][string] %s(%lu)\n", englishText.c_str(), englishText.size());
    std::printf("[std::printf][russian_s_s][string] %s(%lu)\n", russianText.c_str(), russianText.size());
    std::printf(
        "[std::printf][multiculture_s_s][chars] %s(%lu)\n", c_differentCultureText, strlen(c_differentCultureText));

    std::cout << "============" << std::endl;
    std::printf("[std::printf][multiculture_ls_s][string] %ls(%lu)\n",
                differentCultureText.c_str(),
                differentCultureText.size());
    std::printf("[std::printf][english_ls_s][string] %ls(%lu)\n", englishText.c_str(), englishText.size());
    std::printf("[std::printf][russian_ls_s][string] %ls(%lu)\n", russianText.c_str(), russianText.size());
    std::printf(
        "[std::printf][multiculture_ls_s][chars] %ls(%lu)\n", c_differentCultureText, strlen(c_differentCultureText));

    std::cout << "============" << std::endl;
    std::printf("[std::printf][multiculture_s_ws][string] %s(%lu)\n",
                w_differentCultureText.c_str(),
                differentCultureText.size());
    std::printf("[std::printf][english_s_ws][string] %s(%lu)\n", w_englishText.c_str(), englishText.size());
    std::printf("[std::printf][russian_s_ws][string] %s(%lu)\n", w_russianText.c_str(), russianText.size());
    std::printf(
        "[std::printf][multiculture_s_ws][chars] %s(%lu)\n", wc_differentCultureText, strlen(c_differentCultureText));

    std::cout << "============" << std::endl;
    std::printf("[std::printf][multiculture_ls_ws][string] %ls(%lu)\n",
                w_differentCultureText.c_str(),
                differentCultureText.size());
    std::printf("[std::printf][english_ls_ws][string] %ls(%lu)\n", w_englishText.c_str(), englishText.size());
    std::printf("[std::printf][russian_ls_ws][string] %ls(%lu)\n", w_russianText.c_str(), russianText.size());
    std::printf(
        "[std::printf][multiculture_ls_ws][chars] %ls(%lu)\n", wc_differentCultureText, strlen(c_differentCultureText));

    std::cout << "============" << std::endl;
    std::cout << "[COUT][multiculture][string] " << differentCultureText << "(" << differentCultureText.size() << ")"
              << std::endl;
    std::cout << "[COUT][english][string] " << englishText << "(" << englishText.size() << ")" << std::endl;
    std::cout << "[COUT][russian][string] " << russianText << "(" << russianText.size() << ")" << std::endl;
    std::cout << "[COUT][multiculture][chars] " << c_differentCultureText << "(" << strlen(c_differentCultureText)
              << ")" << std::endl;

    std::cout << "============" << std::endl;
  } else {
    std::wcout << L"========" << std::endl;

    wprintf(
        L"[wprintf][multiculture_s_s][string] %s(%lu)\n", differentCultureText.c_str(), w_differentCultureText.size());
    wprintf(L"[wprintf][english_s_s][string] %s(%lu)\n", englishText.c_str(), w_englishText.size());
    wprintf(L"[wprintf][russian_s_s][string] %s(%lu)\n", russianText.c_str(), w_russianText.size());

    wprintf(L"[wprintf][multiculture_s_s][chars] %s(%lu)\n", c_differentCultureText, wcslen(wc_differentCultureText));

    std::wcout << L"============" << std::endl;

    wprintf(L"[wprintf][multiculture_ls_s][string] %ls(%lu)\n",
            differentCultureText.c_str(),
            w_differentCultureText.size());
    wprintf(L"[wprintf][english_ls_s][string] %ls(%lu)\n", englishText.c_str(), w_englishText.size());
    wprintf(L"[wprintf][russian_ls_s][string] %ls(%lu)\n", russianText.c_str(), w_russianText.size());

    wprintf(L"[wprintf][multiculture_ls_s][chars] %ls(%lu)\n", c_differentCultureText, wcslen(wc_differentCultureText));

    std::wcout << L"========" << std::endl;
    wprintf(L"[wprintf][multiculture_s_ws][string] %s(%lu)\n",
            w_differentCultureText.c_str(),
            w_differentCultureText.size());
    wprintf(L"[wprintf][english_s_ws][string] %s(%lu)\n", w_englishText.c_str(), w_englishText.size());
    wprintf(L"[wprintf][russian_s_ws][string] %s(%lu)\n", w_russianText.c_str(), w_russianText.size());

    wprintf(L"[wprintf][multiculture_s_ws][chars] %s(%lu)\n", wc_differentCultureText, wcslen(wc_differentCultureText));

    std::wcout << L"============" << std::endl;

    std::wcout << L"========" << std::endl;
    wprintf(L"[wprintf][multiculture_ls_ws][string] %S(%lu)\n",
            w_differentCultureText.c_str(),
            w_differentCultureText.size());
    wprintf(L"[wprintf][english_ls_ws][string] %ls(%lu)\n", w_englishText.c_str(), w_englishText.size());
    wprintf(L"[wprintf][russian_ls_ws][string] %ls(%lu)\n", w_russianText.c_str(), w_russianText.size());

    std::wcout << L"========" << std::endl;
    std::wprintf(L"[std::wprintf][multiculture_s_s][string] %s(%lu)\n",
                 differentCultureText.c_str(),
                 w_differentCultureText.size());
    std::wprintf(L"[std::wprintf][english_s_s][string] %s(%lu)\n", englishText.c_str(), w_englishText.size());
    std::wprintf(L"[std::wprintf][russian_s_s][string] %s(%lu)\n", russianText.c_str(), w_russianText.size());

    std::wprintf(
        L"[std::wprintf][multiculture_s_s][chars] %s(%lu)\n", c_differentCultureText, wcslen(wc_differentCultureText));

    std::wcout << L"============" << std::endl;

    std::wprintf(L"[std::wprintf][multiculture_ls_s][string] %ls(%lu)\n",
                 differentCultureText.c_str(),
                 w_differentCultureText.size());
    std::wprintf(L"[std::wprintf][english_ls_s][string] %ls(%lu)\n", englishText.c_str(), w_englishText.size());
    std::wprintf(L"[std::wprintf][russian_ls_s][string] %ls(%lu)\n", russianText.c_str(), w_russianText.size());

    std::wprintf(L"[std::wprintf][multiculture_ls_s][chars] %ls(%lu)\n",
                 c_differentCultureText,
                 wcslen(wc_differentCultureText));

    std::wcout << L"========" << std::endl;
    std::wprintf(L"[std::wprintf][multiculture_s_ws][string] %s(%lu)\n",
                 w_differentCultureText.c_str(),
                 w_differentCultureText.size());
    std::wprintf(L"[std::wprintf][english_s_ws][string] %s(%lu)\n", w_englishText.c_str(), w_englishText.size());
    std::wprintf(L"[std::wprintf][russian_s_ws][string] %s(%lu)\n", w_russianText.c_str(), w_russianText.size());

    std::wprintf(L"[std::wprintf][multiculture_s_ws][chars] %s(%lu)\n",
                 wc_differentCultureText,
                 wcslen(wc_differentCultureText));

    std::wcout << L"============" << std::endl;

    std::wcout << L"========" << std::endl;
    std::wprintf(L"[std::wprintf][multiculture_ls_ws][string] %ls(%lu)\n",
                 w_differentCultureText.c_str(),
                 w_differentCultureText.size());
    std::wprintf(L"[std::wprintf][english_ls_ws][string] %ls(%lu)\n", w_englishText.c_str(), w_englishText.size());
    std::wprintf(L"[std::wprintf][russian_ls_ws][string] %ls(%lu)\n", w_russianText.c_str(), w_russianText.size());

    std::wcout << L"========" << std::endl;
    std::wcout << L"========" << std::endl;

    std::wcout << L"[WCOUT][multiculture][string] " << w_differentCultureText << L"(" << w_differentCultureText.size()
               << L")" << std::endl;
    std::wcout << L"[WCOUT][english][string] " << w_englishText << L"(" << w_englishText.size() << L")" << std::endl;
    std::wcout << L"[WCOUT][russian][string] " << w_russianText << L"(" << w_russianText.size() << L")" << std::endl;

    std::wcout << L"[WCOUT][multiculture][chars] " << wc_differentCultureText << L"(" << wcslen(wc_differentCultureText)
               << L")" << std::endl;

    std::wcout << "============" << std::endl;
  }

// 4. restore settings
#ifdef _WIN32
  restore_console_output_codepage();
#endif
  return 0;
}
