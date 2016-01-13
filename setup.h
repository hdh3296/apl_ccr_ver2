
#include	"AllCommom.h"

#define 	dFW_VERSION		1
#define     dDuty_Cnt		40
#define     dDuty_Rate		100
#define		dSETMODE_SEL	0
/*
#define     dSET_VAL_DAY_L	0xd0 // 2000
#define     dSET_VAL_DAY_H	0x07

#define     dSET_VAL_TWL_L	0xe8 // 1000
#define     dSET_VAL_TWL_H	0x03

#define     dSET_VAL_NIG_L	0x64 // 100	
#define     dSET_VAL_NIG_H 	0x00

#define     dMaxSetA_Day_L	0x88 // 5000
#define     dMaxSetA_Day_H	0x13

#define     dMaxSetA_Eve_L	0xd0 // 2000
#define     dMaxSetA_Eve_H	0x07

#define     dMaxSetA_Nig_L	0xe8 // 1000
#define     dMaxSetA_Nig_H	0x03
*/
#define     dSET_VAL_DAY_L	0xd0 // 2000
#define     dSET_VAL_DAY_H	0x07
	
#define     dSET_VAL_TWL_L	0xd2 // 2000
#define     dSET_VAL_TWL_H	0x0f
	
#define     dSET_VAL_NIG_L	0x64 // 100	
#define     dSET_VAL_NIG_H 	0x00
	
#define     dMaxSetA_Day_L	0x88 // 5000
#define     dMaxSetA_Day_H	0x13
	
#define     dMaxSetA_Eve_L	0x88 // 5000
#define     dMaxSetA_Eve_H	0x13
	
#define     dMaxSetA_Nig_L	0xe8 // 1000
#define     dMaxSetA_Nig_H	0x03





extern	unsigned int FlashBlockRd(unsigned int BlkNm);
extern	unsigned int FlashBlockWr(unsigned int BlkNm); 


extern	volatile const unsigned char information[];
extern	unsigned char new_value[64];


