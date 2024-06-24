#pragma once
#include <iostream>
#include <string>
#include <algorithm>
#include <fstream>
#include <ctime>
#include <curl/curl.h>


static size_t fun(char *p, size_t s, size_t n, std::string *d) {
    d->append(p, s * n);
    return s * n;
}

static std::string addDate(int day, int month, int year) {
    char buffer[11];
    snprintf(buffer, sizeof(buffer), "%02d.%02d.%04d", day, month, year);
    return std::string(buffer);
}

std::string ExchangeRate(const std::string &date, const std::string &curCode, int nominal);

std::string searchNumberID(const std::string &date, const std::string &currencyCode);
std::string addDateDate(const std::string &date, const std::string &curCode, size_t nominal);

