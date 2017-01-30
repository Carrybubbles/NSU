package pMenu;

import javax.imageio.ImageIO;
import javax.swing.*;
import java.awt.*;
import java.awt.image.BufferedImage;
import java.io.File;
import java.io.IOException;

public class MenuViewer extends JPanel{
    private JButton PVP = new JButton("Player vs Player");
    private JButton PVE = new JButton("Player vs Bot");
    private JButton quit = new JButton("Quit");
    private ClassLoader classLoader = getClass().getClassLoader();
    private BufferedImage background = ImageIO.read(new File(classLoader.getResource("resources/background.png").getFile()));
    private MenuModel model;

    public MenuViewer(MenuModel model) throws IOException {
        this.model = model;
        add(PVE);
        add(PVP);
        add(quit);
        setLayout(new FlowLayout(FlowLayout.LEFT));
        quit.setVisible(false);
    }

    public JButton getPVP(){
        return PVP;
    }

    public JButton getPVE(){
        return PVE;
    }

    public JButton getQuit(){
        return quit;
    }

    public void blindButtons(boolean flag){
        PVP.setVisible(flag);
        PVE.setVisible(flag);
        quit.setVisible(!flag);
    }

    @Override
    public void paintComponent(Graphics g)
    {
        super.paintComponent(g);
        if (background != null)
        {
            g.drawImage(background,0,0,this);
        }
    }


}