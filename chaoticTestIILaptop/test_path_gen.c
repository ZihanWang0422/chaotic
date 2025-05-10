// Headers

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Colors

#define BLACK '0'
#define WHITE '1'
#define BLUE '2'
#define GREEN '3'
#define YELLOW '4'
#define RED '5' // to be used

// Initial Parameter

#define START_COLOR YELLOW
#define TREASURE_COLOR BLUE
#define FINISH_COLOR GREEN

// Misc

#define TILENUM 9       // 9*9 chessboard
#define MAXLENGTH 81    // 9*9=81 tiles
#define INF 0x3F3F3F3F  // infinity
#define FIND_TREASURE 1 // task flag for finding treasure
#define FIND_FINISH 0   // task flag for finding finish point

// Functions Declaration

// Recursive Acquisition of Path
void get_path(char *srcLine, int srcPoint, int dstPoint, FILE *targetFile);
// Edit distance between two points
void editDistance(int dstGraph[][MAXLENGTH], int target, char *srcLine);
// Initialize the Graph using srcline(description of the graph). Outputs dstgraph and special points in the graph.
void graph_init(char *srcLine, int dstGraph[][MAXLENGTH], int *dstStart, int *dstTreasure, int *dstFinish);
// A dijkstra algorithm to find the shortest path (outputline)
void dijkstra(int srcGraph[][MAXLENGTH], int srcPoint, int dstPoint, char *outputLine, int *outputLength, int taskFlag);

// Global Variables
FILE *in;
FILE *out[10];
// Main Function

int main()
{
    int start, treasure, finish, pathLength;
    int graph[MAXLENGTH][MAXLENGTH];
    char inputLine[MAXLENGTH * 2], outputline[MAXLENGTH * 9] = {0};
    in = fopen("field.txt", "r");
    out[FIND_FINISH] = fopen("findfinish.txt", "w");
    out[FIND_TREASURE] = fopen("findtreasure.txt", "w");
    fgets(inputLine, MAXLENGTH * 2, in);
    graph_init(inputLine, graph, &start, &treasure, &finish);
    dijkstra(graph, start, treasure, outputline, &pathLength, FIND_TREASURE);
    putchar('\n');
    dijkstra(graph, treasure, finish, outputline, &pathLength, FIND_FINISH);
    return 0;
}

// Functions Definition

void get_path(char *srcLine, int srcPoint, int dstPoint, FILE *targetFile)
{
    if (srcLine[dstPoint] == srcPoint)
        fprintf(targetFile, "%d ", srcPoint);
    else
        get_path(srcLine, srcPoint, srcLine[dstPoint], targetFile);
    fprintf(targetFile, "%d ", dstPoint);
    return;
}

void editDistance(int dstGraph[][MAXLENGTH], int target, char *srcLine)
{
    int up = target - 9;
    int down = target + 9;
    int left = target - 1;
    int right = target + 1;
    if (up > 0 && srcLine[up] != BLACK) dstGraph[target][up] = dstGraph[up][target] = 1;
    if (down < MAXLENGTH - 1 && srcLine[down] != BLACK) dstGraph[target][down] = dstGraph[down][target] = 1;
    if (left / TILENUM == target / TILENUM && srcLine[left] != BLACK) dstGraph[target][left] = dstGraph[left][target] = 1;
    if (right / TILENUM == target / TILENUM && srcLine[right] != BLACK) dstGraph[target][right] = dstGraph[up][right] = 1;
}

void graph_init(char *srcLine, int dstGraph[][MAXLENGTH], int *dstStart, int *dstTreasure, int *dstFinish)
{
    int curr, up, down, left, right;
    for (int i = 0; i < MAXLENGTH; ++i) {
        for (int j = 0; j < MAXLENGTH; ++j) {
            dstGraph[i][j] = INF;
        }
    }
    for (curr = 0; curr < MAXLENGTH; ++curr) {
        switch (srcLine[curr]) {
        case WHITE:
            editDistance(dstGraph, curr, srcLine);
            break;
        case START_COLOR:
            editDistance(dstGraph, curr, srcLine);
            *dstStart = curr;
            break;
        case FINISH_COLOR:
            editDistance(dstGraph, curr, srcLine);
            *dstFinish = curr;
            break;
        case TREASURE_COLOR:
            *dstTreasure = curr;
            break;
        default:
            break;
        }
    }
}

void dijkstra(int srcGraph[][MAXLENGTH], int srcPoint, int dstPoint, char *outputLine, int *outputLength, int taskFlag)
{
    char *outputPtr = outputLine;
    int min, tmp = -1;
    int isFound[MAXLENGTH] = {0}, sweight[MAXLENGTH] = {0};
    for (int i = 0; i < MAXLENGTH; ++i) {
        sweight[i] = srcGraph[srcPoint][i];
        outputLine[i] = srcPoint + 1;
    }
    sweight[srcPoint] = 0;
    isFound[srcPoint] = 1;
    for (int i = 1; i < MAXLENGTH; ++i) {
        min = INF;
        for (int j = 0; j < MAXLENGTH; ++j) {
            if (isFound[j] == 0 && sweight[j] < min) {
                min = sweight[j];
                tmp = j;
            }
        }
        isFound[tmp] = 1;
        for (int j = 0; j < MAXLENGTH; ++j) {
            if (isFound[j] == 0 && min + srcGraph[tmp][j] < sweight[j]) {
                sweight[j] = min + srcGraph[tmp][j];
                if (sweight[j] > INF) sweight[j] = INF;
                outputLine[j] = tmp + 1;
            }
        }
    }
    printf("\n\n%d\n\n", sweight[dstPoint]);
    *outputLength = strlen(outputLine);
    for (int i = 0; i < *outputLength; ++i)
        outputLine[i]--;
    get_path(outputLine, srcPoint, dstPoint, out[taskFlag]);
    for (int i = 0; i < *outputLength; ++i)
        outputLine[i]++;
}
