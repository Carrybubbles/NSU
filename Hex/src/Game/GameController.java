package Game;

import HexagonalMap.FieldController;
import HexagonalMap.FieldModel;
import Player.Player;
import pMenu.MenuController;
import pMenu.MenuModel;

import javax.swing.*;
import java.io.IOException;
import java.util.Observable;
import java.util.Observer;


public class GameController implements Observer {
    GameModel model;
    GameViewer viewer;
    FieldController fieldController;
    MenuController menuController;

    public GameController(GameModel model,GameViewer viewer){
        this.model = model;
        this.viewer = viewer;

        model.getFieldModel().addObserver(this);
        model.getMenuModel().addObserver(this);

        fieldController = new FieldController(model.getFieldModel(),viewer.getFieldViewer());
        menuController = new MenuController(model.getMenuModel(),viewer.getMenuViewer());

    }
    @Override
    public void update(Observable o, Object arg) {
        if (o == model.getFieldModel()) {
            model.setFieldModel((FieldModel) o);
            if(model.getMenuModel().getModes() == MenuModel.Modes.PVP) {
                try {
                    run();
                } catch (IOException e) {
                    return;
                }
            }else if(model.getMenuModel().getModes() == MenuModel.Modes.PVE){
                try{
                    runAI();
                }catch (IOException e){
                    return;
                }
            }
        } else if (o == model.getMenuModel() && model.getMenuModel().getGameStatus()) {
            if(model.getMenuModel().getModes() == MenuModel.Modes.PVE){
                model.setPVEunits();
            }else{
                model.setPVPunits();
            }
            SwingUtilities.invokeLater(() -> {
                viewer.getFieldViewer().setVisible(true);
                viewer.getMenuViewer().blindButtons(false);
            });
        } else if (o == model.getMenuModel() && !model.getMenuModel().getGameStatus()){
            //quit game
            SwingUtilities.invokeLater(() -> {
                viewer.getFieldViewer().setVisible(false);
                viewer.getMenuViewer().blindButtons(true);

                if (viewer.getLostframe().isVisible()) {
                    viewer.getLostframe().closeWindow();
                }
            });

            model.resetGame();
            showScore();

            SwingUtilities.invokeLater(() -> {
                try {
                    viewer.setIcon(Player.ONE);
                } catch (IOException e) {
                    return;
                }
            });
        }
        SwingUtilities.invokeLater(() -> viewer.getFieldViewer().repaint());

    }
    private void run() throws IOException {

        if (model.getPlayers()[Player.ONE].getTurn()) {
            model.move(model.getPlayers()[Player.ONE]);
            if(!model.getPlayers()[Player.ONE].getTurn()){
                model.getPlayers()[Player.TWO].setTurn(true);
            }
        } else if (model.getPlayers()[Player.TWO].getTurn()) {
            model.move(model.getPlayers()[Player.TWO]);
            if(!model.getPlayers()[Player.TWO].getTurn()){
                model.getPlayers()[Player.ONE].setTurn(true);
            }
        }

        SwingUtilities.invokeLater(() -> showScore());

        if(model.getPlayers()[Player.ONE].getTurn()) {
            SwingUtilities.invokeLater(() -> {
                try {
                    viewer.setIcon(Player.ONE);
                } catch (IOException e) {
                    return;
                }
            });
        } else if(model.getPlayers()[Player.TWO].getTurn()){
            SwingUtilities.invokeLater(() -> {
                try {
                    viewer.setIcon(Player.TWO);
                } catch (IOException e) {
                    e.printStackTrace();
                }
            });
        }
        if(model.lost()){
            SwingUtilities.invokeLater(this::showLostFrame);
        }
    }

    private void runAI() throws IOException {
        if (model.getPlayers()[Player.ONE].getTurn()) {
            model.move(model.getPlayers()[Player.ONE]);
            if(!model.getPlayers()[Player.ONE].getTurn()){
                model.getPlayers()[Player.TWO].setTurn(true);
            }
        }
        viewer.repaint();
        if (model.getPlayers()[Player.TWO].getTurn()) {
            model.move(model.getPlayers()[Player.TWO]);
            if(!model.getPlayers()[Player.TWO].getTurn()) {
                model.getPlayers()[Player.ONE].setTurn(true);
            }
        }

        showScore();

        if(model.getPlayers()[Player.ONE].getTurn() && model.getFieldModel().findUpCell() != null) {
            SwingUtilities.invokeLater(() -> {
                try {
                    viewer.setIcon(Player.ONE);
                } catch (IOException e) {
                    e.printStackTrace();
                    return;
                }
            });
        }
        else if(model.getPlayers()[Player.TWO].getTurn() && model.getFieldModel().findUpCell() != null){
            SwingUtilities.invokeLater(() -> {
                try {
                    viewer.setIcon(Player.TWO);
                } catch (IOException e) {
                    e.printStackTrace();
                    return;
                }
            });
        }

        if(model.lost()){
            showLostFrame();
        }

    }
    private void showLostFrame(){
        viewer.getLostframe().setVisible(true);
        viewer.getLostframe().getSong().play();
        viewer.getFieldViewer().setVisible(false);
    }

    private void showScore(){
        viewer.getScores()[Player.ONE].setText(String.valueOf(model.getPlayers()[Player.ONE].getNumberOfCells()));
        viewer.getScores()[Player.TWO+1].setText(String.valueOf(model.getPlayers()[Player.TWO].getNumberOfCells()));
    }

}
