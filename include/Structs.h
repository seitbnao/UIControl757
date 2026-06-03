/*
*   Copyright (C) {2019.1}  {Djunio - SeiTbNao - Wed}
*
*   This program is free software: you can redistribute it and/or modify
*   it under the terms of the GNU General Public License as published by
*   the Free Software Foundation, either version 3 of the License, or
*   (at your option) any later version.
*
*   This program is distributed in the hope that it will be useful,
*   but WITHOUT ANY WARRANTY; without even the implied warranty of
*   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
*   GNU General Public License for more details.
*
*   You should have received a copy of the GNU General Public License
*   along with this program.  If not, see [http://www.gnu.org/licenses/].
*
*/
#pragma once


struct	 MSG_STANDARD
{
	    short		  Size;			
		char		  KeyWord;		
		char		  CheckSum;		
		short		  Type;			
		short		  ID;			
		unsigned int  ClientTick;
};


struct STRUCT_ITEM
{
	short sIndex;
	union
	{
		short sValue;

		struct
		{
			unsigned char cEffect;
			unsigned char cValue;
		};

	}stEffect[3];
};

struct STRUCT_SCORE
{
	int Level;	 // The mob's level
	int Ac;		 // The mob's defense
	int Damage;   // The mob's damage force

	unsigned char  Merchant; // UNK
	unsigned char  AttackRun; // The mob's speed
	unsigned char  Direction;
	unsigned char  ChaosRate;

	int MaxHp;     // The max HP the mob can have
	int MaxMp;	  // The max MP the mob can have
	int Hp;		  // The current HP of the mob
	int Mp;		  // The current MP of the mob

	short		   Str;		  // The mob's strength points, affects it's attack power
	short		   Int;		  // The mob's intelligence points, affects it's skill attack powers and MP
	short		   Dex;		  // The mob's dexterity points, affects it's attack speed
	short		   Con;       // The mob's constitution points, affects it's HP

	short  Special[4]; // The mob's special points, affects it's skill tiers
};

struct STRUCT_MOB
{
	char		   MobName[16];	  // The name of the mob
	char		   Clan;		  // The clan the mob belongs to
	unsigned char  Merchant;	  // The mob's merchant ID
	unsigned short Guild;		  // The ID of the guild the mob belongs to
	unsigned char  Class;		  // The mobs class
	unsigned short  Rsv;
	unsigned char Quest;

	int			   Coin;		  // The ammount of coins the mob has

	long long   Exp;			  // The ammount of experience the mob has to level up

	short		   SPX;			 // The Y position saved by the stellar gem, to teleport the mob there when using warp scroll
	short		   SPY;			 // The Y position saved by the stellar gem, to teleport the mob there when using warp scroll

	STRUCT_SCORE   BaseScore;    // The base score of the mob 
	STRUCT_SCORE   CurrentScore; // The score the mob actually has

	STRUCT_ITEM    Equip[16];	 // The items the mob is wearing
	STRUCT_ITEM	   Carry[64];	 // The items the mob is carrying

	long LearnedSkill; // The skills the mob learned, divided into four categories (00 _ 00 _ 00 _ 00)

	unsigned int Magic;

	unsigned short ScoreBonus;   // The points the mob can use to increase score (Str, Int, Dex, Con)
	unsigned short SpecialBonus; // The points the mob can use to increase special, to increase effect of learned skills (score->Special[4])
	unsigned short SkillBonus;	 // The points the mob can use to buy skills

	unsigned char  Critical;	 // The chance the mob has to deliver critical hits
	unsigned char  SaveMana;	 // Uknown use, nomenclature of variable is correct to all current standards

	unsigned char  SkillBar[4];  // The skills saved on the first 4 slots of the skill bar

	unsigned char  GuildLevel;   // The mob's guuld level, used to define if it's a guild member or leader

	unsigned short  RegenHP;		 // UNK
	unsigned short  RegenMP;		 // UNK

	char  Resist[4];	 // The mob's resistencies, to fire / ice / thunder / magic

};

struct STRUCT_MOBEXTRA
{
	short ClassMaster;
	char  Citizen;

