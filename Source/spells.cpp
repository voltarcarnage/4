#include "headers/spells.h"

namespace Game_N{

  Spells::Spells()
  {
    lvlOfSpell_ = 1;
    dmgBySpell_ = 10;
    rangeOfSpell_ = 100;
    e_ = 0.75;
  }

  void Spells::lvlUpSpell()
  {
    ++lvlOfSpell_;
    dmgBySpell_ += lvlOfSpell_ * 0.5;
    rangeOfSpell_ += lvlOfSpell_ * 0.5;
  }

  Necromancy::Necromancy()
  {
    manaCost_ = 10;
  }

  Curse::Curse()
  {
    manaCost_ = 1;
    dmgBySpell_ = 50;
    rangeOfSpell_ = 150;
  }

  Morphism::Morphism()
  {
    manaCost_ = 1;
  }

  Desiccation::Desiccation()
  {
    manaCost_ = 1;
  }

  void Necromancy::castSpell()
  {
    // for(int i = 0; i < hero.amountOfUndeads_; i++)
    // {
    //     undeads_
    // }
  }

  void Curse::castSpell()
  {

  }

  void Morphism::castSpell()
  {
    // if()
  }

  void Desiccation::castSpell()
  {

  }

}
