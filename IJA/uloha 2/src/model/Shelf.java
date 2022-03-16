package model;
import java.util.*;
/**
 * Shelf class representing shelves
 * @author Filip Sapák (xsapak05)
 * @author Matušík Adrián (xmatus35)
 */
public class Shelf {

    private List<Item> items;
    private int id;
    private Position position;

    /**
     * Constructor Shelf
     *
     * @param position Position of Shelf
     * @param id ID of Shelf
     * */
    public Shelf(Position position, int id){
        this.items = new ArrayList<>();
        this.id = id;
        this.position = position;
    }

    /**
     * Add Item to Shelf
     * @param item Item to Add
     * */
    public void addItem(Item item){
        this.items.add(item);
    }

    /**
     * Remove Item from Shelf
     * @param item Item to remove
     * @param quantity Amount of Items to remove
     * */
    public void removeItem(Item item,int quantity){

            Iterator<Item> itemIterator = this.items.iterator();
            while(itemIterator.hasNext()){
                Item tmpItem = itemIterator.next();
                if(tmpItem.getName().equals(item.getName())){
                    tmpItem.decreaseQuantity(quantity);
                }
            }
    }

    /**
     * Get Items from Shelf
     * @return Items in Shelf
     * */
    public List<Item> getItems() {
        return items;
    }

    /**
     * Get ID of Shelf
     * @return ID of Shelf
     * */
    public int getId() {
        return id;
    }

    /**
     * Set Items in Shelf
     * @param items Items in Shelf
     * */
    public void setItems(List<Item> items) {
        this.items = items;
    }

    /**
     * Set ID of Shelf
     * @param id ID of Shelf
     * */
    public void setId(int id) {
        this.id = id;
    }

    /**
     * Get Position of Shelf
     * @return Position of Shelf
     * */
    public Position getPosition() {
        return position;
    }

    /**
     * Set Position of Shelf
     * @param position Position of Shelf
     * */
    public void setPosition(Position position) {
        this.position = position;
    }

    /**
     * Check if shelf contains Item with given name
     * @param name Item name
     * @return True if Shelf contains Item with given name,else returns False
     * */
    public boolean containsItemName(String name){
        return this.items.stream().anyMatch(o -> o.getName().equals(name));
    }
}