// Flash Block 영역 주소 
#define	ByteData001	0
#define	ByteData002	1
#define	ByteData003	2
#define	ByteData004	3
#define	ByteData005	4
#define	ByteData006	5
#define	ByteData007	6
#define	ByteData008	7
#define	ByteData009	8
#define	ByteData010	9
#define	ByteData011	10
#define	ByteData012	11
#define	ByteData013	12
#define	ByteData014	13
#define	ByteData015	14
#define	ByteData016	15
#define	ByteData017	16
#define	ByteData018	17
#define	ByteData019	18
#define	ByteData020	19
#define	ByteData021	20
#define	ByteData022	21
#define	ByteData023	22
#define	ByteData024	23
#define	ByteData025	24
#define	ByteData026	25
#define	ByteData027	26
#define	ByteData028	27
#define	ByteData029	28
#define	ByteData030	29
#define	ByteData031	30
#define	ByteData032	31
#define	ByteData033	32
#define	ByteData034	33
#define	ByteData035	34
#define	ByteData036	35
#define	ByteData037	36
#define	ByteData038	37
#define	ByteData039	38
#define	ByteData040	39
#define	ByteData041	40
#define	ByteData042	41
#define	ByteData043	42
#define	ByteData044	43
#define	ByteData045	44
#define	ByteData046	45
#define	ByteData047	46
#define	ByteData048	47
#define	ByteData049	48
#define	ByteData050	49
#define	ByteData051	50
#define	ByteData052	51
#define	ByteData053	52
#define	ByteData054	53
#define	ByteData055	54
#define	ByteData056	55
#define	ByteData057	56
#define	ByteData058	57
#define	ByteData059	58
#define	ByteData060	59
#define	ByteData061	60
#define	ByteData062	61
#define	ByteData063	62
#define	ByteData064	63
#define	ByteData065	64
#define	ByteData066	65
#define	ByteData067	66
#define	ByteData068	67
#define	ByteData069	68
#define	ByteData070	69
#define	ByteData071	70
#define	ByteData072	71
#define	ByteData073	72
#define	ByteData074	73
#define	ByteData075	74
#define	ByteData076	75
#define	ByteData077	76
#define	ByteData078	77
#define	ByteData079	78
#define	ByteData080	79
#define	ByteData081	80
#define	ByteData082	81
#define	ByteData083	82
#define	ByteData084	83
#define	ByteData085	84
#define	ByteData086	85
#define	ByteData087	86
#define	ByteData088	87
#define	ByteData089	88
#define	ByteData090	89
#define	ByteData091	90
#define	ByteData092	91
#define	ByteData093	92
#define	ByteData094	93
#define	ByteData095	94
#define	ByteData096	95
#define	ByteData097	96
#define	ByteData098	97
#define	ByteData099	98
#define	ByteData100	99
#define	ByteData101	100
#define	ByteData102	101
#define	ByteData103	102
#define	ByteData104	103
#define	ByteData105	104
#define	ByteData106	105
#define	ByteData107	106
#define	ByteData108	107
#define	ByteData109	108
#define	ByteData110	109
#define	ByteData111	110
#define	ByteData112	111
#define	ByteData113	112
#define	ByteData114	113
#define	ByteData115	114
#define	ByteData116	115
#define	ByteData117	116
#define	ByteData118	117
#define	ByteData119	118
#define	ByteData120	119
#define	ByteData121	120
#define	ByteData122	121
#define	ByteData123	122
#define	ByteData124	123
#define	ByteData125	124
#define	ByteData126	125
#define	ByteData127	126
#define	ByteData128	127
#define	ByteData129	128
#define	ByteData130	129
#define	ByteData131	130
#define	ByteData132	131
#define	ByteData133	132
#define	ByteData134	133
#define	ByteData135	134
#define	ByteData136	135
#define	ByteData137	136
#define	ByteData138	137
#define	ByteData139	138
#define	ByteData140	139
#define	ByteData141	140
#define	ByteData142	141
#define	ByteData143	142
#define	ByteData144	143
#define	ByteData145	144
#define	ByteData146	145
#define	ByteData147	146
#define	ByteData148	147
#define	ByteData149	148
#define	ByteData150	149
#define	ByteData151	150
#define	ByteData152	151
#define	ByteData153	152
#define	ByteData154	153
#define	ByteData155	154
#define	ByteData156	155
#define	ByteData157	156
#define	ByteData158	157
#define	ByteData159	158
#define	ByteData160	159
#define	ByteData161	160
#define	ByteData162	161
#define	ByteData163	162
#define	ByteData164	163
#define	ByteData165	164
#define	ByteData166	165
#define	ByteData167	166
#define	ByteData168	167
#define	ByteData169	168
#define	ByteData170	169
#define	ByteData171	170
#define	ByteData172	171
#define	ByteData173	172
#define	ByteData174	173
#define	ByteData175	174
#define	ByteData176	175
#define	ByteData177	176
#define	ByteData178	177
#define	ByteData179	178
#define	ByteData180	179
#define	ByteData181	180
#define	ByteData182	181
#define	ByteData183	182
#define	ByteData184	183
#define	ByteData185	184
#define	ByteData186	185
#define	ByteData187	186
#define	ByteData188	187
#define	ByteData189	188
#define	ByteData190	189
#define	ByteData191	190
#define	ByteData192	191
#define	ByteData193	192
#define	ByteData194	193
#define	ByteData195	194
#define	ByteData196	195
#define	ByteData197	196
#define	ByteData198	197
#define	ByteData199	198
#define	ByteData200	199
#define	ByteData201	200
#define	ByteData202	201
#define	ByteData203	202
#define	ByteData204	203
#define	ByteData205	204
#define	ByteData206	205
#define	ByteData207	206
#define	ByteData208	207
#define	ByteData209	208
#define	ByteData210	209
#define	ByteData211	210
#define	ByteData212	211
#define	ByteData213	212
#define	ByteData214	213
#define	ByteData215	214
#define	ByteData216	215
#define	ByteData217	216
#define	ByteData218	217
#define	ByteData219	218
#define	ByteData220	219
#define	ByteData221	220
#define	ByteData222	221
#define	ByteData223	222
#define	ByteData224	223
#define	ByteData225	224
#define	ByteData226	225
#define	ByteData227	226
#define	ByteData228	227
#define	ByteData229	228
#define	ByteData230	229
#define	ByteData231	230
#define	ByteData232	231
#define	ByteData233	232
#define	ByteData234	233
#define	ByteData235	234
#define	ByteData236	235
#define	ByteData237	236
#define	ByteData238	237
#define	ByteData239	238
#define	ByteData240	239
#define	ByteData241	240
#define	ByteData242	241
#define	ByteData243	242
#define	ByteData244	243
#define	ByteData245	244
#define	ByteData246	245
#define	ByteData247	246
#define	ByteData248	247
#define	ByteData249	248
#define	ByteData250	249
#define	ByteData251	250
#define	ByteData252	251
#define	ByteData253	252
#define	ByteData254	253
#define	ByteData255	254
#define	ByteData256	255





