
#include "POSIXRegex.h"

using namespace std;
using namespace POSIX;

////////////////////// Start Match Implementations //////////////////////

Match::Match()
{
    match = "";
}

Match::Match(string match)
{
    this->match = match;
}

int Match::start(unsigned int group)
{
    if (group >= pgroups.size())
        return -1;

    return pgroups[group].start;
}

int Match::end(unsigned int group)
{
    if (group >= pgroups.size())
        return -1;

    return pgroups[group].end;
}

string Match::group(unsigned int group)
{
    if (group >= pgroups.size())
        return "";

    if (pgroups[group].start == -1 || pgroups[group].end == -1)
        return "";
    
    return match.substr(pgroups[group].start, pgroups[group].end - pgroups[group].start);
}

vector<string> Match::groups()
{
    vector<string> g;

    for (unsigned int i = 0; i < pgroups.size(); i++)
    {
        if (pgroups[i].start >= 0 && pgroups[i].end >= 0)
            g.push_back(match.substr(pgroups[i].start, pgroups[i].end - pgroups[i].start));
    }

    return g;
}

int Match::numGroups()
{
    return pgroups.size();
}

void Match::addGroup(int start, int end)
{
    Group g = {start, end};
    pgroups.push_back(g);
}

////////////////////// Start Regex Implementations //////////////////////

Regex::Regex()
{
    compiled = false;
}

Regex::~Regex()
{
    if (compiled)
    {
        regfree(&regex);
        compiled = false;
    }
}

bool Regex::compile(string pattern, bool case_insensitive)
{
    if (compiled)
    {
        regfree(&regex);
        compiled = false;
    }

    this->pattern = pattern;

    int ret;
    if (case_insensitive)
        ret = regcomp(&regex, pattern.c_str(), REG_ICASE | REG_EXTENDED);
    else
        ret = regcomp(&regex, pattern.c_str(), REG_EXTENDED);

    if (ret == 0)
        compiled = true;

    return (ret == 0);
}

bool Regex::isCompiled()
{
    return compiled;
}

std::string Regex::getPattern()
{
    return pattern;
}

bool Regex::matches(std::string str)
{
    if (!compiled)
        return false;

    int ret = regexec(&regex, str.c_str(), 0, NULL, 0);

    if (ret == 0)
        return true;

    return false;
}

Match Regex::match(std::string str)
{    
    if (!compiled)
        return Match("");

    size_t ngroups = regex.re_nsub + 1;
    regmatch_t * pgroups = (regmatch_t *) malloc(ngroups * sizeof(regmatch_t));
    int ret = regexec(&regex, str.c_str(), ngroups, pgroups, 0);

    if (ret == 0)
    {
        Match m(str);
        for (int i=0; i<(int)ngroups; i++)
        {
            m.addGroup(pgroups[i].rm_so, pgroups[i].rm_eo);
        }

        free(pgroups);
        return m;
    }

    free(pgroups);
    return Match("");
}
