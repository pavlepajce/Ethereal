/*
  Ethereal is a UCI chess playing engine authored by Andrew Grant.
  <https://github.com/AndyGrant/Ethereal>     <andrew@grantnet.us>

  Ethereal is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  Ethereal is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef _SEARCH_H
#define _SEARCH_H

#include <stdint.h>

#include "types.h"

struct SearchInfo {
    int depth;
    int values[MAX_PLY];
    uint16_t bestMoves[MAX_PLY];
    uint16_t ponderMoves[MAX_PLY];
    double startTime;
    double idealUsage;
    double maxAlloc;
    double maxUsage;
    int pvFactor;
};

struct PVariation {
    uint16_t line[MAX_PLY];
    int length;
};


void initSearch();

void getBestMove(Thread* threads, Board* board, Limits* limits, uint16_t *best, uint16_t *ponder);

void* iterativeDeepening(void* vthread);

int aspirationWindow(Thread* thread, int depth, int lastValue);

int search(Thread* thread, PVariation* pv, int alpha, int beta, int depth, int height);

int qsearch(Thread* thread, PVariation* pv, int alpha, int beta, int height);

int staticExchangeEvaluation(Board* board, uint16_t move, int threshold);

int moveIsTactical(Board* board, uint16_t move);

int hasNonPawnMaterial(Board* board, int turn);

int valueFromTT(int value, int height);

int valueToTT(int value, int height);

int thisTacticalMoveValue(Board* board, uint16_t move);

int bestTacticalMoveValue(Board* board);

int moveIsSingular(Thread* thread, uint16_t ttMove, int ttValue, int depth, int height);

static const int SMPCycles      = 16;
static const int SkipSize[16]   = { 1, 1, 1, 2, 2, 2, 1, 3, 2, 2, 1, 3, 3, 2, 2, 1 };
static const int SkipDepths[16] = { 1, 2, 2, 4, 4, 3, 2, 5, 4, 3, 2, 6, 5, 4, 3, 2 };

static const int WindowDepth   = 5;
static const int WindowSize    = 14;
static const int WindowTimerMS = 5000;

static const int RazorDepth = 1;
static const int RazorMargin = 350;

static const int BetaPruningDepth = 8;
static const int BetaMargin = 85;

static const int NullMovePruningDepth = 2;

static const int ProbCutDepth = 5;
static const int ProbCutMargin = 100;

static const int FutilityMargin = 95;
static const int FutilityPruningDepth = 8;
static const int FutilityPruningHistoryLimit[] = { 12000, 6000 };

static const int CounterMovePruningDepth[] = { 3, 2 };
static const int CounterMoveHistoryLimit[] = { 0, -1000 };

static const int FollowUpMovePruningDepth[] = { 3, 2 };
static const int FollowUpMoveHistoryLimit[] = { -2000, -4000 };

static const int LateMovePruningDepth = 8;
static const int LateMovePruningCounts[2][9] = {
    {  0,  3,  4,  7, 12, 16, 21, 28, 34},
    {  0,  5,  7, 12, 18, 27, 38, 50, 65},
};

static const int SEEPruningDepth = 8;
static const int SEEQuietMargin = -85;
static const int SEENoisyMargin = -20;

static const int QSEEMargin = 1;

static const int QFutilityMargin = 100;

static const int SEEPieceValues[] = {
     100,  450,  450,  675,
    1300,    0,    0,    0,
};

#endif
