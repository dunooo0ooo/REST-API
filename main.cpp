#include <iostream>
#include "CURL.h"


int main(int argc, char *argv[]) {
    int nominal = 1;
    std::string curCode;
    std::string date;
    std::string filename;
    std::string DateDate;

    for (int i = 1; i < argc; ++i) {
        std::string arguments = argv[i];
        if (arguments.substr(0, 8) == "--Vname=") {
            curCode = arguments.substr(8);
        } else if (arguments.substr(0, 7) == "--Vnom=") {
            nominal = std::stoi(arguments.substr(7));
        } else if (arguments.substr(0, 7) == "--Date=") {
            date = arguments.substr(7);
        } else if (arguments.substr(0, 11) == "--FileName=") {
            filename = arguments.substr(11);
        } else if (arguments.substr(0, 11) == "--DateDate=") {
            DateDate = arguments.substr(11);
        }
    }

    if(filename.empty()) {
        if (!DateDate.empty()) {
            std::string answer = addDateDate(DateDate, curCode, nominal);
            std::cout << answer << std::endl;
        } else if (date.empty()) {
            time_t t = time(nullptr);
            tm *curTime = localtime(&t);

            int day = curTime->tm_mday;
            int month = curTime->tm_mon + 1;
            int year = curTime->tm_year + 1900;

            std::string curDate = addDate(day, month, year);
            std::string answer = ExchangeRate(curDate, curCode, nominal);
            std::cout << answer << std::endl;
        } else if (!curCode.empty()) {
            std::string answer = ExchangeRate(date, curCode, nominal);
            std::cout << answer << std::endl;
        }
    }
    else {
        std::ofstream FILE(filename);
        if (!DateDate.empty()) {
            std::string answer = addDateDate(DateDate, curCode, nominal);
            if(FILE.is_open()) {
                FILE << answer;
                std::cout << "Answer in file" << std::endl;
            }
            else {
                std::cout << "Error file" << std::endl;
            }
        } else if (date.empty()) {
            time_t t = time(nullptr);
            tm *curTime = localtime(&t);

            int day = curTime->tm_mday;
            int month = curTime->tm_mon + 1;
            int year = curTime->tm_year + 1900;

            std::string curDate = addDate(day, month, year);
            std::string answer = ExchangeRate(curDate, curCode, nominal);
            if(FILE.is_open()) {
                FILE << answer;
                std::cout << "Answer in file" << std::endl;
            }
            else {
                std::cerr << "File doesn't open";
            }
        } else if (!curCode.empty()) {
            std::string answer = ExchangeRate(date, curCode, nominal);
            if(FILE.is_open()) {
                FILE << answer;
                std::cout << "Answer in file" << std::endl;
            }
            else {
                std::cerr << "File doesn't open";
            }
        }
    }
    return 0;
}
