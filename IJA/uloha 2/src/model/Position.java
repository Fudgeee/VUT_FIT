package model;
/**
 * Position class representing coordinates
 * @author Filip Sapák (xsapak05)
 * @author Matušík Adrián (xmatus35)
 */
public class Position {

    private int posx;
    private int posy;

    /**
     * Constructor Position
     *
     * @param posx X position
     * @param posy Y position
     * */
    public Position(int posx, int posy){
        this.posx = posx;
        this.posy = posy;
    }

    /**
     * Get X position
     * @return X position
     * */
    public int getPosx() {
        return posx;
    }

    /**
     * Set X position
     * @param posx X position
     * */
    public void setPosx(int posx) {
        this.posx = posx;
    }

    /**
     * Get Y position
     * @return Y position
     * */
    public int getPosy() {
        return posy;
    }

    /**
     * Set Y position
     * @param posy Y position
     * */
    public void setPosy(int posy) {
        this.posy = posy;
    }

}
