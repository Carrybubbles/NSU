package HexagonalMap;


import Player.Player;

import java.awt.*;
import java.util.ArrayList;
import java.util.Observable;


public class FieldModel extends Observable{
    public static final int SIZE = 8;
    public static final int EMPTY = 0;
    private Cell[][] board = new Cell[SIZE][SIZE];
    private Point userPoint = new Point(0,0);

    public Point getUserPoint(){
        return userPoint;
    }

    public void setUserPoint(Point point){
            userPoint = point;
            setChanged();
            notifyObservers(true);
    }
    private void initPlayersCells(){
        board[0][SIZE - 1].setPlayer(Player.TWO + 1);
        board[SIZE - 1][0].setPlayer(Player.TWO + 1);
        board[0][0].setPlayer(Player.ONE + 1);
        board[SIZE - 1][SIZE - 1].setPlayer(Player.ONE + 1);
    }

    public FieldModel(){
        for(int i = 0 ; i < SIZE; i++){
            for(int j = 0; j < SIZE; j++){
                board[i][j] = new Cell(new Point(i,j));
            }
        }
        initPlayersCells();

    }

    public Cell findUpCell(){
        for(int i = 0; i < SIZE; i++){
            for(int j = 0 ;j < SIZE; j++){
                if(board[i][j].getState()){
                    return board[i][j];
                }
            }
        }
        return  null;
    }

    public void SetCoordinates(int x, int y, int player, boolean duplicate){
        if(duplicate) {
            board[x][y].setPlayer(player);
        }else {
            Cell upCell = findUpCell();
            board[upCell.getXY().x][upCell.getXY().y].setPlayer(FieldModel.EMPTY);
            board[x][y].setPlayer(player);
        }
    }

    public int getPlayerCell(int x, int y){
        return board[x][y].getPlayer();
    }

    public Cell getCell(int x, int y){
        return board[x][y];
    }

    public ArrayList<Cell> getNeigbours(int x, int y){
        ArrayList<Cell> neig = new ArrayList<>();
        Point[] neigPos = new Point[6];
        if(x%2 == 0){
            neigPos[0] = new Point(-1, -1);
            neigPos[1] = new Point(-1, 0);
            neigPos[2] = new Point(0, -1);
            neigPos[3] = new Point(1, -1);
            neigPos[4] = new Point(0, 1);
            neigPos[5] = new Point(1, 0);

        }else{
            neigPos[0] = new Point(0, 1);
            neigPos[1] = new Point(-1, 0);
            neigPos[2] = new Point(0, -1);
            neigPos[3] = new Point(-1, 1);
            neigPos[4] = new Point(1, 1);
            neigPos[5] = new Point(1, 0);

        }
        for(int i = 0; i < 6 ; i++){
            if((neigPos[i].x + x )>= 0 && (neigPos[i].x + x) <SIZE && (neigPos[i].y + y) >= 0 && (neigPos[i].y + y) < SIZE){
                neig.add(getCell(x + neigPos[i].x, y + neigPos[i].y));
            }
        }
        return neig;
    }

    public ArrayList<Cell> getPossibleFirstLevelMovements(int x, int y, boolean flag) {
        ArrayList<Cell> neighbours = getNeigbours(x, y);
        ArrayList<Cell> possibleCell = new ArrayList<>();
        for(Cell cur: neighbours){
            if(cur.getPlayer() == EMPTY && flag){
                possibleCell.add(cur);
            }else if(!flag){
                possibleCell.add(cur);
            }
        }
        return  possibleCell;
    }


    public ArrayList<Cell> getPossibleSecondLevelMovements(ArrayList<Cell> firstLevel){
        ArrayList<Cell> possibleCell = new ArrayList<>();
        for(Cell cur: firstLevel) {
            ArrayList<Cell> neighbours = getNeigbours(cur.getXY().x, cur.getXY().y);
            for (Cell possibleNeigh : neighbours) {
                if(possibleNeigh.getPlayer() == EMPTY) {
                   possibleCell.add(possibleNeigh);
                }
            }
        }
        return possibleCell;
    }



    public void reset(){
        for(int i = 0 ;i < SIZE; i++){
            for(int j = 0; j < SIZE; j++){
                board[i][j].setPlayer(EMPTY);
                board[i][j].setState(false);
            }
        }
        initPlayersCells();
    }

}
