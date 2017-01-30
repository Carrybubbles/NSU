package Player;

import HexagonalMap.Cell;
import HexagonalMap.FieldModel;

import java.awt.*;
import java.util.ArrayList;
import java.util.Random;

public class AIPlayer implements Player {
    private int id;
    private boolean turn = false;
    private FieldModel field;
    private  int score = 0;
    private ArrayList<Cell> hexes = new ArrayList<>();
    public AIPlayer(int id, FieldModel field){
        this.id = id;
        this.field = field;
        refresh();
    }

    public int getId(){
        return  id;
    }


    private void refresh(){
        hexes = new ArrayList<>();
        for(int i = 0; i < FieldModel.SIZE; i++){
            for(int j = 0; j < FieldModel.SIZE; j++){
                if(field.getCell(i,j).getPlayer() == id){
                    hexes.add(field.getCell(i,j));
                }
            }
        }
    }

    @Override
    public boolean haveSteps() {
        int count = 0;
        for(int i = 0;i < FieldModel.SIZE; i++){
            for(int j = 0; j < FieldModel.SIZE; j++){
                if(field.getCell(i,j).getPlayer() == id) {
                    ArrayList<Cell> firstlevel = field.getPossibleFirstLevelMovements(i, j, false);
                    ArrayList<Cell> firstlevel2 = field.getPossibleFirstLevelMovements(i, j, true);
                    ArrayList<Cell> secondlevel = field.getPossibleSecondLevelMovements(firstlevel2);
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

    private void captureEnemyCells(int x, int y){
        ArrayList<Cell> cells = field.getNeigbours(x, y);
        for(Cell cur : cells){
            Cell temp = field.getCell(cur.getXY().x, cur.getXY().y);
            if(temp.getPlayer() != FieldModel.EMPTY) {
                field.SetCoordinates(temp.getXY().x, temp.getXY().y, id, true);
            }
        }
    }
    private void upCell(){
        refresh();
        Cell curCell = null;
        for(Cell cur: hexes){
            ArrayList<Cell>  firstlevel = field.getPossibleFirstLevelMovements(cur.getXY().x,cur.getXY().y,true);
            ArrayList<Cell>  firstlevel2 = field.getPossibleFirstLevelMovements(cur.getXY().x,cur.getXY().y,false);
            ArrayList<Cell>  secondlevel = field.getPossibleSecondLevelMovements(firstlevel2);
            if(!firstlevel.isEmpty()){
                Point point = cur.getXY();
                curCell = field.getCell(point.x, point.y);
                curCell.setState(true);
                break;
            }else if(!secondlevel.isEmpty()){
                Point point = cur.getXY();
                curCell = field.getCell(point.x, point.y);
                curCell.setState(true);
                break;
            }
        }
    }

    @Override
    public void makeStep(){
        upCell();
        Cell upCell = field.findUpCell();
        if(upCell == null){
            return;
        }
        Random rnd = new Random();
        ArrayList<Cell> firstlevel = field.getPossibleFirstLevelMovements(upCell.getXY().x, upCell.getXY().y,true);
        if(!firstlevel.isEmpty()){
            Point point = firstlevel.get(rnd.nextInt(firstlevel.size())).getXY();
            field.SetCoordinates(point.x, point.y, id, true);
            captureEnemyCells(point.x, point.y);
            upCell.setState(false);
            setTurn(false);
            return;
        }
        ArrayList<Cell> firstLevel2 = field.getPossibleFirstLevelMovements(upCell.getXY().x, upCell.getXY().y, false);
        ArrayList<Cell> secondlevel = field.getPossibleSecondLevelMovements(firstLevel2);

        if(!secondlevel.isEmpty()){
            Point point = secondlevel.get(rnd.nextInt(secondlevel.size())).getXY();
            field.SetCoordinates(point.x, point.y, id, false);
            captureEnemyCells(point.x, point.y);
            upCell.setState(false);
            setTurn(false);
        }
    }

    @Override
    public void refreshField(FieldModel fieldModel) {
        this.field = fieldModel;
    }

    @Override
    public boolean getTurn() {
        return turn;
    }

    @Override
    public void setTurn(boolean turn) {
        this.turn = turn;
    }

}
