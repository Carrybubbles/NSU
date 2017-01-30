package pMenu;

/**
 * Created by artem on 19.03.16.
 */
public class GameController {
    private GameModel menu;
    private GameView Drawmenu;
    public GameController(GameView drawMenu, GameModel menu){
        this.Drawmenu = drawMenu;
        this.menu = menu;
    }

    public void setMode(){
        Drawmenu.getMenu().getPVE().addActionListener(e -> {
            if(Drawmenu.getMenu().getPVE().isEnabled()){
                menu.setMode(GameModel.Modes.PVE);
                System.out.print("PVE");

            }
        });
        Drawmenu.getMenu().getPVP().addActionListener(e -> {
            if(Drawmenu.getMenu().getPVP().isEnabled()){
                menu.setMode(GameModel.Modes.PVP);
                System.out.print("PVP");

            }
        });
    }
}
