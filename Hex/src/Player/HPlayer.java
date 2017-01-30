package Player;

import HexagonalMap.Cell;
import HexagonalMap.FieldModel;

import java.awt.*;
import java.util.ArrayList;


public class HPlayer implements Player {
    private int id;
    private boolean turn;
    private FieldModel field;
    private int score = 0;
    public HPlayer(int id, FieldModel field, boolean turn){
        this.id = id;
        this.field = field;
        this.turn = turn;
    }

    public int getId(){
        return  id;
    }
    @Override
    public int getNumberOfCells(){
        int numberOfCells = 0;
        for(int i = 0; i < FieldModel.SIZE; i++) {
            for (int j = 0; j < FieldModel.SIZE; j++) {
                if(field.getCell(i,j).getPlayer() == id){
                    numberOfCells++;
                }
            }
        }
        return  numberOfCells;
    }
    @Override
    public void resScore(){
        score = 0;
    }

    @Override
    public void refreshField(FieldModel fieldModel) {
        this.field = fieldModel;
    }


    private void captureEnemyCells(int x, int y){
        ArrayList<Cell> cells = field.getNeigbours(x, y);
        for(Cell cur : cells){
            Cell temp = field.getCell(cur.getXY().x, cur.getXY().y);
            if(temp.getPlayer() != FieldModel.EMPTY) {
                field.SetCoordinates(temp.getXY().x, temp.getXY().y, id, true);
            }
        }
    }

    private  void upCell(){
        Point user = field.getUserPoint();
        Cell curCell = field.getCell(user.x, user.y);
        if (curCell.getPlayer() == FieldModel.SIZE) {
            return;
        } else if (curCell.getPlayer() == id) {
            if (!curCell.getState()) {
                curCell.setState(true);
            } else {
                curCell.setState(false);
            }
        }
        return;
    }
    @Override
    public void makeStep() {
        Point user = field.getUserPoint();
        Cell curCell = field.getCell(user.x, user.y);
        Cell upCell = field.findUpCell();
        if (upCell == null) {
            upCell();
        } else {
            if (curCell.getPlayer() == FieldModel.EMPTY) {
                ArrayList<Cell> firstLevelCells = field.getPossibleFirstLevelMovements(upCell.getXY().x, upCell.getXY().y, true);
                for (Cell target : firstLevelCells) {
                    if (user.equals(target.getXY())) {
                        field.SetCoordinates(user.x, user.y, id, true);
                        captureEnemyCells(user.x, user.y);
                        upCell.setState(false);
                        setTurn(false);
                        return;
                    }
                }
                ArrayList<Cell> firstLevelCells2 = field.getPossibleFirstLevelMovements(upCell.getXY().x, upCell.getXY().y, false);
                ArrayList<Cell> secondLevelCells = field.getPossibleSecondLevelMovements(firstLevelCells2);
                for (Cell target : secondLevelCells) {
                    if (user.equals(target.getXY())) {
                        field.SetCoordinates(user.x, user.y, id, false);
                        captureEnemyCells(user.x, user.y);
                        upCell.setState(false);
                        setTurn(false);
                        return;
                    }
                }
                upCell.setState(true);
                setTurn(true);
            }
        }
    }

    @Override
    public boolean getTurn() {
        return turn;
    }

    @Override
    public void setTurn(boolean turn) {
        this.turn = turn;
    }

    @Override
    public boolean haveSteps(){
        int count = 0;
        for(int i = 0;i < FieldModel.SIZE; i++){
            for(int j = 0; j < FieldModel.SIZE; j++){
                if(field.getCell(i,j).getPlayer() == id) {
                    ArrayList<Cell> firstlevel = field.getPossibleFirstLevelMovements(i, j, false);
                    ArrayList<Cell> secondlevel = field.getPossibleSecondLevelMovements(firstlevel);
                    for(Cell cur: firstlevel) {
                        if (cur.getPlayer() == FieldModel.EMPTY) {
                            count++;
                        }
                    }
                    for(Cell cur: secondlevel) {
                        if (cur.getPlayer() == FieldModel.EMPTY) {
                            count++;
                        }
                    }
                }
            }
        }
        return count != 0;
    }
}
