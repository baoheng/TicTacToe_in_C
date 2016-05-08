#ifndef TIC_TAC_TOE_H
#define TIC_TAC_TOE_H

enum Marker
{
    X,
    O,
    EMPTY
};

Marker ** createBoard();
char* getBoardDisplay(Marker** board);
void markTheBoard(Marker** board, Marker m, int pos);
bool hasWon(Marker** board, Marker m);
char toChar(Marker m);
bool isTie(Marker** board);

#endif