 #include "POSIXRegex.h"

#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main()
{
    POSIX::Regex re;
    POSIX::Match m;

    re.compile("/hello/(.*)");
    cout << "Matches? " << re.matches("/hello/darkness") << endl;
    cout << "Matches? " << re.matches("/mello/darkness") << endl;
    cout << endl;

    re.compile("hello (\\w+) my old (\\w+)");
    m = re.match("hello darkness my old mellon");

    vector<string> groups = m.groups();
    for (unsigned int i = 0; i < groups.size(); ++i)
        cout << i << ": " << groups[i] << endl;
    cout << endl;

    re.compile("John (.*) is my (B.+)", true); //case insensitive
    m = re.match("John Doe is my boy");
    cout << m.group(0) << endl;
    cout << m.group(1) << endl;
    cout << m.group(2) << endl;
    cout << endl;

    m = re.match("John Smith is my Bizzle");
    cout << "Total groups: " << m.numGroups() << endl;
    cout << "Match start index: " << m.start(0) << endl;
    cout << "Match end index: " << m.end(0) << endl;
    cout << endl;
}