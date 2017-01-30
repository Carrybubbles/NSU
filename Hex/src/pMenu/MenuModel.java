package pMenu;

import java.util.Observable;

public class MenuModel extends Observable{
    public enum Modes{PVP,PVE;};
    private Modes modes;
    private boolean start = false;

    public MenuModel(){
        modes = modes.PVE;
    }

    public void setMode(Modes mode){
        modes = mode;
    }

    public void StartGame(){
        this.start = true;
        setChanged();
        notifyObservers(modes);
    }

    public void reset(){
        modes = null;
        start = false;
    }

    public void quitGame(){
        this.start = false;
        setChanged();
        notifyObservers(false);
    }

    public Modes getModes(){
        return modes;
    }

    public boolean getGameStatus(){
        return start;
    }
}
