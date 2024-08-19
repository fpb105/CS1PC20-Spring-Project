#include "GptApi.h"

GptApi::GptApi() {}

// POSTQuery function that sends a POST request to the GPT-3 API or LLam2 as a fallback
// the code is based on an example form Postman

std::string GptApi::POSTQuery(const std::string& prompt) {
	CURL* curl;
	CURLcode res;
	std::string answer;	
	curl = curl_easy_init();
	if (curl) {
		curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "POST");
		curl_easy_setopt(curl, CURLOPT_URL, "http://127.0.0.1:5001/askgpt");
		curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
		curl_easy_setopt(curl, CURLOPT_DEFAULT_PROTOCOL, "http");
		struct curl_slist* headers = NULL;
		headers = curl_slist_append(headers, "Content-Type: application/json");
		curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
		std::string data = "{\"question\":\" " + prompt + "\"}";
		curl_easy_setopt(curl, CURLOPT_POSTFIELDS, data.c_str());
		res = curl_easy_perform(curl);
		// extract the answer fron res
		if (res == CURLE_OK) {
			char* pAnswer;
			res = curl_easy_getinfo(curl, CURLINFO_CONTENT_TYPE, &pAnswer);
			if ((res == CURLE_OK) && pAnswer) {
				answer = pAnswer;
			}
		}
		curl_slist_free_all(headers);
	}
	curl_easy_cleanup(curl);

	return answer;
}