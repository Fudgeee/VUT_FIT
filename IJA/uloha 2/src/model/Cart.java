package model;
import java.util.ArrayList;
import java.util.List;

/**
 * Cart class representing carts
 * @author Filip Sapák (xsapak05)
 * @author Matušík Adrián (xmatus35)
 */
public class Cart {

    /**Global: CART_CAPACITY carrying capacity of Cart*/
    public static final double CART_CAPACITY = 25;
    private Position position;
    private List<Item> items;
    private int id;
    private boolean flag;

    /**
     * Constructor Cart
     *
     * @param id ID of Cart
     * */
    public Cart(int id) {

        this.position = new Position(0,0);
        this.items = new ArrayList<>();
        this.id = id;
        this.flag = false;

    }

    /**
     * Get Position of Cart
     * @return Position of Cart
     * */
    public Position getPosition() {
        return position;
    }

    /**
     * Set Position of Cart
     * @param position Position of Cart
     * */
    public void setPosition(Position position) {
        this.position = position;
    }

    /**
     * Get Items in Cart
     * @return Items in Cart
     * */
    public List<Item> getItems() {
        return items;
    }

    /**
     * Set Items in Cart
     * @param items Items in Cart
     * */
    public void setItems(List<Item> items) {
        this.items = items;
    }

    /**
     * Add Item to Cart
     * @param item Item to add
     * */
    public void addItem(Item item) {
        this.items.add(item);
    }

    /**
     * Get ID of Cart
     * @return ID of Cart
     * */
    public int getId() {
        return id;
    }

    /**
     * Get Flag of Cart
     * @return Accessibility of Cart
     * */
    public boolean getFlag() {
        return flag;
    }

    /**
     * Set Flag of Cart
     * @param flag Accessibility of Cart
     * */
    public void setFlag(boolean flag) {
        this.flag = flag;
    }
}
