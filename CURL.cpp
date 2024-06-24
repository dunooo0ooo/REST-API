#include "CURL.h"

std::string ExchangeRate(const std::string &date, const std::string &curCode, int nominal) {
    CURL *curl;
    CURLcode c;
    std::string answerServer;
    std::string result;

    std::string url = "http://cbr.ru/scripts/XML_daily.asp?date_req=" + date;
    curl_global_init(CURL_GLOBAL_ALL);
    curl = curl_easy_init();
    if (curl) {
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, fun);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &answerServer);
        c = curl_easy_perform(curl);

        if (c != CURLE_OK) {
            curl_easy_cleanup(curl);
            curl_global_cleanup();
            return "Error fetching data: " + std::string(curl_easy_strerror(c));
        }

        curl_easy_cleanup(curl);
        curl_global_cleanup();

        size_t posCurCode = answerServer.find("<CharCode>" + curCode + "</CharCode>");
        if (posCurCode == std::string::npos) {
            return "Currency code not found";
        }

        size_t posValue = answerServer.find("<Value>", posCurCode);
        size_t endValue = answerServer.find("</Value>", posValue);
        std::string valueStr = answerServer.substr(posValue + 7, endValue - posValue - 7);

        std::replace(valueStr.begin(), valueStr.end(), ',', '.');
        float exchangeValue = std::stof(valueStr);

        result = curCode + " " + std::to_string(nominal) + " " + date + " " + std::to_string(nominal * exchangeValue) + "\n";
    }
    return result;
}

std::string searchNumberID(const std::string &date, const std::string &currencyCode) {
    CURL *curl;
    CURLcode res;
    std::string answerServer;

    std::string url = "http://cbr.ru/scripts/XML_daily.asp?date_req=" + date;
    curl_global_init(CURL_GLOBAL_ALL);
    curl = curl_easy_init();
    if (curl) {
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, fun);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &answerServer);
        res = curl_easy_perform(curl);

        if (res != CURLE_OK) {
            curl_easy_cleanup(curl);
            curl_global_cleanup();
            return "Error fetching data: " + std::string(curl_easy_strerror(res));
        }

        curl_easy_cleanup(curl);
        curl_global_cleanup();

        std::string search_string = "<CharCode>" + currencyCode + "</CharCode>";
        size_t posCurCode = answerServer.find(search_string);
        if (posCurCode == std::string::npos) {
            return "Currency code not found";
        }

        size_t startValuteID = answerServer.rfind('<', posCurCode);
        startValuteID = answerServer.rfind('<', startValuteID - 1);
        startValuteID = answerServer.find('"', startValuteID);
        size_t endValuteID = answerServer.find('"', startValuteID + 1);
        std::string numberID = answerServer.substr(startValuteID + 1, endValuteID - startValuteID - 1);

        return numberID;
    }
    return "Error in function searchNumberID";
}

std::string addDateDate(const std::string &date, const std::string &curCode, size_t nominal) {
    size_t posDate = date.find('-');
    if (posDate == std::string::npos) {
        return "Invalid date format";
    }

    std::string firstDate = date.substr(0, posDate);
    std::string secondDate = date.substr(posDate + 1);

    std::string numberID = searchNumberID(firstDate, curCode);
    if (numberID.empty()) {
        return "Error fetching number ID";
    }

    CURL *curl;
    CURLcode c;
    std::string answerServer;

    std::string url = "http://www.cbr.ru/scripts/XML_dynamic.asp?date_req1=" + firstDate + "&date_req2=" + secondDate + "&VAL_NM_RQ=" + numberID;
    curl_global_init(CURL_GLOBAL_ALL);
    curl = curl_easy_init();
    if (curl) {
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, fun);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &answerServer);
        c = curl_easy_perform(curl);

        if (c != CURLE_OK) {
            curl_easy_cleanup(curl);
            curl_global_cleanup();
            return "Error fetching data: " + std::string(curl_easy_strerror(c));
        }

        curl_easy_cleanup(curl);
        curl_global_cleanup();

        std::string result;
        size_t start = 0;
        while ((start = answerServer.find("Date=", start)) != std::string::npos) {
            std::string curDate = answerServer.substr(start + 6, 10);

            size_t valueStart = answerServer.find("<Value>", start);
            size_t valueEnd = answerServer.find("</Value>", valueStart);
            std::string value = answerServer.substr(valueStart + 7, valueEnd - valueStart - 7);

            std::replace(value.begin(), value.end(), ',', '.');
            float exchangeValue = std::stof(value);

            result += curCode + " " + std::to_string(nominal) + " " + curDate + " "  + std::to_string(nominal * exchangeValue) + "\n";
            start = valueEnd;
        }
        return result;
    }
    return "Error in function addDateDate";
}
