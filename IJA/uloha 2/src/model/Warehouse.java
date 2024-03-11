package model;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.util.*;
import com.fasterxml.jackson.databind.*;

/**
 * Warehouse class representing warehouse
 * @author Filip Sapák (xsapak05)
 * @author Matušík Adrián (xmatus35)
 */
public class Warehouse {

    private int[][] layout;
    private int rows = 11;
    private int cols = 11;
    private List<Shelf> shelves = new ArrayList<>();
    private List<Order> orders = new ArrayList<>();
    private List<Cart> carts = new ArrayList<>();
    public static final int MAX_CARTS = 5;

    /**
     * Add Shelf to Warehouse
     * @param shelf Shelf to Add
     * */
    public void addShelf(Shelf shelf)
    {
        this.shelves.add(shelf);
    }

    /**
     * Get Shelves from Warehouse
     * @return Shelves in Warehouse
     * */
    public List<Shelf> getShelves() {
        return shelves;
    }

    /**
     * Fill Warehouse with Shelves and Items
     * @param filename Name of input file
     * */
    public void seedShelves(String filename) throws Exception
    {

        byte[] jsonData = Files.readAllBytes(Paths.get(filename));
        ObjectMapper objectMapper = new ObjectMapper();
        JsonNode rootNode = objectMapper.readTree(jsonData);
        JsonNode shelves = rootNode.path("shelves");
        JsonNode items = rootNode.path("items");
        Iterator<JsonNode> elementsItems = items.elements();
        Iterator<JsonNode> elementsShelves = shelves.elements();

        while(elementsShelves.hasNext()){

            Position position = new Position(0,0);
            JsonNode elementShelf = elementsShelves.next();
            JsonNode posx = elementShelf.path("posx");
            JsonNode posy = elementShelf.path("posy");
            JsonNode id = elementShelf.path("id");
            position.setPosy(posy.asInt());
            position.setPosx(posx.asInt());
            Shelf tmpShelf = new Shelf(position,id.asInt());
            addShelf(tmpShelf);

        }

        Iterator<Shelf> shelfIterator = this.shelves.iterator();
        while(elementsItems.hasNext()){

            Shelf shelf = shelfIterator.next();
            JsonNode elementItem = elementsItems.next();
            JsonNode name = elementItem.path("name");
            JsonNode quantity = elementItem.path("quantity");
            JsonNode weight = elementItem.path("weight");
            Item tmpItem = new Item(name.toString(),quantity.asInt(),weight.asDouble());
            shelf.addItem(tmpItem);

            if (!shelfIterator.hasNext()) {
                shelfIterator = this.shelves.iterator();
            }

        }
    }

    /**
     * Fill Orders with Items
     * @param filename Name of input file
     * */

    public void fillOrders(String filename) throws Exception
    {
        byte[] jsonData = Files.readAllBytes(Paths.get(filename));
        ObjectMapper objectMapper = new ObjectMapper();
        JsonNode rootNode = objectMapper.readTree(jsonData);
        JsonNode orders = rootNode.path("orders");
        Iterator<JsonNode> orderIterator = orders.elements();

        while(orderIterator.hasNext()){

            JsonNode order = orderIterator.next();
            Iterator<JsonNode> elementOrder = order.elements();

            while(elementOrder.hasNext()){

                JsonNode elementItem = elementOrder.next();
                Iterator<JsonNode> itemIterator = elementItem.elements();
                Order tmpOrder = new Order();

                while (itemIterator.hasNext()){

                    JsonNode item = itemIterator.next();
                    JsonNode name = item.path("name");
                    JsonNode quantity = item.path("quantity");
                    JsonNode weight = item.path("weight");
                    Item tmpItem = new Item(name.toString(),quantity.asInt(),weight.asDouble());
                    tmpOrder.addItem(tmpItem);

                }
                addOrder(tmpOrder);
            }
        }

    }

    /**
     * Get list of Orders to process
     * @return list of Orders to process
     * */
    public List<Order> getOrders() {
        return orders;
    }

    /**
     * Add Order to list of Orders
     * @param order Order to add
     * */
    public void addOrder(Order order) {
        this.orders.add(order);
    }

    /**
     * Remove Order from list of Orders
     * @param order Order to remove
     * */
    public void removeOrder(Order order) {
        this.orders.remove(order);
    }

    /**
     * Create carts
     *
     * */
    public void createCarts() {
        for (int i = 0; MAX_CARTS >= i; i++) {
            Cart cart = new Cart(i);
            addCart(cart);
        }
    }

    /**
     * Add cart to warehouse
     * @param cart Cart to add
     * */
    public void addCart(Cart cart) {
        this.carts.add(cart);
    }

    /**
     * Processes order
     * @param order Order to process
     * */
    public void processOrder(Order order) {

        // TODO pathfinding & path class, pre demonstraciu iba naplnenie vozika,vyhladanie regalov a nasledne odstranenie zbozia z regalov
        Iterator<Item> itemIterator = order.getItems().iterator();
        Iterator<Shelf> shelfIterator = this.shelves.iterator();

        while(itemIterator.hasNext()){
            Item item = itemIterator.next();
            // System.out.println(item.getName());
            while(shelfIterator.hasNext()){

                Shelf shelf = shelfIterator.next();

                if(shelf.containsItemName(item.getName())){

                    shelf.removeItem(item,item.getQuantity());
                }
            }
            shelfIterator = this.shelves.iterator();
        }
    }

}
