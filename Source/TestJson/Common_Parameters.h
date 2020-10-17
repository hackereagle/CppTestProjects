#pragma once
#define WINDB_PARAM 65

typedef struct {
	unsigned char *Src;
	int Width;
	int Height;
}ImageParam;

typedef struct {
	long Left;
	long Top;
	long width;
	long height;
	long param[WINDB_PARAM];
}wdb_type;

typedef struct {
	long hole_win;
	long hole_winsum;
	long hole_ptype;
	long hole_stype;
	long hole_size;
	long hole_level;
	long hole_x;
	long hole_y;
	long hole_sx;
	long hole_sy;
	long hole_dx;
	long hole_dy;
}hole_type;

// ========== here are data relative finding alignment mark algorithm. ============
enum FindMarkParam
{
	MarkScore,
    Algorithm,
    TemplateMatch_Cost,
    TemplateMatch_Method,
    showResult_Mark
};

enum FindMarkAlgo
{
	WaferAlignment_usingTemplateMatch,
	WaferAlignment_usingORB,
	ZComputerAlignment
};

typedef struct {
	float Cx;
	float Cy;
	float angle; // degree
	int width;
	int height;
}Mark;

// ========== here are data relative SEM astigmatism and auto focus algorithm. ============
enum SEM_Algo
{
	astigmatismCorelation,
	autoFocus
};

enum SemParam
{
	threshold,
	showResult,
	algorithm
};

typedef struct {
    float theta; // degree
    float major_stigma;
    float minor_stigma;
	float major_len;
	float minor_len;
	int points_num;
}StigmaInfo;

