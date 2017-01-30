package HexagonalMap;

import java.awt.*;

public class Cell {
    private int player = 0;
    private boolean state = false;
    private Point point = new Point(-1,-1);

    public Cell(){}
    public Cell(Point point){
        this.point = point;
    }

    public boolean getState(){
        return state;
    }

    public Point getXY(){
        return point;
    }
    public int getPlayer(){
        return  player;
    }

    public void setPlayer(int player){
        this.player = player;

    }

    public void setState(boolean state) {
        this.state = state;
    }
}
