#include "../common/debug.h"
#include "../common/timer.h"
#include <cmath>
#include <stdlib.h>
#include "spawn2.h"
#include "entity.h"
#include "masterentity.h"
#include "zone.h"
#include "spawngroup.h"
#include "zonedb.h"
#include "npc.h"
#include "mob.h"
#include "client.h"
#include "worldserver.h"
#include "QuestParserCollection.h"
#include <string>
#include <iostream>

extern EntityList entity_list;
extern Zone* zone;

extern WorldServer worldserver;

using namespace std;

void Zone::mod_init()
{
    const NPCType* tmp = 0;
    if((tmp = database.GetNPCType(999999)))
    {
        NPC* npc = new NPC(tmp, 0, 0, 0, 0, 0, FlyMode3);
        if(npc)
        {
            entity_list.AddNPC(npc);
        }
    }
}

void Zone::mod_repop()
{
    const NPCType* tmp = 0;
    if((tmp = database.GetNPCType(999999)))
    {
        NPC* npc = new NPC(tmp, 0, 0, 0, 0, 0, FlyMode3);
        if(npc)
        {
            entity_list.AddNPC(npc);
        }
    }
}
