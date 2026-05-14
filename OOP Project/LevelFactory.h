#pragma once
#include "Levels.h"

class LevelFactory {
private:
    int height;
    int width;
    char** grid;
public:
    LevelFactory() {
        grid = nullptr;
        height = 0;
        width = 0;
    }

    Level* createLevel(int x) {


        switch (x) {
        case 0:
            height = 14;
            width = 200;
            grid = new char* [height];
            for (int i = 0; i < height; i++) {
                grid[i] = new char[width];
                for (int j = 0; j < width; j++) {
                    grid[i][j] = ' ';
                }
            }

            for (int j = 0; j < width; j++) {
                grid[0][j] = 'w';
                grid[height - 2][j] = 'w';
                grid[height - 1][j] = 'w';
            }
            for (int i = 0; i < height; i++) {
                grid[i][0] = 'w';
                grid[i][width - 1] = ' ';
            }


            grid[9][6] = 'p';
            grid[10][6] = 'b';
            grid[11][6] = 'b';


            grid[7][9] = 'p';
            grid[7][10] = 'p';
            grid[7][11] = 'p';
            grid[7][12] = 'p';

            grid[11][7] = 'M';
            grid[11][14] = 'M';


            grid[7][15] = 'p';
            grid[7][16] = 'p';
            grid[7][17] = 'p';
            grid[7][18] = 'p';


            grid[9][21] = 'p';
            grid[10][21] = 'b';
            grid[11][21] = 'b';


            for (int j = 22; j <= 23; j++) {
                grid[12][j] = 'd';
                grid[13][j] = 'd';
            }


            grid[9][24] = 'p';
            grid[10][24] = 'b';
            grid[11][24] = 'b';


            for (int j = 25; j <= 26; j++) {
                grid[12][j] = 'd';
                grid[13][j] = 'd';
            }


            grid[9][27] = 'p';
            grid[10][27] = 'b';
            grid[11][27] = 'b';


            for (int j = 28; j <= 29; j++) {
                grid[12][j] = 'd';
                grid[13][j] = 'd';
            }


            grid[9][30] = 'p';
            grid[10][30] = 'b';
            grid[11][30] = 'b';


            grid[7][32] = 'p';
            grid[7][33] = 'p';
            grid[7][34] = 'p';
            grid[7][35] = 'p';

            grid[3][31] = 'B';
            grid[3][58] = 'B';


            grid[5][37] = 'p';
            grid[5][38] = 'p';
            grid[5][39] = 'p';
            grid[5][40] = 'p';

            grid[11][37] = 's';
            grid[11][38] = 's';
            grid[11][39] = 's';
            grid[11][40] = 's';


            grid[7][42] = 'p';
            grid[7][43] = 'p';
            grid[7][44] = 'p';
            grid[7][45] = 'p';


            grid[6][50] = 'p';
            grid[6][51] = 'p';
            grid[6][52] = 'p';

            grid[8][58] = 'b';
            grid[9][58] = 'b';
            grid[10][58] = 'b';
            grid[11][58] = 'b';


            grid[4][62] = 'p';
            grid[4][63] = 'p';
            grid[4][64] = 'p';
            grid[4][65] = 'p';


            for (int j = 66; j <= 70; j++) {
                grid[12][j] = 'd';
                grid[13][j] = 'd';
            }


            grid[7][75] = 'p';
            grid[7][76] = 'p';
            grid[7][77] = 'p';
            grid[7][78] = 'p';


            grid[9][82] = 'p';
            grid[10][82] = 'b';
            grid[11][82] = 'b';

            grid[3][86] = 'E';


            grid[5][87] = 'p';
            grid[5][88] = 'p';
            grid[5][89] = 'p';
            grid[5][90] = 'p';


            grid[4][88] = ' ';
            grid[4][89] = ' ';

            grid[11][94] = 's';
            grid[11][95] = 's';

            grid[7][95] = 'p';
            grid[7][96] = 'p';
            grid[7][97] = 'p';
            grid[7][98] = 'p';


            grid[9][102] = 'p';
            grid[10][102] = 'b';
            grid[11][102] = 'b';


            grid[3][103] = 'E';


            grid[6][110] = 'p';
            grid[6][111] = 'p';


            for (int j = 112; j <= 116; j++) {
                grid[12][j] = 'd';
                grid[13][j] = 'd';
            }


            grid[4][120] = 'p';
            grid[4][121] = 'p';
            grid[3][120] = 'C';


            grid[8][125] = 'p';
            grid[9][125] = 'b';
            grid[10][125] = 'b';
            grid[11][125] = 'b';


            for (int j = 130; j <= 136; j++) {
                grid[12][j] = 'd';
                grid[13][j] = 'd';
            }


            grid[11][137] = 'X';
            grid[11][168] = 'X';


            grid[7][140] = 'p';
            grid[7][141] = 'p';
            grid[7][142] = 'p';
            grid[7][143] = 'p';


            grid[6][141] = 's';
            grid[6][142] = 's';


            grid[4][148] = 'p';
            grid[4][149] = 'p';
            grid[3][148] = 'C';


            grid[5][150] = 'p';
            grid[5][151] = 'p';
            grid[5][152] = 'p';
            grid[4][150] = ' ';
            grid[4][151] = ' ';
            grid[4][152] = ' ';


            for (int j = 154; j <= 159; j++) {
                grid[12][j] = 'd';
                grid[13][j] = 'd';
            }



            grid[7][160] = 'p';
            grid[7][161] = 'p';
            grid[7][162] = 'p';
            grid[7][163] = 'p';


            grid[3][170] = 'C';
            grid[4][170] = 'p';

            grid[9][175] = 'p';
            grid[10][175] = 'b';
            grid[11][174] = 's';


            grid[7][180] = 'p';
            grid[7][181] = 'p';
            grid[7][182] = 'p';
            grid[6][182] = 'z';
            grid[5][185] = 'p';
            grid[5][186] = 'p';
            grid[4][185] = 'C';
            grid[4][186] = 'F';

            grid[1][198] = 'b';
            grid[2][198] = 'b';
            grid[3][198] = 'b';
            grid[4][198] = 'b';
            grid[5][198] = 'b';
            grid[6][198] = 'b';
            grid[7][198] = 'b';
            grid[8][198] = 'b';
            grid[9][198] = 'b';
            grid[10][198] = 'b';
            grid[11][198] = 'b';


            for (int i = 1; i < height; i++) {
                for (int j = 1; j < width;j++) {
                    if (grid[i][j] == 'p') {
                        grid[i - 1][j] = 'R';
                    }
                }

            }


            grid[5][46] = 'R';
            grid[4][47] = 'R';
            grid[3][48] = 'R';
            grid[4][49] = 'R';

            grid[5][79] = 'R';
            grid[4][80] = 'R';
            grid[3][81] = 'R';
            grid[2][82] = 'R';
            grid[1][83] = 'R';
            grid[1][84] = 'R';
            grid[1][85] = 'R';
            grid[2][86] = 'R';
            grid[3][87] = 'R';

            grid[4][87] = '0';
            grid[7][58] = 'b';

            grid[4][112] = 'R';
            grid[3][113] = 'R';
            grid[2][114] = 'R';
            grid[1][115] = 'R';
            grid[1][116] = 'R';
            grid[1][117] = 'R';
            grid[1][118] = 'R';
            grid[2][119] = 'R';

            grid[5][164] = 'R';
            grid[4][165] = 'R';
            grid[3][166] = 'R';
            grid[2][167] = 'R';
            grid[1][168] = 'R';
            grid[2][169] = 'R';

            grid[1][58] = 'b';
            grid[2][58] = 'b';
            grid[3][58] = 'b';
            grid[4][58] = 'b';
            grid[5][58] = 'b';
            grid[6][58] = 'b';



            return new Level("Data/bg1.png", grid, 200, 14, 0.2f);
        case 1:
            height = 14;
            width = 250;
            grid = new char* [height];
            for (int i = 0; i < height; i++) {
                grid[i] = new char[width];
                for (int j = 0; j < width; j++) {
                    grid[i][j] = ' ';
                }
            }

            // Set boundaries
            for (int j = 0; j < width; j++) {
                grid[0][j] = 'w';
                grid[height - 2][j] = 'w';
                grid[height - 1][j] = 'w';
            }
            for (int i = 0; i < height; i++) {
                grid[i][0] = 'w';
                grid[i][width - 1] = ' ';
            }

            // Starting area with moving platforms
            grid[9][7] = 'p';
            grid[10][7] = 'b';
            grid[11][7] = 'b';
            grid[11][8] = 'M';

            // Small platforms with gaps
            grid[7][12] = 'p';
            grid[7][14] = 'p';
            grid[7][16] = 'p';
            grid[7][18] = 'p';

            // Spiked platforms
            grid[9][22] = 'p';
            grid[10][22] = 'b';
            grid[11][21] = 's';
            grid[11][22] = 'b';
            grid[8][25] = 'p';
            grid[9][27] = 'p';
            grid[10][27] = 'b';
            grid[11][27] = 'b';

            // Death zones and narrow passages
            for (int j = 30; j <= 35; j++) {
                grid[12][j] = 'd';
                grid[13][j] = 'd';
            }
            grid[7][32] = 'p';
            grid[7][33] = 'p';

            // Elevated platforms with enemies
            grid[5][40] = 'p';
            grid[5][41] = 'p';
            grid[5][42] = 'E';
            grid[4][44] = 'p';
            grid[4][45] = 'p';

            grid[11][48] = 'X';

            // Complex platforming section
            grid[7][50] = 'p';
            grid[7][52] = 'p';
            grid[6][54] = 'p';
            grid[6][56] = 'p';
            grid[5][58] = 'p';
            grid[5][59] = 'p';

            // Spiked platforms
            grid[9][65] = 'p';
            grid[10][65] = 'b';
            grid[11][64] = 's';
            grid[11][65] = 'b';
            grid[8][68] = 'p';
            grid[9][70] = 'p';
            grid[10][70] = 'b';
            grid[11][70] = 'b';

            // Long death zone with floating platforms
            for (int j = 75; j <= 85; j++) {
                grid[12][j] = 'd';
                grid[13][j] = 'd';
            }
            grid[7][78] = 'p';
            grid[7][80] = 'p';
            grid[6][82] = 'p';

            // Enemy gauntlet
            grid[5][90] = 'p';
            grid[5][91] = 'p';
            grid[5][92] = 'E';
            grid[4][94] = 'p';
            grid[4][95] = 'p';
            grid[4][96] = 'E';

            grid[11][98] = 'M';

            // Precision jumps
            grid[7][100] = 'p';
            grid[7][102] = 'p';
            grid[6][104] = 'p';
            grid[6][106] = 'p';
            grid[5][108] = 'p';

            grid[11][109] = 's';
            grid[11][110] = 's';

            // Moving platform challenge
            grid[11][115] = 'M';
            grid[9][117] = 'p';
            grid[8][119] = 'p';

            // Long death zone with sparse platforms
            for (int j = 125; j <= 135; j++) {
                grid[12][j] = 'd';
                grid[13][j] = 'd';
            }
            grid[7][128] = 'p';
            grid[6][131] = 'p';
            grid[5][134] = 'p';

            // Mid-level challenge with collectibles
            grid[4][140] = 'p';
            grid[4][141] = 'p';
            grid[11][142] = 'C';
            grid[3][143] = 'E';
            grid[9][145] = 'p';
            grid[10][145] = 'b';
            grid[11][145] = 'b';

            // Additional obstacles
            grid[5][150] = 'p';
            grid[5][151] = 'p';
            grid[5][152] = 'E';
            grid[4][154] = 'p';
            grid[11][155] = 'C';

            // Pre-final section with moving platforms
            grid[7][160] = 'p';
            grid[7][162] = 'p';
            grid[6][164] = 'p';
            grid[11][166] = 'M';
            grid[9][168] = 'p';

            // Final gauntlet: Dynamic and intense ending
            for (int j = 175; j <= 190; j++) {
                grid[12][j] = 'd';
                grid[13][j] = 'd';
            }
            grid[7][178] = 'p';
            grid[7][180] = 'p';
            grid[6][182] = 'p';
            grid[5][184] = 'p';
            grid[5][185] = 'E';
            grid[4][187] = 'p';
            grid[4][188] = 'C';
            grid[3][190] = 'E';

            // Climactic moving platform sequence
            grid[11][195] = 'M';
            grid[9][197] = 'p';
            grid[7][200] = 'p';
            grid[7][202] = 'p';
            grid[6][204] = 'p';
            grid[5][206] = 'p';
            grid[5][207] = 'E';

            // Final ascent to goal
            grid[4][210] = 'p';
            grid[4][211] = 'p';
            grid[11][212] = 'C';
            grid[9][215] = 'p';
            grid[7][220] = 'p';
            grid[6][222] = 'p';
            grid[5][224] = 'p';
            grid[4][226] = 'p';
            grid[3][228] = 'E';
            grid[11][230] = 'X';

            // Grand finale: Narrow path to finish
            grid[7][235] = 'p';
            grid[7][237] = 'p';
            grid[6][239] = 'p';
            grid[5][241] = 'p';
            grid[4][243] = 'p';
            grid[11][244] = 'C';
            grid[3][246] = 'F';

            // Add 'R' (roof) above platforms
            for (int i = 1; i < height; i++) {
                for (int j = 1; j < width; j++) {
                    if (grid[i][j] == 'p') {
                        grid[i - 1][j] = 'R';
                    }
                }
            }

            // Additional 'R' for challenging navigation
            grid[5][25] = 'R';
            grid[4][26] = 'R';
            grid[3][27] = 'R';
            grid[2][28] = 'R';
            grid[1][29] = 'R';

            grid[4][72] = 'R';
            grid[3][73] = 'R';
            grid[2][74] = 'R';
            grid[1][75] = 'R';

            grid[5][137] = 'R';
            grid[4][138] = 'R';
            grid[3][139] = 'R';

            grid[5][192] = 'R';
            grid[4][193] = 'R';
            grid[3][194] = 'R';
            grid[2][195] = 'R';

            grid[1][215] = 'b';
            grid[2][215] = 'b';
            grid[3][215] = 'b';
            grid[4][215] = 'b';
            grid[5][215] = 'b';
            grid[6][215] = 'b';
            grid[7][215] = 'b';
            grid[8][215] = 'b';
            grid[10][215] = 'b';
            grid[11][215] = 'b';

            grid[1][216] = 'b';
            grid[2][216] = 'b';
            grid[3][216] = 'b';
            grid[4][216] = 'b';
            grid[5][216] = 'b';
            grid[6][216] = 'b';
            grid[7][216] = 'b';
            grid[8][216] = 'b';
            grid[9][216] = 'b';
            grid[10][216] = 'b';
            grid[11][216] = 'b';

            return new Level("Data/bg2.png", grid, 250, 14, 0.5f);

        case 2:

            width = 300;
            height = 14;
            grid = new char* [height];
            for (int i = 0; i < height; i++) {
                grid[i] = new char[width];
                for (int j = 0; j < width; j++) {
                    grid[i][j] = ' ';
                }
            }

            for (int j = 0; j < width; j++) {
                grid[0][j] = 'w';
                grid[12][j] = 'w';
                grid[13][j] = 'w';
            }
            for (int i = 0; i < height; i++) {
                grid[i][0] = 'w';
            }

            // Start platforms & early threats
            grid[9][5] = 'p'; grid[9][6] = 'p';
            grid[8][6] = 'R';
            grid[9][10] = 'p'; grid[9][11] = 'p'; grid[8][10] = 's';
            grid[11][12] = 'X';

            grid[9][20] = 'p';
            grid[10][20] = 'b';
            grid[11][20] = 'b';
            grid[8][21] = 'p';
            grid[7][22] = 'p';
            grid[6][23] = 'p';
            grid[5][24] = 'p';
            grid[4][25] = 'p';
            grid[5][26] = 'p';
            grid[6][27] = 'p';
            grid[7][28] = 'p';
            grid[8][29] = 'p';
            for (int i = 20; i <= 30; i++) { grid[10][i] = 'b'; grid[11][i] = 'b'; }
            for (int i = 21; i <= 29; i++) { grid[9][i] = 'w'; }
            for (int i = 22; i <= 28; i++) { grid[8][i] = 'w'; }
            for (int i = 23; i <= 27; i++) { grid[7][i] = 'w'; }
            for (int i = 24; i <= 26; i++) { grid[6][i] = 'w'; }
            grid[5][25] = 'b';
            grid[2][12] = 'B';

            // Enemies & traps zone
            grid[9][30] = 'p'; grid[10][30] = 'b'; grid[11][30] = 'b';
            grid[10][32] = 'B';
            grid[9][35] = 'p'; grid[9][36] = 'p';
            grid[8][36] = 's'; grid[7][36] = 'R';

            // High platform + boost
            grid[5][45] = 'p'; grid[5][46] = 'p';
            grid[4][45] = 'S';
            grid[11][50] = 'M';

            // Combo platform with pit
            grid[8][55] = 'p'; grid[8][56] = 'p'; grid[8][57] = 'p';
            for (int j = 58; j <= 60; j++) { grid[12][j] = 'd'; grid[13][j] = 'd'; }
            grid[7][61] = 'p'; grid[6][61] = 'R';

            // Bonus section with spike challenge
            grid[6][70] = 'p'; grid[6][71] = 'p'; grid[6][72] = 'p';
            grid[5][71] = 's'; grid[4][71] = 'R';
            grid[6][75] = 'p'; grid[6][76] = 'p';
            grid[5][75] = 'L';

            // BeeBot and ring challenge
            grid[7][85] = 'p'; grid[7][86] = 'p';
            grid[6][85] = 'B';
            grid[6][86] = 'R'; grid[5][86] = 'R';

            // Dangerous spike pit and vertical climb
            for (int j = 90; j <= 94; j++) { grid[12][j] = 'd'; grid[13][j] = 'd'; }
            grid[10][95] = 'p'; grid[9][95] = 'p';
            grid[8][95] = 'p'; grid[7][95] = 'p';
            grid[6][95] = 'S';

            // MotoBug in corridor
            grid[11][100] = 'X';
            grid[9][106] = 'p';
            grid[8][106] = 'R';
            grid[8][107] = 'p';
            grid[7][107] = 'R';
            grid[7][108] = 'p';
            grid[6][108] = 'R';
            grid[6][109] = 'p';
            grid[5][109] = 'R';

            // Upper platform + rings
            grid[5][110] = 'p'; grid[5][111] = 'p'; grid[4][110] = 'R'; grid[4][111] = 'R';

            // BatBrain trap
            grid[6][120] = 'p'; grid[6][121] = 'p';
            grid[5][120] = 'E';
            grid[5][121] = 'R';

            // Mid-pit surprise wall
            for (int j = 125; j <= 127; j++) { grid[12][j] = 'd'; grid[13][j] = 'd'; }
            grid[11][128] = 'p'; grid[10][128] = 'b';

            grid[11][135] = 'b';
            grid[10][135] = 'b';
            grid[9][135] = 'b';
            grid[10][136] = 'b';
            grid[9][136] = 'b';
            grid[8][136] = 'b';
            grid[9][137] = 'b';
            grid[8][137] = 'b';
            grid[7][137] = 'b';
            grid[8][138] = 'b';
            grid[7][138] = 'b';
            grid[6][138] = 'b';
            grid[7][139] = 'b';
            grid[6][139] = 'b';
            grid[5][139] = 'b';
            for (int i = 136; i <= 145; i++) { grid[11][i] = 'p'; }
            for (int i = 137; i <= 145; i++) { grid[10][i] = 'p'; }
            for (int i = 138; i <= 145; i++) { grid[9][i] = 'p'; }
            for (int i = 139; i <= 145; i++) { grid[8][i] = 'p'; }
            for (int i = 140; i <= 145; i++) { grid[7][i] = 'p'; }
            for (int i = 140; i <= 145; i++) { grid[6][i] = 'b'; }
            for (int i = 140; i <= 145; i++) { grid[5][i] = 'b'; }
            for (int i = 135; i <= 145; i++) {
                for (int j = 1; j <= 4; j++) grid[j][i] = 'w';
            }
            grid[5][135] = 'p';
            grid[6][135] = 'p';
            grid[7][135] = 'p';
            grid[8][135] = 'p';

            grid[5][136] = 'p';
            grid[6][136] = 'p';
            grid[7][136] = 'p';

            grid[5][137] = 'p';
            grid[6][137] = 'p';

            grid[5][138] = 'p';

            grid[4][146] = 'b';
            grid[5][146] = 'b';
            grid[6][146] = 'b';
            grid[7][146] = 'b';


            grid[6][147] = 'b';
            grid[7][147] = 'b';
            grid[8][147] = 'b';

            grid[7][148] = 'b';
            grid[8][148] = 'b';
            grid[9][148] = 'b';

            grid[8][149] = 'b';
            grid[9][149] = 'b';
            grid[10][149] = 'b';

            grid[9][150] = 'b';
            grid[10][150] = 'b';
            grid[11][150] = 'b';

            grid[5][147] = 'b';
            grid[4][147] = 'b';
            grid[3][147] = 'b';

            grid[4][148] = 'b';
            grid[3][148] = 'b';
            grid[2][148] = 'b';

            grid[3][149] = 'b';
            grid[2][149] = 'b';
            grid[1][149] = 'b';

            grid[5][148] = 'p';
            grid[6][148] = 'p';

            grid[5][149] = 'p';
            grid[4][149] = 'p';
            grid[6][149] = 'p';
            grid[7][149] = 'p';

            grid[3][150] = 'p';
            grid[4][150] = 'p';
            grid[5][150] = 'p';
            grid[6][150] = 'p';
            grid[7][150] = 'p';
            grid[8][150] = 'p';

            grid[3][151] = 'p';
            grid[4][151] = 'p';
            grid[5][151] = 'p';
            grid[6][151] = 'p';
            grid[7][151] = 'p';
            grid[8][151] = 'p';
            grid[9][151] = 'p';

            grid[3][152] = 'p';
            grid[4][152] = 'p';
            grid[5][152] = 'p';
            grid[6][152] = 'p';
            grid[7][152] = 'p';
            grid[8][152] = 'p';
            grid[9][152] = 'p';

            grid[1][146] = 'p';
            grid[2][146] = 'p';
            grid[3][146] = 'p';

            grid[1][147] = 'p';
            grid[2][147] = 'p';

            grid[1][148] = 'p';

            grid[8][146] = 'p';
            grid[9][146] = 'p';
            grid[10][146] = 'p';
            grid[11][146] = 'p';

            grid[9][147] = 'p';
            grid[10][147] = 'p';
            grid[11][147] = 'p';

            grid[10][148] = 'p';
            grid[11][148] = 'p';

            grid[11][149] = 'p';


            grid[10][230] = 'p'; grid[9][230] = 'R';
            grid[10][232] = 'p'; grid[9][232] = 'R';
            grid[9][234] = 's'; grid[8][234] = 'R';
            grid[11][235] = 'X';

            grid[8][238] = 'p'; grid[8][239] = 'p'; grid[7][239] = 's'; grid[6][239] = 'R';

            for (int j = 242; j <= 245; j++) {
                grid[12][j] = 'd';
                grid[13][j] = 'd';
            }
            grid[10][246] = 'p'; grid[9][246] = 'R';
            grid[10][248] = 'p'; grid[9][248] = 'R';
            grid[9][250] = 'M';

            grid[7][255] = 'p'; grid[6][255] = 'R';
            grid[6][256] = 'S';

            grid[8][260] = 'p'; grid[7][260] = 's'; grid[6][260] = 'R';
            grid[8][263] = 'p'; grid[8][264] = 'p';
            grid[7][265] = 'L';

            grid[5][270] = 'p'; grid[5][271] = 'p';
            grid[4][270] = 'C';

            for (int j = 275; j <= 278; j++) {
                grid[12][j] = 'd';
                grid[13][j] = 'd';
            }
            grid[10][279] = 'F';



            for (int i = 1; i < height; ++i) {
                for (int j = 0; j < width; ++j) {
                    if (grid[i][j] == 'p' && grid[i - 1][j] == ' ') {
                        grid[i - 1][j] = 'R';
                    }
                }
            }

            for (int i = 151; i <= 180; i++) {
                grid[10][i] = 'b';
                grid[11][i] = 'b';
            }
            for (int i = 181; i <= 199; i++) {
                grid[11][i] = 'R';
            }
            for (int i = 200; i <= 223; i++) {
                grid[10][i] = 'w';
                grid[11][i] = 'w';
            }
            for (int i = 150; i <= 223; i++) {
                grid[1][i] = 'b';
                grid[2][i] = 'b';
            }

            return new Level("Data/bg2.png", grid, width, height, 0.2f);

        case 3:

            width = 19;
            height = 14;
            grid = new char* [height];
            for (int i = 0; i < height; i++) {
                grid[i] = new char[width];
                for (int j = 0; j < width; j++) {
                    grid[i][j] = ' ';
                }
            }

            for (int j = 0; j < width; j++) {
                grid[0][j] = 'w';
                grid[12][j] = 'w';
                grid[13][j] = 'w';
            }
            for (int i = 0; i < height; i++) {
                grid[i][0] = 'w';
                grid[i][18] = 'w';
            }

            grid[11][5] = 'p';
            grid[11][6] = 'p';
            grid[11][7] = 'p';
            grid[11][8] = 'p';
            grid[11][9] = 'p';
            grid[11][10] = 'p';
            grid[11][11] = 'p';
            grid[11][12] = 'p';
            grid[11][13] = 'p';

            grid[8][1] = 'p';
            grid[8][2] = 'p';
            grid[8][3] = 'p';
            grid[8][4] = 'p';

            grid[8][14] = 'p';
            grid[8][15] = 'p';
            grid[8][16] = 'p';
            grid[8][17] = 'p';

            grid[3][2] = 'p';
            grid[3][3] = 'p';
            grid[3][4] = 'p';
            grid[3][5] = 'p';
            grid[3][6] = 'p';
            grid[3][7] = 'p';
            grid[3][8] = 'p';
            grid[3][9] = 'p';
            grid[3][10] = 'p';
            grid[3][11] = 'p';
            grid[3][12] = 'p';
            grid[3][13] = 'p';
            grid[3][14] = 'p';
            grid[3][15] = 'p';
            grid[3][16] = 'p';

            grid[2][3] = 'b';
            grid[2][4] = 'b';
            grid[2][5] = 'b';

            grid[2][7] = 'b';
            grid[2][8] = 'b';

            grid[2][10] = 'b';
            grid[2][11] = 'b';

            grid[2][13] = 'b';
            grid[2][14] = 'b';
            grid[2][15] = 'b';

            grid[1][3] = 'b';
            grid[1][4] = 'b';
            grid[1][5] = 'b';

            grid[1][7] = 'b';
            grid[1][8] = 'b';

            grid[1][10] = 'b';
            grid[1][11] = 'b';

            grid[1][13] = 'b';
            grid[1][14] = 'b';
            grid[1][15] = 'b';

            grid[6][9] = 'Y';

            for (int j = 1; j <= 18; j++) {
                grid[12][j] = 'b';
                grid[13][j] = 'b';
            }

            return new Level("Data/bg2.png", grid, width, height, 0.2f);

        default:
            return nullptr;

        }
    }
    ~LevelFactory() {
        for (int i = 0;i < height;i++) {
            delete[] grid[i];
        }
        delete[] grid;
    }
};
