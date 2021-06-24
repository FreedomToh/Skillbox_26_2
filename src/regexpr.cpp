#include <iostream>
#include "regexpr.h"

int RegExpr::checkCounter(int start, int stop, std::string &r) {
    if (r[start] == '{' && r.find('}', stop) < r.size()) {
        start = start + 1;
        stop = r.find('}', stop);

        std::string tmp = "";
        for (int i = start; i < stop; i ++) {
            if (r[i] < '0' || r[i] > '9') {
                return 1;
            } else {
                tmp += r[i];
            }
        }

        try {
            return std::stoi(tmp);
        } catch (std::exception &err){
            return 1;
        }

        // std::cout << tmp << " " << start << " " << stop << std::endl;
    }
    return 1;
}

bool RegExpr::checkDiap(std::string &r, std::string &s, int *pposInR, int *pposInS) {
    // check variant [0-9]
    int posInR = *pposInR;
    int posInS = *pposInS;

    if (r.find(']', posInR) < r.size()) {
        int startPos = posInR;
        int stopPos = r.find(']', startPos + 1);

        if (stopPos == -1) {
            std::cout << "Error in regexp" << std::endl;
            return false;
        }

        // check for {}
        int count = checkCounter(stopPos + 1, stopPos + 2, r);
        count += posInS;

        // check diap
        if (r.find('-', startPos) < stopPos) {
            // if diap [*-*]

            std::string start = r.substr(startPos + 1, r.find('-', startPos) - (startPos + 1));
            std::string stop = r.substr(r.find('-', startPos) + 1, stopPos - (r.find('-', startPos) + 1));

            if (start.length() == 1 && stop.length() == 1) {
                if (start[0] >= '0' && start[0] <= '9' &&
                    stop[0] >= '0' && stop[0] <= '9') {
                    // if digits

                    if (start[0] < stop[0]) {
                        //std::cout << pos << " " << count << std::endl;
                        for (; posInS < count; posInS ++) {

                            bool conf = false;
                            for (int c = start[0]; c <= stop[0]; c++) {
                                if (s[posInS] == c) {
                                    //std::cout << s[posInS] << " (" << c << ") ";
                                    conf = true;
                                    break;
                                }
                            }
                            if (!conf) return false;
                        }
                    } else {
                        std::cout << "Wrong RegExpr: " << r << std::endl;
                        return false;
                    }

                } else if
                        (((start[0] >= 'a' && start[0] <= 'z') &&
                          (stop[0] >= 'a' && stop[0] <= 'z')) ||
                         ((start[0] >= 'A' && start[0] <= 'Z') &&
                          (stop[0] >= 'A' && stop[0] <= 'Z'))){
                    // if chars

                    if (start[0] < stop[0]) {
                        for (; posInS < count; posInS ++) {
                            bool conf = false;
                            for (int c = start[0]; c <= stop[0]; c++) {
                                if (s[posInS] == c) {
                                    //std::cout << s[posInS] << " (" << c << ") ";
                                    conf = true;
                                    break;
                                }
                            }
                            if (!conf) return false;
                        }
                    } else {
                        std::cout << "Wrong RegExpr: " << r << std::endl;
                        return false;
                    }
                }

            } else {
                return false;
            }

            if (count > 1) {
                stopPos = r.find('}', stopPos);
            }

            *pposInR = stopPos;
            *pposInS = posInS - 1;

            //std::cout << std::endl;
            //std::cout << startPos << " " << stopPos << " " << count << std::endl;


            return true;

        } else {
            // if [**]
        }
    } else {
        return false;
    }

    return true;
}

bool RegExpr::match(std::string r, std::string &s) {
    if (r.length() == 0 || s.length() == 0) return false;

    int pos = 0; // pos in string

    // if alone digits not diapason
    //std::cout << r << " " << s << std::endl;
    bool easyFlag = false; // flag for '\'
    for (int i = 0; i < r.length() && pos < s.length(); i++) {
        if (r[i] == '[') {
            int *pPos = &pos;
            int *pI = &i;
            checkDiap(r, s, pI, pPos);
            pos ++;
            continue;
        } else if (r[i] == '.') {

            pos ++;
            easyFlag = false;
            continue;
        } else if (r[i] == '\\') {
            easyFlag = true;

            pos ++;
            continue;
        } else if (r[i] == '{') {
            int count = checkCounter(i, i + 1, r);

            //std::cout << "Repeater: " << count;

            if (pos == 0) return false;

            char c = s[pos - 1];
            //std::cout  << ", char: " << c << std::endl;
            count += pos;

            for (; pos < count - 1; pos++) {
                //std::cout << "Char in string: " << s[pos] <<  ", char in reg: " << c << std::endl;
                if (s[pos] != c) {
                    return false;
                }
            }
            continue;
        } else {
            //std::cout << "Char in string: " << s[pos] <<  ", char in reg: " << r[i] << std::endl;
            if (s[pos] != r[i]) {
                return false;
            }
        }

        pos ++;

    }
    return true;
};