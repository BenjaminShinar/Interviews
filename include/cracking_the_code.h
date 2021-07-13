#include <string>

[[nodiscard]] bool isUniqueWithSet(const std::string & str);
[[nodiscard]] bool isUniqueNoExtraDS(const std::string & str);

[[nodiscard]] bool isPermurationMap(const std::string & str1,const std::string & str2);

[[nodiscard]] std::size_t countChar(const char* str,std::size_t n, char c);
void UrlifyFromStart(char* str,std::size_t n);
void UrlifyFromEnd(char* str,std::size_t n);

[[nodiscard]] bool isPermutationOfPalindromeMapApperences(const std::string & str);
[[nodiscard]] bool isPermutationOfPalindromeSet(const std::string & str);
[[nodiscard]] bool isPermutationOfPalindromeSetEarlyExit(const std::string & str);

[[nodiscard]] bool isOneChangeAway(const std::string & str1,const std::string & str2);
[[nodiscard]] std::string compressString(const std::string &str);
