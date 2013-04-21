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
bool Client::mod_client_message(char* message, uint8 chan_num) { return(true); } //Potentially dangerous string handling here
bool Client::mod_can_increase_skill(SkillType skillid, Mob* against_who) { return(false); }
int16 Client::mod_increase_skill_chance(int16 chance, Mob* against_who) { return(chance); }
int Client::mod_bindwound_percent(int max_percent, Mob* bindmob) { return(max_percent); }
int Client::mod_bindwound_hp(int bindhps, Mob* bindmob) { return(bindhps); }
int Client::mod_client_haste(int h) { return(h); }
void Client::mod_consider(Mob* tmob, Consider_Struct* con) { return; }
bool Client::mod_saylink(const std::string&, bool silentsaylink) { return(true); }
int16 Client::mod_pet_power(int16 act_power, uint16 spell_id) { return(act_power); }

int Mob::mod_effect_value(int effect_value, uint16 spell_id, int effect_type, Mob* caster) { return(effect_value); }
float Mob::mod_hit_chance(float chancetohit, SkillType skillinuse, Mob* attacker) { return(chancetohit); }
float Mob::mod_riposte_chance(float ripostechance, Mob* attacker) { return(ripostechance); }
float Mob::mod_block_chance(float blockchance, Mob* attacker) { return(blockchance); }
float Mob::mod_parry_chance(float parrychance, Mob* attacker) { return(parrychance); }
float Mob::mod_dodge_chance(float dodgechance, Mob* attacker) { return(dodgechance); }
float Mob::mod_monk_weight(float monkweight, Mob* attacker) { return(monkweight); }
float Mob::mod_mitigation_rating(float mitigation_rating, Mob* attacker) { return(mitigation_rating); }
float Mob::mod_attack_rating(float attack_rating, Mob* defender) { return(attack_rating); }
int32 Mob::mod_kick_damage(int32 dmg) { return(dmg); }
int32 Mob::mod_bash_damage(int32 dmg) { return(dmg); }
int32 Mob::mod_frenzy_damage(int32 dmg) { return(dmg); }
int32 Mob::mod_monk_special_damage(int32 ndamage, SkillType skill_type) { return(ndamage); }
int32 Mob::mod_backstab_damage(int32 ndamage) { return(ndamage); }
int Mob::mod_archery_bonus_chance(int bonuschance, const ItemInst* RangeWeapon) { return(bonuschance); }
uint32 Mob::mod_archery_bonus_damage(uint32 MaxDmg) { return(MaxDmg); }
int32 Mob::mod_archery_damage(int32 TotalDmg, bool hasbonus) { return(TotalDmg); }
uint16 Mob::mod_throwing_damage(uint16 MaxDmg) { return(MaxDmg); }
int32 Mob::mod_cast_time(int32 cast_time) { return(cast_time); }
int Mob::mod_buff_duration(int res, Mob* caster, Mob* target, uint16 spell_id) { return(res); }
int Mob::mod_spell_stack(uint16 spellid1, int caster_level1, Mob* caster1, uint16 spellid2, int caster_level2, Mob* caster2) { return(2); }
int Mob::mod_spell_resist(int resist_chance, int level_mod, int resist_modifier, int target_resist, uint8 resist_type, uint16 spell_id, Mob* caster) { return(resist_chance + level_mod + resist_modifier + target_resist); }
