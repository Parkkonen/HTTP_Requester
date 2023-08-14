#include <iostream>
#include <curl/curl.h>
#include <imgui.h>
#include "gui.h"
#include <thread>
#include <json/json.h>

size_t WriteCallback(void* contents, size_t size, size_t nmemb, void* userp) {
    size_t totalSize = size * nmemb;
    std::string* response = static_cast<std::string*>(userp);
    response->append(static_cast<char*>(contents), totalSize);
    return totalSize;
}
void getAllAlerts() {
    CURL* curl;
    CURLcode res;
    Json::CharReaderBuilder reader;
    Json::Value root;
    std::string errs;
    curl_global_init(CURL_GLOBAL_DEFAULT);
    curl = curl_easy_init();

    if (curl) {

        curl_easy_setopt(curl, CURLOPT_URL, gui::url.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);

        std::string response;
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);

        res = curl_easy_perform(curl);
        if (res != CURLE_OK) {
            std::cerr << "curl_easy_perform() failed: " << curl_easy_strerror(res) << std::endl;
            std::string error = curl_easy_strerror(res);
            gui::result = "Failed: " + error;
        }
        else {
            std::cout << "Response:\n" << response << std::endl;
            std::istringstream stream(response);
            Json::parseFromStream(reader, stream, &root, &errs);
            Json::StreamWriterBuilder writer;
            writer["indentation"] = "    "; 
            response = Json::writeString(writer, root);
            gui::result = response;
        }

        curl_easy_cleanup(curl);
    }

    curl_global_cleanup();
}
void gui::sendRequest(std::string type) {

    // Create a map to use switch on our request type
    std::unordered_map<std::string, int> requestMap = {
        {"GET", 1},
        {"POST", 2},
        {"DELETE", 3},
        {"PUT", 4}
    };
    if (requestMap.find(type) != requestMap.end()) {
        int requestTypeInt = requestMap[type];
        switch (requestTypeInt)
        {
        case 1:
            getAllAlerts();
        
        default:
            break;
        }
    }
}

void requestHandle() {

}

int main() {

    return 0;
}
int __stdcall wWinMain(
    HINSTANCE instance,
    HINSTANCE previousInstance,
    PWSTR arguments,
    int commandShow)
{
    gui::CreateHWindow("Test", "testClassName");
    gui::CreateDevice();
    gui::CreateImGui();

    while (gui::exit) {

        gui::BeginRender();
        gui::Render();
        gui::EndRender();

        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }

    gui::DestroyImGui();
    gui::DestroyDevice();
    gui::DestroyHWindow();
    

    return EXIT_SUCCESS;
}


