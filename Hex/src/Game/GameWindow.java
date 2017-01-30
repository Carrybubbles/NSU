package Game;

import pMenu.Menu;
import pMenu.GameModel;

import javax.swing.*;
import java.awt.*;

/**
 * Created by artem on 21.03.16.
 */
public class GameWindow extends JFrame {
    private GameModel model;
    private Menu menu = new Menu();
    public GameWindow(GameModel menu) {
        this.model = menu;
        setSize(500,500);
        //setPreferredSize(new Dimension(500,500));
        add(this.menu, BorderLayout.CENTER);
        pack();
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setVisible(true);

    }
    public Menu getMenu(){
        return menu;
    }
}
