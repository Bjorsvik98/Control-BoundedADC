#ifndef COEFFICIENTS_H
#define COEFFICIENTS_H
#ifdef USE_MYSTDLIB
  #include "stdlib.h"
 #else
  #include <stdlib.h>
 #endif

#define DSR 1
#define K1 120
#define K2 120
#define K 240
#define samples 1024
#define H_Height 240
#define H_Width 7

const int32_t H[H_Height][H_Width] = {
{-94, -242, 49, 26, -10, -2, 1},
{32, -265, 35, 31, -9, -2, 1},
{170, -280, 18, 36, -8, -3, 1},
{313, -286, 0, 40, -5, -4, 1},
{458, -282, -21, 42, -3, -5, 1},
{598, -267, -43, 44, 0, -6, 0},
{729, -241, -65, 43, 2, -6, 0},
{845, -204, -87, 41, 5, -6, 0},
{941, -156, -107, 38, 9, -6, 0},
{1010, -98, -126, 32, 12, -6, 0},
{1048, -31, -141, 25, 15, -5, -1},
{1051, 42, -153, 17, 18, -5, -1},
{1015, 121, -160, 7, 21, -4, -2},
{939, 203, -162, -3, 23, -2, -2},
{821, 284, -157, -15, 24, -1, -2},
{663, 362, -147, -28, 24, 0, -3},
{466, 434, -130, -41, 24, 2, -3},
{234, 497, -107, -53, 23, 4, -3},
{-26, 546, -78, -64, 20, 5, -3},
{-309, 580, -44, -74, 17, 7, -3},
{-607, 596, -5, -82, 13, 9, -2},
{-908, 591, 37, -88, 7, 11, -2},
{-1203, 563, 83, -91, 2, 12, -1},
{-1480, 513, 129, -91, -4, 13, 0},
{-1727, 439, 175, -88, -11, 13, 0},
{-1933, 342, 218, -81, -18, 13, 0},
{-2086, 224, 258, -70, -25, 13, 1},
{-2175, 87, 291, -56, -32, 12, 2},
{-2193, -64, 316, -38, -38, 10, 3},
{-2131, -228, 332, -18, -43, 8, 4},
{-1985, -397, 338, 4, -48, 6, 5},
{-1752, -568, 331, 29, -50, 3, 5},
{-1435, -732, 311, 55, -51, 0, 6},
{-1036, -884, 278, 81, -51, -3, 6},
{-564, -1018, 232, 107, -48, -7, 6},
{-28, -1125, 173, 131, -44, -11, 6},
{555, -1201, 103, 152, -37, -15, 6},
{1172, -1239, 22, 170, -28, -19, 5},
{1800, -1235, -65, 183, -18, -22, 4},
{2417, -1185, -159, 190, -6, -25, 3},
{3001, -1086, -256, 191, 7, -27, 2},
{3526, -939, -352, 185, 21, -28, 0},
{3967, -744, -443, 171, 36, -29, -1},
{4302, -504, -527, 150, 51, -28, -3},
{4508, -224, -598, 122, 65, -26, -5},
{4566, 89, -654, 86, 78, -23, -7},
{4460, 427, -690, 44, 90, -19, -8},
{4180, 780, -704, -2, 99, -14, -10},
{3720, 1136, -694, -54, 105, -7, -12},
{3082, 1481, -657, -108, 108, 0, -13},
{2273, 1803, -592, -163, 107, 6, -14},
{1307, 2087, -500, -217, 103, 15, -14},
{207, 2320, -380, -268, 94, 23, -14},
{-999, 2487, -236, -313, 80, 31, -13},
{-2277, 2577, -70, -351, 63, 39, -12},
{-3585, 2580, 112, -380, 42, 46, -10},
{-4878, 2488, 308, -397, 17, 52, -8},
{-6106, 2295, 511, -401, -10, 57, -5},
{-7218, 2000, 712, -390, -40, 60, -1},
{-8161, 1604, 906, -364, -71, 61, 1},
{-8887, 1112, 1084, -323, -102, 59, 5},
{-9348, 535, 1238, -265, -133, 56, 9},
{-9503, -114, 1360, -193, -161, 50, 14},
{-9319, -819, 1442, -107, -186, 42, 17},
{-8771, -1558, 1480, -9, -206, 31, 21},
{-7846, -2306, 1465, 98, -220, 19, 24},
{-6545, -3037, 1395, 211, -228, 4, 27},
{-4881, -3722, 1267, 327, -229, -11, 29},
{-2883, -4332, 1080, 442, -220, -28, 30},
{-594, -4837, 836, 552, -203, -45, 30},
{1926, -5208, 538, 651, -177, -62, 29},
{4606, -5419, 193, 735, -143, -79, 26},
{7361, -5448, -191, 800, -99, -94, 23},
{10095, -5277, -605, 843, -49, -108, 18},
{12704, -4892, -1036, 858, 8, -118, 12},
{15078, -4289, -1469, 843, 70, -126, 6},
{17107, -3468, -1889, 796, 135, -129, -1},
{18682, -2439, -2279, 716, 202, -128, -9},
{19701, -1220, -2622, 602, 267, -122, -17},
{20072, 160, -2902, 455, 329, -112, -25},
{19719, 1670, -3102, 279, 384, -97, -34},
{18584, 3264, -3208, 75, 432, -77, -41},
{16633, 4893, -3206, -150, 468, -53, -48},
{13859, 6500, -3087, -392, 491, -24, -54},
{10283, 8025, -2843, -644, 500, 6, -58},
{5960, 9402, -2471, -897, 491, 40, -60},
{974, 10569, -1972, -1143, 466, 75, -61},
{-4554, 11460, -1351, -1372, 422, 110, -59},
{-10475, 12015, -617, -1577, 360, 144, -55},
{-16610, 12181, 214, -1747, 282, 176, -49},
{-22750, 11909, 1125, -1875, 187, 204, -41},
{-28667, 11164, 2093, -1953, 79, 227, -30},
{-34118, 9922, 3090, -1974, -40, 244, -18},
{-38845, 8173, 4087, -1933, -167, 253, -4},
{-42594, 5921, 5053, -1826, -297, 255, 10},
{-45110, 3188, 5954, -1654, -428, 248, 26},
{-46158, 14, 6757, -1416, -553, 232, 41},
{-45519, -3546, 7429, -1117, -669, 207, 57},
{-43010, -7423, 7939, -760, -771, 173, 71},
{-38484, -11529, 8261, -356, -854, 131, 83},
{-31840, -15765, 8372, 86, -914, 82, 94},
{-23030, -20021, 8255, 555, -948, 27, 101},
{-12062, -24181, 7898, 1037, -953, -31, 106},
{996, -28121, 7297, 1516, -928, -93, 107},
{16015, -31719, 6457, 1977, -871, -154, 104},
{32802, -34857, 5390, 2404, -783, -214, 96},
{51107, -37423, 4114, 2782, -665, -268, 86},
{70626, -39316, 2659, 3096, -519, -316, 71},
{91004, -40450, 1057, 3332, -351, -356, 53},
{111850, -40760, -648, 3480, -164, -384, 32},
{132738, -40199, -2413, 3531, 35, -400, 9},
{153227, -38746, -4187, 3480, 241, -402, -14},
{172867, -36405, -5919, 3326, 445, -390, -39},
{191216, -33205, -7557, 3069, 642, -364, -63},
{207848, -29202, -9050, 2716, 822, -324, -85},
{222373, -24477, -10351, 2276, 980, -272, -104},
{234443, -19133, -11419, 1761, 1110, -208, -120},
{243765, -13293, -12218, 1187, 1205, -136, -132},
{250110, -7095, -12722, 571, 1261, -58, -139},
{253323, -692, -12913, -66, 1278, 22, -140},
{253323, 5758, -12784, -705, 1252, 102, -136},
{250110, 12098, -12338, -1323, 1186, 179, -126},
{243765, 18168, -11589, -1902, 1081, 249, -112},
{234443, 23822, -10560, -2421, 942, 310, -93},
{222373, 28925, -9283, -2866, 775, 359, -71},
{207848, 33359, -7799, -3223, 585, 394, -47},
{191216, 37029, -6152, -3481, 380, 415, -22},
{172867, 39862, -4394, -3636, 167, 421, 3},
{153227, 41810, -2576, -3684, -45, 413, 28},
{132738, 42854, -752, -3626, -251, 390, 51},
{111850, 42997, 1026, -3469, -442, 355, 72},
{91004, 42270, 2712, -3219, -613, 309, 89},
{70626, 40728, 4260, -2888, -759, 254, 102},
{51107, 38445, 5632, -2490, -876, 193, 111},
{32802, 35513, 6797, -2039, -961, 128, 116},
{16015, 32039, 7732, -1552, -1013, 61, 116},
{996, 28141, 8422, -1045, -1031, -3, 113},
{-12062, 23939, 8860, -534, -1017, -65, 105},
{-23030, 19561, 9046, -36, -972, -122, 95},
{-31840, 15128, 8990, 434, -901, -172, 81},
{-38484, 10759, 8707, 865, -805, -214, 66},
{-43010, 6563, 8219, 1245, -691, -246, 49},
{-45519, 2636, 7552, 1566, -562, -269, 32},
{-46158, -937, 6738, 1821, -424, -281, 14},
{-45110, -4091, 5809, 2007, -281, -284, -2},
{-42594, -6773, 4799, 2122, -139, -278, -18},
{-38845, -8950, 3745, 2168, -3, -263, -32},
{-34118, -10605, 2679, 2147, 124, -240, -44},
{-28667, -11738, 1634, 2065, 240, -212, -54},
{-22750, -12364, 639, 1928, 339, -178, -62},
{-16610, -12513, -279, 1746, 422, -141, -67},
{-10475, -12225, -1102, 1526, 485, -103, -69},
{-4554, -11551, -1811, 1278, 528, -63, -69},
{974, -10549, -2395, 1012, 552, -24, -67},
{5960, -9283, -2845, 737, 557, 11, -63},
{10283, -7819, -3160, 464, 544, 45, -57},
{13859, -6223, -3342, 199, 515, 74, -49},
{16633, -4560, -3395, -47, 472, 99, -41},
{18584, -2892, -3331, -271, 418, 119, -31},
{19719, -1275, -3161, -467, 355, 134, -22},
{20072, 240, -2901, -630, 285, 143, -12},
{19701, 1615, -2566, -758, 213, 147, -3},
{18682, 2813, -2174, -849, 139, 145, 5},
{17107, 3810, -1743, -905, 67, 139, 13},
{15078, 4590, -1291, -926, 0, 129, 20},
{12704, 5146, -835, -914, -62, 116, 25},
{10095, 5479, -390, -873, -117, 100, 30},
{7361, 5596, 29, -805, -164, 82, 33},
{4606, 5512, 411, -717, -201, 62, 34},
{1926, 5246, 747, -612, -228, 43, 35},
{-594, 4825, 1029, -496, -245, 23, 34},
{-2883, 4274, 1252, -372, -253, 4, 32},
{-4881, 3625, 1414, -247, -252, -12, 29},
{-6545, 2906, 1514, -124, -242, -28, 26},
{-7846, 2149, 1554, -7, -225, -41, 22},
{-8771, 1382, 1538, 99, -202, -52, 17},
{-9319, 633, 1472, 194, -174, -60, 12},
{-9503, -75, 1360, 275, -142, -65, 8},
{-9348, -722, 1212, 339, -108, -68, 3},
{-8887, -1290, 1036, 387, -74, -68, 0},
{-8161, -1767, 839, 417, -40, -66, -4},
{-7218, -2144, 629, 431, -7, -62, -8},
{-6106, -2418, 416, 429, 22, -56, -11},
{-4878, -2586, 207, 412, 49, -49, -13},
{-3585, -2652, 8, 383, 72, -41, -15},
{-2277, -2623, -174, 344, 91, -32, -16},
{-999, -2507, -336, 296, 105, -22, -16},
{207, -2315, -473, 242, 114, -13, -16},
{1307, -2061, -583, 184, 119, -4, -15},
{2273, -1758, -663, 125, 119, 4, -14},
{3082, -1420, -715, 67, 115, 11, -12},
{3720, -1061, -738, 11, 108, 18, -10},
{4180, -696, -734, -40, 97, 23, -8},
{4460, -338, -705, -86, 84, 28, -6},
{4566, 1, -655, -125, 70, 30, -4},
{4508, 314, -587, -157, 54, 32, -2},
{4302, 590, -505, -181, 37, 32, 0},
{3967, 823, -412, -197, 21, 32, 2},
{3526, 1010, -313, -205, 5, 30, 3},
{3001, 1146, -211, -205, -8, 27, 5},
{2417, 1233, -111, -198, -21, 24, 6},
{1800, 1271, -15, -185, -33, 20, 7},
{1172, 1262, 73, -167, -42, 15, 7},
{555, 1212, 151, -145, -49, 11, 7},
{-28, 1125, 219, -119, -54, 7, 7},
{-564, 1006, 273, -92, -56, 2, 7},
{-1036, 864, 313, -64, -57, -1, 7},
{-1435, 703, 340, -35, -55, -5, 6},
{-1752, 532, 353, -8, -52, -8, 5},
{-1985, 358, 353, 16, -47, -11, 4},
{-2131, 185, 341, 38, -41, -13, 3},
{-2193, 20, 318, 57, -34, -14, 2},
{-2175, -131, 286, 73, -27, -15, 1},
{-2086, -266, 248, 85, -19, -15, 0},
{-1933, -381, 204, 93, -11, -15, 0},
{-1727, -473, 157, 98, -3, -14, -1},
{-1480, -542, 108, 98, 3, -13, -2},
{-1203, -587, 60, 95, 9, -11, -2},
{-908, -609, 13, 90, 15, -10, -3},
{-607, -608, -29, 81, 19, -7, -3},
{-309, -586, -67, 71, 23, -5, -3},
{-26, -547, -100, 59, 25, -3, -3},
{234, -492, -127, 46, 27, -1, -3},
{466, -425, -148, 32, 27, 0, -3},
{663, -349, -161, 19, 26, 2, -3},
{821, -268, -169, 6, 25, 3, -2},
{939, -184, -169, -6, 23, 5, -2},
{1015, -101, -164, -17, 20, 6, -1},
{1051, -21, -154, -26, 17, 6, -1},
{1048, 52, -140, -34, 13, 7, 0},
{1010, 118, -122, -40, 9, 7, 0},
{941, 175, -101, -44, 6, 7, 0},
{845, 221, -78, -46, 2, 7, 0},
{729, 256, -55, -47, -1, 6, 1},
{598, 279, -32, -46, -4, 5, 1},
{458, 291, -9, -43, -6, 4, 1},
{313, 292, 11, -39, -9, 3, 1},
{170, 283, 29, -34, -10, 2, 1},
{32, 266, 46, -29, -12, 1, 1},
{-94, 240, 59, -23, -12, 0, 1},};

