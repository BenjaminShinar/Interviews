#include <string>
#include <forward_list>

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

[[nodiscard]] bool isRotationOneSubstring(const std::string & str1,const std::string & str2);

[[nodiscard]] bool isListUnique(const std::forward_list<int> & list);
void removeDuplicatesFromListWithSet(std::forward_list<int> & list);
void removeDuplicatesFromListNoExtraDS(std::forward_list<int> &list);
[[nodiscard]] int kToLastElementRecursive(const std::forward_list<int> & list, int kElement);
[[nodiscard]] int kToLastElementIterative(const std::forward_list<int> & list, int kElement);
void deleteNodeFromMiddleOfList(std::forward_list<int> & list,std::forward_list<int>::iterator & node);
void partitionListAroundValue(std::forward_list<int> & list,int x);
[[nodiscard]] std::forward_list<int> sumListsValues(const std::forward_list<int> & list1,const std::forward_list<int> & list2);
[[nodiscard]] bool isListPalindrome(const std::forward_list<int> & list);
[[nodiscard]] std::forward_list<int>::const_iterator areListsIntersecting(const std::forward_list<int> & list1,const std::forward_list<int> & list2);
[[nodiscard]] std::forward_list<int>::const_iterator isListLooping(const std::forward_list<int> & list);

