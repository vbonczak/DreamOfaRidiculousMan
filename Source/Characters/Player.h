#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include "../Base/utils.h"
#include "../Base/config.h"
#include "MovingEntity.h"
#include "LivingEntity.h"
#include <unordered_map>

class Room;
class Map;
class Object;
/// <summary>
/// The Player object is the representation of the person
/// playing the game.
/// </summary>
class Player : public MovingEntity, public LivingEntity
{
protected:
	/// <summary>
	/// Number of lives until game over.
	/// </summary>
	int lives;
	/// <summary>
	/// How much damage the player deals when attacking.
	/// </summary>
	int attack;
	/// <summary>
	/// How much damage can a player absorb when being attacked.
	/// </summary>
	int defense;
	/// <summary>
	/// Player's items
	/// int is how many of that type of item player has (eg might have several times the same potion)
	/// </summary>
	unordered_map <string, int> inventory; 
 
	/// <summary>
	/// Horizontal offset of the infos sub window
	/// </summary>
	int infosX;
	/// <summary>
	/// Vertical ffset of the infos sub window
	/// </summary>
	int infosY;

	/// <summary>
	/// A Heart texture for player lives.
	/// </summary>
	Texture* heart;

public:
 
	~Player();
	/// <summary>
	/// Creates the player
	/// </summary>
	/// <param name="renderer"></param>
	/// <param name="lives"></param>
	/// <param name="attack"></param>
	/// <param name="defense"></param>
	/// <param name="startHealth"></param>
	/// <param name="startMoney"></param>
	/// <param name="startExp"></param>
	Player(RenderContext& renderer, Window& main, int lives = 3, int attack = 5, int defense = 0, int startHealth = 100, int startMoney = 0, int startExp = 0);

	/// <summary>
	/// Instant kill
	/// </summary>
	virtual void kill();

	/* Rendering management */
	virtual void render(RenderContext& renderer, int offsetX = 0, int offsetY = 0);

	/* Time management */
	virtual void tick(int time, GAME* game);

	/// <summary>
	/// When a key is pushed on the keyboard.
	/// </summary>
	/// <param name="ea"></param>
	virtual void onKeyDown(GAME* game);

	/// <summary>
	/// 
	/// </summary>
	void attackMonsters(Room&);

	/// <summary>
	/// 
	/// </summary>
	/// <param name="exp"></param>
	virtual void getExperience(int exp);

	/// <summary>
	/// 
	/// </summary>
	/// <param name="n"></param>
	virtual void getCoins(int n);

	/// <summary>
	/// 
	/// </summary>
	/// <param name=""></param>
	/// <param name=""></param>
	/// <returns></returns>
	bool isInAttackRange(int, int);
	/// <summary>
	/// 
	/// </summary>
	/// <returns></returns>
	int getAttack();
	/// <summary>
	/// 
	/// </summary>
	/// <returns></returns>
	int getDefense();

	/// <summary>
	/// Adds count times the item to a player's inventory.
	/// </summary>
	/// <param name="item"></param>
	/// <param name="count"></param>
	void pickUpObject(Object obj, int count = 1);

	/// <summary>
	/// Tells us whether the player has a particular item or not.
	/// </summary>
	/// <param name="itemId"></param>
	/// <returns></returns>
	bool hasObject(string objId);
	/// <summary>
	/// Tells us whether the player has a particular item or not.
	/// </summary>
	/// <param name="item"></param>
	/// <returns></returns>
	bool hasObject(Object obj);
};

#endif
