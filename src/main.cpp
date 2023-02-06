#include "HeaderReplacer.h"

int main(int ac, char** av)
{
    HeaderReplacer headerReplacer(ac,av);

    headerReplacer.initFlags();
    headerReplacer.initSourceFiles();
    headerReplacer.initDirectories();
    headerReplacer.Run();


    return 0;
}
