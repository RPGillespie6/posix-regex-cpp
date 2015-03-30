
# POSIX Regex C++

## What is it?

POSIXRegex.cpp is a powerful lightweight C++ wrapper for the POSIX regex library commonly used in C, `<regex.h>`.

## Why would you want to use this?

It is well known that `<regex>` has become a part of the C++ standard library with the advent of C++11. However, for various reasons, sometimes using C++11 regex is not possible (old kernel, old compiler, etc.).

This project is an alternative for *nix users who want the syntactic sugar of python without the hassle of 3rd party regex libraries like Boost and PCRE.

## How to Use

*Note: POSIXRegex probably won't compile out of the box on Windows, since Windows does not usually have POSIX libaries.*

However, it is very easy to compile under *nix:

`g++ -c POSIXRegex.cpp`

This yields `POSIXRegex.o` which can then be linked in with the project you want to use.

`example.cpp`:
```
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
    for (int i = 0; i < groups.size(); ++i)
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
```

Run:
```
$ g++ example.cpp POSIXRegex.cpp
$ ./a.out
Matches? 1
Matches? 0

0: hello darkness my old mellon
1: darkness
2: mellon

John Doe is my boy
Doe
boy

Total groups: 3
Match start index: 0
Match end index: 23
$
```