	int	  Fame;

	char  Soul;

	short MortalFace;

	struct
	{
		struct
		{
			char Newbie;//00_01_02_03_04  quest com quatro etapas
			char TerraMistica;//0 : não pegou a quest 1: pegou a quest e não concluiu 2: quest completa
			char MolarGargula;
			char PilulaOrc;

			char EMPTY[30];
		}Mortal;

		struct
		{
			char MortalSlot;
			char MortalLevel;

			char Level355;
			char Level370;

			char Cristal;//00_01_02_03_04 quest com quatro etapas

			char EMPTY[30];
		}Arch;

		struct
		{
			short ArchLevel;
			short CelestialLevel;
			short SubCelestialLevel;

			char Lv40;
			char Lv90;

			char Add120;
			char Add150;
			char Add180;
			char Add200;

			char Arcana;
			char Reset;

			char EMPTY[30];
		}Celestial;

		char Circle;
		char EMPTY[30];

	}QuestInfo;

	struct
	{
		int Class;

		long long   Exp;			  // The ammount of experience the mob has to level up

		short		   SPX;			 // The Y position saved by the stellar gem, to teleport the mob there when using warp scroll
		short		   SPY;			 // The Y position saved by the stellar gem, to teleport the mob there when using warp scroll

		STRUCT_SCORE   BaseScore;    // The base score of the mob 

		long LearnedSkill; // The skills the mob learned, divided into four categories (00 _ 00 _ 00 _ 00)


		unsigned short ScoreBonus;   // The points the mob can use to increase score (Str, Int, Dex, Con)
		unsigned short SpecialBonus; // The points the mob can use to increase special, to increase effect of learned skills (score->Special[4])
		unsigned short SkillBonus;	 // The points the mob can use to buy skills

		unsigned char  SkillBar1[4];  // The skills saved on the first 4 slots of the skill bar
		unsigned char  SkillBar2[16];  // The skills saved on the first 4 slots of the skill bar

		char Soul;
		char EMPTY[30];
	}SaveCelestial[2];

	time_t LastNT;
	int NT;

	int KefraTicket;

	time_t DivineEnd;

	unsigned int Hold;

	struct
	{
		long long Exp;
		int		  YearDay;
	}DayLog;

	struct
	{
		time_t LastTime;
		int Count;
	}DonateInfo;

	int EMPTY[9];
};

struct STRUCT_AFFECT
{
	unsigned char Type;
	unsigned char Value;
	unsigned short Level;
	unsigned int Time;
};

struct STRUCT_LEVELBONUS
{
	unsigned short Level;
	unsigned short ScoreBonus;   // The points the mob can use to increase score (Str, Int, Dex, Con)
	unsigned short SpecialBonus; // The points the mob can use to increase special, to increase effect of learned skills (score->Special[4])
	unsigned short SkillBonus;	 // The points the mob can use to buy skills
	unsigned short Ac;
};


struct STRUCT_SPELL
{
	int	SkillPoint;
	int	TargetType;
	int	ManaSpent;
	int	Delay;
	int	Range;
	int	InstanceType;
	int	InstanceValue;
	int	TickType;
	int	TickValue;
	int	AffectType;
	int	AffectValue;
	int	AffectTime;
	unsigned char Act[8];
	int	InstanceAttribute;
	int	TickAttribute;
	int	Aggressive;
	int	MaxTarget;
	int	bParty;
	int	AffectResist;
	int	Passive;
};

struct STRUCT_ITEMLIST
{
	char					Name[64];
	short				IndexMesh;
	short				IndexTexture;
	short				IndexVisualEffect;
	short				ReqLvl;
	short				ReqStr;
	short				ReqInt;
	short				ReqDex;
	short				ReqCon;

	struct
	{
		short sEffect;
		short sValue;

	} stEffect[12];

	int					Price; // 92
	short				nUnique; // 96
	short				nPos; // 98
	short				Extra; // 100
	short				Grade; // 102 1 = Normal 2 = Mistico = 3 Arcano 4 = Le
};

struct STRUCT_ITEMCARGO
{
	STRUCT_ITEM Item[128];
};