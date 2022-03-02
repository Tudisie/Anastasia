#ifndef STORY_H_INCLUDED
#define STORY_H_INCLUDED

bool close_story;

#include "text.h"

char main_en[6][400],main_ro[6][400];

void Story()
{
    close_story = false;

    if(language == 0)
    {
        strcpy(main_en[0], "Anastasia, a brave warrior of the Old Ages*woke up in the middle of some of the most dangerous challenges,*\
made by a witch named Caspria.*Both of these women were head over heels in love with Eliphas.");

    strcpy(main_en[1], "Being one of the most well known and skilled warriors,*the name of Eliphas had reached far and wide across the realm,*\
for his abilities in handling a sword,*slaying each and every foe that dared to cross his path.*\
Our hero Anastasia met Eliphas the warrior at the celebration*for the 100th year of peace between humans and magic folk.");

    strcpy(main_en[2], "From that night onward, the two were inseparable:*everywhere she went, he followed. *\
Likewise, she was just as devoted to him and accompanied Eliphas*in each and every one of his adventures.");

    strcpy(main_en[3], "Caspria, the witch, was watching them from the shadows.*Her heart was breaking while watching them fall deeper and deeper in love.");

    strcpy(main_en[4], "With each day that passed,*more and more hate filled her senses, her mind, and her very soul. *\
One day, completely blinded by jealousy,*she kidnapped Eliphas and cursed Anastasia.");

    strcpy(main_en[5], "Lost and lonely, Anastasia wakes up at the other side of the world,*in a place full of terrifying monsters and deadly traps.*\
This is how our hero's adventure begins,*with the hope of finding and saving Eliphas…");

        for(int i=0; i<6 && !close_story; ++i)
            fade_text(main_en[i]);
    }
    else
    {
        strcpy(main_ro[0],"Anastasia, o razboinica a acelor veacuri,*se trezeste in mijlocul unor peripetii primejdioase*puse la cale de vrajitoarea Caspria,*\
care este indragostita peste cap de Eliphas.");
        strcpy(main_ro[1],"Eliphas, tanarul cavaler al carui nume*a strabatut pana si cele mai necunoscute taramuri,*\
renumit pentru abilitatile sale de a manui o arma impotriva adversarilor,*o intalneste pe Anastasia la festivitatea \
care avea drept scop*celebrarea pacii dintre oameni si vrajitori ce domneste de 100 ani.");
        strcpy(main_ro[2],"Din acea seara tanarul Eliphas si domnita Anastasia au devenit de nedezlipit.*\
Oriunde mergea ea, trebuia sa mearga si el,*iar oriunde mergea el, trebuia sa mearga si ea.");
        strcpy(main_ro[3],"Aceste fapte erau vazute din umbra de catre Caspria,*\
care simtea cum i se sfasie inima cand ii vedea pe cei 2 fericiti impreuna.");
        strcpy(main_ro[4],"Dragostea lor crestea vazand cu ochii,*si tot pe-atata crestea si dorinta Caspriei de razbunare,*\
pana intr-o zi, cand, oarba de gelozie,*aceasta il rapeste pe Eliphas si arunca cu vraji demonice asupra Anastasiei.");
        strcpy(main_ro[5],"Distrusa trup si suflet, Anastasia se trezeste in celalalt capat al lumii,*\
inconjurata de creaturi periculoase si capcane mortale.*Astfel porneste in cautarea mult iubitului Eliphas,*\
in speranta ca-l va gasi...");

        for(int i=0; i<6 && !close_story; ++i)
            fade_text(main_ro[i]);
    }

}

#endif // STORY_H_INCLUDED
