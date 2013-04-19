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

//Spawn serverman when a zone boots or is repopped.
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

void NPC::mod_prespawn(Spawn2 *sp)
{
    //The spawn has to have 1 kill to qualify
    if(sp->GetKillCount() < 1) { return; }
    //Ignore existing bosses
    if(lastname[0] == '[') { return; }
    //5% chance to elevate
    if(MakeRandomInt(0, 100) > 5) { return; }

    //Let everything else happen in perl.  Our job here is to set the last name
    int npcscore = GetScore();
    std::string bosstag = "<";
    int lvs = (int)(npcscore/10);
    for(int x = 0; x < 10; x++)
    {
        if(x < lvs) { bosstag += "+"; }
        else { bosstag += "="; }
    }
    bosstag += ">";
    strn0cpy(lastname, bosstag.c_str(), sizeof(lastname));

    TempName("DYNBOSS");
}

int NPC::mod_npc_damage(int damage, SkillType skillinuse, int hand, ItemInst* weapon, Mob* other) { return(damage); }

int Client::mod_client_damage(int damage, SkillType skillinuse, int hand, ItemInst* weapon, Mob* other) { return(damage); }

int Mob::mod_effect_value(int effect_value, int effect_type, Mob* caster) { return(effect_value); }
float Mob::mod_hit_chance(float chancetohit, SkillType skillinuse, Mob* attacker) { return(chancetohit); }
float Mob::mod_riposte_chance(float ripostechance, Mob* attacker) { return(ripostechance); }
float Mob::mod_block_chance(float blockchance, Mob* attacker) { return(blockchance); }
float Mob::mod_parry_chance(float parrychance, Mob* attacker) { return(parrychance); }
float Mob::mod_dodge_chance(float dodgechance, Mob* attacker) { return(dodgechance); }
float Mob::mod_monk_weight(float monkweight, Mob* attacker) { return(monkweight); }
float Mob::mod_mitigation_rating(float mitigation_rating, Mob* attacker) { return(mitigation_rating); }
float Mob::mod_attack_rating(float attack_rating, Mob* defender) { return(attack_rating); }
