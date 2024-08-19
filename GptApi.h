// installs curl library using nuget package manager
// the package is called libcurlv143 shared


#include <curl/curl.h>
#include <string>
#include <algorithm>
#include <cctype>

class GptApi {
public:
	GptApi();
	std::string POSTQuery(const std::string& prompt);
};

