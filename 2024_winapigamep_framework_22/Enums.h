#pragma once
enum class LAYER
{
	DEFAULT = 0,
	BACKGROUND,
	EMPTY_TILE,
	OBJECT_TILE,
	ENEMY,
	UI,
	END
};

enum class OBJ_TYPE
{
	NONE = 0,
	MAIN,
	EMPTY,
	NORMAL,
	STONE,
	//WALL
};

enum class GAME_STATE
{
	INIT = 0,
	PLAY,
	MOVE,
	OVER,
	STOP
};

typedef enum class CALCULATE
{
	PLUS = 0,
	MINUS,
	MULTIPLY,
	DIVIDE
} CALC;



enum class PEN_TYPE
{
	HOLLOW, RED, GREEN,
	BLUE, YELLOW, END
};

enum class BRUSH_TYPE
{
	HOLLOW, RED, GREEN,
	BLUE, YELLOW, END
};


enum class EVENT_TYPE
{
	CREATE_OBJECT,
	DELETE_OBJECT,
	SCENE_CHANGE,
	END,
};
