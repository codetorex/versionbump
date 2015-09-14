//
// Created by KALEM on 9/12/2015.
//

#ifndef VERSIONBUMP_PATHITERATOR_H
#define VERSIONBUMP_PATHITERATOR_H

#include <string>


class PathIterator {
private:
    unsigned int m_start;
    int m_end;
    std::string full;
    std::string value;
    char sep;
    bool found;

public:
    PathIterator(std::string path, char separator = '.') {
        this->full = path;
        this->sep = separator;
        this->m_start = 0;
        this->m_end = -1;
        this->found = false;
    }

    bool next() {
        this->m_start = this->m_end + 1;

        if (this->m_start >= this->full.length()) {
            this->found = false;
            return false;
        }

        bool found = false;
        for (unsigned int i = this->m_start; i < this->full.length(); i++) {
            if (this->full[i] == this->sep) {
                this->m_end = i;
                found = true;
                break;
            }
        }

        if (found == false) {
            this->m_end = this->full.length();
        }

        int length = this->m_end - this->m_start;
        value = full.substr(this->m_start, length);

        return true;
    }

    std::string get() {
        return this->value;
    }
};

#endif //VERSIONBUMP_PATHITERATOR_H
