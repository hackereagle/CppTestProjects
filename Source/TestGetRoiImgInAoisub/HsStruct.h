#ifndef _HSSTRUCT_H_
#define _HSSTRUCT_H_

const int WINDB_PARAM = 64 + 1;
const int WINDB_PARAM_DOUBLE = 1 + 1;
//#define WINDB_PARAM 60
#define COND_COUNT 4
#define COND1_DSPCNT 4

class enumLineSealInspectPosition
{
public:
	static const long
	//Center = 0,
	Top = 1,
	Bottom = 2,
	Left = 3,
	Right = 4,
	All = 0;
};

class enumPosition
{
public:
	static const long
	Top = 0,
	Bottom = 1,
	Left = 2,
	Right = 3;
};

typedef struct 
{
    long ChipNo;
    long WinNo;
	long Distance;
    long Direction; 
    long Seal_1_X;
    long Seal_1_Y;
    long Seal_2_X;
    long Seal_2_Y;
    long SealCenter_X;
    long SealCenter_Y;
    long Baseline_1_X;
    long Baseline_1_Y;
    long Baseline_2_X;
    long Baseline_2_Y;
    long BaselineCenter_X;
    long BaselineCenter_Y;
}SealShiftUsingBaselineResult;

typedef struct {
    long ChipNo;
    long ScanIndex;
    long Distance;
    long Direction; //0: X, 1: Y
} SealShiftResultType;

typedef struct{
	long NuzzleNo;
	long WinNo;
	long ChipNo;
	long Position;
	long CamUnit;
	long X;
	long Y;
} typePositionForSealShift;

typedef struct
{
	typePositionForSealShift Center[2];
}TwoCenterStruct;

typedef struct {
	long id;
	long PUnit;
	long chip;
	long no;
	long Left;
	long Top;
	long width;
	long height;
	long SkipLRng;
	long SkipRRng;
	long size;
	long padjx; // SealHeadID2
	long padjy; // ModelNo
	long wp;
	long wpl;
	long ladj; // ChipID2
	long dsp1;
	long dsp12; // SealPosition
	long slice1p;
	long slice1n;
	long dsp2;
	long slice2p;
	long slice2n;
	long siz_def[8];
	long ng_def[8];
	long fuse_h;
	long fuse_v;
	long param[WINDB_PARAM];
	//double paramDouble[WINDB_PARAM_DOUBLE];
	//long SealLocateMethod;
	long id_AB;
}wdb_type;

typedef struct{
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
	long ChipNo;
	long SealHead;
}hole_type;

typedef struct{
	long size[ COND_COUNT ][ COND1_DSPCNT ];
	long OLMS_cnt[ COND_COUNT][ COND1_DSPCNT ];

}condw_type;

typedef struct{
	long data[COND_COUNT][COND1_DSPCNT];
}OLMS_type;

typedef struct{
	unsigned char *Src;
	int Width;
	int Height;
} ImageParam;

typedef struct{
	long PeakUBound;
	long PeakLBound;
	long DXUBound;
	long DXLBound;
	long DYUBound;
	long DYLBound;
	long SizeUBound;
	long SizeLBound;
}DefectSelectUnitType;


typedef struct{
	bool Enable;
	long UnitNum;
	DefectSelectUnitType DefectSelectUnit[50];
} DefectSelectSettingType;

typedef struct{
	bool DefectFull;
	bool InspOverTime;
	long OMPProc;
	long UseDoubleSlice;
	DefectSelectSettingType *DefectSelectSetting;
	long CutImgWidth;
	long CutImgHeight;
	long SoftwareFilter;
	long MaxImgBack;
}InspParamSetting;


enum WdbIDType{
	win_del			=	-1,      
	wid_none		=	0 ,     
	wid_inspect		=	1 ,
	wid_mark		=	2 ,  
	wid_seal		=	3 ,
	wid_chk_area	=	5 ,
	wid_chk_edge	=	6 ,
	wid_bm			=	7 ,     
	wid_prf			=	8 ,   
	wid_alignment	=	9 ,
	wid_daikei		=	10,   
	wid_musi		=	11,    
	wid_chk_light	=	12,
	wid_count		=	13,    
	wid_origin		=	14, 
	wid_AB			=	15,    
	wid_Mask		=	17
};

inline void SET_B32(long *var, long bit)
{
	*var = *var | (1<<bit);
}
inline void RST_B32(long *var, long bit)
{
	long temp = 0;
	for(int i=0;i<32;i++)
	{
		if(i!=bit)
			SET_B32(&temp,i);
	}
	*var = (*var) & temp;
}
inline long GET_B32(long var, long bit)
{
	return (var>>bit) & 1;
}

class enumCornerParameter
{	
public:
	static const long
	WidthInspectEnable = 31,
	Position = 32,
	NewMethodEnable = 33,
	RB_ChipNo = 34,
    LB_ChipNo = 35,
    RT_ChipNo = 36,
    LT_ChipNo = 37,
	ChipID = 38,
	SealHeadID = 39,
	SealHeadID2 = 40,
	ModelNo = 41,
	ChipID2 = 42,
	SealPosition = 43,
	SaveProcessImageEnable = 44;
};

class enumWinType
{
public:
	static const long Particle = 0,
	CornerSeal = -1,
	SealWidth = -2,
	DummySeal = -3,
	MarkForSealShift = -4,
	SealForSealShift = -5,
	DummyCornerSeal = -6,
	SealShiftUsingBlackLine = -7,
	Crack = -8,
	LineSeal = -9,
	TriggerDelayAdjust = -10,
	CSOT_T3_Seal_Corner_Inspect = -11,
    CSOT_T3_Seal_Line_Inspect = -12,
	AutoSeal = -30,
	SealAu = 511,
	HVAAu = 512;
};

class enumDefectType
{	
public:
	static const long Particle = 0,
	SealBreak = 1,
	SealThin = 2,
	SealThick = 3,
	HVAAuMiss = 4,
	HVAAuSmall = 5,
	HVAAuBig = 6,
	SealAuMiss = 7,
	SealAuSmall = 8,
	SealAuBig = 9,
	DummySealThick = 10,
	CornerSealBreak = 11,
	CornerSealThin = 12,
	CornerSealThick = 13,
	Chipping = 14,
	Crack = 15,
	Mura = 16,
	DummySealBreak = 17,
	DummySealThin = 18,
	CornerChipping = 19;
};

class enumSealParameter
{	
public:
	static const long
	DummySealPosition = 1,
	NuzzleNo = 2,
	Direction = 3,
	Position = 4,
	StandarWidth = 5,
	SealStyle = 6,	//0: Single, 1: Paired, 2: Overlap
	CornerMaxWidth = 7,
	CornerMinWidth = 8,
    MaxDefectImage = 11,
	LeftOrTop_ChipNo = 19,
	RightOrBottom_ChipNo = 20,
	CornerPosition = 21,
    DummyPosition = 22,
    UpLeftAttachedSealWidthUpperLimit = 23,
    UpLeftAttachedSealWidthLowerLimit = 24,
    RightBottomAttachedSealWidthUpperLimit = 25,
    RightBottomAttachedSealWidthLowerLimit = 26,
	SealAttachedWithoutCorner = 27,
	PositionForSealAttachedWithoutCorner = 28;
};

#endif

