package pMenu;

import javax.swing.*;
import java.awt.*;

/**
 * Created by artem on 21.03.16.
 */
public class Menu extends JMenuBar {
    private JButton PVP = new JButton("Player vs Player");
    private JButton PVE = new JButton("Player vs Bot");
    public Menu(){
        add(PVE);
        add(PVP);

        setLayout(new FlowLayout(FlowLayout.LEFT));

    }
    public JButton getPVP(){
        return PVP;
    }
    public JButton getPVE(){
        return PVE;
    }

}