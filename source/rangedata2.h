#ifndef RANGEDATA2_H
#define RANGEDATA2_H

const int range_length=1024;

/*const unsigned int long_range_data[range_length] PROGMEM = {
550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,541,536,532,527,522,518,514,509,505,501,497,492,488,484,481,477,473,469,466,462,458,455,451,448,445,441,438,435,432,429,426,423,420,417,414,411,408,405,402,400,397,394,392,389,387,384,381,379,377,374,372,369,367,365,363,360,358,356,354,352,350,347,345,343,341,339,337,335,333,332,330,328,326,324,
322,321,319,317,315,314,312,310,308,307,305,304,302,300,299,297,296,294,293,291,290,288,287,285,284,283,281,280,278,277,276,274,273,272,270,269,268,267,265,264,263,262,260,259,258,257,256,255,253,252,251,250,249,248,247,246,245,243,242,241,240,239,238,237,236,235,234,233,232,231,230,229,228,227,227,226,225,224,223,222,221,220,219,218,218,217,216,215,214,213,213,212,211,210,209,208,208,207,206,205,205,204,203,202,202,201,200,199,199,198,197,196,196,195,194,194,193,192,191,191,190,189,189,188,187,187,186,186,185,184,184,183,182,182,181,181,180,179,179,178,177,177,176,176,175,175,174,173,173,172,172,171,171,170,170,169,168,168,167,167,166,166,165,165,164,164,163,163,162,162,161,161,160,160,159,159,158,158,157,157,156,156,155,155,154,154,154,153,153,152,152,151,151,150,150,149,149,149,148,148,147,147,146,146,146,145,145,144,144,144,143,143,142,142,142,141,141,140,140,140,139,139,138,138,138,137,137,137,136,136,136,135,135,134,134,134,133,133,133,132,132,132,131,131,131,130,130,130,129,129,129,128,128,128,127,127,127,126,126,126,125,125,125,124,124,124,123,123,123,122,122,122,122,121,121,121,120,120,120,119,119,119,119,118,118,118,117,117,117,117,116,116,116,115,115,115,115,114,114,114,114,113,113,113,112,112,112,112,111,111,111,111,110,110,110,110,109,109,109,109,108,108,108,108,107,107,107,107,106,106,106,106,105,105,105,105,105,104,104,104,104,103,103,103,103,102,102,102,102,102,101,101,101,101,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100
};
*/
const unsigned int medium_range_data[] PROGMEM = {
150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,149,148,148,147,146,145,145,144,143,142,142,141,140,140,139,138,138,137,136,136,135,134,134,133,132,132,131,130,130,129,129,128,127,127,126,126,125,124,124,123,123,122,122,121,121,120,120,119,118,118,117,117,116,116,115,115,114,114,113,113,112,112,112,111,111,110,110,109,109,108,108,107,107,107,106,106,105,105,104,104,104,103,103,102,102,102,101,101,100,100,100,99,99,98,98,98,97,97,97,96,96,95,95,95,94,94,94,93,93,93,92,92,92,91,91,91,90,90,90,89,89,89,88,88,88,87,87,87,86,86,86,86,85,85,85,84,84,84,83,83,83,83,82,82,82,81,81,81,81,80,80,80,80,79,79,79,78,78,78,78,77,77,77,77,76,76,76,76,75,75,75,75,74,74,74,74,74,73,73,73,73,72,72,72,72,71,71,71,71,71,70,70,70,70,69,69,69,69,69,68,68,68,68,68,67,67,67,67,67,66,66,66,66,66,65,65,65,65,65,64,64,64,64,64,63,63,63,63,63,62,62,62,62,62,62,61,61,61,61,61,61,60,60,60,60,60,59,59,59,59,59,59,
58,58,58,58,58,58,57,57,57,57,57,57,57,56,56,56,56,56,56,55,55,55,55,55,55,55,54,54,54,54,54,54,54,53,53,53,53,53,53,53,52,52,52,52,52,52,52,51,51,51,51,51,51,51,50,50,50,50,50,50,50,50,49,49,49,49,49,49,49,49,48,48,48,48,48,48,48,48,47,47,47,47,47,47,47,47,46,46,46,46,46,46,46,46,46,45,45,45,45,45,45,45,45,44,44,44,44,44,44,44,44,44,44,43,43,43,43,43,43,43,43,43,42,42,42,42,42,42,42,42,42,42,41,41,41,41,41,41,41,41,41,41,40,40,40,40,40,40,40,40,40,40,39,39,39,39,39,39,39,39,39,39,39,38,38,38,38,38,38,38,38,38,38,38,37,37,37,37,37,37,37,37,37,37,37,37,36,36,36,36,36,36,36,36,36,36,36,36,35,35,35,35,35,35,35,35,35,35,35,35,34,34,34,34,34,34,34,34,34,34,34,34,34,33,33,33,33,33,33,33,33,33,33,33,33,33,32,32,32,32,32,32,32,32,32,32,32,32,32,32,31,31,31,31,31,31,31,31,31,31,31,31,31,31,31,30,30,30,30,30,30,30,30,30,30,30,30,30,30,30,29,29,29,29,29,29,29,29,29,29,29,29,29,29,29,29,28,28,28,28,28,28,28,28,28,28,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20
};


#endif
