package model;
/**
 * Item class representing items
 * @author Filip Sapák (xsapak05)
 * @author Matušík Adrián (xmatus35)
 */
public class Item {

    private String name;
    private int quantity;
    private double weight;

    /**
     * Constructor Item
     *
     * @param name Item name
     * @param quantity Amount of items
     * @param weight Weight of single item
     * */
    public Item(String name,int quantity,double weight){
        this.name = name;
        this.quantity = quantity;
        this.weight = weight;
    }

    /**
     * Get quantity of an Item
     * @return Quantity of an Item
     * */
    public int getQuantity() {
        return quantity;
    }

    /**
     * Set quantity of an Item
     * @param quantity  Quantity of an Item
     * */
    public void setQuantity(int quantity) {
        this.quantity = quantity;
    }

    /**
     * Decrease quantity of an Item
     * @param quantity  Quantity of an Item
     * */
    public void decreaseQuantity(int quantity) {
        this.quantity = this.quantity - quantity;
    }

    /**
     * Get weight of an Item
     * @return Weight of an Item
     * */
    public double getWeight() {
        return weight;
    }

    /**
     * Set weight of an Item
     * @param weight Weight of an Item
     * */
    public void setWeight(double weight) {
        this.weight = weight;
    }

    /**
     * Get name of an Item
     * @return Name of an Item
     * */
    public String getName() {
        return name;
    }

    /**
     * Set name of an Item
     * @param name Name of an Item
     * */
    public void setName(String name) {
        this.name = name;
    }
}