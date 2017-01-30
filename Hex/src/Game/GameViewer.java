package Game;

import HexagonalMap.FieldViewer;
import Player.Player;
import pMenu.MenuViewer;

import javax.imageio.ImageIO;
import javax.swing.*;
import java.awt.*;
import java.awt.image.BufferedImage;
import java.io.File;
import java.io.IOException;

public class GameViewer extends JFrame{
    private MenuViewer menuViewer;
    private FieldViewer fieldViewer;
    private JLabel playerIcon = new JLabel();
    private JLabel[] score = new JLabel[3];
    private LostFrame lostframe = new LostFrame();
    private ClassLoader classLoader = getClass().getClassLoader();
    private final BufferedImage playerImage = ImageIO.read(new File(classLoader.getResource("resources/mortalkombat2_128.png").getFile()));
    private GameModel model;

    public GameViewer(GameModel model) throws IOException {
            fieldViewer = new FieldViewer(model.getFieldModel());
            menuViewer = new MenuViewer(model.getMenuModel());
        this.model = model;
        setSize(800,800);
        score = initScore();
        add(menuViewer, BorderLayout.NORTH);
        add(fieldViewer, BorderLayout.CENTER);
        add(playerIcon, BorderLayout.EAST);
        lostframe.setVisible(false);
        FlowLayout postion = new FlowLayout();
        menuViewer.setLayout(postion);
        getContentPane().setBackground(new Color(0, 0, 0));
        for(JLabel cur: score){
            menuViewer.add(cur);
        }

        playerIcon.setIcon(new ImageIcon(playerImage));
        setResizable(false);
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setVisible(true);

    }

    public FieldViewer getFieldViewer(){
        return  fieldViewer;
    }

    public MenuViewer getMenuViewer(){
        return  menuViewer;
    }

    public LostFrame getLostframe(){
        return lostframe;
    }

    @Override
    public void paint(Graphics g) {
        super.paint(g);
    }
    public JLabel[] getScores(){
        return  score;
    }
    private JLabel[] initScore(){
        JLabel[] temp = new JLabel[3];
        for(int i = 0; i < 3; i++){
            temp[i] = new JLabel();
        }

        temp[0].setFont(new Font("Georgia", Font.PLAIN, 30));
        temp[0].setForeground(new Color(41, 42, 255));
        temp[0].setText(String.valueOf(model.getPlayers()[Player.ONE].getNumberOfCells()));
        temp[1].setFont(new Font("Georgia", Font.PLAIN, 30));
        temp[1].setForeground(new Color(255, 9, 10));
        temp[1].setText("Score");
        temp[2].setFont(new Font("Georgia", Font.PLAIN, 30));
        temp[2].setForeground(new Color(247, 231, 20));
        temp[2].setText(String.valueOf(model.getPlayers()[Player.TWO].getNumberOfCells()));
        return temp;
    }

    public void setIcon(int id) throws IOException {
        if(id == Player.TWO) {
            BufferedImage myPicture = ImageIO.read(new File(classLoader.getResource("resources/mortalkombat3_128.png").getFile()));
            playerIcon.setIcon(new ImageIcon(myPicture));
        }else if(id == Player.ONE) {
            BufferedImage myPicture = ImageIO.read(new File(classLoader.getResource("resources/mortalkombat2_128.png").getFile()));
            playerIcon.setIcon(new ImageIcon(myPicture));
        }
        playerIcon.repaint();
    }
}
