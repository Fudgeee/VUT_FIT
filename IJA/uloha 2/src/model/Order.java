package model;
import java.util.*;
/**
 * Order class representing orders
 * @author Filip Sapák (xsapak05)
 * @author Matušík Adrián (xmatus35)
 */
public class Order {

    private List<Item> items;
    private int flag;
    private double total_weight;

    /**
     * Constructor Order
     *
     * */
    public Order() {
        this.items = new ArrayList<>();
        this.flag = 0;
        this.total_weight = 0;
    }

    /**
     * Get Items in Order
     * @return Items in Order
     * */
    public List<Item> getItems() {
        return items;
    }

    /**
     * Set Items in Order
     * @param items Items in Order
     * */
    public void setItems(List<Item> items) {
        this.items = items;
    }

    /**
     * Get Order flag(state)
     * @return Order state
     * */
    public int getFlag() {
        return flag;
    }

    /**
     * Add Item to Order
     * @param item Item to Add
     * */
    public void addItem(Item item) {
        this.items.add(item);
    }

    /**
     * Set Order flag
     * @param flag Order state
     * */
    public void setFlag(int flag) {
        this.flag = flag;
    }

    /**
     * Get total weight of an Order
     * @return Total weight of an Order
     * */
    public double getTotal_weight() {

        Iterator<Item> itemIterator = this.items.iterator();

        while(itemIterator.hasNext()){
            Item item = itemIterator.next();
            this.total_weight += item.getWeight()*item.getQuantity();
        }
        return this.total_weight;
    }
}
