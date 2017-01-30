package Game;

import HexagonalMap.FieldModel;
import Player.HPlayer;
import Player.Player;
import Player.AIPlayer;
import pMenu.MenuModel;

public class GameModel{
    private Player[] players = new Player[2];
    private FieldModel fieldModel;
    private MenuModel menuModel;
    public GameModel(FieldModel field, MenuModel menuModel){
        this.fieldModel = field;
        this.menuModel = menuModel;
        players[Player.ONE] = new HPlayer(1,fieldModel,true);
        players[Player.TWO] = new HPlayer(2,fieldModel,false);
    }
    public void setPVEunits(){
        players[Player.ONE] = new HPlayer(1,fieldModel,true);
        players[Player.TWO] = new AIPlayer(2,fieldModel);

    }
    public void setPVPunits(){
        players[Player.ONE] = new HPlayer(1,fieldModel,true);
        players[Player.TWO] = new HPlayer(2,fieldModel,false);

    }
    public FieldModel getFieldModel(){
        return  fieldModel;
    }

    public void setFieldModel(FieldModel model){
        fieldModel = model;
    }

    public MenuModel getMenuModel(){
        return menuModel;
    }

    public void move(Player player){
        player.makeStep();
    }

    public void resetGame(){
        getFieldModel().reset();
        players[Player.ONE].setTurn(true);
        players[Player.TWO].setTurn(false);
        players[Player.ONE].resScore();
        players[Player.TWO].resScore();
        getMenuModel().reset();
    }
    public Player[] getPlayers(){
        return  players;
    }

    public boolean lost(){
        if(players[Player.ONE].getNumberOfCells() == FieldModel.EMPTY || players[Player.TWO].getNumberOfCells() == FieldModel.EMPTY) {
            return true;
        }
        if(!players[Player.ONE].haveSteps() || !players[Player.TWO].haveSteps()){
            return  true;
        }
        return  false;
    }
}
