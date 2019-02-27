
#ifndef ECPP_REGEX_H
#define ECPP_REGEX_H

#include <sys/types.h>
#include <stdlib.h>
#include <regex.h>
#include <vector>
#include <string>

namespace POSIX
{

struct Group
{
    int start;
    int end;
};

class Match
{
    private:
        std::string match;
        std::vector<Group> pgroups;

        void addGroup(int start, int end);

    public:
        Match();
        Match(std::string match);

        /*
            Returns the starting index of the group
        */
        int start(unsigned int group);

        /*
            Returns the ending index of the group
        */
        int end(unsigned int group);

        /*
            Returns a string representing the provided groups
        */
        std::string group(unsigned int group);

        /*
            Returns a list of strings representing all capture groups
        */
        std::vector<std::string> groups();

        /*
            Returns the number of groups in the match
        */
        int numGroups();

        friend class Regex;
};

class Regex
{
    private:
        std::string pattern;
        regex_t regex;
        bool compiled;

    public:
        Regex();
        ~Regex();

        /*
            Compiles the provided pattern and returns whether the compilation was successful or not
        */
        bool compile(std::string pattern, bool case_sensitive=true);

        /*
            Returns whether the provided string matches the compiled pattern
        */
        bool matches(std::string str);

        /*
            Returns the first Match in str
        */
        Match match(std::string str);

        /*
            Returns the current compiled pattern in string form
        */
        std::string getPattern();

        /*
            Returns whether there is a current compiled regex in memory
        */
        bool isCompiled();
};

}

#endif