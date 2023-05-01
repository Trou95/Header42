#include "HeaderReplacer.h"

int main(int ac, char** av)
{
    if(ac < 2)
        return 0;

    HeaderReplacer headerReplacer(ac,av);

    headerReplacer.initFlags();
    headerReplacer.initSourceFiles();
    headerReplacer.initDirectories();
    headerReplacer.Run();


    return 0;
}
