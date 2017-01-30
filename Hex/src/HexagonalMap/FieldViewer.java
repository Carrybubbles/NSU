package HexagonalMap;

import javax.imageio.ImageIO;
import javax.swing.*;
import java.awt.*;
import java.awt.image.BufferedImage;
import java.io.File;
import java.io.IOException;
import java.util.ArrayList;


public class FieldViewer extends JPanel{
    private FieldModel model;
    private Hexagon Hex = new Hexagon(50, 60);
    ClassLoader classLoader = getClass().getClassLoader();
    BufferedImage background = ImageIO.read(new File(classLoader.getResource("resources/background.png").getFile()));

    public FieldViewer(FieldModel model) throws IOException {
        this.model = model;
        setVisible(false);
    }

    @Override
    public void paint(Graphics g) {
        super.paint(g);
        Graphics2D g2d = (Graphics2D) g;
        drawHexagons(g2d);
        showPossibleMovement(g2d);
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

    public Hexagon getHex(){
        return Hex;
    }

    public void showPossibleMovement(Graphics g) {
        if(model.findUpCell() != null) {
            Cell upCell = model.findUpCell();
            ArrayList<Cell> firslLevel = model.getPossibleFirstLevelMovements(upCell.getXY().x, upCell.getXY().y,true);
            ArrayList<Cell> firslLevel2 = model.getPossibleFirstLevelMovements(upCell.getXY().x, upCell.getXY().y,false);
            ArrayList<Cell> secondLevel = model.getPossibleSecondLevelMovements(firslLevel2);
            for (Cell cur : secondLevel) {
                Point myPoint = cur.getXY();
                Hex.drawHex(myPoint.x, myPoint.y, new Color(158, 29, 254), true, (Graphics2D) g);
            }
            for (Cell cur : firslLevel) {
                Point myPoint = cur.getXY();
                Hex.drawHex(myPoint.x, myPoint.y, new Color(23, 255, 18), true, (Graphics2D) g);
            }
        }
    }
    public void drawHexagons(Graphics2D g){
        g.setStroke(new BasicStroke(5));
        g.drawRect(0,0,getWidth(), getHeight());

        for (int y1 = 0; y1 < FieldModel.SIZE; y1++) {
            for (int x2 = 0; x2 < FieldModel.SIZE; x2++) {
                if (model.getPlayerCell(x2, y1) == 0) {
                    Hex.fillHex(x2, y1, true, new Color(80, 80, 80), g);
                    Hex.drawHex(x2, y1, new Color(0, 0, 0), true,  g);
                } else if (model.getPlayerCell(x2, y1) == 1) {
                    Hex.fillHex(x2, y1, true, new Color(58, 41, 255),  g);
                    Hex.drawHex(x2, y1, new Color(0, 0, 0), true,  g);
                } else if (model.getPlayerCell(x2, y1) == 2) {
                    Hex.fillHex(x2, y1, true, new Color(247, 231, 20), g);
                    Hex.drawHex(x2, y1, new Color(0, 0, 0), true, g);
                }
            }
        }
    }
}


