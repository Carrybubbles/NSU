package HexagonalMap;

import java.awt.*;


public class Hexagon {
    /**
     * length of hex side
     */
    private int s = 0;
    /**
     * hieght of hexagon
     */
    private int h = 0;

    private int BORDERS = 100;
    private int r = 0;
    private int t = 0;

    public Hexagon(int length, int height){
        this.s = length;
        this.r = (int) (length * Math.cos(Math.PI / 6));
        this.h = 2 * r ;
        this.t = (length / 2);


        h = height;
        r = h/2;
        s = (int) (h / Math.sqrt(3));
        t = (int) (r / Math.sqrt(3));

    }

    public Polygon convertToPolygon(int x0, int y0){
        int x = x0 + BORDERS;
        int y = y0 + BORDERS;
        int[] vX = new int[] {x, x+s, x+t+s, x+s, x, x-t};
        int[] vY = new int[] {y, y, y+r ,y+2*r, y+2*r, y+r};
        return new Polygon(vX, vY, 6);
    }

    public void drawHex(int x0, int y0, Color color, boolean flag, Graphics2D g){
        int x = x0 * (s + t);
        int y = y0 * h + (x0%2) * h / 2 ;
        if(flag) {
            Polygon poly = convertToPolygon(x, y);
            g.setColor(color);
            g.drawPolygon(poly);
        }
    }

    public void fillHex(int x0, int y0, boolean flag,Color color, Graphics2D g){
        int x = x0 * (s + t);
        int y = y0 * h + (x0%2) * h / 2 ;
        if(flag) {
            g.setColor(color);
            g.fillPolygon(convertToPolygon(x,y));
        }

    }

    public Point getHexCoordinate(int x , int y){
        Point point = new Point(-1,-1);
        x -= BORDERS;
        y -= BORDERS;
        x += t;
        int xc = (int)( x / (s + t));
        int yc = (int) ((y - ((xc % 2) * r)) / h);
        int dx = x - xc*(s + t);
        int dy = y - yc*h;
        if( y - (xc%2) * r < 0)
            return point;
        if(xc%2 == 0){
            if(dy > r){
                if(dx * r / t < dy - r){
                    xc--;
                }
            }
            if(dy < r){
                if((t - dx) * r / t > dy){
                    xc--;
                    yc--;
                }
            }
        }else{
            if(dy > h){
                if(dx *r /t < dy - h){
                    xc--;
                    yc++;
                }
            }
            if(dy < h){
                if((t - dx) * r /t > dy - r){
                    xc--;
                }
            }
        }
        point.x = xc;
        point.y = yc;
        return point;
    }

}
