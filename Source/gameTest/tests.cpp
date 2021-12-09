#include <gtest/gtest.h>

#include "../headers/enemy.h"
#include "../headers/hero.h"

using namespace Game_N;

TEST(GameTest, HeroDefaultConstructor)
{
  Hero hero;
  EXPECT_EQ(100, hero.getMaxHp());
  EXPECT_EQ(100, hero.getHp());
  EXPECT_EQ(15, hero.getDamage());
  EXPECT_EQ(1,hero.getLvl());
  EXPECT_EQ(0,hero.getExp());
  EXPECT_EQ(100,hero.getMaxMana());
  EXPECT_EQ(100,hero.getMana());
  EXPECT_EQ(100,hero.getExpToNextLvl());
  EXPECT_EQ(2,hero.getRange());
  EXPECT_EQ(2,hero.getUndeads());
}

TEST(GameTest, HeroCustomConstructor)
{
  Hero hero(2,100,15,100,200,200,4,5);
  EXPECT_EQ(100, hero.getMaxHp());
  EXPECT_EQ(100, hero.getHp());
  EXPECT_EQ(15, hero.getDamage());
  EXPECT_EQ(2,hero.getLvl());
  EXPECT_EQ(100,hero.getExp());
  EXPECT_EQ(200,hero.getMaxMana());
  EXPECT_EQ(200,hero.getMana());
  EXPECT_EQ(200,hero.getExpToNextLvl());
  EXPECT_EQ(5,hero.getRange());
  EXPECT_EQ(4,hero.getUndeads());
}

TEST(GameTest, HeroTestHp)
{
  Hero hero(2,100,15,100,200,200,4,5);
  hero.takeDamage(30);
  int hpNow = hero.getHp();
  int maxHp = hero.getMaxHp();
  EXPECT_EQ(70, hpNow);
  EXPECT_EQ(100, maxHp);
}

TEST(GameTest, HeroTakeDamage)
{
  Hero hero(2,100,15,100,200,200,4,5);
  hero.takeDamage(40);

  EXPECT_EQ(60, hero.getHp());
}

TEST(GameTest, HeroLvlUp)
{
  Hero hero;
  hero.lvlUp();

  EXPECT_LT(100, hero.getMaxHp());
}

TEST(GameTest, HeroHeal)
{
  Hero hero;
  hero.takeDamage(40);

  hero.heal(20,20);

  EXPECT_EQ(80, hero.getHp());
  EXPECT_EQ(100, hero.getMana());
}

TEST(GameTest, EnemyConstructor)
{
  Enemy enemy(1,2,10,"Tests", sf::Vector2i(0,0));

  EXPECT_EQ(100, enemy.getHp());
}

TEST(GameTest, EnemyMove)
{
  Enemy enemy(1,2,10,"Tests", sf::Vector2i(1,1));
  enemy.moveUp();
  EXPECT_EQ(0,enemy.getPos().y);
  enemy.moveDown();
  EXPECT_EQ(1,enemy.getPos().y);
  enemy.moveLeft();
  EXPECT_EQ(0,enemy.getPos().x);
  enemy.moveRight();
  EXPECT_EQ(1,enemy.getPos().x);
}

TEST(GameTest, EnemyTakeDMG)
{
  Enemy enemy(1,2,10,"Tests", sf::Vector2i(0,0));

  enemy.takeDamage(50);

  EXPECT_EQ(50, enemy.getHp());
}


int main()
{
  ::testing::InitGoogleTest();
  return RUN_ALL_TESTS();
}
