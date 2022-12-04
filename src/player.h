#pragma once

#include "unit.h"
#include "talents.h"
#include "config.h"

#include <vector>

namespace unit
{
class Player : public Unit
{
public:
    Stats summon_stats;
    Talents talents;
    Glyphs glyphs;
    Race race = RACE_UNDEAD;

    int combustion;
    int fingers_of_frost;
    bool heating_up;
    double t_living_bomb;
    double t_flamestrike;
    double t_scorch;
    double t_brain_freeze;
    double t_incanters_absorption;
    double t_mana_spent;
    double fire_ward;
    double mana_shield;
    int mana_sapphire;
    int ab_streak;
    bool waited;
    bool should_wait;

    Player(std::shared_ptr<Config> _config);

    void reset();

    Stats getStats();

    void setStats(Stats _stats);

    Stats getSummonStats();

    void setSummonStats(Stats _stats);

    Talents getTalents();

    void setTalents(Talents _talents);

    Glyphs getGlyphs();

    void setGlyphs(Glyphs _glyphs);

    Faction faction();

    bool hasTrinket(Trinket trinket) const;

    double manaPerSecond(const State& state);

    double maxMana() const;

    double baseCastTime(std::shared_ptr<spell::Spell> spell) const;

    double castHaste() const;

    double hitChance(std::shared_ptr<spell::Spell> spell, double dlevel = 3);

    double critChance(std::shared_ptr<spell::Spell> spell);

    bool canCrit(std::shared_ptr<spell::Spell> spell);

    double baseCritMultiplier(std::shared_ptr<spell::Spell> spell);

    double critMultiplierMod(std::shared_ptr<spell::Spell> spell);

    double spellCoeffMod(std::shared_ptr<spell::Spell> spell);

    double buffDmgMultiplier(std::shared_ptr<spell::Spell> spell, const State& state);

    double baseManaCost(std::shared_ptr<spell::Spell> spell) const;

    double manaCostMod(std::shared_ptr<spell::Spell> spell) const;

    double manaCostMultiplier(std::shared_ptr<spell::Spell> spell) const;

    double getSpellPower(School school = SCHOOL_NONE);

    double getHasteRating();

    bool shouldConsumeClearcast(std::shared_ptr<spell::Spell>  spell) const;

    double cooldownMod(const cooldown::Cooldown& cooldown) const;

    bool isFrozen();

    bool hasChillEffect(std::shared_ptr<spell::Spell> spell) const;

    std::vector<action::Action> onBuffGain(const State& state, std::shared_ptr<buff::Buff> buff);

    std::vector<action::Action> onBuffExpire(const State& state, std::shared_ptr<buff::Buff> buff);

    std::vector<action::Action> onCastSuccessProc(const State& state, std::shared_ptr<spell::Spell> spell);

    std::vector<action::Action> onSelfDmg(const State& state, double dmg, School school = SCHOOL_NONE);

    std::vector<action::Action> onSpellImpactProc(const State& state, const spell::SpellInstance &instance);

    std::vector<action::Action> onSpellTickProc(const State& state, std::shared_ptr<spell::Spell> spell, int tick);

    std::vector<action::Action> onCastOrTick(const State& state, std::shared_ptr<spell::Spell> spell);

    bool hasManaGem() const;

    double manaGemMax() const;

    // TODO: Given the name, this function should be const and not affect state
    // (i.e. not call useTiming)
    bool shouldUseManaGem(const State& state);

    // TODO: Given the name, this function should be const and not affect state
    // (i.e. not call useTiming)
    bool shouldUseManaPotion(const State& state);

    bool shouldEvocate(const State& state);

    std::vector<action::Action> useManaGem();

    std::vector<action::Action> useConjured(const State& state, Conjured conjured);

    std::vector<action::Action> usePotion(Potion potion, bool in_combat);

    bool isTrinketOnSharedCD(Trinket trinket) const;

    bool trinketSharesCD(Trinket trinket) const;

    bool isUseTrinket(Trinket trinket) const;

    bool isTimingReady(const Timing& timing, const State& state) const;

    bool useTimingIfPossible(const std::string& name, const State& state, bool expl = false);

    bool isTimingReadySoon(const std::string& name, const State& state, double t = 5);

    std::vector<action::Action> useTrinket(Trinket trinket, std::shared_ptr<cooldown::Cooldown> cooldown);

    int evocationTicks() const;

    action::Action useCooldown(const State& state);

    bool canBlast(const State& state) const;

    action::Action preCombat(const State& state);

    action::Action nextAction(const State& state);

private:
    Timing* getNextTiming(const std::string& name);

};
}