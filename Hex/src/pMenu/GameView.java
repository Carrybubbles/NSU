package pMenu;

import HexagonalMap.FieldController;
import HexagonalMap.FieldModel;
import HexagonalMap.FieldViewer;
import HexagonalMap.Hexagon;

import javax.swing.*;
import java.awt.*;
import java.awt.event.MouseAdapter;

/**
 * Created by artem on 21.03.16.
 */
public class GameView extends JFrame{
    private Menu menu = new Menu();

    private GameModel model;
    private FieldModel model2 = new FieldModel();

    private FieldViewer field = new FieldViewer(model2);
    //?????
    FieldController controller2 = new FieldController(model2, field);

    public GameView(GameModel model) {
        this.model = model;
        setSize(1000,1000);
        setPreferredSize(new Dimension(500,500));
        addMouseListener(controller2);
        field.setSize(350,350);
        add(menu, BorderLayout.NORTH);
        add(field, BorderLayout.CENTER);
        setPreferredSize(new Dimension(250,250));
        setResizable(false);

        //pack();
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setVisible(true);

    }

    @Override
    public void paint(Graphics g) {
        super.paint(g);
        //field.paint(g);
    }

    public Menu getMenu(){
        return menu;
    }
    public FieldViewer getField(){
        return field;
    }
    public static void main(String[] args) {
        GameModel model = new GameModel();
        GameView view = new GameView(model);
    }
}
