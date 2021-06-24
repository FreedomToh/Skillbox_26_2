#pragma once

class RegExpr {
private:
    static int checkCounter(int start, int stop, std::string &r);

public:
    bool match(std::string r, std::string &s);
    bool checkDiap(std::string &r, std::string &s, int *pposInR, int *pposInS);
};