#define S_Height 1024
#define S_Width 7

const int32_t S[S_Height][S_Width] = {
{0, 0, 0, 0, 0, 0, 0},
{1, 1, 0, 0, 0, 0, 0},
{1, 0, 1, 1, 1, 0, 0},
{1, 1, 0, 0, 0, 1, 1},
{1, 1, 1, 1, 0, 0, 1},
{0, 0, 0, 0, 1, 1, 0},
{1, 1, 1, 1, 1, 0, 1},
{1, 1, 1, 1, 0, 1, 0},
{1, 1, 0, 0, 1, 0, 1},
{1, 0, 1, 1, 0, 1, 0},
{1, 1, 0, 0, 0, 0, 1},
{1, 0, 1, 1, 1, 1, 0},
{0, 1, 0, 0, 0, 0, 0},
{1, 1, 1, 1, 1, 1, 1},
{1, 0, 1, 0, 0, 0, 1},
{1, 1, 0, 1, 1, 1, 0},
{1, 1, 1, 0, 1, 1, 1},
{1, 0, 0, 1, 0, 0, 0},
{0, 1, 1, 1, 1, 1, 1},
{1, 1, 1, 0, 0, 0, 0},
{1, 1, 0, 1, 1, 1, 1},
{1, 0, 1, 0, 0, 0, 0},
{1, 1, 0, 1, 1, 1, 1},
{1, 1, 1, 1, 1, 1, 0},
{1, 0, 1, 0, 0, 0, 1},
{1, 1, 0, 1, 1, 1, 0},
{0, 0, 1, 0, 0, 0, 0},
{1, 1, 1, 1, 1, 0, 1},
{1, 1, 0, 0, 0, 1, 1},
{1, 1, 1, 1, 1, 1, 0},
{1, 0, 1, 1, 1, 0, 1},
{1, 1, 0, 0, 0, 1, 0},
{1, 1, 1, 1, 1, 0, 1},
{0, 0, 0, 0, 0, 1, 0},
{1, 1, 1, 1, 1, 0, 0},
{1, 1, 1, 0, 0, 0, 1},
{1, 1, 0, 1, 1, 1, 0},
{1, 0, 1, 0, 0, 0, 1},
{1, 1, 0, 1, 1, 1, 1},
{1, 1, 1, 0, 0, 0, 0},
{1, 0, 1, 1, 1, 1, 1},
{0, 1, 0, 0, 1, 1, 0},
{1, 1, 1, 1, 0, 0, 1},
{1, 0, 0, 0, 1, 1, 0},
{1, 1, 1, 1, 0, 0, 1},
{1, 1, 1, 0, 1, 1, 0},
{1, 1, 0, 1, 1, 0, 1},
{1, 0, 1, 0, 0, 1, 1},
{1, 1, 0, 1, 1, 0, 0},
{0, 0, 1, 0, 0, 1, 1},
{1, 1, 0, 1, 1, 0, 0},
{1, 1, 1, 0, 0, 1, 0},
{1, 1, 1, 1, 1, 0, 1},
{1, 0, 0, 1, 0, 0, 0},
{1, 1, 1, 0, 1, 1, 1},
{1, 1, 1, 1, 0, 0, 0},
{1, 0, 0, 0, 1, 1, 1},
{0, 1, 1, 0, 0, 0, 0},
{1, 0, 0, 1, 0, 0, 1},
{1, 1, 1, 0, 1, 1, 0},
{1, 1, 1, 1, 0, 1, 1},
{1, 1, 0, 0, 1, 0, 1},
{1, 0, 1, 1, 0, 1, 0},
{1, 1, 0, 0, 1, 0, 1},
{0, 0, 1, 1, 0, 1, 0},
{1, 1, 1, 0, 1, 1, 1},
{1, 1, 0, 1, 1, 0, 0},
{1, 1, 1, 0, 0, 1, 1},
{1, 0, 1, 1, 1, 0, 0},
{1, 1, 0, 0, 0, 1, 1},
{1, 1, 1, 1, 1, 0, 0},
{0, 0, 0, 1, 1, 1, 1},
{1, 1, 1, 0, 0, 0, 0},
{1, 1, 0, 1, 0, 1, 1},
{1, 0, 1, 0, 1, 0, 0},
{1, 1, 1, 1, 0, 1, 1},
{1, 1, 0, 0, 1, 0, 0},
{0, 0, 1, 1, 1, 1, 1},
{1, 1, 0, 1, 0, 0, 0},
{1, 1, 1, 0, 1, 1, 1},
{1, 1, 1, 1, 0, 0, 0},
{1, 0, 0, 0, 1, 1, 1},
{1, 1, 1, 1, 0, 0, 0},
{0, 0, 0, 0, 1, 1, 0},
{1, 1, 1, 1, 0, 0, 1},
{1, 1, 1, 1, 1, 1, 0},
{1, 1, 0, 0, 0, 0, 1},
{1, 0, 1, 1, 1, 1, 0},
{1, 1, 1, 1, 1, 1, 1},
{0, 1, 0, 0, 0, 0, 0},
{1, 0, 1, 1, 0, 0, 1},
{1, 1, 0, 0, 1, 1, 0},
{1, 1, 1, 1, 0, 0, 1},
{1, 0, 0, 0, 1, 1, 0},
{0, 1, 1, 1, 0, 0, 1},
{1, 0, 0, 0, 0, 0, 0},
{1, 1, 1, 1, 1, 1, 1},
{1, 1, 1, 0, 0, 0, 0},
{1, 1, 0, 1, 1, 1, 1},
{0, 0, 1, 1, 1, 1, 1},
{1, 1, 0, 0, 0, 0, 0},
{1, 0, 1, 1, 1, 1, 1},
{1, 1, 0, 0, 0, 0, 0},
{0, 1, 1, 1, 0, 0, 0},
{1, 0, 0, 0, 1, 1, 1},
{1, 1, 1, 1, 1, 1, 1},
{1, 1, 1, 1, 0, 0, 0},
{1, 0, 0, 0, 1, 1, 1},
{0, 1, 1, 1, 0, 0, 0},
{1, 0, 1, 1, 1, 1, 0},
{1, 1, 0, 0, 0, 0, 1},
{1, 1, 1, 0, 1, 1, 0},
{0, 0, 0, 1, 0, 0, 1},
{1, 1, 1, 1, 1, 1, 0},
{1, 1, 1, 0, 0, 0, 1},
{1, 0, 0, 1, 1, 1, 1},
{0, 1, 0, 0, 0, 1, 0},
{1, 0, 1, 1, 1, 0, 1},
{1, 1, 0, 0, 0, 1, 0},
{0, 0, 1, 1, 1, 0, 1},
{1, 1, 0, 0, 0, 0, 0},
{1, 1, 1, 1, 0, 1, 1},
{1, 0, 0, 0, 1, 0, 0},
{0, 1, 1, 1, 0, 1, 1},
{1, 0, 0, 0, 1, 0, 0},
{1, 1, 1, 1, 0, 1, 1},
{0, 0, 1, 1, 1, 1, 0},
{1, 1, 0, 0, 1, 0, 1},
{1, 1, 1, 1, 0, 1, 1},
{0, 0, 0, 0, 1, 0, 0},
{1, 1, 1, 1, 0, 1, 1},
{1, 1, 1, 0, 1, 0, 0},
{0, 0, 0, 1, 0, 1, 0},
{1, 1, 0, 0, 1, 0, 1},
{1, 0, 1, 1, 0, 1, 0},
{0, 1, 1, 0, 1, 0, 1},
{1, 1, 0, 1, 1, 1, 1},
{1, 0, 1, 0, 0, 1, 0},
{0, 1, 0, 1, 1, 0, 1},
{1, 0, 1, 0, 0, 1, 0},
{1, 1, 0, 1, 1, 0, 0},
{0, 0, 1, 1, 1, 1, 1},
{1, 1, 1, 0, 0, 0, 0},
{0, 1, 0, 1, 1, 1, 1},
{1, 0, 1, 0, 0, 0, 0},
{1, 1, 0, 1, 0, 0, 1},
{0, 0, 1, 0, 1, 1, 0},
{1, 1, 0, 1, 0, 1, 1},
{1, 1, 1, 0, 1, 0, 0},
{0, 0, 1, 1, 1, 1, 1},
{1, 1, 0, 1, 0, 0, 1},
{0, 0, 0, 0, 1, 1, 0},
{1, 1, 1, 0, 0, 0, 1},
{0, 0, 0, 1, 1, 1, 0},
{1, 1, 1, 0, 0, 0, 1},
{1, 0, 0, 1, 1, 1, 1},
{0, 1, 1, 1, 1, 1, 0},
{1, 0, 0, 0, 0, 0, 1},
{0, 1, 1, 1, 1, 0, 0},
{1, 0, 1, 0, 0, 1, 1},
{0, 1, 0, 1, 1, 0, 0},
{1, 1, 1, 1, 0, 1, 1},
{0, 0, 0, 0, 1, 0, 0},
{1, 1, 1, 1, 0, 1, 1},
{1, 0, 0, 0, 1, 0, 0},
{0, 1, 1, 1, 0, 1, 1},
{1, 0, 0, 0, 1, 0, 0},
{0, 1, 1, 1, 0, 1, 1},
{1, 0, 0, 1, 1, 0, 0},
{0, 0, 1, 0, 1, 1, 1},
{1, 1, 0, 1, 0, 0, 1},
{0, 0, 1, 0, 1, 1, 0},
{1, 1, 0, 1, 0, 0, 1},
{0, 0, 1, 1, 1, 1, 0},
{1, 1, 0, 0, 0, 0, 1},
{0, 0, 1, 1, 1, 1, 0},
{1, 0, 0, 0, 0, 0, 0},
{0, 1, 1, 1, 1, 0, 1},
{0, 0, 0, 0, 0, 1, 0},
{1, 1, 1, 1, 1, 0, 1},
{0, 0, 0, 0, 0, 1, 0},
{1, 1, 1, 1, 0, 0, 1},
{0, 0, 0, 0, 1, 1, 0},
{1, 1, 1, 1, 0, 0, 0},
{0, 0, 0, 0, 1, 1, 1},
{1, 1, 1, 1, 0, 0, 0},
{0, 0, 0, 0, 1, 1, 1},
{0, 1, 1, 1, 0, 0, 0},
{1, 0, 0, 0, 1, 1, 1},
{0, 1, 1, 1, 1, 0, 0},
{1, 0, 0, 0, 0, 1, 1},
{0, 1, 0, 1, 1, 0, 0},
{0, 0, 1, 0, 0, 1, 1},
{1, 0, 0, 1, 0, 0, 0},
{0, 1, 1, 0, 1, 0, 1},
{1, 1, 0, 1, 0, 1, 0},
{0, 0, 1, 0, 1, 0, 1},
{0, 0, 0, 1, 0, 1, 0},
{1, 1, 1, 0, 1, 0, 1},
{0, 0, 0, 0, 0, 1, 1},
{1, 1, 1, 1, 1, 0, 0},
{0, 0, 0, 0, 0, 1, 0},
{0, 0, 0, 1, 1, 0, 1},
{1, 1, 1, 0, 0, 0, 0},
{0, 0, 1, 1, 1, 1, 1},
{0, 1, 0, 0, 0, 0, 0},
{1, 0, 0, 1, 1, 1, 1},
{0, 0, 1, 0, 0, 1, 0},
{0, 1, 0, 1, 1, 0, 1},
{1, 0, 1, 0, 1, 1, 0},
{0, 1, 0, 1, 0, 0, 1},
{0, 0, 1, 0, 1, 1, 0},
{1, 0, 0, 1, 0, 0, 1},
{0, 1, 1, 0, 1, 1, 1},
{0, 0, 0, 1, 0, 1, 0},
{1, 1, 1, 0, 1, 0, 1},
{0, 0, 0, 1, 0, 1, 0},
{0, 0, 0, 0, 1, 0, 1},
{0, 1, 1, 0, 0, 1, 0},
{1, 0, 0, 1, 0, 0, 1},
{0, 0, 0, 0, 1, 1, 0},
{0, 1, 1, 0, 0, 0, 0},
{1, 0, 0, 1, 1, 0, 1},
{0, 1, 1, 0, 0, 1, 0},
{0, 0, 0, 1, 1, 0, 1},
{0, 0, 0, 0, 0, 1, 0},
{1, 1, 1, 1, 1, 0, 1},
{0, 0, 0, 0, 0, 1, 0},
{0, 0, 1, 1, 1, 0, 0},
{0, 1, 0, 0, 1, 1, 1},
{1, 0, 1, 1, 0, 0, 1},
{0, 1, 0, 0, 1, 1, 0},
{0, 0, 1, 1, 0, 0, 1},
{0, 0, 0, 0, 1, 1, 0},
{1, 1, 0, 0, 0, 0, 1},
{0, 0, 1, 1, 1, 1, 0},
{0, 0, 0, 0, 0, 0, 1},
{0, 1, 1, 1, 1, 0, 0},
{1, 0, 0, 0, 0, 1, 1},
{0, 1, 1, 1, 1, 1, 0},
{0, 0, 0, 0, 0, 0, 1},
{0, 0, 0, 1, 1, 1, 0},
{0, 0, 0, 0, 0, 0, 1},
{1, 1, 1, 1, 1, 1, 0},
{0, 0, 1, 0, 0, 0, 1},
{0, 0, 0, 1, 1, 1, 0},
{0, 1, 1, 0, 0, 0, 1},
{0, 0, 0, 0, 0, 1, 0},
{1, 1, 1, 1, 1, 0, 1},
{0, 0, 0, 0, 1, 1, 0},
{0, 0, 0, 1, 0, 0, 1},
{0, 1, 1, 0, 0, 1, 0},
{0, 0, 0, 1, 1, 0, 0},
{1, 0, 0, 0, 0, 1, 1},
{0, 1, 1, 1, 1, 0, 0},
{0, 0, 0, 0, 0, 0, 1},
{0, 0, 1, 1, 1, 1, 0},
{0, 1, 0, 0, 0, 0, 1},
{0, 0, 0, 1, 0, 1, 0},
{1, 0, 1, 0, 1, 0, 0},
{0, 1, 0, 1, 0, 1, 1},
{0, 0, 1, 0, 1, 0, 0},
{0, 0, 0, 1, 0, 1, 1},
{0, 1, 1, 0, 1, 0, 1},
{0, 0, 0, 1, 0, 1, 0},
{1, 0, 0, 0, 1, 0, 1},
{0, 1, 1, 0, 0, 1, 0},
{0, 0, 0, 1, 1, 0, 1},
{0, 0, 1, 0, 0, 1, 0},
{0, 0, 0, 1, 1, 0, 1},
{0, 1, 1, 0, 0, 1, 0},
{0, 0, 0, 1, 1, 0, 1},
{1, 1, 1, 0, 0, 0, 0},
{0, 0, 0, 1, 0, 1, 0},
{0, 0, 1, 0, 1, 0, 1},
{0, 1, 0, 0, 0, 1, 0},
{0, 0, 0, 1, 1, 0, 1},
{0, 0, 1, 0, 0, 1, 0},
{0, 1, 0, 1, 1, 0, 1},
{1, 0, 1, 0, 0, 1, 0},
{0, 1, 0, 1, 1, 0, 1},
{0, 0, 1, 1, 1, 1, 0},
{0, 0, 0, 0, 0, 0, 1},
{0, 0, 0, 0, 0, 1, 0},
{0, 1, 1, 1, 1, 0, 1},
{0, 0, 0, 0, 0, 1, 0},
{1, 1, 1, 1, 1, 0, 1},
{0, 0, 0, 0, 0, 1, 0},
{0, 0, 0, 0, 0, 0, 1},
{0, 0, 0, 1, 1, 0, 0},
{0, 0, 1, 0, 0, 1, 1},
{0, 1, 0, 1, 1, 0, 0},
{0, 0, 1, 0, 0, 1, 1},
{0, 1, 0, 1, 1, 1, 1},
{1, 0, 1, 0, 1, 0, 0},
{0, 0, 0, 1, 0, 1, 0},
{0, 1, 1, 0, 1, 0, 1},
{0, 0, 0, 1, 0, 1, 0},
{0, 0, 0, 0, 1, 0, 1},
{0, 0, 0, 0, 0, 1, 0},
{0, 1, 1, 1, 1, 0, 0},
{0, 0, 0, 1, 1, 1, 1},
{1, 1, 1, 0, 0, 0, 0},
{0, 0, 0, 1, 1, 0, 0},
{0, 0, 1, 0, 0, 1, 1},
{0, 0, 0, 1, 1, 0, 0},
{0, 1, 0, 0, 0, 1, 1},
{0, 0, 1, 1, 1, 0, 0},
{0, 0, 0, 0, 0, 0, 1},
{0, 1, 1, 1, 0, 1, 0},
{1, 0, 0, 0, 1, 0, 1},
{0, 1, 1, 1, 0, 1, 0},
{0, 0, 0, 0, 1, 1, 1},
{0, 0, 0, 1, 0, 0, 0},
{0, 0, 1, 0, 1, 1, 1},
{0, 1, 0, 1, 0, 0, 0},
{0, 0, 1, 0, 1, 1, 1},
{1, 1, 0, 1, 0, 0, 0},
{0, 0, 1, 0, 1, 1, 1},
{0, 0, 0, 0, 0, 0, 0},
{0, 0, 0, 1, 1, 1, 1},
{0, 1, 1, 0, 0, 0, 0},
{0, 0, 0, 1, 1, 0, 0},
{0, 0, 0, 0, 0, 1, 1},
{1, 1, 1, 1, 0, 0, 0},
{0, 0, 0, 0, 1, 1, 1},
{0, 0, 1, 1, 0, 0, 0},
{0, 0, 0, 0, 1, 1, 1},
{0, 1, 1, 1, 0, 0, 0},
{0, 0, 0, 0, 1, 1, 1},
{0, 1, 1, 1, 0, 0, 0},
{1, 0, 0, 0, 0, 0, 0},
{0, 0, 0, 0, 1, 1, 1},
{0, 1, 1, 1, 0, 0, 0},
{0, 0, 0, 0, 1, 1, 1},
{0, 0, 1, 1, 0, 0, 0},
{0, 1, 0, 0, 1, 1, 1},
{1, 0, 0, 1, 0, 0, 1},
{0, 0, 1, 0, 1, 1, 0},
{0, 1, 0, 1, 0, 1, 1},
{0, 0, 1, 0, 1, 0, 0},
{0, 0, 0, 1, 0, 0, 1},
{0, 1, 0, 0, 1, 1, 0},
{1, 0, 1, 1, 0, 0, 1},
{0, 1, 0, 0, 0, 1, 0},
{0, 0, 1, 1, 1, 0, 0},
{0, 0, 0, 0, 0, 0, 1},
{0, 0, 0, 0, 1, 1, 0},
{1, 1, 1, 1, 0, 0, 1},
{0, 0, 1, 1, 1, 1, 0},
{0, 1, 0, 0, 0, 0, 1},
{0, 0, 0, 0, 0, 1, 0},
{0, 0, 1, 1, 1, 0, 1},
{1, 1, 0, 0, 0, 1, 0},
{0, 0, 1, 1, 1, 0, 1},
{0, 0, 0, 0, 0, 1, 0},
{0, 1, 0, 0, 1, 0, 1},
{0, 0, 1, 1, 0, 1, 0},
{1, 1, 0, 0, 1, 0, 0},
{0, 0, 1, 1, 0, 0, 1},
{0, 0, 0, 0, 1, 1, 0},
{0, 1, 0, 1, 0, 0, 1},
{1, 0, 1, 0, 0, 1, 0},
{0, 1, 0, 1, 1, 0, 1},
{0, 0, 1, 0, 0, 1, 0},
{0, 0, 0, 0, 1, 0, 1},
{1, 1, 0, 1, 0, 1, 0},
{0, 0, 1, 0, 1, 0, 1},
{0, 0, 0, 0, 0, 0, 0},
{0, 1, 0, 1, 0, 1, 1},
{1, 0, 1, 0, 1, 0, 0},
{0, 0, 0, 1, 0, 1, 1},
{0, 1, 1, 0, 1, 1, 0},
{0, 0, 0, 0, 0, 0, 1},
{1, 1, 0, 1, 1, 1, 0},
{0, 0, 1, 0, 0, 0, 1},
{0, 0, 0, 1, 1, 1, 0},
{1, 1, 1, 0, 1, 0, 1},
{0, 0, 0, 1, 0, 1, 0},
{0, 0, 1, 0, 1, 0, 1},
{0, 1, 0, 1, 0, 1, 0},
{1, 0, 1, 0, 1, 0, 1},
{0, 1, 0, 1, 0, 1, 0},
{0, 0, 1, 0, 1, 0, 1},
{1, 1, 0, 1, 0, 0, 0},
{0, 0, 1, 0, 0, 1, 0},
{0, 0, 0, 1, 1, 0, 1},
{1, 1, 1, 0, 0, 1, 1},
{0, 0, 0, 0, 1, 0, 0},
{0, 1, 1, 1, 0, 1, 1},
{1, 0, 0, 0, 1, 0, 0},
{0, 1, 1, 1, 0, 1, 1},
{0, 0, 0, 0, 0, 0, 0},
{1, 0, 0, 0, 1, 1, 0},
{0, 1, 1, 1, 0, 0, 1},
{0, 0, 0, 0, 1, 1, 0},
{1, 1, 1, 1, 0, 0, 1},
{0, 0, 0, 0, 1, 1, 0},
{1, 1, 1, 1, 1, 0, 1},
{0, 0, 0, 0, 0, 1, 0},
{0, 0, 1, 1, 1, 0, 1},
{1, 1, 0, 0, 0, 1, 1},
{0, 0, 1, 1, 1, 0, 0},
{0, 1, 0, 0, 1, 1, 1},
{1, 0, 1, 1, 0, 0, 0},
{0, 1, 0, 0, 1, 1, 1},
{1, 0, 1, 1, 0, 0, 1},
{0, 1, 0, 0, 1, 1, 0},
{1, 0, 1, 1, 0, 0, 0},
{0, 0, 0, 0, 1, 1, 1},
{0, 1, 1, 1, 0, 0, 0},
{1, 0, 0, 0, 0, 0, 1},
{0, 1, 1, 0, 1, 1, 0},
{1, 0, 0, 1, 0, 0, 1},
{0, 1, 1, 0, 1, 1, 0},
{1, 0, 0, 1, 0, 0, 1},
{0, 1, 1, 0, 1, 1, 0},
{0, 0, 0, 1, 0, 0, 1},
{1, 1, 0, 0, 1, 1, 0},
{0, 0, 1, 0, 0, 0, 1},
{1, 1, 0, 1, 1, 1, 0},
{0, 0, 1, 0, 0, 0, 1},
{1, 1, 0, 1, 1, 1, 0},
{0, 0, 1, 0, 0, 0, 0},
{1, 1, 0, 1, 1, 0, 1},
{0, 0, 1, 0, 0, 1, 0},
{1, 1, 0, 1, 0, 0, 1},
{0, 0, 1, 0, 1, 1, 0},
{1, 1, 0, 1, 0, 0, 1},
{0, 0, 1, 0, 1, 1, 1},
{1, 1, 1, 1, 0, 0, 0},
{0, 1, 0, 0, 1, 1, 1},
{1, 0, 1, 1, 0, 1, 1},
{0, 1, 0, 0, 1, 0, 0},
{1, 0, 1, 1, 0, 1, 1},
{0, 1, 0, 0, 1, 0, 0},
{1, 0, 1, 0, 0, 1, 1},
{1, 1, 0, 1, 1, 0, 0},
{0, 1, 1, 0, 0, 1, 1},
{1, 0, 0, 1, 1, 0, 0},
{0, 1, 1, 1, 0, 1, 0},
{1, 0, 0, 0, 1, 0, 1},
{0, 1, 1, 0, 0, 1, 0},
{1, 0, 0, 1, 1, 0, 1},
{1, 1, 0, 0, 0, 1, 0},
{0, 0, 1, 1, 1, 0, 1},
{1, 1, 0, 0, 0, 1, 0},
{0, 0, 1, 1, 1, 0, 1},
{1, 1, 0, 1, 0, 1, 0},
{1, 0, 1, 0, 1, 0, 1},
{0, 1, 1, 1, 0, 1, 0},
{1, 0, 0, 0, 1, 0, 1},
{0, 1, 1, 1, 0, 1, 0},
{1, 0, 0, 0, 1, 0, 1},
{1, 1, 1, 1, 0, 1, 0},
{0, 1, 0, 0, 1, 0, 1},
{1, 0, 1, 1, 0, 1, 1},
{1, 1, 0, 0, 1, 0, 0},
{0, 0, 1, 1, 0, 1, 0},
{1, 1, 0, 0, 0, 0, 1},
{0, 0, 0, 0, 1, 0, 0},
{1, 1, 1, 1, 0, 1, 1},
{1, 0, 0, 0, 1, 0, 0},
{0, 1, 1, 1, 0, 1, 1},
{1, 1, 1, 1, 1, 1, 1},
{1, 0, 0, 0, 1, 0, 0},
{0, 1, 1, 1, 0, 1, 1},
{1, 1, 0, 0, 1, 0, 0},
{1, 0, 1, 1, 0, 1, 1},
{0, 1, 0, 0, 1, 0, 1},
{1, 1, 1, 1, 0, 1, 0},
{1, 0, 0, 0, 1, 0, 1},
{1, 1, 1, 1, 1, 1, 0},
{0, 0, 0, 1, 0, 1, 1},
{1, 1, 1, 0, 1, 0, 0},
{1, 1, 1, 1, 0, 0, 1},
{0, 0, 0, 0, 1, 1, 0},
{1, 1, 0, 1, 0, 1, 1},
{1, 0, 1, 0, 1, 0, 0},
{1, 1, 1, 1, 0, 1, 1},
{0, 1, 0, 1, 1, 0, 0},
{1, 0, 1, 0, 0, 1, 1},
{1, 1, 0, 1, 1, 0, 0},
{1, 0, 1, 0, 0, 1, 1},
{0, 1, 0, 1, 1, 1, 1},
{1, 0, 1, 0, 0, 0, 0},
{1, 1, 1, 1, 1, 0, 0},
{1, 1, 0, 0, 0, 1, 1},
{0, 0, 1, 1, 1, 0, 1},
{1, 1, 0, 0, 0, 1, 0},
{1, 0, 1, 1, 0, 0, 1},
{1, 1, 0, 0, 1, 1, 0},
{0, 0, 1, 0, 0, 0, 1},
{1, 1, 0, 1, 1, 1, 0},
{1, 1, 1, 1, 0, 0, 1},
{1, 0, 1, 0, 1, 1, 1},
{0, 1, 0, 1, 0, 1, 0},
{1, 1, 1, 0, 1, 0, 1},
{1, 0, 0, 1, 0, 1, 0},
{1, 1, 1, 0, 1, 0, 0},
{1, 1, 1, 1, 0, 0, 1},
{0, 0, 0, 0, 1, 1, 0},
{1, 1, 1, 1, 0, 0, 1},
{1, 1, 0, 0, 0, 1, 0},
{1, 0, 1, 0, 1, 0, 1},
{1, 1, 0, 1, 0, 1, 1},
{0, 0, 1, 0, 1, 0, 0},
{1, 1, 0, 1, 0, 1, 1},
{1, 1, 1, 0, 1, 1, 0},
{1, 1, 1, 1, 1, 0, 1},
{1, 0, 0, 1, 0, 1, 0},
{0, 1, 1, 0, 1, 0, 1},
{1, 0, 0, 1, 0, 1, 0},
{1, 1, 1, 0, 1, 0, 1},
{1, 1, 1, 1, 0, 1, 0},
{1, 1, 1, 0, 0, 0, 1},
{1, 0, 0, 1, 1, 1, 0},
{0, 1, 1, 0, 0, 0, 1},
{1, 1, 0, 1, 1, 1, 0},
{1, 1, 1, 0, 0, 0, 1},
{1, 0, 0, 1, 1, 1, 0},
{1, 1, 1, 0, 0, 0, 1},
{1, 1, 0, 1, 1, 1, 0},
{1, 0, 1, 0, 0, 0, 0},
{0, 1, 0, 1, 1, 1, 1},
{1, 0, 1, 1, 0, 0, 0},
{1, 1, 0, 0, 1, 1, 1},
{1, 1, 1, 1, 0, 0, 0},
{1, 1, 1, 1, 1, 1, 0},
{1, 0, 0, 0, 0, 0, 1},
{0, 1, 1, 0, 1, 0, 0},
{1, 0, 0, 1, 0, 1, 1},
{1, 1, 1, 0, 1, 0, 0},
{1, 1, 1, 1, 0, 1, 1},
{1, 1, 0, 1, 1, 0, 0},
{1, 0, 1, 0, 0, 1, 1},
{1, 1, 1, 1, 1, 1, 1},
{1, 1, 0, 0, 0, 0, 0},
{0, 0, 1, 1, 1, 1, 1},
{1, 1, 0, 0, 0, 0, 0},
{1, 1, 1, 1, 1, 1, 1},
{1, 0, 0, 0, 0, 0, 0},
{1, 1, 1, 1, 1, 1, 1},
{1, 1, 1, 1, 1, 1, 0},
{1, 0, 0, 0, 0, 0, 1},
{0, 1, 1, 0, 0, 0, 0},
{1, 1, 0, 1, 1, 1, 1},
{1, 0, 1, 1, 1, 0, 0},
{1, 1, 1, 0, 0, 1, 1},
{1, 1, 0, 1, 0, 0, 0},
{1, 1, 1, 0, 1, 1, 1},
{1, 0, 1, 1, 1, 0, 0},
{1, 1, 0, 0, 0, 1, 1},
{0, 0, 1, 1, 1, 0, 0},
{1, 1, 0, 0, 0, 1, 1},
{1, 1, 1, 1, 1, 0, 0},
{1, 1, 1, 1, 0, 1, 1},
{1, 1, 0, 0, 1, 0, 0},
{1, 0, 1, 1, 1, 1, 1},
{1, 1, 0, 0, 0, 0, 0},
{1, 0, 1, 1, 1, 1, 1},
{0, 1, 1, 1, 1, 1, 1},
{1, 1, 0, 0, 0, 0, 0},
{1, 0, 1, 1, 0, 0, 0},
{1, 1, 0, 0, 1, 1, 1},
{1, 1, 1, 1, 0, 0, 0},
{1, 1, 1, 1, 1, 1, 1},
{1, 0, 0, 0, 1, 1, 1},
{1, 1, 1, 1, 0, 0, 0},
{0, 0, 0, 0, 1, 1, 1},
{1, 1, 1, 1, 0, 0, 0},
{1, 1, 1, 1, 1, 1, 0},
{1, 1, 0, 0, 0, 0, 1},
{1, 0, 1, 1, 1, 1, 0},
{1, 1, 0, 0, 0, 0, 1},
{1, 0, 1, 1, 1, 1, 0},
{0, 1, 1, 0, 0, 0, 1},
{1, 1, 0, 1, 1, 1, 0},
{1, 1, 1, 0, 1, 1, 1},
{1, 0, 0, 1, 0, 0, 1},
{1, 1, 1, 0, 1, 1, 0},
{1, 1, 0, 1, 0, 0, 0},
{1, 0, 1, 0, 1, 1, 1},
{0, 1, 0, 1, 0, 0, 0},
{1, 0, 1, 1, 1, 1, 1},
{1, 1, 1, 0, 1, 0, 0},
{1, 1, 0, 1, 0, 1, 1},
{1, 1, 1, 0, 1, 0, 0},
{1, 0, 1, 1, 0, 1, 1},
{0, 1, 0, 0, 1, 0, 0},
{1, 0, 1, 1, 0, 1, 1},
{1, 1, 0, 0, 1, 0, 0},
{1, 1, 1, 1, 0, 1, 1},
{1, 1, 1, 1, 1, 0, 0},
{1, 0, 0, 0, 0, 1, 1},
{0, 1, 1, 1, 1, 0, 1},
{1, 1, 1, 1, 0, 1, 0},
{1, 1, 0, 0, 1, 1, 1},
{1, 0, 1, 1, 0, 0, 0},
{1, 1, 0, 0, 1, 1, 1},
{1, 1, 1, 1, 0, 0, 0},
{0, 0, 0, 0, 0, 0, 0},
{1, 1, 1, 1, 1, 1, 1},
{1, 0, 0, 0, 0, 1, 1},
{1, 1, 1, 1, 1, 0, 0},
{1, 1, 1, 0, 0, 1, 1},
{0, 0, 0, 1, 0, 0, 0},
{1, 1, 1, 0, 1, 0, 0},
{1, 1, 0, 0, 0, 1, 1},
{1, 0, 1, 1, 1, 0, 0},
{1, 1, 0, 0, 0, 1, 1},
{0, 0, 1, 1, 1, 0, 1},
{1, 1, 1, 1, 0, 1, 0},
{1, 1, 0, 0, 1, 1, 1},
{1, 1, 1, 1, 0, 0, 0},
{0, 0, 0, 0, 1, 1, 1},
{1, 1, 1, 1, 0, 0, 0},
{1, 1, 0, 0, 1, 1, 0},
{1, 0, 1, 1, 0, 0, 1},
{1, 1, 0, 0, 1, 1, 0},
{0, 0, 1, 1, 0, 0, 1},
{1, 1, 0, 1, 1, 1, 0},
{1, 1, 1, 0, 1, 0, 1},
{1, 0, 1, 1, 0, 1, 0},
{0, 1, 0, 0, 1, 0, 1},
{1, 0, 1, 1, 0, 1, 0},
{1, 1, 0, 0, 1, 0, 1},
{1, 1, 1, 1, 0, 1, 0},
{0, 0, 0, 0, 1, 0, 1},
{1, 1, 0, 0, 0, 0, 0},
{1, 0, 1, 1, 1, 1, 0},
{0, 1, 0, 1, 0, 0, 1},
{1, 0, 1, 0, 1, 1, 0},
{1, 1, 1, 1, 0, 0, 1},
{1, 1, 0, 0, 1, 1, 0},
{0, 0, 1, 1, 0, 0, 1},
{1, 1, 0, 0, 1, 1, 0},
{1, 0, 1, 1, 0, 0, 1},
{0, 1, 0, 0, 1, 1, 0},
{1, 0, 1, 1, 0, 0, 0},
{1, 1, 0, 0, 1, 1, 1},
{0, 1, 1, 1, 0, 0, 0},
{1, 0, 1, 1, 1, 1, 1},
{1, 1, 0, 0, 1, 1, 1},
{0, 1, 1, 1, 0, 0, 0},
{1, 0, 0, 0, 1, 0, 0},
{1, 1, 1, 1, 0, 1, 1},
{0, 0, 0, 0, 1, 0, 0},
{1, 1, 1, 1, 0, 1, 1},
{1, 1, 1, 1, 1, 0, 0},
{0, 0, 0, 0, 0, 1, 1},
{1, 1, 1, 0, 0, 0, 0},
{1, 0, 0, 1, 1, 1, 0},
{0, 1, 1, 0, 0, 0, 1},
{1, 0, 0, 1, 1, 1, 0},
{0, 1, 1, 0, 0, 0, 1},
{1, 1, 0, 1, 1, 1, 0},
{1, 0, 1, 0, 0, 0, 1},
{0, 1, 1, 1, 1, 1, 0},
{1, 0, 0, 0, 0, 0, 1},
{1, 1, 1, 1, 1, 1, 0},
{0, 0, 0, 0, 1, 1, 1},
{1, 1, 1, 1, 0, 0, 0},
{0, 0, 0, 0, 1, 0, 1},
{1, 1, 1, 1, 0, 1, 0},
{0, 1, 1, 1, 1, 0, 1},
{1, 0, 0, 0, 0, 1, 1},
{1, 1, 1, 1, 1, 1, 0},
{0, 0, 0, 0, 0, 0, 1},
{1, 1, 1, 0, 1, 1, 0},
{0, 0, 0, 1, 0, 0, 0},
{1, 1, 1, 0, 1, 1, 1},
{0, 0, 0, 1, 0, 0, 0},
{1, 1, 1, 0, 1, 1, 1},
{0, 1, 0, 1, 0, 0, 0},
{1, 0, 1, 0, 1, 1, 1},
{1, 1, 0, 1, 1, 1, 0},
{0, 0, 1, 1, 0, 0, 1},
{1, 1, 0, 0, 1, 1, 0},
{0, 0, 1, 0, 0, 0, 1},
{1, 0, 0, 1, 1, 0, 0},
{0, 1, 1, 0, 0, 1, 1},
{1, 0, 0, 1, 1, 0, 0},
{0, 1, 1, 0, 0, 1, 1},
{1, 0, 0, 0, 0, 0, 0},
{0, 1, 0, 1, 1, 1, 0},
{1, 0, 1, 0, 0, 0, 1},
{0, 0, 0, 1, 1, 1, 0},
{1, 1, 1, 0, 0, 0, 1},
{0, 0, 0, 1, 1, 1, 1},
{0, 0, 0, 0, 0, 1, 0},
{1, 1, 1, 1, 1, 0, 1},
{0, 1, 1, 0, 0, 1, 0},
{1, 0, 0, 1, 1, 0, 1},
{0, 1, 1, 0, 0, 1, 1},
{1, 0, 0, 1, 1, 1, 0},
{0, 1, 1, 0, 1, 0, 1},
{1, 0, 0, 1, 0, 1, 0},
{0, 0, 0, 0, 1, 0, 0},
{0, 1, 1, 1, 0, 0, 1},
{1, 0, 1, 0, 0, 1, 0},
{0, 1, 0, 1, 1, 0, 1},
{1, 0, 1, 0, 0, 1, 0},
{0, 1, 0, 1, 1, 0, 1},
{0, 0, 1, 0, 0, 1, 1},
{1, 1, 0, 1, 1, 1, 0},
{0, 0, 1, 0, 0, 0, 1},
{1, 1, 0, 1, 1, 1, 0},
{0, 0, 1, 0, 0, 0, 1},
{0, 1, 0, 1, 1, 1, 0},
{1, 0, 1, 0, 0, 0, 1},
{0, 1, 0, 1, 1, 1, 0},
{1, 0, 1, 0, 0, 0, 1},
{0, 0, 0, 1, 1, 1, 0},
{0, 1, 0, 0, 0, 1, 1},
{1, 0, 1, 1, 1, 0, 0},
{0, 1, 0, 0, 0, 0, 1},
{0, 0, 1, 1, 0, 1, 0},
{1, 0, 0, 0, 1, 0, 1},
{0, 1, 0, 0, 0, 1, 0},
{0, 0, 1, 1, 1, 0, 1},
{1, 1, 0, 0, 0, 0, 0},
{0, 0, 1, 1, 1, 1, 0},
{0, 0, 0, 0, 0, 0, 1},
{1, 1, 0, 1, 1, 1, 1},
{0, 0, 1, 0, 0, 0, 0},
{0, 0, 0, 1, 1, 1, 1},
{1, 1, 1, 0, 0, 0, 0},
{0, 0, 0, 1, 1, 1, 1},
{0, 0, 1, 0, 0, 1, 1},
{0, 1, 0, 1, 1, 0, 0},
{1, 0, 1, 0, 0, 1, 1},
{0, 1, 0, 1, 1, 0, 0},
{0, 0, 1, 0, 0, 1, 1},
{1, 1, 0, 1, 1, 1, 0},
{0, 0, 0, 0, 0, 0, 1},
{0, 0, 1, 1, 1, 1, 0},
{0, 0, 0, 0, 0, 0, 0},
{1, 1, 1, 0, 1, 1, 1},
{0, 0, 0, 1, 0, 0, 0},
{0, 1, 1, 0, 1, 0, 1},
{0, 0, 0, 1, 0, 1, 0},
{1, 0, 0, 0, 1, 0, 1},
{0, 1, 1, 1, 0, 1, 0},
{0, 0, 1, 0, 1, 0, 1},
{0, 1, 0, 1, 0, 1, 0},
{1, 0, 0, 0, 1, 0, 1},
{0, 0, 1, 1, 0, 1, 1},
{0, 1, 0, 0, 1, 0, 0},
{0, 0, 1, 1, 0, 1, 1},
{1, 0, 0, 0, 1, 0, 0},
{0, 1, 1, 0, 0, 1, 1},
{0, 0, 0, 1, 0, 0, 0},
{0, 0, 0, 0, 1, 1, 1},
{0, 1, 1, 1, 0, 0, 0},
{1, 0, 0, 0, 1, 1, 0},
{0, 0, 1, 0, 0, 0, 1},
{0, 1, 0, 1, 1, 0, 0},
{0, 0, 1, 0, 0, 1, 1},
{0, 0, 0, 1, 1, 0, 0},
{1, 1, 0, 0, 0, 1, 1},
{0, 0, 1, 1, 0, 0, 0},
{0, 0, 0, 0, 1, 0, 0},
{0, 1, 1, 1, 0, 1, 1},
{0, 0, 1, 0, 1, 0, 1},
{1, 1, 0, 1, 0, 1, 0},
{0, 0, 0, 0, 1, 0, 1},
{0, 0, 1, 1, 0, 1, 0},
{0, 0, 0, 0, 1, 0, 1},
{0, 1, 1, 0, 0, 1, 0},
{0, 0, 0, 1, 1, 0, 1},
{1, 1, 0, 0, 0, 1, 1},
{0, 0, 1, 1, 1, 0, 0},
{0, 0, 0, 0, 0, 1, 1},
{0, 0, 1, 1, 1, 0, 0},
{0, 1, 0, 0, 0, 1, 1},
{0, 0, 1, 1, 1, 0, 0},
{1, 1, 0, 0, 0, 1, 1},
{0, 0, 0, 0, 0, 0, 0},
{0, 0, 1, 1, 1, 1, 0},
{0, 0, 0, 0, 1, 0, 1},
{0, 1, 1, 1, 0, 1, 0},
{0, 0, 0, 0, 1, 0, 1},
{0, 1, 1, 1, 0, 1, 1},
{1, 0, 0, 0, 1, 1, 0},
{0, 0, 0, 0, 0, 0, 1},
{0, 1, 1, 1, 1, 1, 0},
{0, 0, 0, 0, 1, 0, 1},
{0, 0, 0, 1, 0, 1, 0},
{0, 1, 1, 0, 1, 0, 1},
{0, 0, 0, 1, 0, 1, 0},
{1, 0, 1, 0, 1, 0, 0},
{0, 1, 0, 1, 0, 1, 1},
{0, 0, 1, 0, 1, 0, 0},
{0, 0, 0, 1, 0, 1, 1},
{0, 1, 0, 0, 1, 0, 0},
{0, 0, 1, 0, 0, 1, 1},
{0, 0, 0, 1, 0, 0, 0},
{1, 1, 0, 0, 1, 0, 0},
{0, 0, 1, 1, 0, 1, 1},
{0, 0, 0, 0, 1, 0, 1},
{0, 0, 1, 1, 0, 1, 0},
{0, 1, 0, 0, 1, 0, 1},
{0, 0, 1, 1, 0, 1, 0},
{0, 0, 0, 0, 1, 0, 1},
{0, 1, 0, 0, 0, 1, 0},
{1, 0, 1, 1, 0, 0, 0},
{0, 1, 0, 0, 1, 0, 1},
{0, 0, 1, 1, 0, 1, 0},
{0, 0, 0, 0, 1, 1, 1},
{0, 0, 0, 1, 0, 0, 0},
{0, 1, 1, 0, 1, 1, 1},
{0, 0, 0, 0, 0, 0, 0},
{0, 0, 0, 1, 1, 1, 1},
{1, 1, 1, 0, 0, 0, 0},
{0, 0, 0, 1, 1, 1, 1},
{0, 0, 1, 0, 0, 0, 0},
{0, 1, 0, 1, 0, 0, 0},
{0, 0, 0, 0, 1, 1, 1},
{0, 0, 1, 1, 0, 1, 1},
{0, 1, 0, 0, 1, 0, 0},
{0, 0, 0, 0, 0, 0, 0},
{1, 1, 1, 1, 1, 1, 1},
{0, 0, 0, 0, 0, 0, 0},
{0, 0, 0, 1, 1, 1, 1},
{0, 0, 1, 0, 0, 0, 1},
{0, 1, 0, 1, 1, 1, 0},
{0, 0, 1, 0, 1, 1, 1},
{0, 0, 0, 1, 0, 0, 0},
{1, 1, 0, 0, 1, 0, 1},
{0, 0, 1, 1, 0, 1, 0},
{0, 0, 0, 0, 0, 0, 1},
{0, 0, 1, 1, 1, 1, 0},
{0, 1, 0, 0, 0, 0, 0},
{0, 0, 1, 1, 1, 1, 1},
{0, 0, 0, 0, 0, 0, 0},
{1, 1, 1, 0, 0, 0, 1},
{0, 0, 0, 1, 1, 1, 0},
{0, 0, 1, 0, 0, 0, 1},
{0, 1, 0, 1, 1, 1, 0},
{0, 0, 1, 0, 1, 1, 1},
{0, 0, 0, 1, 0, 0, 0},
{0, 1, 0, 0, 0, 0, 1},
{1, 0, 1, 1, 1, 1, 0},
{0, 1, 0, 0, 0, 0, 1},
{0, 0, 1, 1, 1, 1, 0},
{0, 0, 0, 0, 0, 0, 1},
{0, 0, 0, 0, 0, 0, 0},
{0, 1, 1, 1, 1, 1, 1},
{1, 0, 0, 0, 0, 0, 0},
{0, 1, 1, 1, 0, 1, 1},
{0, 0, 0, 0, 1, 0, 0},
{0, 0, 0, 0, 0, 1, 1},
{0, 0, 1, 1, 1, 0, 0},
{0, 1, 0, 0, 0, 1, 1},
{1, 0, 1, 1, 1, 0, 0},
{0, 1, 0, 0, 0, 1, 1},
{0, 0, 1, 1, 1, 0, 0},
{0, 0, 0, 0, 0, 1, 1},
{0, 1, 0, 0, 0, 0, 0},
{1, 0, 1, 1, 1, 1, 1},
{0, 0, 0, 0, 1, 0, 0},
{0, 1, 1, 1, 0, 1, 1},
{0, 0, 0, 0, 1, 0, 1},
{0, 0, 1, 1, 0, 1, 0},
{1, 1, 0, 0, 1, 1, 1},
{0, 0, 1, 1, 0, 0, 0},
{0, 0, 0, 0, 1, 1, 1},
{0, 1, 1, 1, 0, 0, 0},
{0, 0, 0, 0, 1, 1, 1},
{1, 1, 1, 0, 0, 0, 1},
{0, 0, 0, 1, 1, 1, 0},
{0, 0, 0, 0, 0, 0, 1},
{0, 1, 1, 1, 0, 1, 0},
{1, 0, 0, 0, 1, 0, 0},
{0, 1, 1, 1, 1, 1, 1},
{0, 0, 0, 0, 0, 0, 0},
{0, 0, 1, 1, 1, 1, 1},
{1, 1, 0, 0, 0, 0, 0},
{0, 0, 1, 1, 1, 1, 1},
{0, 0, 0, 0, 0, 0, 0},
{0, 1, 0, 0, 0, 1, 1},
{1, 0, 1, 1, 1, 0, 0},
{0, 1, 0, 0, 1, 1, 0},
{0, 0, 1, 1, 0, 0, 1},
{0, 0, 0, 0, 1, 1, 0},
{1, 1, 0, 0, 0, 0, 1},
{0, 0, 1, 1, 1, 0, 0},
{0, 0, 0, 0, 0, 1, 1},
{1, 1, 1, 1, 1, 0, 0},
{0, 0, 0, 0, 0, 1, 1},
{0, 1, 1, 1, 1, 0, 0},
{0, 0, 0, 0, 0, 1, 1},
{1, 0, 0, 1, 1, 0, 0},
{0, 1, 1, 0, 0, 0, 0},
{0, 0, 1, 1, 1, 1, 1},
{1, 1, 0, 0, 0, 0, 1},
{0, 0, 1, 1, 1, 1, 0},
{0, 1, 0, 0, 0, 0, 1},
{1, 0, 0, 1, 1, 1, 0},
{0, 0, 1, 0, 0, 0, 1},
{0, 1, 0, 1, 0, 1, 0},
{1, 0, 1, 0, 1, 0, 1},
{0, 1, 0, 1, 0, 1, 0},
{0, 0, 1, 0, 1, 0, 0},
{1, 1, 0, 1, 0, 1, 1},
{0, 0, 1, 0, 1, 0, 0},
{0, 0, 0, 0, 0, 0, 1},
{1, 1, 0, 1, 1, 1, 0},
{0, 0, 1, 0, 0, 0, 1},
{1, 1, 1, 1, 1, 1, 0},
{0, 0, 0, 0, 0, 0, 1},
{0, 0, 0, 1, 1, 0, 0},
{1, 1, 1, 0, 0, 1, 1},
{0, 0, 1, 1, 1, 0, 0},
{0, 1, 0, 0, 0, 1, 1},
{1, 0, 1, 1, 1, 0, 0},
{0, 1, 0, 0, 0, 1, 1},
{1, 0, 1, 1, 1, 0, 0},
{0, 1, 0, 0, 0, 1, 1},
{1, 0, 1, 1, 1, 1, 0},
{0, 1, 0, 0, 0, 0, 1},
{0, 0, 1, 1, 1, 1, 0},
{1, 0, 0, 0, 1, 0, 1},
{0, 1, 1, 1, 0, 1, 0},
{1, 0, 0, 0, 0, 0, 1},
{0, 1, 1, 0, 1, 1, 0},
{1, 0, 0, 1, 0, 0, 1},
{0, 1, 1, 0, 1, 1, 1},
{0, 0, 0, 1, 1, 1, 0},
{1, 1, 0, 0, 0, 0, 1},
{0, 0, 1, 1, 1, 1, 0},
{1, 1, 0, 0, 0, 0, 0},
{0, 0, 1, 1, 1, 1, 1},
{1, 1, 0, 1, 0, 0, 0},
{0, 0, 1, 0, 1, 1, 1},
{1, 1, 1, 1, 0, 0, 0},
{0, 0, 0, 0, 1, 1, 1},
{1, 1, 1, 1, 0, 1, 0},
{0, 0, 0, 0, 1, 0, 1},
{1, 1, 1, 1, 1, 1, 0},
{0, 1, 1, 1, 0, 0, 1},
{1, 0, 0, 0, 1, 1, 0},
{0, 1, 0, 0, 0, 0, 1},
{1, 0, 1, 1, 0, 0, 0},
{0, 1, 0, 0, 1, 1, 1},
{1, 0, 1, 1, 1, 1, 1},
{0, 1, 0, 1, 0, 0, 0},
{1, 1, 1, 0, 1, 1, 0},
{1, 0, 1, 1, 0, 0, 1},
{0, 1, 0, 0, 1, 1, 0},
{1, 0, 0, 1, 0, 0, 1},
{0, 1, 1, 0, 1, 0, 0},
{1, 0, 0, 1, 0, 1, 1},
{0, 1, 1, 0, 0, 0, 0},
{1, 0, 0, 1, 1, 1, 1},
{1, 1, 1, 0, 0, 0, 0},
{0, 0, 0, 1, 1, 1, 1},
{1, 1, 1, 0, 0, 0, 0},
{0, 0, 0, 1, 1, 1, 1},
{1, 1, 1, 0, 0, 0, 0},
{1, 0, 0, 1, 1, 1, 1},
{0, 1, 1, 0, 0, 0, 0},
{1, 0, 1, 1, 1, 1, 1},
{0, 1, 0, 1, 0, 0, 0},
{1, 0, 1, 0, 1, 1, 0},
{1, 1, 0, 1, 0, 0, 1},
{0, 1, 1, 0, 1, 1, 0},
{1, 0, 0, 1, 0, 0, 1},
{1, 1, 1, 0, 1, 1, 0},
{0, 0, 0, 1, 0, 0, 1},
{1, 1, 1, 1, 1, 1, 0},
{0, 0, 0, 0, 0, 0, 0},
{1, 1, 1, 1, 1, 1, 1},
{1, 1, 0, 0, 0, 0, 0},
{0, 0, 1, 1, 1, 1, 1},
{1, 1, 0, 0, 0, 0, 0},
{1, 0, 1, 1, 0, 0, 1},
{0, 1, 0, 0, 1, 1, 0},
{1, 1, 1, 1, 0, 0, 1},
{1, 0, 0, 0, 1, 1, 0},
{0, 1, 1, 1, 0, 0, 1},
{1, 1, 1, 0, 1, 1, 0},
{1, 0, 0, 1, 0, 0, 1},
{1, 1, 1, 0, 1, 1, 0},
{0, 0, 0, 1, 0, 0, 1},
{1, 1, 1, 0, 1, 1, 0},
{1, 1, 0, 1, 0, 0, 1},
{0, 0, 1, 0, 1, 1, 0},
{1, 1, 0, 1, 1, 1, 1},
{1, 1, 1, 1, 0, 0, 1},
{1, 0, 0, 0, 1, 1, 0},
{0, 1, 1, 1, 0, 0, 1},
{1, 0, 0, 0, 1, 1, 0},
{1, 1, 1, 1, 0, 1, 1},
{1, 0, 0, 0, 1, 0, 0},
{0, 1, 1, 1, 1, 1, 1},
{1, 0, 1, 1, 0, 0, 0},
{1, 1, 0, 0, 1, 1, 1},
{1, 1, 1, 1, 0, 0, 1},
{0, 0, 0, 0, 1, 1, 0},
{1, 1, 1, 1, 0, 0, 1},
{1, 0, 0, 0, 1, 1, 0},
{1, 1, 1, 1, 0, 0, 1},
{0, 0, 1, 1, 1, 1, 0},
{1, 1, 0, 0, 0, 0, 1},
{1, 1, 1, 1, 1, 1, 0},
{1, 0, 1, 0, 0, 0, 1},
{0, 1, 0, 1, 1, 1, 0},
{1, 1, 1, 0, 0, 0, 1},
{1, 0, 0, 1, 0, 0, 0},
{1, 1, 1, 0, 1, 1, 1},
{1, 1, 1, 1, 0, 0, 0},
{0, 0, 0, 0, 1, 1, 1},
{1, 1, 1, 1, 0, 0, 0},
{1, 1, 0, 0, 1, 1, 1},
{1, 0, 1, 1, 0, 0, 0},
{1, 1, 0, 0, 1, 1, 1},
{0, 0, 1, 1, 0, 0, 0},
{1, 1, 1, 0, 1, 0, 1},
{1, 1, 0, 1, 0, 1, 0},
{1, 1, 1, 0, 1, 0, 1},
{1, 0, 0, 1, 0, 1, 0}};

#endif