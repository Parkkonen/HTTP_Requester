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
class CurlWrapper {
    public:
    CurlWrapper() {
        curl_global_init(CURL_GLOBAL_DEFAULT);
        curl = curl_easy_init();
    }

    ~CurlWrapper() {
        if (curl) {
            curl_easy_cleanup(curl);
            curl_global_cleanup();
        }
    }

    CURL* getHandle() const {
        return curl;
    }

private:
    CURL* curl;
};

enum class eRequestType 
{
    kUnknownRequest = 0,
    kGETRequest = 1,
    kPOSTRequest = 2,
    kDELETERequest = 3,
    kPUTRequest = 4
};



static void get(CURL* curl, CURLcode res, Json::CharReaderBuilder reader, Json::Value root, std::string errs) 
{

    curl_easy_setopt(curl, CURLOPT_URL, gui::url.c_str());
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);

    std::string response;
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);

    res = curl_easy_perform(curl);
    if (res != CURLE_OK) 
    {
        std::string error = curl_easy_strerror(res);
        gui::result = "GET FAILED: " + error;
    }
    else 
    {
        std::istringstream stream(response);
        Json::parseFromStream(reader, stream, &root, &errs);
        Json::StreamWriterBuilder writer;
        writer["indentation"] = "    ";
        response = Json::writeString(writer, root);
        gui::result = response;
    }
}
static void post(CURL* curl, CURLcode res, Json::CharReaderBuilder reader, Json::Value root, std::string errs) 
{
    const char* requestBody = "Don't Know what to put here yet";

    curl_easy_setopt(curl, CURLOPT_URL, gui::url);
    curl_easy_setopt(curl, CURLOPT_POST, 1);


    curl_easy_setopt(curl, CURLOPT_POSTFIELDS, requestBody);

    std::string response;
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);

    res = curl_easy_perform(curl);

    if (res != CURLE_OK) 
    {
        std::string error = curl_easy_strerror(res);
        gui::result = "POST FAILED: " + error;
    }
    else
        gui::result = response;
}
static void del(CURL* curl, CURLcode res, Json::CharReaderBuilder reader, Json::Value root, std::string errs)
{
    curl_easy_setopt(curl, CURLOPT_URL, gui::url);

    curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "DELETE");

    std::string response;
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);

    res = curl_easy_perform(curl);

    if (res != CURLE_OK)
    {
        std::string error = curl_easy_strerror(res);
        gui::result = "DELETE FAILED: " + error;
    }
    else
    {
        gui::result = response;
    }
}
static void put(CURL* curl, CURLcode res, Json::CharReaderBuilder reader, Json::Value root, std::string errs)
{
    curl_easy_setopt(curl, CURLOPT_URL, gui::url);

    curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "PUT");

    std::string response;
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);

    res = curl_easy_perform(curl);

    if (res != CURLE_OK)
    {
        std::string error = curl_easy_strerror(res);
        gui::result = "PUT FAILED: " + error;
    }
    else
    {
        gui::result = response;
    }
}



void gui::sendRequest(int type) 
{
    CurlWrapper curlWrapper;
    CURL* curl = curlWrapper.getHandle();
    if (!curl)
        return;

    CURLcode res = CURLE_OK;
    Json::CharReaderBuilder reader;
    Json::Value root;
    std::string errs;

    switch (type)
    {
    case 0:
        get(curl, res, reader, root, errs);
        break;
    case 1:
        post(curl, res, reader, root, errs);
        break;
    case 2:
        del(curl, res, reader, root, errs);
        break;
    case 3:
        put(curl, res, reader, root, errs);
        break;
    default:
        break;
            
    }
}

int main() 
{

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

    while (gui::exit) 
    {

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


