#pragma once
enum class Layer
{
	DEFAULT,
	BACKGROUND,
	// 밑에 변경 가능
	PLAYER,
	ENEMY,
	PROJECTILE,
	Weapon,
	Boom,
	END
};

enum class PenType
{
	RED, GREEN, END
};

enum class BrushType
{
	HOLLOW, RED, GREEN, END
};

enum class FontType
{
	UI, TITLE, END
};

enum class PlayMode
{
	Once, Loop, Counted
};

enum class TurnType
{
	Select,
	Play,
	Waiting,
	GameEnd,

	Player1,
	Player2,
};

enum class CanvasType
{
	Title,
	InGame,
	Tutorial,
	Credit
};