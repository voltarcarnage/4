
// #include "hero.h"
// #include "enemy.h"

#pragma once

namespace Game_N{

  class Spells{
    protected:
      int lvlOfSpell_;
      int dmgBySpell_;
      int rangeOfSpell_;
    public:
      Spells();

      int getLvlOfSpell() const {return lvlOfSpell_;}
      int getDmgBySpell() const {return dmgBySpell_;}
      int getRangeOfSpell() const {return rangeOfSpell_;}
      void setLvlOfSpell(int lvl) {lvlOfSpell_ = lvl;}
      void setDmgBySpell(int dmg) {dmgBySpell_ = dmg;}
      void setRangeOfSpell(int rng) {rangeOfSpell_ = rng;}

      virtual void castSpell() = 0;
  };

  class Necromancy : public Spells{
    public:
      Necromancy();

      void castSpell();
  };

  class Curse : public Spells{
    public:
      Curse();
      void castSpell();
  };

  class Morphism : public Spells{
    public:
      Morphism();
      void castSpell();
  };

  class Desiccation : public Spells{
    public:
      Desiccation();
      void castSpell();
  };

}
