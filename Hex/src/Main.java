import Game.GameController;
import Game.GameModel;
import Game.GameViewer;
import HexagonalMap.FieldModel;
import pMenu.MenuModel;

import javax.swing.*;
import java.io.IOException;

/**
 * Created by artem on 19.03.16.
 */
public class Main {
    public static void main(String[] args) throws IOException {
        MenuModel menuModel = new MenuModel();

        FieldModel fieldModel = new FieldModel();
        System.out.println(Thread.currentThread().getId());

        GameModel gameModel = new GameModel(fieldModel, menuModel);
        GameViewer gameViewer = new GameViewer(gameModel);
        GameController controller = new GameController(gameModel, gameViewer);
    }
}
