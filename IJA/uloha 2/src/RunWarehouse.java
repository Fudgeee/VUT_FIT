import model.Item;
import model.Order;
import model.Shelf;
import model.Warehouse;

import java.util.List;
/**
 * Demonstration class
 * @author Filip Sapák (xsapak05)
 * @author Matušík Adrián (xmatus35)
 */
public class RunWarehouse {

    /**
     * Run warehouse with given input
     * @param args input arguments
     * */
    public static void main(String[] args) {

        Warehouse warehouse1 = new Warehouse();

        try {

            warehouse1.seedShelves("data/warehouse.json");
            warehouse1.fillOrders("data/warehouse.json");
            warehouse1.createCarts();
            List<Shelf> shelves = warehouse1.getShelves();
            List<Order> orders = warehouse1.getOrders();
            warehouse1.processOrder(orders.get(0));
            int i = 0;
            int j = 0;
            /*System.out.println("SHELVES - CONTENT");

            for (Shelf shelf:shelves) {

                for (Item item:shelf.getItems()) {
                    System.out.println(item.getName());
                    System.out.println(item.getQuantity());
                    System.out.println(item.getWeight());
                    i++;
                }
                System.out.println("-------------------------");
            }
            System.out.println("Items in total:" + i);*/

            System.out.println("ORDERS - CONTENT");
	    System.out.println("-------------------------");
            for (Order order:orders) {

                for (Item item:order.getItems()) {
                    System.out.println(item.getName());
                    System.out.println(item.getQuantity());
                    System.out.println(item.getWeight());
                    j++;
                }
                System.out.println("Total order weight:" + order.getTotal_weight());
                System.out.println("-------------------------");

            }


        } catch (Exception e) {
            e.printStackTrace();
            System.out.println("Failed to load the file");
        }

    }
}