#define	IntzData001		ByteData001
#define	IntzData002		ByteData003
#define	IntzData003		ByteData005
#define	IntzData004		ByteData007
#define	IntzData005		ByteData009
#define	IntzData006		ByteData011
#define	IntzData007		ByteData013
#define	IntzData008		ByteData015
#define	IntzData009		ByteData017
#define	IntzData010		ByteData019
#define	IntzData011		ByteData021
#define	IntzData012		ByteData023
#define	IntzData013		ByteData025
#define	IntzData014		ByteData027
#define	IntzData015		ByteData029
#define	IntzData016		ByteData031
#define	IntzData017		ByteData033
#define	IntzData018		ByteData035
#define	IntzData019		ByteData037
#define	IntzData020		ByteData039
#define	IntzData021		ByteData041
#define	IntzData022		ByteData043
#define	IntzData023		ByteData045
#define	IntzData024		ByteData047
#define	IntzData025		ByteData049
#define	IntzData026		ByteData051
#define	IntzData027		ByteData053
#define	IntzData028		ByteData055
#define	IntzData029		ByteData057
#define	IntzData030		ByteData059
#define	IntzData031		ByteData061
#define	IntzData032		ByteData063
#define	IntzData033		ByteData065
#define	IntzData034		ByteData067
#define	IntzData035		ByteData069
#define	IntzData036		ByteData071
#define	IntzData037		ByteData073
#define	IntzData038		ByteData075
#define	IntzData039		ByteData077
#define	IntzData040		ByteData079
#define	IntzData041		ByteData081
#define	IntzData042		ByteData083
#define	IntzData043		ByteData084
#define	IntzData044		ByteData087
#define	IntzData045		ByteData089
#define	IntzData046		ByteData091
#define	IntzData047		ByteData093
#define	IntzData048		ByteData095
#define	IntzData049		ByteData097
#define	IntzData050		ByteData099
#define	IntzData051		ByteData101
#define	IntzData052		ByteData103
#define	IntzData053		ByteData105
#define	IntzData054		ByteData107
#define	IntzData055		ByteData109
#define	IntzData056		ByteData111
#define	IntzData057		ByteData113
#define	IntzData058		ByteData115
#define	IntzData059		ByteData117
#define	IntzData060		ByteData119
#define	IntzData061		ByteData121
#define	IntzData062		ByteData123
#define	IntzData063		ByteData125
#define	IntzData064		ByteData127
#define	IntzData065		ByteData129
#define	IntzData066		ByteData131
#define	IntzData067		ByteData133
#define	IntzData068		ByteData135
#define	IntzData069		ByteData137
#define	IntzData070		ByteData139
#define	IntzData071		ByteData141
#define	IntzData072		ByteData143
#define	IntzData073		ByteData145
#define	IntzData074		ByteData147
#define	IntzData075		ByteData149
#define	IntzData076		ByteData151
#define	IntzData077		ByteData153
#define	IntzData078		ByteData155
#define	IntzData079		ByteData157
#define	IntzData080		ByteData159
#define	IntzData081		ByteData161
#define	IntzData082		ByteData163
#define	IntzData083		ByteData165
#define	IntzData084		ByteData167
#define	IntzData085		ByteData169
#define	IntzData086		ByteData171
#define	IntzData087		ByteData173
#define	IntzData088		ByteData175
#define	IntzData089		ByteData177
#define	IntzData090		ByteData179
#define	IntzData091		ByteData181
#define	IntzData092		ByteData183
#define	IntzData093		ByteData185
#define	IntzData094		ByteData187
#define	IntzData095		ByteData189
#define	IntzData096		ByteData191
#define	IntzData097		ByteData193
#define	IntzData098		ByteData195
#define	IntzData099		ByteData197
#define	IntzData100		ByteData199
#define	IntzData101		ByteData201
#define	IntzData102		ByteData203
#define	IntzData103		ByteData205
#define	IntzData104		ByteData207
#define	IntzData105		ByteData209
#define	IntzData106		ByteData211
#define	IntzData107		ByteData213
#define	IntzData108		ByteData215
#define	IntzData109		ByteData217
#define	IntzData110		ByteData219
#define	IntzData111		ByteData221
#define	IntzData112		ByteData223
#define	IntzData113		ByteData225
#define	IntzData114		ByteData227
#define	IntzData115		ByteData229
#define	IntzData116		ByteData231
#define	IntzData117		ByteData233
#define	IntzData118		ByteData235
#define	IntzData119		ByteData237
#define	IntzData120		ByteData239
#define	IntzData121		ByteData241
#define	IntzData122		ByteData243
#define	IntzData123		ByteData245
#define	IntzData124		ByteData247
#define	IntzData125		ByteData249
#define	IntzData126		ByteData251
#define	IntzData127		ByteData253
#define	IntzData128		ByteData255



