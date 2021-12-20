
// #include "hero.h"
#include "enemy.h"

#pragma once

namespace Game_N{

  class Spells{
    protected:
      unsigned int lvlOfSpell_;
      unsigned int dmgBySpell_;
      unsigned int rangeOfSpell_;
      unsigned int manaCost_;
      double e_;
    public:
      Spells();

      unsigned int getLvlOfSpell() const {return lvlOfSpell_;}
      unsigned int getDmgBySpell() const {return dmgBySpell_;}
      unsigned int getRangeOfSpell() const {return rangeOfSpell_;}
      unsigned int getManaCost() const {return manaCost_;}
      void setLvlOfSpell(int lvl) {lvlOfSpell_ = lvl;}
      double getE() const {return e_;}
      void setDmgBySpell(int dmg) {dmgBySpell_ = dmg;}
      void setRangeOfSpell(int rng) {rangeOfSpell_ = rng;}
      void lvlUpSpell();

      virtual void castSpell(Enemy& enemy) = 0;
  };

  class Necromancy : public Spells{
    public:
      Necromancy();

      void castSpell(Enemy& enemy);
  };

  class Curse : public Spells{
    public:
      Curse();
      void castSpell(Enemy& enemy);
  };

  class Morphism : public Spells{
    public:
      Morphism();
      void castSpell(Enemy& enemy);
  };

  class Desiccation : public Spells{
    public:
      Desiccation();
      void castSpell(Enemy& enemy);
  };

}
