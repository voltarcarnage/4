#include <iostream>

#pragma once

namespace Game_N{

  class Spells{
    private:
      int lvlOfSpell_;
      int dmgBySpell_;
      int rangeOfSpell_;
    public:
      int getLvlOfSpell() const {return lvlOfSpell_;}
      int getDmgBySpell() const {return dmgBySpell_;}
      int getRangeOfSpell() const {return rangeOfSpell_;}
      void setLvlOfSpell(int lvl) {lvlOfSpell_ = lvl;}
      void setDmgBySpell(int dmg) {dmgBySpell_ = dmg;}
      void setRangeOfSpell(int rng) {rangeOfSpell_ = rng;}

      virtual void castSpell() = 0;
  };

  class Necromancy : public Spells{
    private:
      int amountOfundeads_;
    public:
      int getAmountOfUndeads() const {return amountOfundeads_;}
      void setAmountOfUndeads(int amount) {amountOfundeads_ = amount;}

      void castSpell();
  };

  class Curse : public Spells{
    public:
        void castSpell();
  };

  class Morphism : public Spells{
    public:
      void castSpell();
  };

  class Desiccation : public Spells{
    public:
      void castSpell();
  };

}