#define	longData001		ByteData001
#define	longData002		ByteData005
#define	longData003		ByteData009
#define	longData004		ByteData013
#define	longData005		ByteData017
#define	longData006		ByteData021
#define	longData007		ByteData025
#define	longData008		ByteData029
#define	longData009		ByteData033
#define	longData010		ByteData037
#define	longData011		ByteData041
#define	longData012		ByteData045
#define	longData013		ByteData049
#define	longData014		ByteData053
#define	longData015		ByteData057
#define	longData016		ByteData061
#define	longData017		ByteData065
#define	longData018		ByteData069
#define	longData019		ByteData073
#define	longData020		ByteData077
#define	longData021		ByteData081
#define	longData022		ByteData085
#define	longData023		ByteData089
#define	longData024		ByteData093
#define	longData025		ByteData097
#define	longData026		ByteData101
#define	longData027		ByteData105
#define	longData028		ByteData109
#define	longData029		ByteData113
#define	longData030		ByteData117
#define	longData031		ByteData121
#define	longData032		ByteData125
#define	longData033		ByteData129
#define	longData034		ByteData133
#define	longData035		ByteData137
#define	longData036		ByteData141
#define	longData037		ByteData145
#define	longData038		ByteData149
#define	longData039		ByteData153
#define	longData040		ByteData157
#define	longData041		ByteData161
#define	longData042		ByteData165
#define	longData043		ByteData169
#define	longData044		ByteData173
#define	longData045		ByteData177
#define	longData046		ByteData181
#define	longData047		ByteData185
#define	longData048		ByteData189
#define	longData049		ByteData193
#define	longData050		ByteData197
#define	longData051		ByteData201
#define	longData052		ByteData205
#define	longData053		ByteData209
#define	longData054		ByteData213
#define	longData055		ByteData217
#define	longData056		ByteData221
#define	longData057		ByteData225
#define	longData058		ByteData229
#define	longData059		ByteData233
#define	longData060		ByteData237
#define	longData061		ByteData241
#define	longData062		ByteData245
#define	longData063		ByteData249
#define	longData064		ByteData253

// 기본  
#define BLOCK_VERSION			ByteData001 // 1
#define BLOCK_DUTY_CNT 			ByteData002	// 2	
#define BLOCK_DUTY_RATE			ByteData003	// 3
#define BLOCK_SETMODE_SEL		ByteData004	// 4

#define BLOCK_SET_VALUE_DAY		IntzData003	// 5, 6
#define BLOCK_SET_VALUE_TWL		IntzData004	// 7, 8
#define BLOCK_SET_VALUE_NIG		IntzData005	// 9, 10
#define BLOCK_MaxSetDAY			IntzData006	// 11, 12
#define BLOCK_MaxSetTWL			IntzData007	// 13, 14
#define BLOCK_MaxSetNIG			IntzData008	// 15, 16
// 기타 
#define BLOCK_SET_DUTYCYCLE_DAY	IntzData009	// 
#define BLOCK_SET_DUTYCYCLE_TWL	IntzData010	// 
#define BLOCK_SET_DUTYCYCLE_NIG	IntzData011	//





