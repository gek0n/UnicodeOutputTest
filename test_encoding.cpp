int main() {
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
    printf("[printf][multiculture_s_s][string] %s(%lu)\n", differentCultureText.c_str(), differentCultureText.size());
    printf("[printf][english_s_s][string] %s(%lu)\n", englishText.c_str(), englishText.size());
    printf("[printf][russian_s_s][string] %s(%lu)\n", russianText.c_str(), russianText.size());
    printf("[printf][multiculture_s_s][chars] %s(%lu)\n", c_differentCultureText, strlen(c_differentCultureText));

    std::cout << "============" << std::endl;
    std::cout << "[COUT][multiculture][string] " << differentCultureText << "(" << differentCultureText.size() << ")"
              << std::endl;
    std::cout << "[COUT][english][string] " << englishText << "(" << englishText.size() << ")" << std::endl;
    std::cout << "[COUT][russian][string] " << russianText << "(" << russianText.size() << ")" << std::endl;
    std::cout << "[COUT][multiculture][chars] " << c_differentCultureText << "(" << strlen(c_differentCultureText)
              << ")" << std::endl;

    std::wcout << L"========" << std::endl;

    wprintf(
        L"[wprintf][multiculture_s_s][string] %s(%lu)\n", differentCultureText.c_str(), w_differentCultureText.size());
    wprintf(L"[wprintf][english_s_s][string] %s(%lu)\n", englishText.c_str(), w_englishText.size());
    wprintf(L"[wprintf][russian_s_s][string] %s(%lu)\n", russianText.c_str(), w_russianText.size());

    wprintf(L"[wprintf][multiculture_s_s][chars] %s(%lu)\n", c_differentCultureText, wcslen(wc_differentCultureText));

    std::wcout << L"========" << std::endl;

    std::wcout << L"[WCOUT][multiculture][string] " << w_differentCultureText << L"(" << w_differentCultureText.size()
               << L")" << std::endl;
    std::wcout << L"[WCOUT][english][string] " << w_englishText << L"(" << w_englishText.size() << L")" << std::endl;
    std::wcout << L"[WCOUT][russian][string] " << w_russianText << L"(" << w_russianText.size() << L")" << std::endl;

    std::wcout << L"[WCOUT][multiculture][chars] " << wc_differentCultureText << L"(" << wcslen(wc_differentCultureText)
               << L")" << std::endl;

  return 0;
}
