#include "init.h"
#include "intro.h"
#include "beg.h"
#include "ending.h"

void Program()
{
    //intro();
    beg();
}

int main()
{
    init();
    Program();
    ending();

    return 0;
}
