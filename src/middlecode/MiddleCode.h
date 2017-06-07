//
// Created by plter on 6/7/17.
//

#ifndef SRC_MIDDLECODE_H
#define SRC_MIDDLECODE_H


#include <string>

namespace rml {
    namespace mc {
        class MiddleCode {

        private:
            std::string name;

        public:
            explicit MiddleCode(const std::string &name);

            const std::string &getName() const;

        };
    }
}


#endif //SRC_MIDDLECODE_H
