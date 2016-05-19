Biblioteken kompilerade för VS2015 med statisk C runtime.

För ditt projekt som skall använda MazeLib2015.lib (det besvärligaste
biblioteket) eller om du får länkfel om LIBCMD och/eller fel om
/SAFESEH från länkaren:

* Sätt projekt->C++/C->Code Generation->Runtime Library till "Multi-threaded Debug"

* Sätt projekt->Linker->Advanced->Image Has Safe Exception Handlers till "No (/SAFESEH:NO)"

